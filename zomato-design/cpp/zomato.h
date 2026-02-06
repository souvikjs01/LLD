#ifndef ZOMATO_APP_H
#define ZOMATO_APP_H

#include<vector>
#include<string>
#include "models/Restaurant.h"
#include "managers/RestaurantManager.h"
#include "models/User.h"
#include "models/Order.h"
#include "factories/OrderFactory.h"
#include "factories/NowOrderFactory.h"
#include "factories/ScheduleOrderFactory.h"
#include "managers/OrderManager.h"
#include "services/NotificationService.h"

using namespace std;

class ZomatoApp {
public:
    ZomatoApp() {
        initializedRestaurant();
    }

    void initializedRestaurant() {
        Restaurant* res1 = new Restaurant("Panjabi Dhaba", "Raipur");
        res1->addMenuItem(MenuItem("P1", "Paneer tikka", 150));
        res1->addMenuItem(MenuItem("p2", "Dal makni", 90));

        Restaurant* res2 = new Restaurant("Haldi Ram", "Kolkata");
        res2->addMenuItem(MenuItem("P1", "Raj Kachori", 80));
        res2->addMenuItem(MenuItem("P2", "Alu Biriyani", 130));
        res2->addMenuItem(MenuItem("P3", "Dhokla", 100));

        Restaurant* res3 = new Restaurant("Bikaner", "Delhi");
        res3->addMenuItem(MenuItem("P1", "Chole Bhature", 120));
        res3->addMenuItem(MenuItem("P2", "Samossa", 15));

        ResturantManager* resManager =  ResturantManager::getInstance();
        resManager->addRestuarant(res1);
        resManager->addRestuarant(res2);
        resManager->addRestuarant(res3);

        // Add other restaurants
    }

    vector<Restaurant*> searchRestaurant(const string& location) {
        return ResturantManager::getInstance()->searchByLocation(location);
    }

    void selectResraurant(User* user, Restaurant* res) {
        Cart* cart = user->getCart();
        cart->setRestaurant(res);
    }

    void addToCart(User* user, const string& itemCode) {
        Restaurant* res = user->getCart()->getRestaurant();
        if(!res) {
            cout << "Please select a restaurant first." << endl;
            return;
        }
        for(const auto& item : res->getMenu()) {
            if(item.getCode() == itemCode) {
                user->getCart()->addItem(item);
                break;
            }
        }
    }

    Order* checkoutNow(User* user, const string& orderType, PaymentStrategy* ps) {
        return checkout(user, orderType, ps, new NowOrderFactory());
    }

    Order* checkoutScheduled(User* user, const string& orderType, PaymentStrategy* ps, const string& scheduledTime) {
        return checkout(user, orderType, ps, new ScheduleOrderFactory(scheduledTime));
    }
    

    Order* checkout(User* user, const string& orderType, PaymentStrategy* ps, OrderFactory* orderFactory) {
        if(user->getCart()->isEmpty()) {
            return nullptr;
        }

        Cart* userCart = user->getCart();
        Restaurant* orderedRestaurant = userCart->getRestaurant();
        vector<MenuItem> orderedItems = userCart->getItems();
        double totalCost = userCart->getTotalCost();

        Order* order = orderFactory->createOrder(user, userCart, orderedRestaurant, orderedItems, ps, orderType);
        OrderManagaer::getInstance()->addOrder(order);
    }

    void payForOrder(User* user, Order* order) {
        bool isPaymentSuccess = order->processPayment();

        if(isPaymentSuccess) {
            NotificationService* notification = new NotificationService();
            notification->notify(order);
            user->getCart()->clear();
        }
    }

    void printUserCart(User* user) {
        cout << "Items in cart:" << endl;
        cout << "-----------------------------------" << endl;
        for(const auto& item : user->getCart()->getItems()) {
            cout << item.getCode() << " : " << item.getName() << " : Rs. " << item.getPrice() << endl;
        }
        cout << "-----------------------------------" << endl;
    }
};

#endif