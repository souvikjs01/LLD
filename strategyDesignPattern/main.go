package main

import (
	"fmt"

	"github.com/souvikjs01/LLD/strategyDesignPattern/example"
)

type PaymentStrategy interface {
	Pay(amount float64) error
}

type CreditCardPayment struct {
	CardNumb string
}

func (c *CreditCardPayment) Pay(amount float64) error {
	fmt.Printf("Paid %.2f through credit card with num %s\n", amount, c.CardNumb)
	return nil
}

type UpiPayment struct {
	UpiID string
}

func (u *UpiPayment) Pay(amount float64) error {
	fmt.Printf("Paid %.2f through UPI with ID %s\n", amount, u.UpiID)
	return nil
}

type PaypalPayment struct {
	EmailId string
}

func (p *PaypalPayment) Pay(amount float64) error {
	fmt.Printf("Paid %.2f through Paypal with email %s\n", amount, p.EmailId)
	return nil
}

type PaymentService struct {
	PaymentStrategy
}

func (p *PaymentService) SetStrategy(strategy PaymentStrategy) {
	p.PaymentStrategy = strategy
}

func (p *PaymentService) Pay(amount float64) error {
	if p.PaymentStrategy == nil {
		return fmt.Errorf("payment strategy is not set up")
	}
	return p.PaymentStrategy.Pay(amount)
}

func main() {
	payment := &PaymentService{}

	payment.SetStrategy(&CreditCardPayment{CardNumb: "8764 3667 0983 7646"})
	payment.Pay(300)

	payment.SetStrategy(&UpiPayment{UpiID: "1234785"})
	payment.Pay(899)

	payment.SetStrategy(&PaypalPayment{"svk@gmail.com"})
	payment.Pay(999)

	fmt.Println("---------------Second Example-------------")

	// db := &example.DBService{}

	// db.SetDatabase(&example.MongoDB{MongoUri: "mongo uri-hhdkfhf"})
	// db.Connect()

	// db.SetDatabase(&example.PostgresDB{PgUri: "postgres uri-dhjsahgdgh"})
	// db.Connect()

	// db.SetDatabase(&example.Redis{RedisUri: "redis uri-dhdhfdgcvdgfhghd"})
	// db.Connect()

	mgConn := &example.MongoDB{}
	conn1 := example.DBService{DBConnection: mgConn}
	conn1.Connect()

	pgConn := &example.PostgresDB{}
	conn2 := example.DBService{DBConnection: pgConn}
	conn2.Connect()

	rdsConn := &example.Redis{}
	conn3 := example.DBService{DBConnection: rdsConn}
	conn3.Connect()
}
