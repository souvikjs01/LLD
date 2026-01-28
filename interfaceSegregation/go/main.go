package main

import (
	"fmt"
	"math"
)

// bad example
/*
type shape interface {
	area() float64
	volume() float64
}

func areaSum(sh ...shape) float64 {
	var sum float64
	for _, s := range sh {
		sum += s.area()
	}
	return sum
}

func areaVolumeSum(sh ...shape) float64 {
	var sum float64
	for _, s := range sh {
		sum += s.area() + s.volume()
	}
	return sum
}

type square struct {
	len float64
}

func (s *square) area() float64 {
	return s.len * s.len
}

func (s *square) volume() float64 {
	// since square has not volume
	return 0
}

type cube struct {
	len float64
}

func (c *cube) area() float64 {
	return 6 * c.len * c.len
}

func (c *cube) volume() float64 {
	return c.len * c.len * c.len
}

func main() {
	s := &square{len: 4}
	c := &cube{len: 5}

	fmt.Println(areaSum(s, c))
	fmt.Println(areaVolumeSum(s, c))
}
*/

type shape interface {
	area() float64
}

type object interface {
	shape
	volume() float64
}

func areaSum(sh ...shape) float64 {
	var sum float64
	for _, s := range sh {
		sum += s.area()
	}
	return sum
}

func areaVolumeSum(sh ...object) float64 {
	var sum float64
	for _, s := range sh {
		sum += s.area() + s.volume()
	}
	return sum
}

type square struct {
	len float64
}

func (s *square) area() float64 {
	return s.len * s.len
}

type cube struct {
	len float64
}

func (c *cube) area() float64 {
	return 6 * c.len * c.len
}

func (c *cube) volume() float64 {
	return c.len * c.len * c.len
}

type sphere struct {
	rad float64
}

func (s *sphere) area() float64 {
	return 4 * math.Phi * s.rad * s.rad
}

func (s *sphere) volume() float64 {
	return (4 / 3) * math.Phi * s.rad * s.rad * s.rad
}

func main() {
	s := &square{len: 4}
	c := &cube{len: 5}
	sp := &sphere{rad: 7}

	fmt.Println(areaSum(s, c, sp))
	fmt.Println(areaVolumeSum(c, sp))
}
