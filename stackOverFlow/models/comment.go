package models

import "time"

type Comment struct {
	Id        string
	Author    *User
	Content   string
	CreatedAt time.Time
}
