package state

import (
	"fmt"
	"tms/models"
)

type DoneState struct{}

func (d *DoneState) StartProgress(t *models.Task) error {
	return fmt.Errorf("task is already completed, cannot start progress")
}

func (d *DoneState) CompleteTask(t *models.Task) error {
	return fmt.Errorf("task is already completed")
}

func (d *DoneState) ReopenTask(t *models.Task) error {
	fmt.Println("task is reopen now")
	t.Status = models.Todo
	return nil
}

func (d *DoneState) GetStatus() models.TaskStatus {
	return models.Done
}
