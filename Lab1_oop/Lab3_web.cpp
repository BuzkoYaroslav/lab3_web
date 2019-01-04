// Lab1_oop.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Triangle.h"
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

const char *queryStringKey = "QUERY_STRING";

char *splitter = ",";

const char *minimizeAngleCommand = "M";
const char *determineTypeCommand = "T";
const char *distanceBetweenCentersCommand = "D";
const char *determineAnglesCommand = "A";
const char *infoCommand = "I";

const char *triangleType1 = "Разносторонний";
const char *triangleType2 = "Равнобедренный";
const char *triangleType3 = "Равносторонний";

const int anglesCount = 3;
const int triangleParametersCount = 3;

void writeInfo(Triangle *triangle, ostream *stream);
const char* triangleTextType(Triangle *triangle);
char* anglesString(Triangle *triangle);
Triangle** parseTrianglesFromString(int num, char **arguments);
int getArgumentsCount(char *string, char splitter);
char** getArgumentsFromString(char* string, char* splitter);

int main()
{
	cout << "Content-type:text/html\n\n";
	cout << "<html><body>";

	char *queryString = getenv(queryStringKey);
	/*char *queryString = new char[256]{ NULL };
	strcat(queryString, "2,20,20,60,3,4,90,1,A,2,A");*/
		char **arguments = getArgumentsFromString(queryString, splitter);

	int num = atoi(arguments[0]),
		count = getArgumentsCount(queryString, splitter[0]);

	Triangle** triangles = parseTrianglesFromString(num, arguments + 1);

	for (int i = 0; i < num; i++)
		writeInfo(triangles[i], &cout);

	cout << "<p>Available commands: <br>"
		<< minimizeAngleCommand << " - maximizing angle <br>"
		<< determineTypeCommand << " - determine type <br>"
		<< distanceBetweenCentersCommand << " - distance between centers <br>"
		<< determineAnglesCommand << " - determine angles <br>"
		<< infoCommand << " - info about triangle</p>";

	int pointer = num * triangleParametersCount + 1;

	while (pointer < count) {
		int index = atoi(arguments[pointer++]) - 1;

		char *command = arguments[pointer++];

		cout << "<p><strong>Triangle</strong> " << (index + 1) 
			<< ", <strong>command</strong> - " << command << "</p>";

		if (strcmp(command, minimizeAngleCommand) == 0) {
			int percent = atoi(arguments[pointer++]);

			triangles[index]->increaseAngle(percent);

			cout << "<p>After increasing</p>";

			writeInfo(triangles[index], &cout);
		}
		else if (strcmp(command, determineTypeCommand) == 0) {
			cout << triangleTextType(triangles[index]) << endl;
		}
		else if (strcmp(command, distanceBetweenCentersCommand) == 0) {
			cout << "<p><strong>Distance between centers</strong> = "
				/*<< fixed << setprecision(3)*/
				<< triangles[index]->calculateLengthBetweenCenters() << "</p>";
		}
		else if (strcmp(command, determineAnglesCommand) == 0) {
			cout << "<p>" << anglesString(triangles[index]) << "</p>" << endl;
		}
		else if (strcmp(command, infoCommand) == 0) {
			writeInfo(triangles[index], &cout);
		}
		else {
			cout << "<p><strong>Incorrect command!</strong></p>";
		}
	}

	//for (int i = 0; i < num; i++)
	//	delete arguments[i];

	//delete arguments;
	//delete queryString;

	cout << "</body></html>";

	return 0;
}

void writeInfo(Triangle *triangle, ostream *stream) {
	*stream << "<p>Info about triangle<br>\n";

	*stream << "<strong>Side 1</strong> = " << triangle->side1 << "<br>";
	*stream << "<strong>Side 2</strong> = " << triangle->side2 << "<br>";
	*stream << "<strong>Angle in degrees</strong> = " << Triangle::radiansToDegrees(triangle->angle) << "</p>";
}

const char* triangleTextType(Triangle *triangle) {
	int res = triangle->determineType();

	switch (res)
	{
	case 1:
		return triangleType1;
	case 2:
		return triangleType2;
	case 3:
		return triangleType3;
	}
}

char* anglesString(Triangle *triangle) {
	int *angles = triangle->getAngles();
	char *str = new char[256]{ NULL };

	for (int i = 0; i < anglesCount; i++) {
		char *strAngle = new char[3]{ NULL };

		itoa(angles[i], strAngle, 10);

		strcat(str, "angle = ");
		strcat(str, strAngle);
		strcat(str, " degrees, ");

		delete strAngle;
	}
	
	return str;
}

Triangle** parseTrianglesFromString(int num, char **arguments) {
	Triangle **result = new Triangle*[num];

	for (int i = 0; i < num * 3; i += 3) {
		double side1 = atoi(arguments[i]),
			side2 = atoi(arguments[i + 1]),
			angle = atoi(arguments[i + 2]);

		result[i / 3] = new Triangle(angle, side1, side2);
	}

	return result;
}

int getArgumentsCount(char *string, char splitter) {
	int count = 1;

	for (int i = 0; i < strlen(string); i++)
		if (string[i] == splitter)
			count++;

	return count;
}

char** getArgumentsFromString(char* string, char* splitter) {
	int count = getArgumentsCount(string, splitter[0]);
	int j = 0;

	char *copyString = new char[256]{ NULL };
	strcpy(copyString, string);

	char** arguments = new char*[count]{ NULL };
	for (int i = 0; i < count; i++)
		arguments[i] = new char[10]{ NULL };

	char *p = strtok(copyString, splitter);

	while (p != NULL) {
		strcpy(arguments[j], p);
		p = strtok(NULL, splitter);

		j++;
	}

	delete copyString;

	return arguments;
}
