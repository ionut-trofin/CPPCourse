// Section 14 Challenge
// Operator Functions
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

/*Here is a list of some of the operators that you can overload for this class :

    --unary minus.Returns the lowercase version of the object's string
    - s1
    == -returns true if the two strings are equal
    (s1 == s2)
    != -returns true if the two strings are not equal
    (s1 != s2)
    < -returns true if the lhs string is lexically less than the rhs string
    (s1 < s2)
    > -returns true if the lhs string is lexically greater than the rhs string
    (s1 > s2)
    + -concatenation.Returns an object that concatenates the lhs and rhs
    s1 + s2
    += -concatenate the rhs string to the lhs string and store the result in lhs object
    s1 += s2;      equivalent to s1 = s1 + s2;
*-repeat - results in a string that is copied n times
s2 * 3;          ex).s2 = "abc";
s1 = s2 * 3;
s1 will result in "abcabcabc"
*= -repeat the string on the lhs n times and store the result back in the lhs object
s1 = "abc";
s1 *= 4;        s1 = s1 will result in "abcabcabcabc"
*/
class Mystring {
private:
    string str;
public:
    Mystring() : str{""} {
        cout << "Default constructor" << endl;
    }
    Mystring(const string& s) : str{ s } {
        cout << "Overloaded constructor" << endl;
    }
    Mystring(const Mystring& source) :str{ source.str } {
        cout << "Copy cosntructor used" << endl;
    }
    Mystring( Mystring&& source) : str{ move(source.str) } {
        cout << "Move constructor used" << endl;
    }
    Mystring& operator=(const Mystring& rhs) {
        cout << "Copy assignment" << endl;
        if (this != &rhs) {
            str = rhs.str;
        }
        return *this;
    }
    Mystring& operator=( Mystring&& rhs) {
        cout << "Move assignment" << endl;
        if (this != &rhs) {
            str = move(rhs.str);
        }
        return *this;
    }
    ~Mystring() { cout << "Destructor!" << endl; }

    void display() const {
        cout << str << " : " << get_length() << endl;
    }

    int get_length() const {
        return str.length();
    }
    string get_string() const {
        return str;
    }
    friend ostream& operator<<(ostream& os, const Mystring& rhs);
    friend istream& operator>>(istream& is,  Mystring& rhs);

    Mystring operator-()const {
        string lwc = str;
        for (size_t i = 0; i < lwc.length(); i++) {
            lwc[i] = tolower(lwc[i]);
        }
        return Mystring(lwc);
    }
    Mystring operator+(const Mystring& rhs) const {
        string concatenated = str + rhs.str;
        return Mystring(concatenated);
    }
    bool operator==(const Mystring& rhs) const {
        if (this->str == rhs.str) {
            return true;
        }
        else {
            return false;
        }
    }
    bool operator!=(const Mystring& rhs)const {
        if (this->str == rhs.str) {
            return false;
        }
        else {
            return true;
        }
    }
    bool operator<(const Mystring& rhs) const{
        return this->str.length() < rhs.str.length();
    }
    bool operator>(const Mystring& rhs) const {
        return this->str.length() > rhs.str.length();
    }
    Mystring& operator+=(const Mystring& rhs) {
        this->str = this->str + rhs.str;
        return *this;
    }
    Mystring operator*(int n) const {
        Mystring temp;
        for (size_t i = 1; i <= n; i++) {
            temp = temp + *this;
        }
        return temp;
    }
    Mystring& operator*=(int n) {
        string original = this->str;
        this->str.clear();
        for (size_t i = 1; i <= n; i++) {
            this->str += original;
        }
        return *this;
    }
    //constructor special pt test case
    Mystring(const char* s) :str{ s } {
        cout << "Overloaded constructor(Ctype Strings)" << endl;
    }
};
ostream& operator<<(ostream& os, const Mystring& rhs) {
    os << rhs.str;
    return os;
}
istream& operator>>(istream& is, Mystring& rhs) {
    string temp;
    is >> temp;
    rhs.str = temp;
    return is;
}
int main() {    
    cout << boolalpha << endl;
    Mystring a{ "Ionut" };
    Mystring b{ "Ionut" };
    cout << (a == b) << endl;         // true
    cout << (a != b) << endl;           // false

    b = "Theo";
    cout << (a == b) << endl;         // false
    cout << (a != b) << endl;          // true
    cout << (a < b) << endl;         // true
    cout << (a > b) << endl;          // false

    Mystring s1{ "IONUT" };
    s1 = -s1;
    cout << s1 << endl;             // ionut          

    s1 = s1 + "*****";
    cout << s1 << endl;             // ionut*****       

    s1 += "-----";                      // ionut*****-----
    cout << s1 << endl;

    Mystring s2{ "12345" };
    s1 = s2 * 3;
    cout << s1 << endl;           // 123451234512345

    Mystring s3{ "abcdef" };
    s3 *= 5;
    cout << s3 << endl;             // abcdefabcdefabcdefabcdefabcdef

    Mystring repeat_string;
    int repeat_times;
    cout << "Enter a string to repeat: " << endl;
    cin >> repeat_string;
    cout << "How many times would you like it repeated? " << endl;
    cin >> repeat_times;
    repeat_string *= repeat_times;
    cout << "The resulting string is: " << repeat_string << endl;

    cout << (repeat_string * 12) << endl;

    repeat_string = "RepeatMe";
    cout << (repeat_string + repeat_string + repeat_string) << endl;

    repeat_string += (repeat_string * 3);
    cout << repeat_string << endl;

    repeat_string = "RepeatMe";
    repeat_string += (repeat_string + repeat_string + repeat_string);


    Mystring s{"Ionut"};

    s = -s;
    cout << s << endl;                  // ionut

    s = -s;
    cout << s << endl;                  // ionut
    return 0;
}