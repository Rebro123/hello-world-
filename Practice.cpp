#include "math.h"
#include "iostream"
#include <vector>
#include "string"
#include <fstream>
#include <sstream>
using namespace std;

double k, b;
struct Point {
	double x;
	double y;
};
void findParameters(const vector<Point>& what)
{
	if (what.size() == 0)
		throw runtime_error("No what");

	double Sxx = 0, Sx = 0, Sy = 0, Sxy = 0;
	for (int x = 0; x < what.size(); x++)
	{
		Point i = what[x];
	 	Sxx += i.x * i.x;
		Sx += i.x;
		Sy += i.y;
		Sxy += i.x * i.y;
	}

	double mainDet = what.size() * Sxx - Sx * Sx;
	if (mainDet == 0)
		throw runtime_error("Main determinant is 0");

	double kDet = what.size() * Sxy - Sx * Sy;
	double bDet = Sxx * Sy - Sx * Sxy;

	k = kDet / mainDet;
	b = bDet / mainDet;
}

int main()
{

	vector <Point> Rebro;
	ifstream work_file("C:/Книга6.csv");
	string line;
	while (getline(work_file, line))
	{
		stringstream streamline(line);
		string num;
		char delim = ';';
		int x = 0;
		while (getline(streamline, num, delim))
		{
			stringstream streamnum(num);
			double y;
			streamnum >> y;
			Point point;
			point.x = x;
			point.y = y;
			Rebro.push_back(point);
			x++;

		}
		try {
			findParameters(Rebro);
			cout << k << " " << b << endl;
		}
		catch (exception& ex) {
			cout << ex.what();
		}
		Rebro.clear();
	}
	work_file.close();
}