#include "Exam.h"



Exam::Exam()
{
}


Exam::~Exam()
{
}


//Get input from the user to populate exam result.
int Exam::examMarkResult()
{
	int examMark = 0;
	cout << "What is the exam mark?" << endl;
	cin >> examMark;
	while (examMark < 0 || examMark > 100)
	{
		cout << "Error in exam mark, please try again" << endl;
		cin >> examMark;
	}
	return examMark;
}