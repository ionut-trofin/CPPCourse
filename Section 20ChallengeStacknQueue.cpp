#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>
#include<stack>
#include <queue>
/*SECTION 20 Challenge
A common method to solve this problem is to compare the string to its reverse and
if the are equal then it must be a palindrome. But we will use a deque.

I am providing the main driver for you which will automatically run several test cases.
You challenge is to write the following function:

bool is_palindrome(const std::string &s) {

This function will expect a string and it must determine if that string is a palindrome and return true if it is, or false if it is not.

So,

is_palindrome("A Santa at Nasa");   will return true
is_palindrome("Hello");   will return false

Please use a stack and a queue to solve the problem.
*/
using namespace std;
bool is_palindrome(const std::string& s)
{
    // You must implement this function.
    // Since we are learning the STL - use a stack and a queue to solve the problem.
    stack<char>stack;
    queue<char>queue;
    char c1 = NULL;
    char c2 = NULL;
    for (auto c : s) {
        if (isalpha(c)) {
            c = toupper(c);
            queue.push(c);
            stack.push(c);
        }
    }
    while (!queue.empty()) {
        c1 = queue.front();
        queue.pop();
        c2 = stack.top();
        stack.pop();
        if (c1 != c2) {
            return false;
        }
    }
    return true;
}

int main()
{
    std::vector<std::string> test_strings{ "a", "aa", "aba", "abba", "abbcbba", "ab", "abc", "radar", "bob", "ana",
        "avid diva", "Amore, Roma", "A Toyota's a toyota", "A Santa at NASA", "C++",
        "A man, a plan, a cat, a ham, a yak, a yam, a hat, a canal-Panama!", "This is a palindrome", "palindrome" };

    std::cout << std::boolalpha;
    std::cout << std::setw(8) << std::left << "Result" << "String" << std::endl;
    for (const auto& s : test_strings) {
        std::cout << std::setw(8) << std::left << is_palindrome(s) << s << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

