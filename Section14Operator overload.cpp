// Section 14
// Operator Functions
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;
class Mystring {
private:
	char* str;
public:
	Mystring() :str{ nullptr } {
		str = new char[1];
		*str = '\0';
	}
	Mystring(const char* s) :str{ nullptr } {
		if (s == nullptr) {
			str = new char[1];
			*str = '\0';
		}
		else {
			str = new char[strlen(s) + 1];
			strcpy(str, s);
		}
	}
	Mystring(const Mystring& source) :str{ nullptr } {
		str = new char[strlen(source.str) + 1];
		strcpy(str, source.str);
		cout << "Copy constructor used" << endl;
	}
	Mystring(Mystring&& source) :str(source.str){
		source.str = nullptr;
		cout << "Move constructor used: " << endl;
	}

	~Mystring() {
		delete[]str;
	}

	Mystring &operator=(const Mystring& rhs) {
		cout << "Using copy assignment" << endl;
		if (this == &rhs) {
			return *this;
		}
		delete[]str;
		str = new char[strlen(rhs.str) + 1];
		strcpy(str, rhs.str);
		return *this;
	}
	Mystring& operator=(Mystring&& rhs) {
		cout << "Using move assignment" << endl;
		if (this == &rhs) {
			return *this;
		}
		delete[]str;
		str = rhs.str;
		rhs.str = nullptr;
		return *this;
	}
	void display() const {
		cout << str << " : " << get_length() <<endl;
	}
	int get_length() const {
		return strlen(str);
	}
	const char* get_str() const {
		return str;
	}
	friend bool operator==(const Mystring& lhs, const Mystring& rhs);
	friend Mystring operator-(const Mystring& obj);
	friend Mystring operator+(const Mystring& lhs, const Mystring& rhs);
	friend ostream& operator<<(ostream& os, const Mystring& rhs);
	friend istream& operator >> (istream& is, Mystring& rhs);
};
bool operator==(const Mystring& lhs, const Mystring& rhs) {
	return (strcmp(lhs.str, rhs.str) == 0);
}
//lowercase
Mystring operator-(const Mystring& obj) {
	char* buffer = new char[strlen(obj.str) + 1];
	strcpy(buffer, obj.str);
	for (size_t i = 0; i < strlen(buffer); i++) {
		buffer[i] = tolower(buffer[i]);
	}
	Mystring temp{ buffer };
	delete[] buffer;
	return temp;
}
//concatenate
Mystring operator+(const Mystring& lhs, const Mystring& rhs) {
	char* buffer = new char[strlen(lhs.str) + strlen(rhs.str) +1];
	strcpy(buffer, lhs.str);
	strcat(buffer, rhs.str);
	Mystring temp = buffer;
	delete[] buffer;
	return temp;
}
ostream& operator<<(ostream& os, const Mystring& rhs) {
	os << rhs.str;
	return os;
}
istream& operator >> (istream& is, Mystring& rhs) {
	char* buffer = new char[1000];
	is >> buffer;
	rhs=Mystring{ buffer };
	delete[]buffer;
	return is;
}
int main() {
	Mystring nume1{ "Ionut" };
	Mystring nume2{ "Theo" };
	Mystring nume3;

	cout << "Introdu al treilea nume: ";
	cin >> nume3;

	cout << "Numele este " << nume1 << " " << nume2 << " " << nume3 << endl;