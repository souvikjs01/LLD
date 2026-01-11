package main

import "fmt"

// no high level struct or class should depend directly on low level struct or class

type greet interface {
	Greet() string
}

type English struct{}

func (e *English) Greet() string {
	return "Hello! welcome"
}

type Spanish struct{}

func (s *Spanish) Greet() string {
	return "Holla! de nada"
}

type Hindi struct{}

func (h *Hindi) Greet() string {
	return "Namaste! swagatam"
}

// abstruction
func Greeting(g greet) {
	fmt.Println(g.Greet())
}

func main() {
	g1 := &English{}
	Greeting(g1)

	g2 := &Spanish{}
	Greeting(g2)

	g3 := &Hindi{}
	Greeting(g3)
}
