#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;
// Section 19
// Challenge 2
// Automated Grader
/*
Write a program that reads a file named 'responses.txt" that contains the answer key for a quiz
as well as student responses for the quiz.

The answer key is the first item in the file.
Student1 name
Student1 responses
Student2 name
Student2 responses
. . .

Here is a sample file.

You should read the file and display:
Each student's name and score (#correct out of 5)
At the end, the class average should be displayed
You may assume that the data in the file is properly formatted

Program should output to the console the following :
Student               Score
----------------------------
Student1                    5
Student2                    3
Student3                    4
....
---------------------------
*/
int response_compute(string& response, string& answers) {
	int score = 0;
	for (int i = 0; i < answers.size(); i++) {
		if (response.at(i) == answers.at(i)) {
			score++;
		}
	}
	return score;
}
int main() {
	ifstream file{ "responses.txt" };

	if (!file) {
		cerr << "Error opening the file" << endl;
		return 1;
	}
	else {
		string answers;
		string names;
		string responses;
		int total_stud = 0;
		int contor_scor = 0;
		double average_score = 0;

		cout << setw(15) << left << "Student" << setw(5) << "Score" << endl;
		cout << setw(20) << setfill('=') << "" << endl;
		cout << setfill(' ');

		file >> answers;
		while (file >> names >> responses) {
			++total_stud;
			int score = response_compute(responses, answers);
			contor_scor = contor_scor + score;
			cout << setprecision(1) << fixed;
			cout << setw(15) << left << names << setw(5) << right << score << endl;
		}
		average_score = static_cast<double>(contor_scor) / total_stud;

		cout << setw(20) << setfill('=') << "" << endl;
		cout << setfill(' ');
		cout << setw(15) << left << "Average Score" << setw(5) << right << average_score << endl;
	}
	file.close();
	return 0;
}
