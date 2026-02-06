#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>

/*Section 19
Challenge 3
Word finder

Ask the user to enter a word
Process the Romeo and Juliet file and determine how many total words there are
and how many times the word the user entered appears as a substring of a word in the play.

For example.
If the user enters : love
Then the words love, lovely, and beloved will all be considered matches.
*/

using namespace std;
int main() {
	ifstream file{ "textsample.txt" };

	if (!file) {
		cerr << "Error opening the file" << endl;
		return 1;
	}
	else {
		int total_words = 0;
		int match = 0;
		string searchword;
		int choice;
		string word;
		cout << "Enter a word to search: ";
		cin >> searchword;
		cout << "Text Filtering Option..." << endl;
		cout << "1 for Case Sensitive search, 2 for Case Insensitive search: ";
		cin >> choice;

		
		switch (choice) {
			case 1:
				while (file >> word) {
					total_words++;
					bool found = false;
					if (searchword.length() <= word.length()) {
						for (int i = 0; i <= word.length() - searchword.length(); i++) {
							if (word.substr(i, searchword.length()) == searchword) {
								found = true;
								break;
							}
						}
					}
					if (found) {
						match++;
					}
				}
				break;

			case 2:
				for (int i = 0; i < searchword.length(); i++) {
					searchword[i] = tolower(searchword[i]);
				}
				while (file >> word) {
					total_words++;
					string insensit_word = word;
					for (int i = 0; i < insensit_word.length(); i++) {
						insensit_word[i] = tolower(insensit_word[i]);
					}
					bool found = false;
					if (searchword.length() <= insensit_word.length()) {
						for (int i = 0; i <= insensit_word.length() - searchword.length(); i++) {
							if (insensit_word.substr(i, searchword.length()) == searchword) {
								found = true;
								break;
							}
						}
					}
					if (found) {
						match++;
					}
				}
				break;

			default:
				cout << "Invalid choice!" << endl;
				return 1;
		}

		cout << endl;
		cout << "\nTotal words: " << total_words << endl;
		cout << "Matches: " << match << endl;
	}
	file.close();

	return 0;
}


