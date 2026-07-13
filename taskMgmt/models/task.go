package models

import "time"

type Task struct {
	Id          string
	Title       string
	Description string
	DueDate     time.Time
	Priority    TaskPriority
	Status      TaskStatus
	CreatedBy   *User
	Assignee    *User

	SubTasks []*Task

	Comments     []*Comment
	ActivityLogs []ActivityLog
	Tags         []*Tag
}

func NewTask(id, title, description string, dueDate time.Time, priority TaskPriority, createdBy *User) *Task {
	return &Task{
		Id:           id,
		Title:        title,
		Description:  description,
		DueDate:      dueDate,
		Priority:     priority,
		Status:       Todo,
		CreatedBy:    createdBy,
		SubTasks:     []*Task{},
		Comments:     []*Comment{},
		ActivityLogs: []ActivityLog{},
		Tags:         []*Tag{},
	}
}
