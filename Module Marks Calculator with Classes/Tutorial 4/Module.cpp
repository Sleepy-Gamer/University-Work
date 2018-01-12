#include "Module.h"



Module::Module()
{
}


Module::~Module()
{
}


void Module::moduleMarkCalculation()
{
	CourseWork student1;
	Exam studentExam;

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
				courseWorkMarks[i] = student1.courseWorkMark(i);
				courseWorkWeightingAmount[i] = student1.courseWorkWeighting(i);
				examWeighting = examWeighting - courseWorkWeightingAmount[i];
				OverAllCourseWorkMark[i] = courseWorkMarks[i] * courseWorkWeightingAmount[i];
			}

			examMark = studentExam.examMarkResult();
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



}
