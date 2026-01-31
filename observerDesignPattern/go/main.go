package main

import "fmt"

type ISubscriber interface {
	Update()
}

type IChannel interface {
	Subscribe(subsriber ISubscriber)
	Unsubscribe(subsriber ISubscriber)
	NotifySubsribers()
}

type Channel struct {
	name        string
	latestVideo string
	subscribers []ISubscriber
}

func NewChannel(name string) *Channel {
	return &Channel{
		name: name,
	}
}

func (c *Channel) Subscribe(subsriber ISubscriber) {
	for _, sub := range c.subscribers {
		if sub == subsriber {
			return
		}
	}
	c.subscribers = append(c.subscribers, subsriber)
}

func (c *Channel) Unsubscribe(subscriber ISubscriber) {
	for i, sub := range c.subscribers {
		if sub == subscriber {
			c.subscribers = append(
				c.subscribers[:i],
				c.subscribers[i+1:]...,
			)
			return
		}
	}
}

func (c *Channel) NotifySubsribers() {
	for _, sub := range c.subscribers {
		sub.Update()
	}
}

func (c *Channel) UploadVideo(title string) {
	c.latestVideo = title
	fmt.Println("Uploaded video", title)
	c.NotifySubsribers()
}

func (c *Channel) GetVideoData() string {
	return "Checkout our new video " + c.latestVideo
}

type Subscriber struct {
	name    string
	channel *Channel
}

func NewSubscriber(name string, ch *Channel) *Subscriber {
	return &Subscriber{
		name:    name,
		channel: ch,
	}
}

func (s *Subscriber) Update() {
	fmt.Println("Hey", s.name, s.channel.GetVideoData())
}

func main() {
	channel := &Channel{name: "FreeCodeCamp"}

	sub1 := &Subscriber{name: "Tim", channel: channel}
	sub2 := &Subscriber{name: "Emily", channel: channel}

	// subscribe the channel
	channel.Subscribe(sub1)
	channel.Subscribe(sub2)

	// upload video
	channel.UploadVideo("DSA with GO")

	// let unsubscribe the channel
	channel.Unsubscribe(sub1)

	// upload another video
	channel.UploadVideo("Backend with GO")
}
