package state

import (
	"fmt"
	"tms/models"
)

type TodoState struct{}

func (to *TodoState) StartProgress(t *models.Task) error {
	fmt.Println("Task is in Progress")
	t.Status = models.Progress
	return nil
}

func (to *TodoState) CompleteTask(t *models.Task) error {
	// cant complete a task in todo state
	return fmt.Errorf("task is in todo state, cannot complete")
}

func (to *TodoState) ReopenTask(t *models.Task) error {
	fmt.Println("Task is already open")
	return nil
}

func (to *TodoState) GetStatus() models.TaskStatus {
	return models.Todo
}
