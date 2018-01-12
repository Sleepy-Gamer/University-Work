//Write a program that asks the user to enter the marks that a student gains for 4 assignments and an exam mark. 

#include <iostream>

using namespace std;

int courseWorkMark(int count);
double courseWorkWeighting(int count);
int examMarkResult();

int main()
{
	//Declare variables.
	const int numberOfCourseWorks = 4;
	int courseWorkMarks[numberOfCourseWorks] = { 0, 0, 0, 0 };
	double courseWorkWeightingAmount[numberOfCourseWorks] = { 0.0, 0.0, 0.0, 0.0 };
	int examMark = 0;
	double examWeighting = 1.0;
	int moduleMark = 0;
	int OverAllCourseWorkMark[4];
	char userInput = 'n';

	do
	{
		do {
			//Calculate exam weighting.
			for (int i = 0; i < numberOfCourseWorks; i++)
			{
				courseWorkMarks[i] = courseWorkMark(i);
				courseWorkWeightingAmount[i] = courseWorkWeighting(i);
				examWeighting = examWeighting - courseWorkWeightingAmount[i];
				OverAllCourseWorkMark[i] = courseWorkMarks[i] * courseWorkWeightingAmount[i];
			}

			examMark = examMarkResult();
		} while (examMark < 0 || examMark > 100);


		cout << "Marks for the course works including weighting: " << endl;

		//Print out the course work marks and corresponding weighting.
		for (int i = 0; i < numberOfCourseWorks; i++)
		{
			cout << "Course work " << i + 1 << ": " << courseWorkMarks[i] << " weighting: " << courseWorkWeightingAmount[i] << endl;
		}

		//Print out the exam mark and how much it weighs 
		cout << "Exam mark is " << examMark << endl;
		cout << "Exam mark weighting is: " << examWeighting << endl;
		//Calculate module mark.
		for (int i = 0; i < numberOfCourseWorks; i++)
		{
			moduleMark = moduleMark + OverAllCourseWorkMark[i];
		}
		moduleMark = moduleMark + (examMark * examWeighting);
		//Print out overall mark.
		cout << "Total module mark is " << moduleMark << endl;
		cout << "Calculate again? [y/n]" << endl;
		cin >> userInput;
	} while (userInput == 'y' || userInput == 'Y');

	system("pause");
	return 0;
}


//Get input from the user to populate course work marks.
int courseWorkMark(int count)
{
	int mark = 0;
	
	cout << "What is the mark for course work " << count + 1 << " 0-100 " << endl;
	cin >> mark;
	while (mark < 0 || mark > 100)
	{
		cout << "Error in course work" << count + 1 << ". Please try again" << endl;
		cin >> mark;
	}

	return mark;
}

//Get input from the user to populate course work weighting.
double courseWorkWeighting(int count)
{

	double weighting = 0.0;

	cout << "What is the mark for course weighting for course work " << count + 1 << " 0.1 - 0.2 " << endl;
	cin >> weighting;
	while (weighting < 0.1 || weighting > 0.2)
	{
		cout << "Error in course work weighting " << count + 1 << ". Please try again" << endl;
		cin >> weighting;
	}

	return weighting;
}

//Get input from the user to populate exam result.
int examMarkResult()
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