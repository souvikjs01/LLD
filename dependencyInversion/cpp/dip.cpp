/**
 * High level module or class should not depend on low level module or class, instead both should depend
 * on abstruction
 */

#include<iostream>
using namespace std;

// DIP violated:--------
/*
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
*/


// DIP followed:----------

class Database {
public:
    virtual void save(string data) = 0;
};

class SqlDatabase : public Database {
public:
    void save(string data) override {
        cout << "Saving data: " << data << " to sql database" << endl;
    }
};

class MongoDatabase : public Database {
public:
    void save(string data) override {
        cout << "Saving data: " << data << " to mongo database" << endl;
    }
};

class UserService {
private:
    Database* db;
public:
    UserService(Database* db) {
        this->db = db;
    }
    void saveUserData(string user) {
        db->save(user);
    }
};

int main() {
    SqlDatabase pgdb;
    MongoDatabase mgdb;

    UserService service1(&pgdb);
    service1.saveUserData("Pedri");

    UserService service2(&mgdb);
    service2.saveUserData("De Jong");

    return 0;
}