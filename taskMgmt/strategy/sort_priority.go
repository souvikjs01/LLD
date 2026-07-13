package strategy

import (
	"fmt"
	"sort"
	"tms/models"
)

type SortByPriority struct{}

func (s *SortByPriority) Sort(tasks []*models.Task) {
	fmt.Println("Sorting task by its priority")
	sort.Slice(tasks, func(i, j int) bool {
		return tasks[i].Priority > tasks[j].Priority
	})
}
