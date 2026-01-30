#ifndef SCHEDULE_ORDER_FACTORY_H
#define SCHEDULE_ORDER_FACTORY_H

#include<vector>
#include<string>
#include "OrderFactory.h"
#include "../models/DeliveryOrder.h"
#include "../models/PickupOrder.h"
#include "../utils/TimeUtils.h"
using namespace std;

class ScheduleOrderFactory : public OrderFactory {
private:
    string scheduleTime;
public:
    ScheduleOrderFactory(string scheduleTime) {
        this->scheduleTime = scheduleTime;
    } 

    Order* createOrder(User* user, Cart* cart, 
    Restaurant* res, const vector<MenuItem>& menuItems,
    PaymentStrategy* ps, const string &orderType) override {
        Order* order = nullptr;
        if(orderType == "Delivery") {
            auto deliveryOrder = new DeliveryOrder();
            deliveryOrder->setAddress(user->getAddress());
            order = deliveryOrder;
        } 
        else {
            auto pickupOrder = new PickupOrder();
            pickupOrder->setRestaurantAddress(res->getLocation());
        }
        order->setUser(user);
        order->setRestaurant(res);
        order->setItems(menuItems);
        order->setPaymentStrategy(ps);
        order->setSchedule(scheduleTime);
        order->setTotal(cart->getTotalCost());
        return order;
    }
};

#endif