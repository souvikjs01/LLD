#ifndef CART_H
#define CART_H
#include<iostream>
#include<string>
#include<vector>
#include "Restaurant.h"
#include "./MenuItem.h"

using namespace std;

class Cart {
private:
    Restaurant* res;
    vector<MenuItem> items;
public:
    Cart() {
        res = nullptr;
    }

    void addItem(const MenuItem &it) {
        if(!res) {
            cout << "Select a restaurant first then add item" << endl;
            return;
        }
        items.push_back(it);
    }

    double getTotalCost() const {
        double sum = 0;
        for (const auto& it : items) {
            sum += it.getPrice();
        }
        return sum;
    }

    bool isEmpty() {
        return (!res || items.empty()); 
    }

    void clear() {
        items.clear();
        res = nullptr;
    }

    // getter setter
    void setRestaurant(Restaurant* r) {
        res = r;
    }

    Restaurant* getRestaurant() const {
        return res;
    }

    const vector<MenuItem>& getItems() const {
        return items;
    }
};

#endif