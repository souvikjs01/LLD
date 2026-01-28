#ifndef DELIVERY_ORDER_H
#define DELIVERY_ORDER_H
#include <iostream>
#include <string>
#include "Order.h"

using namespace std;

class DeliveryOrder : public Order {
private:
    string userAddress;
public:
    DeliveryOrder() {
        this->userAddress = "";
    }

    string getType() const override {
        return "Delivery";
    }

    // getter & setter
    void setAddress(const string& addr) {
        userAddress = addr;
    }
    string getAddress() const {
        return userAddress;
    }
};

#endif