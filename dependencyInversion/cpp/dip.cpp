/**
 * High level module or class should not depend on low level module or class, instead both should depend
 * on abstruction
 */

#include<iostream>
using namespace std;

// DIP violated:--------

class SqlDatabase {
public:
    void saveToSQLdb(string data) {
        cout << "Saving data: " << data << " to sql database" << endl;
    }
};

class MongoDatabase {
public:
    void saveToMongodb(string data) {
        cout << "Saving data: " << data << " to mongo database" << endl;
    }
};

class UserService {
private:
    SqlDatabase sqldb;
    MongoDatabase mongodb;
public:
    void saveUserDataToSql(string user) {
        sqldb.saveToSQLdb(user);
    }
    void saveUserDataToMongoDb(string user) {
        mongodb.saveToMongodb(user);
    } 
};

int main() {
    UserService us;
    us.saveUserDataToSql("Alex");
    us.saveUserDataToMongoDb("Alex");

    return 0;
}