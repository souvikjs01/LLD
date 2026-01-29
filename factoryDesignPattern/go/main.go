package main

import "fmt"

type Shape interface {
	Draw() string
}

type Circle struct{}

func (c *Circle) Draw() string {
	return "Drawing circle"
}

type Rectangle struct{}

func (r *Rectangle) Draw() string {
	return "Drawing rectangle"
}

type Triangle struct{}

func (t *Triangle) Draw() string {
	return "Drawing triangle"
}

func ShapeFactory(sh string) Shape {
	switch sh {
	case "circle":
		return &Circle{}
	case "rectangle":
		return &Rectangle{}
	case "triangle":
		return &Triangle{}
	default:
		return nil
	}
}

func main() {
	input := "circle"
	shape := ShapeFactory(input)
	if shape != nil {
		fmt.Println(shape.Draw())
	} else {
		fmt.Println("no shape exist")
	}

	input2 := "rectangle"
	shape2 := ShapeFactory(input2)
	if shape2 != nil {
		fmt.Println(shape2.Draw())
	} else {
		fmt.Println("no shape exist")
	}

	input3 := "circle"
	shape3 := ShapeFactory(input3)
	if shape3 != nil {
		fmt.Println(shape3.Draw())
	} else {
		fmt.Println("no shape exist")
	}

	input4 := "temp"
	shape4 := ShapeFactory(input4)
	if shape4 != nil {
		fmt.Println(shape4.Draw())
	} else {
		fmt.Println("no shape exist")
	}

}
