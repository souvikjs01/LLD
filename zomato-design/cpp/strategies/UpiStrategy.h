#ifndef UPI_PAYMENT_STRATEGY_H
#define UPI_PAYMENT_STRATEGY_H
#include "PaymentStrategy.h"
#include <iostream>
#include <string>
using namespace std;

class UpiPaymentStrategy : public PaymentStrategy {
private:
    string upiId;
public:
    UpiPaymentStrategy(const string& id) {
        this->upiId = id;    
    }

    void pay(double amount) override {
        cout << "Payment of " << amount << " using UPI " << upiId << " is successfull" << endl;
    }
};

#endif