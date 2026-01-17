#ifndef UPI_PAYMENT_STRATEGY_H
#define UPI_PAYMENT_STRATEGY_H
#include "PaymentStrategy.h"
#include <iostream>
#include <string>
using namespace std;

class CardPaymentStrategy : public PaymentStrategy {
private:
    string cardNumber;
public:
    CardPaymentStrategy(const string &card) {
        this->cardNumber = card;
    }

    void pay(double amount) override {
        cout << "Payment of " << amount << " using Card " << cardNumber << " is successfull" << endl;
    }
};

#endif