package manager

import (
	"fmt"
	"sync"
	"time"
	"tms/models"
	"tms/strategy"
)

type TaskManager struct {
	mu sync.RWMutex

	tasks map[string]*models.Task
	users map[string]*models.User
}

// singleton pattern

var (
	instance *TaskManager
	once     sync.Once
)

func GetInstance() *TaskManager {
	once.Do(func() {
		instance = &TaskManager{
			tasks: make(map[string]*models.Task),
			users: make(map[string]*models.User),
		} // makes sure only one go routine has access the code
	})

	return instance
}

func (tm *TaskManager) CreateUser(id, name, email string) *models.User {
	tm.mu.Lock()
	defer tm.mu.Unlock()

	fmt.Println("creating a new user")

	user := models.NewUser(id, name, email)

	tm.users[id] = user

	return user
}

func (tm *TaskManager) CreateTask(id, title, description string, dueDate time.Time, priority models.TaskPriority, createdBy *models.User) *models.Task {
	tm.mu.Lock()
	defer tm.mu.Unlock()

	fmt.Println("creating a new task")

	task := models.NewTask(id, title, description, dueDate, priority, createdBy)

	tm.tasks[id] = task

	return task
}

func (tm *TaskManager) getTask(id string) (*models.Task, error) {
	task, ok := tm.tasks[id]
	if !ok {
		return nil, fmt.Errorf("task not found")
	}
	return task, nil
}

func (tm *TaskManager) GetTask(id string) (*models.Task, error) {
	tm.mu.RLock()
	defer tm.mu.RUnlock()

	return tm.getTask(id)
}

func (tm *TaskManager) findUser(id string) (*models.User, error) {
	user, ok := tm.users[id]
	if !ok {
		return nil, fmt.Errorf("user not found")
	}
	return user, nil
}

func (tm *TaskManager) FindUser(id string) (*models.User, error) {
	tm.mu.RLock()
	defer tm.mu.RUnlock()

	return tm.findUser(id)
}

// assign task
func (tm *TaskManager) AssignTask(taskId, userId string) error {
	tm.mu.Lock()
	defer tm.mu.Unlock()

	task, err := tm.getTask(taskId)
	if err != nil {
		return err
	}

	user, err := tm.findUser(userId)
	if err != nil {
		return err
	}

	task.Assignee = user

	fmt.Printf("Task %s assigned to user %s\n", task.Id, user.Id)

	return nil
}

// sort task
func (tm *TaskManager) SortTask(sorter strategy.TaskSortStrategy) []*models.Task {
	tm.mu.RLock()
	defer tm.mu.RUnlock()

	tasks := make([]*models.Task, 0, len(tm.tasks))

	for _, task := range tm.tasks {
		tasks = append(tasks, task)
	}

	sorter.Sort(tasks)

	return tasks
}

// remove task
func (tm *TaskManager) RemoveTask(id string) error {
	tm.mu.Lock()
	defer tm.mu.Unlock()

	if _, err := tm.getTask(id); err != nil {
		return err
	}

	delete(tm.tasks, id)

	fmt.Println("removed task:", id)

	return nil
}

// add comment
func (tm *TaskManager) AddComment(taskId, commentId, content string, author *models.User) error {
	tm.mu.Lock()
	defer tm.mu.Unlock()

	task, err := tm.getTask(taskId)
	if err != nil {
		return err
	}

	if _, err := tm.findUser(author.Id); err != nil {
		return err
	}

	comment := models.NewComment(commentId, content, author)
	task.Comments = append(task.Comments, comment)

	fmt.Println("added comment by", author.Name)

	return nil
}

// add tag
func (tm *TaskManager) AddTag(taskId, tagName string) error {
	tm.mu.Lock()
	defer tm.mu.Unlock()

	task, err := tm.getTask(taskId)
	if err != nil {
		return err
	}

	task.Tags = append(task.Tags, models.NewTag(tagName))

	fmt.Println("added tag:", tagName)

	return nil
}

// get all tasks
func (tm *TaskManager) GetAllTasks() []*models.Task {
	tm.mu.RLock()
	defer tm.mu.RUnlock()

	result := make([]*models.Task, 0, len(tm.tasks))

	for _, task := range tm.tasks {
		result = append(result, task)
	}

	return result
}

// remove user
func (tm *TaskManager) RemoveUser(userId string) error {
	tm.mu.Lock()
	defer tm.mu.Unlock()

	if _, err := tm.findUser(userId); err != nil {
		return err
	}

	delete(tm.users, userId)

	fmt.Println("removed user:", userId)

	return nil
}

// you can create other methods according to the interview requirements
