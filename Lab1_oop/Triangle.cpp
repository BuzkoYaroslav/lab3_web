#include "stdafx.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include "Triangle.h"
using namespace std;

Triangle::Triangle(int _angle, double _side1, double _side2) {
	side1 = _side1;
	side2 = _side2;

	if (_angle <= 0 || _angle >= 180)
		_angle = defaultAngle;

	angle = Triangle::degreesToRadians(_angle);
}

void Triangle::increaseAngle(int percentage) {
	if (percentage + 100 < 0 && percentage + 100 > 200)
		return;

	double temp = angle;

	temp *= 1 + double(percentage) / 100;

	if (temp >= PI)
		return;

	angle = temp;
}

int Triangle::determineType() {
	double side3 = calculateThirdSide();
	if (abs(side1 - side2) < epsilan &&
		abs(side1 - side3) < epsilan &&
		abs(side2 - side3) < epsilan)
		return 3;
	else if (abs(side1 - side2) < epsilan ||
		abs(side1 - side3) < epsilan ||
		abs(side2 - side3) < epsilan)
		return 2;
	else
		return 1;
}

int* Triangle::getAngles() {
	int *angles = new int[3];
	double side3 = calculateThirdSide();

	angles[0] = Triangle::radiansToDegrees(angle);
	angles[1] = Triangle::radiansToDegrees(asin(sin(angle) * side2 / side3));
	angles[2] = Triangle::radiansToDegrees(asin(sin(angle) * side1 / side3));

	return angles;
}

double Triangle::calculateThirdSide() {
	return sqrt(pow(side1, 2) + pow(side2, 2) - 2 * side1 * side2 * cos(angle));
}

double Triangle::calculateLengthBetweenCenters() {
	double smallRadius = calculateSmallRadius(),
		bigRadius = calculateBigRadius();

	return sqrt(pow(bigRadius, 2) - 2 * bigRadius * smallRadius);
}

double Triangle::calculateBigRadius() {
	return calculateThirdSide() / (2 * sin(angle));
}

double Triangle::calculateSmallRadius() {
	return side1 * side2 * sin(angle) / (side1 + side2 + calculateThirdSide());
}

double Triangle::degreesToRadians(int degrees) {
	return degrees * 3.14 / 180;
}

int Triangle::radiansToDegrees(double radians) {
	return radians * 180 / 3.14;
}