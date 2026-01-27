#include<iostream>
#include<vector>

using namespace std;

// Not following LDP:----------------------
/*
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

*/

// Following LDP:-----------------

class DepositOnlyAccount {
public:
    virtual void deposit(double amount) = 0;
};

class WithdrawableAccount : public DepositOnlyAccount {
public: 
    virtual void withdraw(double amount) = 0;
};

class SavingAccount : public WithdrawableAccount {
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

class CurrentAccount : public WithdrawableAccount {
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

class FixedTermAccount : public DepositOnlyAccount {
private:
    double balance;
public:
    FixedTermAccount() {
        balance = 0;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited in Fixed term account $" << amount << " New balance: " << balance << endl; 
    }
};

class BankClient {
private:
    vector<DepositOnlyAccount*> depositOnlyAccounts;
    vector<WithdrawableAccount*> withdrawableAccounts;
public:
    BankClient(vector<DepositOnlyAccount*> depositOnlyAccounts,
    vector<WithdrawableAccount*> withdrawableAccounts) {
        this->depositOnlyAccounts = depositOnlyAccounts;
        this->withdrawableAccounts = withdrawableAccounts;
    }

    void processTransactions() {
        for(WithdrawableAccount* acc : withdrawableAccounts) {
            acc->deposit(2500.50);
            acc->withdraw(350);
        }
        for(DepositOnlyAccount* acc : depositOnlyAccounts) {
            acc->deposit(450.25);
        }
    }
};

int main() {
    vector<WithdrawableAccount*> withdrawableAccounts;
    vector<DepositOnlyAccount*> depositOnlyAccounts;

    withdrawableAccounts.push_back(new SavingAccount());
    withdrawableAccounts.push_back(new CurrentAccount());

    depositOnlyAccounts.push_back(new FixedTermAccount());

    BankClient* client = new BankClient(depositOnlyAccounts, withdrawableAccounts);
    client->processTransactions();

    return 0;
}