#pragma once
#include "Button.h"
#include <vector>
using namespace std;
class Score
{
public:
	Score();
	~Score();
	void UpdatingScores();
	vector<int> scores;
	int finalScore;
private:
	bool Init();
};

