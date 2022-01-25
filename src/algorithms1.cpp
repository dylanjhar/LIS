//============================================================================
// Name        : algorithms1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void loadSequence(ifstream& infile, vector<int>& seq) {
	string line, num;
	getline(infile, line);
	stringstream ss(line);

	while(getline(ss, num, ',')) {
		seq.push_back(stoi(num));
	}
}

void lis(vector<int>& seq) {
	vector<int> length(seq.size());
	vector<string> subSeq(seq.size());

	int max = 1;

	for(int i = 0; i < seq.size(); i++) {
		length[i] = 1;
		subSeq[i] = to_string(seq[i]) + " ";
	}

	for(int i = 1; i < seq.size(); i++) {
		for(int j = 0; j < i; j++) {
			if(seq[i] > seq[j] && length[i] <= length[j]) {
				length[i] = length[j] + 1;
				subSeq[i] = subSeq[j] + to_string(seq[i]) + " ";
			}
			if(length[i] > max) {
				max = length[i];
			}
		}
	}

	for(int i = 0; i < subSeq.size(); i++) {
		if(length[i] == max) {
			cout << max << ": " << subSeq[i];
		}
	}
}

int main() {
	ifstream infile("data.txt");
	if(!infile) {
		cout << "Unable to get file" << endl;
		exit(-1);
	}

	vector<int> seq;
	loadSequence(infile, seq);
	lis(seq);

	return 0;
}
