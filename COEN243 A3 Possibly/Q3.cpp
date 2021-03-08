#include <iostream>
#include <istream>
#include <iomanip>
#include <string>
#include <vector>;

using namespace std;

void right(bool*, const unsigned int&, const unsigned int&, vector<int>&);
void left(bool*, const unsigned int&, const unsigned int&, vector<int>&);
void display(bool*, const unsigned int&);
void reboot(bool*, const unsigned int&, vector<int>&, vector<int>&);
void show(bool*, const unsigned int&);
void cancel(bool*, const unsigned int&, const unsigned int&, vector<int>&, vector<int>&);
void replay(bool*, const unsigned int&, const unsigned int&, vector<int>&, vector<int>&);

int main() {
	bool grid[8]; // Size can be dynamically set precompiling without hampering code
	bool exit = false;
	bool replayable = false;

	vector<int> history;
	vector<int> replayHold;

	unsigned int size = sizeof(grid) / sizeof(grid[0]);
	reboot(grid, size, history, replayHold);

	cout << "Please enter a command: ";

	do {
		string input;
		getline(cin, input);

		if (input.substr(0, 7) == "Right (") {
			string temp = "";
			for (int i = 7; i < input.length(); i++) {
				if (input[i] == ')') 
					right(grid, stoi(temp), size, history);
				temp += input[i];
			}
		}
		else if (input.substr(0, 6) == "Left (") {
			string temp = "";
			for (int i = 6; i < input.length(); i++) {
				if (input[i] == ')') 
					left(grid, stoi(temp), size, history);
				temp += input[i];
			}
		}
		else if (input == "Display") {
			display(grid, size);
			replayable = false;
		}
		else if (input == "Reboot") {
			reboot(grid, size, history, replayHold);
		}
		else if (input == "Show Array") {
			show(grid, size);
			replayable = false;
		}
		else if (input == "Exit") {
			exit = true;
		}
		else if (input.substr(0, 8) == "Cancel (") {
			replayable = false;
			string temp = "";
			for (int i = 8; i < input.length(); i++) {
				if (input[i] == ')') 
					cancel(grid, stoi(temp), size, history, replayHold);
				temp += input[i];
			}
		}
		else if (input.substr(0, 8) == "Replay (") {
			replayable = false;
			string temp = "";
			for (int i = 8; i < input.length(); i++) {
				if (input[i] == ')') 
					replay(grid, stoi(temp), size, history, replayHold);
				temp += input[i];
			}
		}
		if (replayable == true) {
			replayHold.clear();
			replayable = false;
		}
		if (!replayHold.empty()) replayable = true;

	} while (!exit);

	return 0;
}

void right(bool* grid, const unsigned int& increment, const unsigned int& size, vector<int>& history) {
	unsigned int position, newPosition;
	for (int i = 0; i < size; i++) {
		if (grid[i]) {
			position = i;
			i = size;
		}
	}
	if (position + increment >= size) newPosition = size - 1;
	else newPosition = position + increment;

	history.push_back(newPosition - position);

	grid[position] = false;
	grid[newPosition] = true;
}

void left(bool* grid, const unsigned int& increment, const unsigned int& size, vector<int>& history) {
	unsigned int position, newPosition;
	for (int i = 0; i < size; i++) {
		if (grid[i]) {
			position = i;
			i = size;
		}
	}
	if (position - increment < 0) newPosition = 0;
	else newPosition = position - increment;

	history.push_back(newPosition - position);

	grid[position] = false;
	grid[newPosition] = true;
}

void display(bool* grid, const unsigned int& size) {
	unsigned int position;
	for (int i = 0; i < size; i++) {
		if (grid[i]) {
			position = i;
			i = size;
		}
	}
	cout << "The position of the robot is x = " << position << endl;
}

void reboot(bool* grid, const unsigned int& size, vector<int>& history, vector<int>& replay) {
	history.clear();
	replay.clear();
	grid[0] = true;
	for (int i = 1; i < size; i++) {
		grid[i] = false;
	}
}

void show(bool* grid, const unsigned int& size) {
	cout << "The location of the robot is denoted by position:1" << endl << "| ";
	for (int i = 0; i < size; i++) {
		cout << i << " : " << grid[i] << " | ";
	}
	cout << endl;
}

void cancel(bool* grid, const unsigned int& steps, const unsigned int& size, vector<int>& history, vector<int>& replay) {
	replay.clear();
	for (int i = 0; i < steps; i++) {
		int temp = history.back();
		history.pop_back();
		if (temp > 0) left(grid, temp, size, replay);
		else right(grid, -temp, size, replay);
	}
}

void replay(bool* grid, const unsigned int& steps, const unsigned int& size, vector<int>& history, vector<int>& replay) {
	for (int i = 0; i < steps; i++) {
		int temp = replay.back();
		replay.pop_back();
		if (temp > 0) left(grid, temp, size, history);
		else right(grid, -temp, size, history);
	}
}

