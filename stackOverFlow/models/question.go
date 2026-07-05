package models

import (
	"fmt"
	"time"
)

type Question struct {
	Id        string
	Title     string
	Content   string
	Author    *User
	Answer    []*Answer
	Comments  []Comment
	Tags      []Tag
	Votes     []Vote
	CreatedAt time.Time
}

func NewQuestion(id, title, content string, author *User, tags []Tag) *Question {
	return &Question{
		Id:        id,
		Title:     title,
		Content:   content,
		Author:    author,
		Tags:      tags,
		CreatedAt: time.Now(),
	}
}

func (q *Question) AddComment(c Comment) {
	fmt.Println("Adding comment to question:", q.Id)
	q.Comments = append(q.Comments, c)
}

func (q *Question) AddVote(user *User, voteType VoteType) {
	q.Votes = append(q.Votes, Vote{
		Voter:       user,
		VoteingType: voteType,
	})
}

func (q *Question) AddAnswer(a *Answer) {
	fmt.Println("adding answer...")
	q.Answer = append(q.Answer, a)
}

func (q *Question) GetComments() []Comment {
	return q.Comments
}

func (q *Question) GetVoteCounts() int {
	count := 0

	for _, vote := range q.Votes {
		if vote.VoteingType == Upvote {
			count++
		} else {
			count--
		}
	}

	return count
}
