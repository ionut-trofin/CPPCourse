#include <iostream>
#include <vector>
/*
Please refer to the source code provided and the video explanation of this challenge for more details.
You are provided with a simple Account class hierarchy that contains
Account - Base class
Savings Account - Derived class

An Account has a name and a balance.
A Savings Account is an Account and adds an interest rate.

Your challenge is the following:

1. Add a Checking account class to the Account hierarchy
    A Checking account has a name and a balance and has a fee of $1.50 per withdrawal transaction.
    Every withdrawal transaction will be assessed this flat fee.

2. Add a Trust account class to the Account hierarchy
    A Trust account has a name, a balance, and an interest rate
    The Trust account deposit works just like a savings account deposit.
    However, any deposits of $5000.00 or more will receive a $50.00 bonus deposited to the account.

    The Trust account withdrawal should only allow 3 withdrawals per year and each of these must be less than 20% of the account balance.
*/
using namespace std;


class Account {
    friend std::ostream& operator<<(std::ostream& os, const Account& account);

private:
    static constexpr const char* def_name = "Unnamed Account";
    static constexpr double def_balance = 0.0;

protected:
    std::string name;
    double balance;

public:
    Account(std::string name = def_name, double balance = def_balance);
    bool deposit(double amount);
    bool withdraw(double amount);
    double get_balance() const;
};

Account::Account(std::string name, double balance)
    : name{ name }, balance{ balance } {
}

bool Account::deposit(double amount) {
    if (amount < 0) return false;
    balance += amount;
    return true;
}

bool Account::withdraw(double amount) {
    if (balance - amount >= 0) {
        balance -= amount;
        return true;
    }
    return false;
}

double Account::get_balance() const { return balance; }

std::ostream& operator<<(std::ostream& os, const Account& account) {
    os << "[Account: " << account.name << ": " << account.balance << "]";
    return os;
}

class Savings_Account : public Account {
    friend std::ostream& operator<<(std::ostream& os, const Savings_Account& account);

private:
    static constexpr const char* def_name = "Unnamed Savings Account";
    static constexpr double def_balance = 0.0;
    static constexpr double def_int_rate = 0.0;

protected:
    double int_rate;

public:
    Savings_Account(std::string name = def_name, double balance = def_balance, double int_rate = def_int_rate);
    bool deposit(double amount);
};

Savings_Account::Savings_Account(std::string name, double balance, double int_rate)
    : Account{ name, balance }, int_rate{ int_rate } {
}

bool Savings_Account::deposit(double amount) {
    amount += amount * (int_rate / 100);
    return Account::deposit(amount);
}

std::ostream& operator<<(std::ostream& os, const Savings_Account& account) {
    os << "[Savings_Account: " << account.name << ": " << account.balance << ", " << account.int_rate << "%]";
    return os;
}
//Challenge solution
//1.
class Checking_Account: public Account {
private:
    static constexpr const char* def_name = "Unanmed Checking Account";
    static constexpr double def_balance = 0.0;
    static constexpr double def_fee = 1.50;
public:
    
    Checking_Account(string name=def_name, double balance=def_balance) : Account(name, balance) {};
    bool withdraw(double amount) {
        amount = amount + def_fee;
        return Account::withdraw(amount);
    }
    friend ostream& operator<<(ostream& os, const Checking_Account& account) {
        os << "Checking Account: " << account.name << ", with balance: " << account.balance << endl;
        return os;
    }
};
//2.
class Trust_Account :public Savings_Account {
private:
    static constexpr const char* def_name = "Unnamed Trust Account";
    static constexpr double def_balance = 0.0;
    static constexpr double def_int_rate = 0.0;
    static constexpr double bonus_amount = 50.0;
    static constexpr double bonus_range = 5000.0;
    static constexpr int max_withdrawal = 3;
    static constexpr double max_withdraw_percentage = 0.2;
protected:
    int withdrawals;
public:
    Trust_Account(string name = def_name, double balance = def_balance, double int_rate = def_int_rate) : Savings_Account(name, balance, int_rate), withdrawals{ 0 } {};
    bool deposit(double amount) {
        if (amount >= bonus_range) {
            amount = amount + bonus_amount;
        }
        return Savings_Account::deposit(amount);
    }
    bool withdraw(double amount) {
        if (withdrawals >= max_withdrawal) {
            return false;
        }
        if (amount > balance * 0.2) {
            return false;
        }
        if (Savings_Account::withdraw(amount)) {
            withdrawals++;
            return true;
        }
        return false;
    }
    friend ostream& operator <<(ostream& os, const Trust_Account& account) {
        os << "Trust Account: " << account.name << "with balance: " << account.balance << " and interest rate: " << account.int_rate << "%, and number of withdrawas: " << account.withdrawals << endl;
        return os;
    }
};


// Helpers for Account
void display(const std::vector<Account>& accounts) {
    cout << "\n=== Accounts ==========================================" << endl;
    for (const auto& acc : accounts) cout << acc << endl;
}

void deposit(std::vector<Account>& accounts, double amount) {
    cout << "\n=== Depositing to Accounts =================================" << endl;
    for (auto& acc : accounts) {
        if (acc.deposit(amount)) cout << "Deposited " << amount << " to " << acc << endl;
        else cout << "Failed Deposit of " << amount << " to " << acc << endl;
    }
}

void withdraw(std::vector<Account>& accounts, double amount) {
    cout << "\n=== Withdrawing from Accounts ==============================" << endl;
    for (auto& acc : accounts) {
        if (acc.withdraw(amount)) cout << "Withdrew " << amount << " from " << acc << endl;
        else cout << "Failed Withdrawal of " << amount << " from " << acc << endl;
    }
}

void display(const std::vector<Savings_Account>& accounts) {
    cout << "\n=== Savings Accounts ====================================" << endl;
    for (const auto& acc : accounts) cout << acc << endl;
}

void deposit(std::vector<Savings_Account>& accounts, double amount) {
    cout << "\n=== Depositing to Savings Accounts ==========================" << endl;
    for (auto& acc : accounts) {
        if (acc.deposit(amount)) cout << "Deposited " << amount << " to " << acc << endl;
        else cout << "Failed Deposit of " << amount << " to " << acc << endl;
    }
}

void withdraw(std::vector<Savings_Account>& accounts, double amount) {
    cout << "\n=== Withdrawing from Savings Accounts ======================" << endl;
    for (auto& acc : accounts) {
        if (acc.withdraw(amount)) cout << "Withdrew " << amount << " from " << acc << endl;
        else cout << "Failed Withdrawal of " << amount << " from " << acc << endl;
    }
}
// Displays Checking Account objects in a  vector of Checking Account objects 
void display(const std::vector<Checking_Account>& accounts) {
    std::cout << "\n=== Checking Accounts=====================================" << std::endl;
    for (const auto& acc : accounts)
        std::cout << acc << std::endl;
}

// Deposits supplied amount to each Checking Account object in the vector
void deposit(std::vector<Checking_Account>& accounts, double amount) {
    std::cout << "\n=== Depositing to Checking Accounts===========================" << std::endl;
    for (auto& acc : accounts) {
        if (acc.deposit(amount))
            std::cout << "Deposited " << amount << " to " << acc << std::endl;
        else
            std::cout << "Failed Deposit of " << amount << " to " << acc << std::endl;
    }
}

// Withdraw supplied amount from each Checking Account object in the vector
void withdraw(std::vector<Checking_Account>& accounts, double amount) {
    std::cout << "\n=== Withdrawing from Checking Accounts=======================" << std::endl;
    for (auto& acc : accounts) {
        if (acc.withdraw(amount))
            std::cout << "Withdrew " << amount << " from " << acc << std::endl;
        else
            std::cout << "Failed Withdrawal of " << amount << " from " << acc << std::endl;
    }
}

// Helper functions for Trust Account class

// Displays Trust Account objects in a  vector of Trust Account objects 
void display(const std::vector<Trust_Account>& accounts) {
    std::cout << "\n=== Trust Accounts=====================================" << std::endl;
    for (const auto& acc : accounts)
        std::cout << acc << std::endl;
}

// Deposits supplied amount to each Trust Account object in the vector
void deposit(std::vector<Trust_Account>& accounts, double amount) {
    std::cout << "\n=== Depositing to Trust Accounts===========================" << std::endl;
    for (auto& acc : accounts) {
        if (acc.deposit(amount))
            std::cout << "Deposited " << amount << " to " << acc << std::endl;
        else
            std::cout << "Failed Deposit of " << amount << " to " << acc << std::endl;
    }
}

// Withdraw supplied amount from each Trust Account object in the vector
void withdraw(std::vector<Trust_Account>& accounts, double amount) {
    std::cout << "\n=== Withdrawing from Trust Accounts=======================" << std::endl;
    for (auto& acc : accounts) {
        if (acc.withdraw(amount))
            std::cout << "Withdrew " << amount << " from " << acc << std::endl;
        else
            std::cout << "Failed Withdrawal of " << amount << " from " << acc << std::endl;
    }
}
int main() {
    cout.precision(2);
    cout << fixed;

    vector<Account> accounts;
    accounts.push_back(Account{});
    accounts.push_back(Account{ "J" });
    accounts.push_back(Account{ "M", 2000 });
    accounts.push_back(Account{ "C", 5000 });

    display(accounts);
    deposit(accounts, 1000);
    withdraw(accounts, 2000);

    vector<Savings_Account> sav_accounts;
    sav_accounts.push_back(Savings_Account{});
    sav_accounts.push_back(Savings_Account{ "Superman" });
    sav_accounts.push_back(Savings_Account{ "Batman", 2000 });
    sav_accounts.push_back(Savings_Account{ "Wonderwoman", 5000, 5.0 });

    display(sav_accounts);
    deposit(sav_accounts, 1000);
    withdraw(sav_accounts, 2000);
// call in main
    vector<Trust_Account>trust_accounts;
    trust_accounts.push_back(Trust_Account{});
    trust_accounts.push_back(Trust_Account{ "J",30000, 8.0 });
    trust_accounts.push_back(Trust_Account{ "M", 2000, 5.0 });
    trust_accounts.push_back(Trust_Account{ "C", 5000,20.0 });

    display(trust_accounts);
    deposit(trust_accounts, 1000);
    withdraw(trust_accounts, 3000);
    return 0;
}