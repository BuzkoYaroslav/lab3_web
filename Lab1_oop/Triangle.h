#pragma once
class Triangle
{
private:
	const double epsilan = 0.01;
	const double defaultAngle = 30;
	const double PI = 3.14;

	double calculateThirdSide();
	double calculateBigRadius();
	double calculateSmallRadius();
public:
	static double degreesToRadians(int degrees);
	static int radiansToDegrees(double radians);

	double angle;
	double side1, side2;

	void increaseAngle(int percentage);
	// 1 - for 3 different sides
	// 2 - for 2 equal sides
	// 3 - for all equal sides
	int determineType();
	// return array with 3 elements - angles
	int* getAngles();
	double calculateLengthBetweenCenters();

	Triangle(int angle, double side1, double side2);
};

