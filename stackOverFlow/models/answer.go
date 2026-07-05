package models

import "time"

type Answer struct {
	Id        string
	Content   string
	Author    *User
	Ques      *Question
	Comments  []Comment
	Votes     []Vote
	CreatedAt time.Time
}

func NewAnswer(id, content string, author *User, ques *Question) *Answer {
	return &Answer{
		Id:        id,
		Content:   content,
		Author:    author,
		Ques:      ques,
		CreatedAt: time.Now(),
	}
}

func (a *Answer) AddComment(c Comment) {
	a.Comments = append(a.Comments, c)
}

func (a *Answer) AddVote(user *User, voteType VoteType) {
	a.Votes = append(a.Votes, Vote{
		Voter:       user,
		VoteingType: voteType,
	})
}

func (a *Answer) GetComments() []Comment {
	return a.Comments
}

func (a *Answer) GetVoteCounts() int {
	count := 0

	for _, vote := range a.Votes {
		if vote.VoteingType == Upvote {
			count++
		} else {
			count--
		}
	}

	return count
}
