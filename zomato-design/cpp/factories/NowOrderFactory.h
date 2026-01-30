#ifndef NOW_ORDER_FACTORY_H
#define NOW_ORDER_FACTORY_H

#include<vector>
#include<string>
#include "OrderFactory.h"
#include "../models/DeliveryOrder.h"
#include "../models/PickupOrder.h"
#include "../utils/TimeUtils.h"
using namespace std;

class NowOrderFactory : public OrderFactory {
public:
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
            order = pickupOrder;
        }

        order->setUser(user);
        order->setItems(menuItems);
        order->setRestaurant(res);
        order->setPaymentStrategy(ps);
        order->setTotal(cart->getTotalCost());
        order->setSchedule(TimeUtils::getCurrentTime());
    }
};

#endif