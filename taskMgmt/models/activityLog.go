package models

import "time"

type ActivityLog struct {
	Description string
	TimeStamp   time.Time
}

func NewActivityLog(description string) ActivityLog {
	return ActivityLog{
		Description: description,
		TimeStamp:   time.Now(),
	}
}
