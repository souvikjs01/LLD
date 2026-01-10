package main

import (
	"fmt"
)

// bad example
/*
type UserService struct {}

func (u *UserService) CreateUser(name string) error {
	// validate
	if name == "" {
		return fmt.Errorf("invalid name")
	}

	// save to DB
	fmt.Println("Saving user to database")

	// log
	fmt.Println("User created")

	return nil
}
*/

type User struct {
	Name string
}

type ValidateUser struct{}

func (v *ValidateUser) Validate(user User) error {
	if user.Name == "" {
		return fmt.Errorf("ErrUserName")
	}
	return nil
}

type UserRepo struct{}

func (r *UserRepo) SaveUser(u User) error {
	fmt.Println("Saveed user details to database")
	return nil
}

type Logger struct{}

func (l *Logger) Info(msg string) {
	fmt.Println(msg)
}

type UserService struct {
	validator *ValidateUser
	repo      *UserRepo
	log       *Logger
}

func (u *UserService) CreateUser(user User) error {
	if err := u.validator.Validate(user); err != nil {
		return err
	}

	if err := u.repo.SaveUser(user); err != nil {
		return nil
	}

	u.log.Info("User created successfully")

	return nil
}

func main() {
	validator := &ValidateUser{}
	repo := &UserRepo{}
	logg := &Logger{}

	userSrv := &UserService{
		validator: validator,
		repo:      repo,
		log:       logg,
	}

	usr := &User{Name: "Alex"}

	if err := userSrv.CreateUser(*usr); err != nil {
		fmt.Println(err)
		return
	}

	fmt.Println("Done")

}
