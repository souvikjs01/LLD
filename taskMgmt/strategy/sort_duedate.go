package strategy

import (
	"fmt"
	"sort"
	"tms/models"
)

type SortByDuedate struct{} // empty

func (s *SortByDuedate) Sort(tasks []*models.Task) {
	fmt.Println("Sorting task by its due date")
	sort.Slice(tasks, func(i, j int) bool {
		return tasks[i].DueDate.Before(tasks[j].DueDate)
	})
}
