#include <vector>
#include <iomanip>
#include <iostream>

using namespace std;

void adder(int*, const int&);

int main() {

	vector<int> input;
	
	for (int i = 200; i <= 1500; i += 100) {
		input.push_back(i);
	}
	string salaryGroup[9] = {"200-299: ", "300-399: ", "400-499: ", "500-599: ", "600-699: ", "700-799: ", "800-899: ", "900-999: ", "1000+: "};
	int count[9] = { 0, 0, 0, 0, 0, 0, 0, 0 , 0};

	for (int i = 0; i < input.size(); i++) {
		adder(count, input[i]);
	}

	for (int i = 0; i < 9; i++) {
		cout << salaryGroup[i] << count[i] << setw(5);
	}
	return 0;
}

void adder(int* count, const int& salary) {
	int relative = salary / 100;
	switch (relative) {
	case 2:
		count[0]++; // can also be *(count + increment)++;
		break;
	case 3:
		count[1]++;
		break;
	case 4:
		count[2]++;
		break;
	case 5:
		count[3]++;
		break;
	case 6:
		count[4]++;
		break;
	case 7:
		count[5]++;
		break;
	case 8:
		count[6]++;
		break;
	case 9:
		count[7]++;
		break;
	default: //Assumes perfect user that would never enter a salary <200
		count[8]++;
	}

}