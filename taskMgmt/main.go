package main

import (
	"fmt"
	"time"
	"tms/manager"
	"tms/models"
	"tms/strategy"
)

func main() {
	// create instance
	tm := manager.GetInstance()

	// create some user
	john := tm.CreateUser(
		"101",
		"john cena",
		"john@gmail.com",
	)

	randy := tm.CreateUser(
		"102",
		"randy ortan",
		"randy@gmail.com",
	)

	nicky := tm.CreateUser(
		"103",
		"nicky bella",
		"nicky@gmail.com",
	)

	// create some task
	task1 := tm.CreateTask(
		"201",
		"design database",
		"create the database initial schema",
		time.Now().Add(12*time.Hour),
		models.Critical,
		john,
	)

	task2 := tm.CreateTask(
		"202",
		"build REST API",
		"create initial basic apis",
		time.Now().Add(12*time.Hour),
		models.Medium,
		nicky,
	)

	task3 := tm.CreateTask(
		"203",
		"write tests",
		"create unit tests",
		time.Now().Add(12*time.Hour),
		models.High,
		randy,
	)
	fmt.Println("task added ", task1.Title)
	fmt.Println("task added ", task2.Title)
	fmt.Println("task added ", task3.Title)

	// add some tags
	tm.AddTag("201", "DB")
	tm.AddTag("202", "API")
	tm.AddTag("203", "test")

	// add comments
	tm.AddComment("201", "301", "initial db schema is completed", john)
	tm.AddComment("202", "302", "initial rest api is completed", nicky)
	tm.AddComment("203", "303", "initial test cases are completed", randy)

	// display all tasks
	for _, task := range tm.GetAllTasks() {
		fmt.Printf("%s | %s | %s | %s\n", task.Id, task.Title, task.Priority.String(), task.Status.StringState())
	}

	// sort task
	// sort by due date
	dueDateTasks := tm.SortTask(&strategy.SortByDuedate{})
	for _, task := range dueDateTasks {
		fmt.Printf("%s | %s | %s | %s | %s\n", task.Id, task.Title, task.Priority.String(), task.Status.StringState(), task.DueDate)
	}

	// sort by priority
	priorityTasks := tm.SortTask(&strategy.SortByPriority{})
	for _, task := range priorityTasks {
		fmt.Printf("%s | %s | %s | %s | %s\n", task.Id, task.Title, task.Priority.String(), task.Status.StringState(), task.DueDate)
	}
}
