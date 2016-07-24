// Spacing Calculator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <algorithm>
using std::min;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <limits>;
using std::numeric_limits;
#include <string>
using std::string;

#include <vector>
using std::vector;

#include <cstdlib>
#include <cmath>

int main() {
	int spacers[8] = {125, 250, 375, 500, 190, 330, 32, 40};
	string spacerNames[8] = {"0.125 Spacer (Nylon)", "0.250 Spacer (Nylon)", "0.375 Spacer (Nylon)", "0.500 Spacer (Nylon)", "4.6mm Spacer", "8mm Spacer", "Steel Washer (0.032)", "Teflon Washer (0.040)"};
	int distance;
	string buffer;
	cout << "What distance (inches) do you want to fill? (rounds after thousandths place): ";
	cin >> buffer; distance = static_cast<int> (round(1000 * atof(buffer.c_str())));
	 
	vector<int> table;
	vector<int> lastSpacer;
	vector<int> solutions;
	for (int i = 0; i <= distance; i++) {
		table.push_back(numeric_limits<int>::max() - 1);
		lastSpacer.push_back(-1);
	};
	table[0] = 0;

	// find number of spacers in optimal solution
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j <= distance; j++) {
			if (j >= spacers[i]) {
				table[j] = min(table[j], (table[j - spacers[i]]) + 1);

				if (table[j] == (table[j - spacers[i]]) + 1) {
					lastSpacer[j] = i;
				}
			}
		}
	} 

	int numSpacers = table[distance];
	
	// find which spacers were used
	do {
		solutions.push_back(lastSpacer[distance]);
		distance -= spacers[lastSpacer[distance]];
		numSpacers--;
	} while (lastSpacer[distance] > -1);

	int sumSpacers = 0;
	int spacerCount[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	for (int i : solutions) {
		sumSpacers += spacers[i];
		spacerCount[i]++;
	}
	cout << endl;

	int spacerSum = 0;
	for (int s : solutions) {
		spacerSum += spacers[s];
	}

	for (int i = 0; i < 8; i++) {
		if (spacerCount[i] > 0) cout << spacerNames[i] << " (x" << spacerCount[i] << ") " << endl;
	}
	cout << endl;
	cout << "The spacers fill up " << spacerSum / 1000.0 << " inches." << endl;

	return 0;
}
