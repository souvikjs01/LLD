package main

import (
	"fmt"
	"stackoverflow/models"
	"stackoverflow/service"
)

func main() {
	sof := service.NewStackOverFlow()

	// create user
	alice := sof.CreateUser("101", "Alice", "alice01@gmail.com")
	bob := sof.CreateUser("102", "Bob", "bob@gmail.com")

	// add tags
	golangTag := models.Tag{
		Id:   "1",
		Name: "multi thread",
	}

	q := models.NewQuestion("10", "what is golang", "explain in brief", alice, []models.Tag{golangTag})

	sof.CreateQuetion(q.Id, q.Title, q.Content, q.Author, q.Tags)

	// ans
	ans := models.NewAnswer("100", "golang is a programming language", alice, q)

	q.AddAnswer(ans)
	q.AddVote(bob, models.Upvote)

	fmt.Println("Question votes", q.GetVoteCounts())

	result := sof.SearchQueation("golang")

	for _, ques := range result {
		fmt.Println("Question Title:", ques.Title)
	}
}
