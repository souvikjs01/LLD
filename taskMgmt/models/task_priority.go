package models

type TaskPriority int

const (
	Low TaskPriority = iota
	Medium
	High
	Critical
)

func (p TaskPriority) String() string {
	switch p {
	case Low:
		return "LOW"
	case Medium:
		return "MEDIUM"
	case High:
		return "HIGH"
	case Critical:
		return "CRITICAL"
	default:
		return "UNKNOWN"
	}
}
