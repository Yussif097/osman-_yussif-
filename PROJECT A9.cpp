

#include <iostream>
#include <vector>

class Transaction {
public:
    enum class Type { DEPOSIT, WITHDRAWAL, TRANSFER };

    Transaction(Type type, double amount) : type(type), amount(amount) {}

    Type getType() const {
        return type;
    }

    double getAmount() const {
        return amount;
    }

private:
    Type type;
    double amount;
};

class Account {
public:
    Account(int accountNumber, double balance) : accountNumber(accountNumber), balance(balance) {}

    int getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            transactions.push_back(Transaction(Transaction::Type::DEPOSIT, amount));
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            transactions.push_back(Transaction(Transaction::Type::WITHDRAWAL, amount));
        }
    }

    const std::vector<Transaction>& getTransactions() const {
        return transactions;
    }

private:
    int accountNumber;
    double balance;
    std::vector<Transaction> transactions;
};

class Customer {
public:
    Customer(int customerId, const std::string& name) : customerId(customerId), name(name) {}

    int getCustomerId() const {
        return customerId;
    }

    const std::string& getName() const {
        return name;
    }

    void addAccount(Account&& account) {
        accounts.push_back(std::move(account));
    }

    const std::vector<Account>& getAccounts() const {
        return accounts;
    }

private:
    int customerId;
    std::string name;
    std::vector<Account> accounts;
};

int main() {
    Customer customer1(1, "John Doe");
    customer1.addAccount(Account(101, 1000));
    customer1.addAccount(Account(102, 2000));

    Customer customer2(2, "Jane Smith");
    customer2.addAccount(Account(201, 1500));

    // Sample transactions
    customer1.getAccounts()[0].deposit(500);
    customer1.getAccounts()[1].withdraw(300);
    customer2.getAccounts()[0].deposit(1000);

    // Print account details and transactions
    for (const Account& account : customer1.getAccounts()) {
        std::cout << "Account Number: " << account.getAccountNumber() << std::endl;
        std::cout << "Balance: $" << account.getBalance() << std::endl;
        std::cout << "Transactions:" << std::endl;
        for (const Transaction& transaction : account.getTransactions()) {
            std::string typeStr;
            switch (transaction.getType()) {
                case Transaction::Type::DEPOSIT:
                    typeStr = "Deposit";
                    break;
                case Transaction::Type::WITHDRAWAL:
                    typeStr = "Withdrawal";
                    break;
                default:
                    typeStr = "Unknown";
                    break;
            }
            std::cout << "- " << typeStr << ": $" << transaction.getAmount() << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}

