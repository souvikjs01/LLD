#include<iostream>
#include<vector>

using namespace std;

// Not following OCP-----------
/*
class Product {
public:
    string name;
    double price;

    Product(string name, double price) {
        this->name = name;
        this->price = price;
    }
};

class ShoppingCart {
private:
    vector<Product*> products;
public:
    void addProduct(Product* p) {
        products.push_back(p);
    }

    const vector<Product*>& getProducts() {
        return products;
    }
    
    double calculateTotal() {
        double total = 0;
        for(auto p : products) {
            total += p->price;
        }
        return total;
    }
};

class ShoppingCartPrinter {
private:
    ShoppingCart* cart;
public:
    ShoppingCartPrinter(ShoppingCart* cart) {
        this->cart = cart;
    }

    void printInvoice() {
        cout << "Shopping cart invoices: " << endl;
        for(auto p : cart->getProducts()) {
            cout << p->name << " - $ " << p->price << endl;
        }
        cout << "Total: $" << cart->calculateTotal() << endl;
    }
};

// shopping cart storage (save to database)
class ShoppingCartStorage {
private:
    ShoppingCart* cart;
public:
    ShoppingCartStorage(ShoppingCart* cart) {
        this->cart = cart;
    }

    void saveToSQLDatabase() {
        cout << "Saving cart to sql database..." << endl;
    }
    void saveToMongoDatabase() {
        cout << "Saving cart to mongo database..." << endl;
    }
    void saveToFile() {
        cout << "Saving cart to File..." << endl;
    }
};

int main() {
    ShoppingCart* cart = new ShoppingCart();
    
    cart->addProduct(new Product("Laptop", 1500));
    cart->addProduct(new Product("Phone", 500));
    cart->addProduct(new Product("PS5", 2500));

    ShoppingCartPrinter* printer = new ShoppingCartPrinter(cart);
    printer->printInvoice();

    ShoppingCartStorage* db = new ShoppingCartStorage(cart);
    db->saveToMongoDatabase();

    return 0;
}

*/


// Proper OCP

class Product {
public:
    string name;
    double price;

    Product(string name, double price) {
        this->name = name;
        this->price = price;
    }
};

class ShoppingCart {
private:
    vector<Product*> products;
public:
    void addProduct(Product* p) {
        products.push_back(p);
    }

    const vector<Product*>& getProducts() {
        return products;
    }
    
    double calculateTotal() {
        double total = 0;
        for(auto p : products) {
            total += p->price;
        }
        return total;
    }
};

class ShoppingCartPrinter {
private:
    ShoppingCart* cart;
public:
    ShoppingCartPrinter(ShoppingCart* cart) {
        this->cart = cart;
    }

    void printInvoice() {
        cout << "Shopping cart invoices: " << endl;
        for(auto p : cart->getProducts()) {
            cout << p->name << " - $ " << p->price << endl;
        }
        cout << "Total: $" << cart->calculateTotal() << endl;
    }
};

class Persistence{
private:
    ShoppingCart* cart;
public:
    virtual void save(ShoppingCart* cart) = 0;
};

class SQLPersistence : public Persistence {
public:
    void save(ShoppingCart* cart) {
        cout << "Saving cart to SQL database..." << endl;
    }
};

class MongoPersistence : public Persistence {
public:
    void save(ShoppingCart* cart) {
        cout << "Saving cart to Mongo database..." << endl;
    }
};

class FilePersistence : public Persistence {
public:
    void save(ShoppingCart* cart) {
        cout << "Saving cart to File system..." << endl;
    }
};

int main() {
    ShoppingCart* cart = new ShoppingCart();
    
    cart->addProduct(new Product("Laptop", 1500));
    cart->addProduct(new Product("Phone", 500));
    cart->addProduct(new Product("PS5", 2500));

    ShoppingCartPrinter* printer = new ShoppingCartPrinter(cart);
    printer->printInvoice();

    Persistence* db = new SQLPersistence();
    Persistence* mongo = new MongoPersistence();
    Persistence* file = new FilePersistence();

    db->save(cart);
    mongo->save(cart);
    file->save(cart);
    
    return 0;
}
