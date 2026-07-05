package models

type VoteType int

const (
	Upvote VoteType = iota
	Downvote
)

type Vote struct {
	Voter       *User
	VoteingType VoteType
}
