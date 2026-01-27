#include<iostream>
#include<vector>

using namespace std;

// Not following LDP:----------------------
class Account {
public:
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
};

class SavingAccount : public Account {
private:
    double balance;
public:
    SavingAccount() {
        balance = 0;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited in saving account $" << amount << " New balance: " << balance << endl; 
    }
    void withdraw(double amount) {
        if(balance < amount) {
            cout << "Insufficient funds in saving account!" << endl;
        } else {
            balance -= amount;
            cout << "Withdrawn: $" << amount << " from saving account, current balance $" << balance << endl;
        }
    }
};

class CurrentAccount : public Account {
private:
    double balance;
public:
    CurrentAccount() {
        balance = 0;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited in current account $" << amount << " New balance: " << balance << endl; 
    }
    void withdraw(double amount) {
        if(balance < amount) {
            cout << "Insufficient funds in current account!" << endl;
        } else {
            balance -= amount;
            cout << "Withdrawn: $" << amount << " from current account, current balance $" << balance << endl;
        }
    }
};

class FixedDeposit : public Account {
private:
    double balance;
public:
    FixedDeposit() {
        balance = 0;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited in Fixed term account $" << amount << " New balance: " << balance << endl; 
    }
    void withdraw(double amount) {
        throw logic_error("Withdrawal not allowed in Fixed term account!");
    }
};

class BankClient {
private:
    vector<Account*> accounts;
public:
    BankClient(vector<Account*> accounts) {
        this->accounts = accounts;
    }

    void processTransactions() {
        for(Account* acc : accounts) {
            acc->deposit(1000);

            try{
                acc->withdraw(500);
            } catch(const logic_error& e) {
                cout << "Exception: " << e.what() << endl;
            }
        }
    }
};

int main() {
    vector<Account*> accounts;

    accounts.push_back(new SavingAccount());
    accounts.push_back(new CurrentAccount());
    accounts.push_back(new FixedDeposit());

    BankClient* client = new BankClient(accounts);
    client->processTransactions();

    return 0;
}