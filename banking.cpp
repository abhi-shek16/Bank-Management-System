#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class BankAccount {
protected:
    int accountNumber;
    string name;
    double balance;
    vector<string> transactionHistory;

public:
    BankAccount(int accNo, string accName, double initialBalance)
        : accountNumber(accNo), name(accName), balance(initialBalance) {}

    virtual void deposit(double amount) {
        balance += amount;
        transactionHistory.push_back("Deposited: Rs." + to_string(amount));
    }

    virtual void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            transactionHistory.push_back("Withdrawn: Rs." + to_string(amount));
        } else {
            cout << "\n❌ Insufficient balance.\n";
        }
    }

    virtual void display() const {
        cout << "\nAccount Number: " << accountNumber << "\nName: " << name << "\nBalance: Rs." << balance << endl;
    }

    virtual void calculateInterest() = 0; // pure virtual

    void showTransactionHistory() const {
        cout << "\n📄 Transaction History for Account " << accountNumber << ":\n";
        for (const string &record : transactionHistory) {
            cout << "- " << record << endl;
        }
    }

    int getAccountNumber() const { return accountNumber; }
};

class SavingsAccount : public BankAccount {
public:
    SavingsAccount(int accNo, string accName, double initialBalance)
        : BankAccount(accNo, accName, initialBalance) {}

    void calculateInterest() override {
        double interest = balance * 0.04; // 4% annual interest
        balance += interest;
        transactionHistory.push_back("Interest Added: Rs." + to_string(interest));
        cout << "\n✅ Interest of Rs." << interest << " added to Savings Account " << accountNumber << ".\n";
    }
};

class CurrentAccount : public BankAccount {
    double overdraftLimit;

public:
    CurrentAccount(int accNo, string accName, double initialBalance)
        : BankAccount(accNo, accName, initialBalance), overdraftLimit(10000.0) {}

    void withdraw(double amount) override {
        if (amount <= balance + overdraftLimit) {
            balance -= amount;
            transactionHistory.push_back("Withdrawn: Rs." + to_string(amount));
        } else {
            cout << "\n❌ Overdraft limit exceeded.\n";
        }
    }

    void calculateInterest() override {
        cout << "\nℹ️ No interest on Current Account " << accountNumber << ".\n";
    }
};

map<int, BankAccount *> accounts;

bool accountExists(int accNo) {
    return accounts.find(accNo) != accounts.end();
}

int main() {
    int choice;
    do {
        cout << "\n===== 💳 Enhanced Bank Management System =====\n";
        cout << "1. Create Savings Account\n";
        cout << "2. Create Current Account\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Display Account Details\n";
        cout << "6. Calculate Interest\n";
        cout << "7. Transaction History\n";
        cout << "8. Exit\n";
        cout << "Choose an option (1-8): ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            int accNo;
            string name;
            double initialBalance;

            cout << "\nEnter Account Number: ";
            cin >> accNo;

            if (accountExists(accNo)) {
                cout << "\n⚠️ Account number already exists.\n";
                continue;
            }

            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Initial Balance: ";
            cin >> initialBalance;

            if (choice == 1)
                accounts[accNo] = new SavingsAccount(accNo, name, initialBalance);
            else
                accounts[accNo] = new CurrentAccount(accNo, name, initialBalance);

            cout << "\n✅ Account created successfully.\n";

        } else if (choice == 3 || choice == 4) {
            int accNo;
            double amount;
            cout << "\nEnter Account Number: ";
            cin >> accNo;

            if (!accountExists(accNo)) {
                cout << "\n❌ Account not found.\n";
                continue;
            }

            cout << "Enter Amount: ";
            cin >> amount;

            if (choice == 3)
                accounts[accNo]->deposit(amount);
            else
                accounts[accNo]->withdraw(amount);

        } else if (choice == 5) {
            int accNo;
            cout << "\nEnter Account Number: ";
            cin >> accNo;

            if (!accountExists(accNo)) {
                cout << "\n❌ Account not found.\n";
                continue;
            }

            accounts[accNo]->display();

        } else if (choice == 6) {
            int accNo;
            cout << "\nEnter Account Number: ";
            cin >> accNo;

            if (!accountExists(accNo)) {
                cout << "\n❌ Account not found.\n";
                continue;
            }

            accounts[accNo]->calculateInterest();

        } else if (choice == 7) {
            int accNo;
            cout << "\nEnter Account Number: ";
            cin >> accNo;

            if (!accountExists(accNo)) {
                cout << "\n❌ Account not found.\n";
                continue;
            }

            accounts[accNo]->showTransactionHistory();

        } else if (choice == 8) {
            cout << "\n👋 Exiting...\n";
        } else {
            cout << "\n❌ Invalid choice. Try again.\n";
        }

    } while (choice != 8);

    // Clean up memory
    for (auto &entry : accounts)
        delete entry.second;

    return 0;
}
