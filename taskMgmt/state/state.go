package state

import "tms/models"

type TaskState interface {
	StartProgress(t *models.Task) error
	CompleteTask(t *models.Task) error
	ReopenTask(t *models.Task) error
	GetStatus() models.TaskStatus
}

func GetState(status models.TaskStatus) TaskState {
	switch status {
	case models.Todo:
		return &TodoState{}
	case models.Progress:
		return &ProgressState{}
	case models.Done:
		return &DoneState{}
	default:
		return &TodoState{}
	}
}
