#include<iostream>

using namespace std;

// interface
class PaymentStrategy{
public:
    virtual void pay(double amount) = 0;
    virtual ~PaymentStrategy() {
        cout << "Payment strategy destroyed" << endl;
    }
};

class CreditCardPayment : public PaymentStrategy {
public:
    void pay(double amount) override {
        cout << "Paying amount of Rs. " << amount << " using Credit card" << endl; 
    }

    ~CreditCardPayment() override {
        cout << "Creditcard payment destroyed" << endl;
    }
};

class UPIPayment : public PaymentStrategy {
public:
    void pay(double amount) override {
        cout << "Paying amount of Rs. " << amount << " using UPI" << endl; 
    }

    ~UPIPayment() override {
        cout << "UPI payment destroyed" << endl;
    }
};

class PayPalPayment : public PaymentStrategy {
public:
    void pay(double amount) override {
        cout << "Paying amount of Rs. " << amount << " using PayPal" << endl; 
    }

    ~PayPalPayment() override {
        cout << "PayPal payment destroyed" << endl;
    }
};

class PaymentContext {
private:
    PaymentStrategy* strategy;
public:
    PaymentContext(PaymentStrategy* strategy) {
        this->strategy = strategy;
    }
    void setStrategy(PaymentStrategy* obj) {
        if(strategy == obj) {
            return;
        }

        delete strategy;
        strategy = obj;
    }

    void executePayment(double amount) {
        if(strategy != nullptr) {
            strategy->pay(amount);
        }
    }
    ~PaymentContext() {
        delete strategy;
        cout << "PaymentContext destroyed" << endl;
    }
};

int main() {
    PaymentStrategy* credit = new CreditCardPayment();
    PaymentStrategy* upi = new UPIPayment();

    PaymentContext* paymentCtx = new PaymentContext(credit);
    paymentCtx->executePayment(199.99);
    
    paymentCtx->setStrategy(upi);
    paymentCtx->executePayment(299.99);
    
    delete paymentCtx;

    return 0;
}