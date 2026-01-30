#ifndef NOTIFICATION_SERVICE_H
#define NOTIFICATION_SERVICE_H

#include<iostream>
#include "../models/Order.h"
using namespace std;

// *** we assume that notification service is an external service

class NotificationService {
public:
    static void notify(Order* order) {
        cout << "\nNotification: New " << order->getType() << " order placed" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Order ID: " << order->getOrderId() << endl;
        cout << "Customer: " << order->getUser() << endl;
        cout << "Restaurant: " << order->getRestaurant() << endl;
        cout << "Item ordered: " << endl;

        const vector<MenuItem> &items = order->getItems();
        for(const auto& item : items) {
            cout << "  - " << item.getName() << " Rs. " << item.getPrice() << endl;
        }

        cout << "Total: Rs. " << order->getTotal() << endl;
        cout << "Scheduled for: " << order->getSchedule() << endl;
        cout << "Payment: Done" << endl;
        cout << "-----------------------------------------" << endl;
    }
};

#endif