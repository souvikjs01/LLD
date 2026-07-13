package state

import (
	"fmt"
	"tms/models"
)

type ProgressState struct{}

func (p *ProgressState) StartProgress(t *models.Task) error {
	return fmt.Errorf("task is already in progress")
}

func (p *ProgressState) CompleteTask(t *models.Task) error {
	fmt.Println("Task is completed")
	t.Status = models.Done
	return nil
}

func (p *ProgressState) ReopenTask(t *models.Task) error {
	fmt.Println("Task is reopen now")
	t.Status = models.Todo
	return nil
}

func (p *ProgressState) GetStatus() models.TaskStatus {
	return models.Progress
}
