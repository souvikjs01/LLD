#ifndef ORDER_H
#define ORDER_H
#include <iostream>
#include <string>
#include "../strategies/PaymentStrategy.h"
#include "User.h"
#include "Restaurant.h"
#include "MenuItem.h"

using namespace std;

class Order {
protected:
    static int nextOrderId;
    int orderID;
    User* user;
    Restaurant* res;
    vector<MenuItem> items;
    PaymentStrategy* ps;
    double total;
    string scheduled;
public:
    Order() {
        orderID = ++nextOrderId;
        user = nullptr;
        res = nullptr;
        ps = nullptr;
        total = 0.0;
        scheduled = "";
    }

    virtual ~Order() {
        delete ps;
    }

    bool processPayment() {
        if(ps) {
            ps->pay(total);
            return true;
        } else {
            cout << "Choose a payment method first" << endl;
            return false; 
        }
    }

    virtual string getType() const = 0;

    // getters & setters
    int getOrderId() const {
        return orderID;
    }

    void setUser(User* u) {
        user = u;
    }

    User* getUser() const {
        return user;
    }

    void setRestaurant(Restaurant* r) {
        res = r;
    }

    Restaurant* getRestaurant() const {
        return res;
    }

    void setItems(const vector<MenuItem> &its) {
        items = its;
        total = 0;
        for(auto &i : items) {
            total += i.getPrice();
        }
    }

    const vector<MenuItem>& getItems() const {
        return items;
    }

    void setPaymentStrategy(PaymentStrategy* p) {
        ps = p;
    }
    
    void setSchedule(const string &sch) {
        scheduled = sch;
    }

    string getSchedule() const {
        return scheduled;
    }

    void setTotal(int total) {
        this->total = total;
    }

    double getTotal() const {
        return total;
    }
};

int Order:: nextOrderId = 0;

#endif