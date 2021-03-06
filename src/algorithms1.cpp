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
	vector<int> length(seq.size(), 1);
	vector<vector<int>> pos;
	vector<vector<int>> subSeq;

	int max = 1;

	for(int i = 1; i < seq.size(); i++) {
		for(int j = 0; j < i; j++) {
			if(seq[i] > seq[j] && length[i] <= length[j]) {
				length[i] = length[j] + 1;
			}
			if(length[i] > max) {
				max = length[i];
			}
		}
	}

	int maxConst = max;

	for(int i = length.size() - 1; i >= 0; i--) {
		for(int j = length.size() - 1; j >= 0; j--) {
			if(i == length.size() - 1 && length[j] == max) {
				subSeq.push_back({seq[j]});
				pos.push_back({j});
			}
			else if(length[j] == max) {
				int size = subSeq.size();
				for(int x = 0; x < size; x++) {
					if(j < pos[x][pos[x].size() - 1] &&
							seq[j] < subSeq[x][subSeq[x].size() - 1]) {
						subSeq[x].push_back(seq[j]);
						pos[x].push_back(j);
					}
					else if(subSeq[x].size() >= 2 &&
							j < pos[x][pos[x].size() - 2] && seq[j] < subSeq[x][subSeq[x].size() - 2]) {
						vector<int> temp = subSeq[x];
						subSeq.push_back(temp);
						subSeq[subSeq.size() - 1][subSeq[x].size() - 1] = seq[j];
						temp = pos[x];
						pos.push_back(temp);
						pos[pos.size() - 1][pos[x].size() - 1] = j;
					}
				}
			}
		}
		max--;
	}

	for(int i = 0; i < subSeq.size(); i++) {
		cout << subSeq[i].size() << ": ";
		for (int j = 0; j < subSeq[i].size(); j++) {
			cout << subSeq[i][j] << " ";
		}
		cout << endl;
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
