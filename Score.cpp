#include "Score.h"
#include <fstream>
#include <sstream>
#include <iostream>

Score::Score() 
{
	Init();
}


Score::~Score()
{
}

bool Score::Init() {
	ifstream scoreRecord("score.txt");
	string line;
	if (scoreRecord.is_open())
	{
		while (getline(scoreRecord, line)) {
			int s = stoi(line);
			scores.push_back(s);
		}
		scoreRecord.close();
	}
	else printf_s("unable to open score.txt\n");
	return true;
}

void Score::UpdatingScores() {
	scores.push_back(finalScore);
	sort(scores.begin(), scores.end(), greater<int>());
	ofstream scoreRecord("score.txt");
	if (scoreRecord.is_open()) {
		for (auto ite = scores.begin(); ite != scores.end()-1; ++ite) {
			scoreRecord << *ite << endl;
		}
		scoreRecord.close();
	}
	else cout << "Unable to open file score.txt\n";
}
