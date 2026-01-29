#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include<iostream>
#include<string>
#include<vector>
#include "../models/Order.h"
using namespace std;

class OrderManagaer {
private:
    vector<Order*> orders;
    static OrderManagaer* instance;
    
    OrderManagaer() {
        // private constructor
    }
public:
    static OrderManagaer* getInstance() {
        if(!instance) {
            instance = new OrderManagaer();
        }
        return instance;
    }

    void addOrder(Order* odr) {
        orders.push_back(odr);
    }
    void listOrders() {
        cout << "<--------------All orders-------------->" << endl;
        for(auto order : orders) {
            cout << order->getType() << " order for " << order->getUser()->getName() 
            << " | Total: Rs." << order->getTotal() 
            << " | At: " << order->getSchedule() << endl;
        }
    }
};

OrderManagaer* OrderManagaer::instance = nullptr;

#endif