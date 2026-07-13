package models

type TaskStatus int

const (
	Todo TaskStatus = iota
	Progress
	Done
)

func (s TaskStatus) StringState() string {
	switch s {
	case Todo:
		return "Todo"
	case Progress:
		return "Progress"
	case Done:
		return "Done"
	default:
		return "Unknown"
	}
}
