#ifndef PICKUP_ORDER_H
#define PICKUP_ORDER_H
#include <iostream>
#include <string>
#include "Order.h"

using namespace std;

class PickupOrder : public Order {
private:
    string restaurantAddress;
public:
    PickupOrder() {
        restaurantAddress = "";
    }

    string getType() const override {
        return "Pickup";
    }

    // getter setter 
    void setRestaurantAddress(const string& addr) {
        restaurantAddress = addr;
    }
    string getRestaurantAddress() const {
        return restaurantAddress;
    }
};

#endif