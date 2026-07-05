package service

import (
	"stackoverflow/models"
	"strings"
	"sync"
)

type StackOverFlow struct {
	mu    sync.RWMutex
	Users map[string]*models.User
	Ques  map[string]*models.Question
	Tags  map[string]*models.Tag
}

func NewStackOverFlow() *StackOverFlow {
	return &StackOverFlow{
		Users: make(map[string]*models.User),
		Ques:  make(map[string]*models.Question),
		Tags:  make(map[string]*models.Tag),
	}
}

func (s *StackOverFlow) CreateUser(id, name, email string) *models.User {
	s.mu.Lock()
	defer s.mu.Unlock()

	user := models.User{
		Id:    id,
		Name:  name,
		Email: email,
	}

	s.Users[id] = &user

	return &user
}

func (s *StackOverFlow) CreateQuetion(id, title, content string, author *models.User, tags []models.Tag) *models.Question {
	s.mu.Lock()
	defer s.mu.Unlock()

	question := models.NewQuestion(id, title, content, author, tags)

	s.Ques[id] = question

	return question
}

func (s *StackOverFlow) SearchQueation(key string) []*models.Question {
	s.mu.Lock()
	defer s.mu.Unlock()

	var result []*models.Question

	for _, ques := range s.Ques {
		if strings.Contains(strings.ToLower(ques.Title), strings.ToLower(key)) {
			result = append(result, ques)
		}
	}
	return result
}

func (s *StackOverFlow) SearchByTag(tag string) []*models.Question {
	s.mu.Lock()
	defer s.mu.Unlock()

	result := []*models.Question{}

	for _, ques := range s.Ques {
		for _, t := range ques.Tags {
			if t.Name == tag {
				result = append(result, ques)
			}
		}
	}

	return result
}

func (s *StackOverFlow) QuestionByUser(userId string) []*models.Question {
	s.mu.Lock()
	defer s.mu.Unlock()

	result := []*models.Question{}

	for _, ques := range s.Ques {
		if ques.Author.Id == userId {
			result = append(result, ques)
		}
	}

	return result
}
