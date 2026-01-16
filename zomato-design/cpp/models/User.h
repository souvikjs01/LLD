#ifndef USER_H
#define USER_H
#include<iostream>
#include<string>
#include<vector>
#include "Cart.h"

using namespace std;

class User {
private:
    int userId;
    string name;
    string address;
    Cart *cart;
public:
    User(int userId, const string &name, const string& address) {
        this->userId = userId;
        this->name = name;
        this->address = address;
        cart = new Cart();
    }
    ~User() {
        delete cart;
    }

    // getters setters
    void setName(const string& n) {
        name = n;
    }
    string getName() const {
        return name;
    }

    void setAddress(const string& add) {
        address = add;
    }
    string getAddress() const {
        return address;
    }

    Cart* getCart() const {
        return cart;
    }

};

#endif