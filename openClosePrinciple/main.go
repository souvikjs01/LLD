package main

import (
	"fmt"
)

// struct/class or entities should be open for extention and close for modification

// bad example
/*
type Payment struct{}

func (p *Payment) Pay(method string) {
	switch method {
	case "card":
		fmt.Println("Paying with card")
	case "upi":
		fmt.Println("Paying with upi")
	case "paypal":
		fmt.Println("Paying with paypal")
	}

	// but if we support another payment way we need to modify this piece of code
	// which disobey the rule of open close principle
}

func main() {
	payment := &Payment{}
	payment.Pay("upi")
}

*/

// OCP :

type PaymentGetway interface {
	Pay(amount float64)
}

type UpiPayment struct{}

func (u *UpiPayment) Pay(amount float64) {
	fmt.Printf("Paying %.2f through upi\n", amount)
}

type CardPayment struct{}

func (u *CardPayment) Pay(amount float64) {
	fmt.Printf("Paying %.2f through Card\n", amount)
}

type PaypalPayment struct{}

func (u *PaypalPayment) Pay(amount float64) {
	fmt.Printf("Paying %.2f through Paypal\n", amount)
}

type PaymentService struct {
	PaymentGetway
}

func (p *PaymentService) Process(amount float64) {
	p.PaymentGetway.Pay(amount)
}

func main() {
	card := &CardPayment{}
	payment := &PaymentService{PaymentGetway: card}
	payment.PaymentGetway.Pay(99.99)

	upi := &UpiPayment{}
	payment2 := &PaymentService{PaymentGetway: upi}
	payment2.PaymentGetway.Pay(199.99)
}
