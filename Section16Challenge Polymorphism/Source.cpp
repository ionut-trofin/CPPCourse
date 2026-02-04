#include <iostream>
#include <vector>
#include "Account.h"
#include "Account_Utility.h"
#include"Savings_Account.h"
#include"Trust_Account.h"
#include"Checking_Account.h"

using namespace std;
/* Section 16 Challenge
* 
You are provided with a completed Account class hierarchy
The provided class hierarchy does not use dynamic polymorphism (it has no virtual functions!)
Your challenge is the following:

1.  Modify the Account class so that it is now an Abstract class by adding the following pure virtual functions:
        virtual bool deposit(double amount) = 0;
        virtual bool withdraw(double amount) = 0;

        Hint: you can implement these functions in the Account class if it makes sense

2. Create an I_Printable class interface as we did in the course and provide functionality so
    all accounts are printable to an ostream using the overloaded insertion operator.

        class I_Printable
        {
            friend std::ostream &operator<<(std::ostream &os, const I_Printable &obj);
        public:
            virtual void print(std::ostream &os) const = 0;
            virtual ~I_Printable() = default;
        };

3. Modify the functions in the Account_Util files so we only have one version of each. For example,

        void display(const std::vector<Account *> &accounts);
        void deposit(std::vector<Account *> &accounts, double amount);
        void withdraw(std::vector<Account *> &accounts, double amount);

        Note that the vector is a vector of pointers to Account objects <Account *>
*/
void main() {
    //Account Theo;
    Checking_Account c;
    cout << c << endl;
    Account* ptr = new Trust_Account("Odin", 100000, 6.7);//Slices 6.7
    cout << *ptr << endl;
    Account* trust = new Trust_Account("Theod");
    cout << *trust << endl;
        
    Account *p1 = new Checking_Account("Mocity", 100);
    Account *p2 = new Savings_Account("Flexologist", 10);
    Account *p3 = new Trust_Account("Scott");
        
    std::vector<Account *> accounts {p1,p2,p3};
        
    display(accounts);
    deposit(accounts, 1000);
    withdraw(accounts, 2000);
        
    display(accounts);
        
    delete p1;
    delete p2;
    delete p3;
}