#ifndef RESTAURANT_MANAGER_H
#define RESTAURANT_MANAGER_H
#include<iostream>
#include<string>
#include<vector>
#include "../models/Restaurant.h"
#include<algorithm>

using namespace std;

class ResturantManager {
private:
    vector<Restaurant*> restaurants;
    static ResturantManager* instance;

    ResturantManager() {
        // private constructor
    }
public:
    static ResturantManager* getInstance() {
        if(!instance) {
            instance = new ResturantManager();
        }
        return instance;
    }

    void addRestuarant(Restaurant* r) {
        restaurants.push_back(r);
    }

    vector<Restaurant*> searchByLocation(string loc) {
        vector<Restaurant*> result;
        transform(loc.begin(), loc.end(), loc.begin(), ::tolower);

        for(auto res : restaurants) {
            string rl = res->getLocation();
            transform(rl.begin(), rl.end(), rl.begin(), ::tolower);
            if(rl == loc) {
                result.push_back(res);
            }
        }
        return result;
    }
};

ResturantManager* ResturantManager::instance = nullptr;

#endif