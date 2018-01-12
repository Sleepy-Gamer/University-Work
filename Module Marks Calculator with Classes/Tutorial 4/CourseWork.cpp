#include "CourseWork.h"



CourseWork::CourseWork()
{
}


CourseWork::~CourseWork()
{
}

//Get input from the user to populate course work marks.
int CourseWork::courseWorkMark(int count)
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
double CourseWork::courseWorkWeighting(int count)
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
