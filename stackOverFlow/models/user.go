package models

type User struct {
	Id         string
	Name       string
	Email      string
	Reputation int
}

func NewUser(id string, name string, email string) *User {
	return &User{
		Id:    id,
		Name:  name,
		Email: email,
	}
}

func (u *User) UpdateReputation(rep int) {
	u.Reputation += rep
}

func (u *User) GetUserName() string {
	return u.Name
}
