package main

import (
	"fmt"
	"sync"
)

type Sigleton struct{}

var (
	instance *Sigleton
	once     sync.Once
)

func GetSingletonInstance() *Sigleton {
	once.Do(func() {
		if instance == nil {
			instance = &Sigleton{}
		}
	})
	return instance
}

func main() {
	s1 := GetSingletonInstance()
	s2 := GetSingletonInstance()

	fmt.Println(s1 == s2)
}
