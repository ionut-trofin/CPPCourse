#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>

/*Section 19
Challenge 4
Copy Romeo and Juliet with line numbers from textsample
*/

using namespace std;
int main() {
	ofstream out_file{ "output.txt"};
	if (!out_file) {
		cerr << "Error creating file!" << endl;
		return 1;
	}
	ifstream in_file{ "textsample.txt" };
	if (!in_file) {
		cerr << "Error opening the source file!" << endl;
		return 2;
	}
	string line;
	int linecounter = 0;
	while (getline(in_file, line)) {
		if (line == "") {
			out_file << endl;
		}
		else {
			out_file << setw(5) << left << linecounter << line << endl;
			linecounter++;
		}
	}
	in_file.close();
	out_file.close();
	return 0;
}
