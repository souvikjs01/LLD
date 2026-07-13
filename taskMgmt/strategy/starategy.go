package strategy

import "tms/models"

type TaskSortStrategy interface {
	Sort(tasks []*models.Task)
}
