#include <iostream>
#include <string>

using namespace std;

bool testPalindrome(string, const int&);

int main() {
	string input = "aaala";

	(testPalindrome(input,0)) ? cout << input << " is a Palindrome" : cout << input << " isnt a Palindrome";

	return 0;
}

bool testPalindrome(string input, const int& place) {
	if (place < input.length() / 2) {
		if (input[place] == input[input.length() - place -1]) {
			return testPalindrome(input, place + 1);
		}
		else return false;
	}
	else {
		return true;
	}
}	