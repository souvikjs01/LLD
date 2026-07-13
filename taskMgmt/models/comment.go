package models

import "time"

type Comment struct {
	Id        string
	Content   string
	Author    *User
	CreatedAt time.Time
}

func NewComment(id, content string, user *User) *Comment {
	return &Comment{
		Id:        id,
		Content:   content,
		Author:    user,
		CreatedAt: time.Now(),
	}
}
