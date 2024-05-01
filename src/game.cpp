//============================================================================
// Student Name : Sabih Nasir	
// Roll No      : 21I-2769
// Version      : 1.0
//============================================================================

#ifndef RushHour_CPP_
#define RushHour_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include<cmath>
#include<fstream>
using namespace std;


/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 20, 0, 21, 1, -1); // set the screen size to given width and height.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//--------------------------------------------------------------------Start variables------------------------------------
float taxiStartXAxis = 0, taxiStartYAxis = 19;
int buildingArray[154] = { 2,17 ,3,17, 4,17, 2,13, 3,13, 3,12, 3,11, 2,6, 3,6, 2,5, 3,5, 2,4, 3,4, 5,13, 6,13, 7,13, 7,14,
					7,15, 7,16, 5,2, 5,3, 5,4, 5,5, 5,6, 5,7, 5,8, 7,5, 8,5, 9,5, 10,5, 11,5, 11,6, 11,7,
					7,9, 8,9, 9,9, 9,10, 9,12, 9,17, 10,17, 11,17, 12,17, 13,17, 14,17, 15,17, 16,17, 17,17, 18,17,
					19,17, 9,0, 9,1, 9,2, 14,3, 14,4, 14,5, 14,6, 15,6, 16,6, 17,6, 18,6, 19,6, 17,1, 18,1, 12,10,
					12,11, 12,12, 12,13, 12,14, 12,15, 13,13, 14,13, 15,13, 18,11, 18,12, 18,13, 18,14, 18,15 };//x,y cordinates
int obstaclesArray[14] = { 1000,1000, 1000,1000, 1000,1000, 1000,1000, 1000,1000, 1000,1000, 1000,1000 };
int passengersArray[10] = { 1000,1000, 1000,1000, 1000,1000, 1000,1000, 1000,1000, };
int currentDropLocationX = -1;
int currentDropLocationY = -1;
string displayThisScreen = "menu1";
string flags[] = { "left","up","right","down","right","left","down","up" ,"right","left","down","up" ,"right","left","down","up" ,"right","left","down","up" };
bool justCollided = false;
bool passengerInCar = false;
int numberOfPassengersDropped = 0;
int carsArray[50] = { -1, -1, -1,-1, -1,-1, -1,-1, -1,-1,
				  -1,-1, -1,-1, -1,-1, -1,-1, -1,-1,
				  -1,-1, -1,-1, -1,-1, -1,-1, -1,-1,
				  -1,-1, -1,-1, -1,-1, -1,-1, -1,-1,
				  -1,-1, -1,-1, -1,-1, -1,-1, -1,-1 };
int speed = 1000;
int speed2 = 2000;
bool verticalTaxi = false;
int randomColorArray[15] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
int seconds = 0;
int scores[11] = { 0,0,0,0,0,0,0,0,0,0,0, };
int score = 0;
string names[11] = { "","","","","","","","","","","" };

string taxiColors[] = { "yellow", "red" };
string taxiColor = "yellow";
string taxiDirection = "";
float taxiSpeed = 1;
//--------------------------------------------------------------------Start variables end------------------------------------

//--------------------------------------------------------------------Function prototypes------------------------------------
void addCar(); //Adds a car to the map.
void addHighScore(int scores[], string names[]); //Add new high score at the end of game

bool check_double(float a, float b);/*Checks float with another. Returns true if difference less than 0.6. i.e 1.41==2,
Solves the problem of collision on movements of 0.5 multiples.
The car can not move 1.5 towards the x axis if there is a building or obstacle on 2 xaxis.*/
void drawBoard();
void addHighScore(int scores[], string names[]); //Add new high score at the end of game
void AutoCarMovement(int m); //Automatically moves cars on the board
void swapElements(int array[], int fromIndex, int toIndex); //Swap int array elements, by index
void swapElementsString(string array[], int fromIndex, int toIndex); //Swap string array elements by index
void sortArrayDescending(int array[], int size, string array2[]); /*Sort array in descending order.
Different from other sort functions as it also peforms the same swaps on a string array passed as 3rd parameter.*/
void readHighScores(int scores[], string names[]); //Reads high scores from highscore.txt
void drawTree(int x, int y); //Draws tree
void drawPerson(int x, int y); //Draws stick figure.
void drawCarHorizontal(int x, int y, int color); //Draw horizontal car if car is going left or right.
void drawCarVertical(int x, int y, int color);  //Draw vertical car if car is going up or down.
void drawCube(int x, int y); //Draws cube like brick

bool checkExistence(int array[]/*Array containing x,y coordinates to check against*/,
	int size/*Size of array*/,
	float x, float y,
	bool closeBy = false /*Should check close by coordinates for existence too?.*/); //Checks existence of various objects(obstacles,buildings,passengers) on specified x,y coordinates.
bool colorExists(int color); //Checks if color already exists in color array(To remove duplicate colors). 
bool taxiExists(float x, float y); //Checks if taxi exists on specified x,y coordinates.
bool passengerAdjacent(int x, int y); //Checks if passenger is adjacent to specified x,y. (used in picking up people.)
void replaceXYCoordinates(int array[], int toReplaceX, int toReplaceY, int size); //Replaces certain x,y coordinates with random non-interfering coordinates.
void generateDropLocation(int pickedupX, int pickedupY); //Generate drop location for a passenger after he is picked up.
void generateRandomColors(); //Generates random colors(doesn't generate shades of yellow, red or white.
void generateRandomCoordinates(int array[], int size); //Generate random coordinates to draw objects.
void drawTaxi(); //Draws taxi on canvas using taxiStartXAxis, taxiStartYAxis
void drawBuildings();
void drawObstacles();
void drawPassengers();
void drawCars();
void drawDropLocation(int x, int y);
void drawTaxiHorizontal();
void drawTaxiVertical();
//--------------------------------------------------------------------Function prototypes end------------------------------------

//Auto car movement, called in glutTimerFunc function.
void moveCarRight(int& x, int& y)
{
	x += 1;
}
void moveCarLeft(int& x, int& y)
{
	x -= 1;
}
void moveCarUp(int& x, int& y)
{
	y += 1;
}
void moveCarDown(int& x, int& y)
{
	y -= 1;
}
bool check_double(float a, float b)/*Checks float with integer. Returns true if difference less than 0.6. i.e 1.4==2,
Solves the problem of collision on movements of 0.5 multiples.
The car can not move 1.5 towards the x axis if there is a building or obstacle on 2 xaxis.*/
{
	if (fabs(a - b) < 0.6)
		return true;
	return false;
}
void drawBoard()
{
	//lines on roads
	for (float x = 0.5; x < 20; x++)
	{
		for (float y = 0.5; y < 20; y++)
		{
			DrawLine(x, y + 0.3, x, y + 0.6, 6, colors[WHITE]);
		}
	}
	//horizontal seperator line
	for (int x = 0; x < 20; x++)
	{
		DrawLine(x, 20.1, x + 1, 20.1, 2, colors[BLACK]);
	}
	glutPostRedisplay();
}
void addCar()
{
	int index = numberOfPassengersDropped + 8;
	replaceXYCoordinates(carsArray, carsArray[index], carsArray[index + 1], 50);
}
void addHighScore(int scores[], string names[]) //Add new high score at the end of game
{
	sortArrayDescending(scores, 11, names);
	ofstream out_file;
	out_file.open("highscores.txt");
	for (int i = 0; i < 10; i++)
	{
		out_file << names[i] << endl;
	}
	for (int i = 0; i < 10; i++)
	{
		out_file << scores[i] << endl;
	}
}
void AutoCarMovement(int m) //Automatically moves cars on the board
{
	if (displayThisScreen == "game")
	{
		//Movement
		for (int i = 0; i < 50; i += 2)
		{
			if (carsArray[i] != -1)
			{
				if (flags[i / 2] == "right")
				{
					if (checkExistence(buildingArray, 154, carsArray[i] + 1, carsArray[i + 1]) != true &&
						checkExistence(obstaclesArray, 14, carsArray[i] + 1, carsArray[i + 1]) != true &&
						checkExistence(passengersArray, 10, carsArray[i] + 1, carsArray[i + 1]) != true &&
						taxiExists(carsArray[i] + 1, carsArray[i + 1]) != true &&
						checkExistence(carsArray, 50, carsArray[i] + 1, carsArray[i + 1]) != true &&
						carsArray[i] < 19)
					{
						moveCarRight(carsArray[i], carsArray[i + 1]);
					}
				}
				else if (flags[i / 2] == "left")
				{
					if (checkExistence(buildingArray, 154, carsArray[i] - 1, carsArray[i + 1]) != true &&
						checkExistence(obstaclesArray, 14, carsArray[i] - 1, carsArray[i + 1]) != true &&
						checkExistence(passengersArray, 10, carsArray[i] - 1, carsArray[i + 1]) != true &&
						taxiExists(carsArray[i] - 1, carsArray[i + 1]) != true &&
						checkExistence(carsArray, 50, carsArray[i] - 1, carsArray[i + 1]) != true && carsArray[i] > 0)
						moveCarLeft(carsArray[i], carsArray[i + 1]);
				}
				else if (flags[i / 2] == "up")
				{
					if (checkExistence(buildingArray, 154, carsArray[i], carsArray[i + 1] + 1) != true &&
						checkExistence(obstaclesArray, 14, carsArray[i], carsArray[i + 1] + 1) != true &&
						checkExistence(passengersArray, 10, carsArray[i], carsArray[i + 1] + 1) != true &&
						taxiExists(carsArray[i], carsArray[i + 1] + 1) != true &&
						checkExistence(carsArray, 50, carsArray[i], carsArray[i + 1] + 1) != true &&
						carsArray[i + 1] < 19)
						moveCarUp(carsArray[i], carsArray[i + 1]);
				}
				else if (flags[i / 2] == "down")
				{
					if (checkExistence(buildingArray, 154, carsArray[i], carsArray[i + 1] - 1) != true &&
						checkExistence(obstaclesArray, 14, carsArray[i], carsArray[i + 1] - 1) != true &&
						checkExistence(passengersArray, 10, carsArray[i], carsArray[i + 1] - 1) != true &&
						taxiExists(carsArray[i], carsArray[i + 1] - 1) != true &&
						checkExistence(carsArray, 50, carsArray[i], carsArray[i + 1] - 1) != true &&
						carsArray[i + 1] > 0)
						moveCarDown(carsArray[i], carsArray[i + 1]);
				}
			}
		}
	}


	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(speed, AutoCarMovement, 0);
}
void swapElements(int array[], int fromIndex, int toIndex)
{
	int temp = array[fromIndex];
	array[fromIndex] = array[toIndex];
	array[toIndex] = temp;
}
void swapElementsString(string array[], int fromIndex, int toIndex)
{
	string temp = array[fromIndex];
	array[fromIndex] = array[toIndex];
	array[toIndex] = temp;
}
void sortArrayDescending(int array[], int size, string array2[])
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j <= (size - 2); j++)
		{
			if (array[j] < array[j + 1])
			{
				swapElements(array, j, j + 1);
				swapElementsString(array2, j, j + 1);
			}
		}
	}
}
void readHighScores(int scores[], string names[])
{
	int counter = 0;
	ifstream in_file;
	in_file.open("HighScores.txt");
	string readText;
	while (!in_file.eof())
	{

		counter++;
		getline(in_file, readText);
		if (readText == "")
		{
			continue;
		}
		if (counter <= 10)
		{
			names[counter - 1] = readText;
		}
		else if (counter <= 20)
		{
			scores[counter - 11] = stoi(readText);
		}
	}
}
void drawBoard();//Draws white lines on roads and a horizontal line to seperate the score display.
//Functions that draw base object(Person,Tree etc)
void drawTree(int x, int y)
{
	DrawLine(x + 0.5, y + 0.2, x + 0.5, y + 0.7, 9, colors[BROWN]);
	DrawCircle(x + 0.5, y + 0.7, 0.3, colors[GREEN]);

}
void drawPerson(int x, int y)
{
	//Head
	DrawCircle((float)x + 0.5, (float)y + 0.8, 0.1, colors[BLACK]);
	//Body
	DrawLine((float)x + 0.5, (float)y + 0.8, (float)x + 0.5, (float)y + 0.4, 2, colors[BLACK]);
	//Arm 1(Left)
	DrawLine((float)x + 0.5, (float)y + 0.6, (float)x + 0.3, (float)y + 0.4, 2, colors[BLACK]);
	//Arm 2(Right)
	DrawLine((float)x + 0.5, (float)y + 0.6, (float)x + 0.7, (float)y + 0.4, 2, colors[BLACK]);
	//Leg 1(Left)
	DrawLine((float)x + 0.5, (float)y + 0.4, (float)x + 0.3, (float)y, 2, colors[BLACK]);
	//Leg 2(Right)
	DrawLine((float)x + 0.5, (float)y + 0.4, (float)x + 0.7, (float)y, 2, colors[BLACK]);
	//
	glutPostRedisplay();
}
void drawCarHorizontal(int x, int y, int color) //When car is moving right or left
{
	DrawRoundRect(x + 0.1, y + 0.2, 0.8, 0.8, colors[color], 0.2);
	//Front windshield
	DrawLine(x + 0.7, y + 0.8, x + 0.7, y + 0.4, 8, colors[BLACK]);
	//Back shield
	DrawLine(x + 0.3, y + 0.8, x + 0.3, y + 0.4, 8, colors[BLACK]);
	//Wheel 1(Right bottom)
	DrawLine(x + 0.6, y + 0.2, x + 0.8, y + 0.2, 6, colors[BLACK]);
	//Wheel 2(Right top )
	DrawLine(x + 0.6, y + 1, x + 0.8, y + 1, 6, colors[BLACK]);
	//Wheel 3(Left bottom)
	DrawLine(x + 0.2, y + 0.2, x + 0.4, y + 0.2, 6, colors[BLACK]);
	//Wheel 4(Left top)
	DrawLine(x + 0.2, y + 1, x + 0.4, y + 1, 6, colors[BLACK]);
}
void drawCarVertical(int x, int y, int color)
{
	DrawRoundRect(x + 0.2, y, 0.6, 1, colors[color], 0.2);
	//Front windshield
	DrawLine(x + 0.35, y + 0.7, x + 0.65, y + 0.7, 8, colors[BLACK]);
	////Back shield
	DrawLine(x + 0.35, y + 0.3, x + 0.65, y + 0.3, 8, colors[BLACK]);
	//Wheel 1(Left top)
	DrawLine(x + 0.2, y + 0.5, x + 0.2, y + 0.8, 6, colors[BLACK]);
	//Wheel 2(Right top )
	DrawLine(x + 0.8, y + 0.5, x + 0.8, y + 0.8, 6, colors[BLACK]);
	//Wheel 3(Left bottom)
	DrawLine(x + 0.2, y + 0.1, x + 0.2, y + 0.4, 6, colors[BLACK]);
	////Wheel 4(Left top)
	DrawLine(x + 0.8, y + 0.1, x + 0.8, y + 0.4, 6, colors[BLACK]);
} //When car is moving vertically.
void drawCube(int x, int y)
{
	DrawLine(x + 0.1, y + 0.6, x + 0.5, y + 0.4, 3, colors[BLACK]); //Top diagonal

	//Used to color between faces
	DrawLine(x + 0.1, y + 0.5, x + 0.5, y + 0.3, 5, colors[FIREBRICK]);
	DrawLine(x + 0.1, y + 0.4, x + 0.5, y + 0.2, 5, colors[FIREBRICK]);
	DrawLine(x + 0.1, y + 0.3, x + 0.5, y + 0.1, 5, colors[FIREBRICK]);
	//

	DrawLine(x + 0.1, y + 0.2, x + 0.5, y, 3, colors[BLACK]); //Bottom Diagonal

	DrawLine(x + 0.1, y + 0.6, x + 0.1, y + 0.2, 3, colors[BLACK]); //Top to bottom line joining start of diagonals

	DrawLine(x + 0.5, y + 0.4, x + 0.5, y, 5, colors[BLACK]); //Top to bottom line joining end of diagonals

	DrawLine(x + 0.1, y + 0.6, x + 0.5, y + 0.8, 3, colors[BLACK]); //First line of top face


	DrawLine(x + 0.5, y + 0.4, x + 0.9, y + 0.6, 3, colors[BLACK]); //Second line of top face

	DrawLine(x + 0.9, y + 0.6, x + 0.9, y + 0.2, 5, colors[BLACK]); //Line from top face to bottom

	DrawLine(x + 0.5, y + 0.8, x + 0.9, y + 0.6, 3, colors[BLACK]); //Line joining first and second line.

	DrawLine(x + 0.5, y, x + 0.9, y + 0.2, 3, colors[BLACK]); //Line creating bottom of right face.
	//To color
	DrawLine(x + 0.5, y + 0.1, x + 0.9, y + 0.3, 5, colors[FIREBRICK]);
	DrawLine(x + 0.5, y + 0.2, x + 0.9, y + 0.4, 5, colors[FIREBRICK]);
	DrawLine(x + 0.5, y + 0.3, x + 0.9, y + 0.5, 5, colors[FIREBRICK]);
	//
}
//Checks existence of various objects(obstacles,buildings,passengers) on specified x,y coordinates.
bool checkExistence(int array[]/*Array containing x,y coordinates to check against*/,
	int size/*Size of array*/,
	float x, float y,
	bool closeBy /*Should check close by coordinates for existence too?.*/)
{
	for (int i = 0; i < size; i += 2)
	{
		int arrayX = array[i];
		int arrayY = array[i + 1];
		if (check_double(x, arrayX) && check_double(y, arrayY))
		{
			return true;
		}
		else if (closeBy && (abs(x - arrayX) < 2 && abs(y - arrayY) < 2)) // Checks for existence of close by objects too.
		{
			return true;
		}
	}
	return false;
}
//Checks if color already exists in color array(To remove duplicate colors). 
bool colorExists(int color)
{
	for (int i = 0; i < 10; i++)
	{
		if (randomColorArray[i] == color)
			return true;
	}
	return false;
}
//Checks if taxi exists on specified x,y coordinates.
bool taxiExists(float x, float y)
{
	if (check_double(x, taxiStartXAxis) && check_double(y, taxiStartYAxis))
	{
		return true;
	}
	return false;
}
//Checks if passenger is adjacent to specified x,y. (used in picking up people.)
bool passengerAdjacent(int x, int y)
{
	for (int i = 0; i < 10; i += 2)
	{
		int passengerX = passengersArray[i];
		int passengerY = passengersArray[i + 1];
		if ((x + 1 == passengerX && y == passengerY) /*Right side*/
			|| (x - 1 == passengerX && y == passengerY) /*Left Side*/
			|| (x == passengerX && y + 1 == passengerY) /*Top side*/
			|| (x == passengerX && y - 1 == passengerY) /*Bottom Side*/
			|| (x - 1 == passengerX && y + 1 == passengerY) /*Left  Top Side*/
			|| (x + 1 == passengerX && y + 1 == passengerY) /*Right  Top Side*/
			|| (x - 1 == passengerX && y - 1 == passengerY) /*Left  Bottom Side*/
			|| (x + 1 == passengerX && y - 1 == passengerY) /*Right Bottom Side*/)
		{
			return true;
		}
	}
	return false;
}
//Replaces certain x,y coordinates with random non-interfering coordinates.
void replaceXYCoordinates(int array[], int toReplaceX, int toReplaceY, int size) /* Function finds specified x y coordinates in given array and replaces with non-conflicting random values*/
{
	int x, y;
	for (int i = 0; i < size; i += 2)
	{
		if (array[i] == toReplaceX && array[i + 1] == toReplaceY)
		{
			do {
				x = rand() % 20;
				y = rand() % 20;
			} while (checkExistence(buildingArray, 154, x, y, true) || checkExistence(obstaclesArray, 14, x, y, true) || checkExistence(carsArray, 50, x, y, true) || checkExistence(passengersArray, 14, x, y, true) || taxiExists(x, y) || (abs(array[i - 2] - x) < 8));
			array[i] = x;
			array[i + 1] = y;
			break;
		}
	}
}
//Generate drop location for a passenger after he is picked up.
void generateDropLocation(int pickedupX, int pickedupY)
{
	int x, y;
	do
	{
		x = rand() % 20;
		y = rand() % 20;
	} while (checkExistence(buildingArray, 154, x, y)
		|| checkExistence(obstaclesArray, 14, x, y)
		|| checkExistence(passengersArray, 10, x, y)
		|| taxiExists(x, y)
		|| (x == pickedupX && y == pickedupY)  //Drop off location is not same as pickup location
		|| (abs(pickedupX - x) < 5)); //Drop off location is sufficiently far away from the pickup location.
	currentDropLocationX = x;
	currentDropLocationY = y;
};
//Generates random colors(doesn't generate shades of yellow, red or white.
void generateRandomColors()
{
	for (int i = 0; i < 15; i++)
	{
		do {
			randomColorArray[i] = rand() % 140;
		} while (
			colorExists(randomColorArray[i] ||
				/*Background colors*/
				randomColorArray[i] == 137 ||
				randomColorArray[i] == 138 ||
				randomColorArray[i] == 125 ||
				randomColorArray[i] == 123 ||
				randomColorArray[i] == 92 ||
				randomColorArray[i] == 110 ||
				/*Yellow and red values */
				randomColorArray[i] == 1 ||
				randomColorArray[i] == 0 ||
				randomColorArray[i] == 23 ||
				randomColorArray[i] == 24 ||
				randomColorArray[i] == 29 ||
				randomColorArray[i] == 99 ||
				randomColorArray[i] == 100 ||
				randomColorArray[i] == 5 ||
				randomColorArray[i] == 8 ||
				randomColorArray[i] == 13 ||
				randomColorArray[i] == 86 ||
				randomColorArray[i] == 87
			));
	}
}
//Generate random coordinates to draw objects.
void generateRandomCoordinates(int array[], int size)
{
	int x, y;
	for (int i = 0; i < size; i += 2)
	{
		do {
			x = rand() % 20;
			y = rand() % 20;
		} while (checkExistence(buildingArray, 154, x, y, true) || checkExistence(obstaclesArray, 14, x, y, true) || checkExistence(carsArray, 50, x, y, true) || checkExistence(passengersArray, 10, x, y, true) || taxiExists(x, y));
		array[i] = x;
		array[i + 1] = y;
	}
}
void generateRandomCoordinatesForBuilding(int array[], int size)
{
	int x, y;
	for (int i = 0; i < size; i += 2)
	{
		do {
			x = rand() % 20;
			y = rand() % 20;
		} while (taxiExists(x, y) ||x<2 ||x>17 ||y<2 || y>17);
		array[i] = x;
		array[i + 1] = y;
	}
}


//Functions used to draw final objects on canvas.
void drawTaxi()
{
	float yellowColor[] = { 1.0,1.0,0.0,1.0 };
	//Windshield
	DrawCircle(taxiStartXAxis + 0.5, taxiStartYAxis + 0.7, 0.3, yellowColor);
	//Body
	DrawRoundRect(taxiStartXAxis, taxiStartYAxis + 0.2, 1, 0.5, yellowColor, 0.2);
	//First wheel
	DrawCircle((float)taxiStartXAxis + 0.3, (float)taxiStartYAxis + 0.2, 0.1, colors[BLACK]);
	//Second wheel
	DrawCircle((float)taxiStartXAxis + 0.7, (float)taxiStartYAxis + 0.2, 0.1, colors[BLACK]);
	//
	glutPostRedisplay();
}
void drawBuildings()
{
	for (int i = 0; i < 154; i += 2)
	{
		int x = buildingArray[i];
		int y = buildingArray[i + 1];
		DrawSquare(x, y, 2, colors[BLACK]);
	}
	glutPostRedisplay();
}
void drawObstacles()
{
	int x, y;
	for (int i = 0; i < 8; i += 2)
	{
		x = obstaclesArray[i];
		y = obstaclesArray[i + 1];
		drawTree(x, y);
	}
	for (int i = 8; i < 14; i += 2)
	{
		x = obstaclesArray[i];
		y = obstaclesArray[i + 1];
		drawCube(x, y);
	}
	glutPostRedisplay();
}
void drawPassengers()
{
	int x, y;
	for (int i = 0; i < 10; i += 2)
	{
		x = passengersArray[i];
		y = passengersArray[i + 1];
		drawPerson(x, y);
	}
	glutPostRedisplay();
}
void drawCars()
{
	int x, y;
	for (int i = 0; i < 50; i += 2)
	{
		x = carsArray[i];
		y = carsArray[i + 1];
		if (x != -1)
			if (flags[i / 2] == "right" || flags[i / 2] == "left")
				drawCarHorizontal(x, y, randomColorArray[i / 2]);
			else
				drawCarVertical(x, y, randomColorArray[i / 2]);
	}
	glutPostRedisplay();
}
void drawDropLocation(int x, int y)
{
	DrawSquare(x, y, 2, colors[GREEN]);
}
void drawTaxiHorizontal()
{
	float myYellow[] = { 1.0,1.0,0.0,0.0 };
	if (taxiColor == "yellow")
	{
		DrawRoundRect(taxiStartXAxis + 0.1, taxiStartYAxis + 0.2, 0.8, 0.8, myYellow, 0.2);
		//Front windshield
		DrawLine(taxiStartXAxis + 0.7, taxiStartYAxis + 0.8, taxiStartXAxis + 0.7, taxiStartYAxis + 0.4, 8, colors[BLACK]);
		//Back shield
		DrawLine(taxiStartXAxis + 0.3, taxiStartYAxis + 0.8, taxiStartXAxis + 0.3, taxiStartYAxis + 0.4, 8, colors[BLACK]);
		//Wheel 1(Right bottom)
		DrawLine(taxiStartXAxis + 0.6, taxiStartYAxis + 0.2, taxiStartXAxis + 0.8, taxiStartYAxis + 0.2, 6, colors[BLACK]);
		//Wheel 2(Right top )
		DrawLine(taxiStartXAxis + 0.6, taxiStartYAxis + 1, taxiStartXAxis + 0.8, taxiStartYAxis + 1, 6, colors[BLACK]);
		//Wheel 3(Left bottom)
		DrawLine(taxiStartXAxis + 0.2, taxiStartYAxis + 0.2, taxiStartXAxis + 0.4, taxiStartYAxis + 0.2, 6, colors[BLACK]);
		//Wheel 4(Left top)
		DrawLine(taxiStartXAxis + 0.2, taxiStartYAxis + 1, taxiStartXAxis + 0.4, taxiStartYAxis + 1, 6, colors[BLACK]);
	}
	else if (taxiColor == "red")
	{
		DrawRoundRect(taxiStartXAxis + 0.1, taxiStartYAxis + 0.2, 0.8, 0.8, colors[RED], 0.2);
		//Front windshield
		DrawLine(taxiStartXAxis + 0.7, taxiStartYAxis + 0.8, taxiStartXAxis + 0.7, taxiStartYAxis + 0.4, 8, colors[BLACK]);
		//Back shield
		DrawLine(taxiStartXAxis + 0.3, taxiStartYAxis + 0.8, taxiStartXAxis + 0.3, taxiStartYAxis + 0.4, 8, colors[BLACK]);
		//Wheel 1(Right bottom)
		DrawLine(taxiStartXAxis + 0.6, taxiStartYAxis + 0.2, taxiStartXAxis + 0.8, taxiStartYAxis + 0.2, 6, colors[BLACK]);
		//Wheel 2(Right top )
		DrawLine(taxiStartXAxis + 0.6, taxiStartYAxis + 1, taxiStartXAxis + 0.8, taxiStartYAxis + 1, 6, colors[BLACK]);
		//Wheel 3(Left bottom)
		DrawLine(taxiStartXAxis + 0.2, taxiStartYAxis + 0.2, taxiStartXAxis + 0.4, taxiStartYAxis + 0.2, 6, colors[BLACK]);
		//Wheel 4(Left top)
		DrawLine(taxiStartXAxis + 0.2, taxiStartYAxis + 1, taxiStartXAxis + 0.4, taxiStartYAxis + 1, 6, colors[BLACK]);
	}

}
void drawTaxiVertical()
{
	float myYellow[] = { 1.0,1.0,0.0,0.0 };
	if (taxiColor == "yellow")
	{
		DrawRoundRect(taxiStartXAxis + 0.2, taxiStartYAxis, 0.6, 1, myYellow, 0.2);
		//Front windshield
		DrawLine(taxiStartXAxis + 0.35, taxiStartYAxis + 0.7, taxiStartXAxis + 0.65, taxiStartYAxis + 0.7, 8, colors[BLACK]);
		////Back shield
		DrawLine(taxiStartXAxis + 0.35, taxiStartYAxis + 0.3, taxiStartXAxis + 0.65, taxiStartYAxis + 0.3, 8, colors[BLACK]);
		//Wheel 1(Left top)
		DrawLine(taxiStartXAxis + 0.2, taxiStartYAxis + 0.5, taxiStartXAxis + 0.2, taxiStartYAxis + 0.8, 6, colors[BLACK]);
		//Wheel 2(Right top )
		DrawLine(taxiStartXAxis + 0.8, taxiStartYAxis + 0.5, taxiStartXAxis + 0.8, taxiStartYAxis + 0.8, 6, colors[BLACK]);
		//Wheel 3(Left bottom)
		DrawLine(taxiStartXAxis + 0.2, taxiStartYAxis + 0.1, taxiStartXAxis + 0.2, taxiStartYAxis + 0.4, 6, colors[BLACK]);
		////Wheel 4(Left top)
		DrawLine(taxiStartXAxis + 0.8, taxiStartYAxis + 0.1, taxiStartXAxis + 0.8, taxiStartYAxis + 0.4, 6, colors[BLACK]);
	}
	else if (taxiColor == "red")
	{
		DrawRoundRect(taxiStartXAxis + 0.2, taxiStartYAxis, 0.6, 1, colors[RED], 0.2);
		//Front windshield
		DrawLine(taxiStartXAxis + 0.35, taxiStartYAxis + 0.7, taxiStartXAxis + 0.65, taxiStartYAxis + 0.7, 8, colors[BLACK]);
		////Back shield
		DrawLine(taxiStartXAxis + 0.35, taxiStartYAxis + 0.3, taxiStartXAxis + 0.65, taxiStartYAxis + 0.3, 8, colors[BLACK]);
		//Wheel 1(Left top)
		DrawLine(taxiStartXAxis + 0.2, taxiStartYAxis + 0.5, taxiStartXAxis + 0.2, taxiStartYAxis + 0.8, 6, colors[BLACK]);
		//Wheel 2(Right top )
		DrawLine(taxiStartXAxis + 0.8, taxiStartYAxis + 0.5, taxiStartXAxis + 0.8, taxiStartYAxis + 0.8, 6, colors[BLACK]);
		//Wheel 3(Left bottom)
		DrawLine(taxiStartXAxis + 0.2, taxiStartYAxis + 0.1, taxiStartXAxis + 0.2, taxiStartYAxis + 0.4, 6, colors[BLACK]);
		////Wheel 4(Left top)
		DrawLine(taxiStartXAxis + 0.8, taxiStartYAxis + 0.1, taxiStartXAxis + 0.8, taxiStartYAxis + 0.4, 6, colors[BLACK]);
	}

}




//Overtake function
void carOvertake()
{
	int carX, carY;
	string carDirection;
	for (int i = 0; i < 50; i += 2)
	{
		if (carsArray[i] == -1)
			continue;
		carX = carsArray[i];
		carY = carsArray[i + 1];
		carDirection = flags[i / 2];
		if (carDirection == taxiDirection)
		{
			if (carDirection == "up")
			{
				if (carX - 1 == taxiStartXAxis || carX + 1 == taxiStartXAxis)
				{
					if (carY + 1 == taxiStartYAxis)
					{
						scores[10] += 1;
					}
				}

			}
			else if (carDirection == "down")
			{
				if (carX - 1 == taxiStartXAxis || carX + 1 == taxiStartXAxis)
				{
					if (carY - 1 == taxiStartYAxis)
					{
						scores[10] += 1;
					}
				}

			}
			else if (carDirection == "left")
			{
				if (carY + 1 == taxiStartYAxis || carY - 1 == taxiStartYAxis)
				{
					if (carX - 1 == taxiStartXAxis)
					{
						scores[10] += 1;
					}
				}

			}
			else if (carDirection == "right")
			{
				if (carY + 1 == taxiStartYAxis || carY - 1 == taxiStartYAxis)
				{
					if (carX + 1 == taxiStartXAxis)
					{
						scores[10] += 1;
					}
				}

			}
		}

	}
}
//Movement taxi functions
void moveTaxiLeft(float x)
{
	if (checkExistence(buildingArray, 154, taxiStartXAxis - x, taxiStartYAxis))
	{
		scores[10] = scores[10];
	}
	//Obstacles
	else if (checkExistence(obstaclesArray, 14, taxiStartXAxis - x, taxiStartYAxis))
	{
		if (justCollided == false)
		{
			if (taxiColor == "yellow")
				scores[10] -= 4;
			else if (taxiColor == "red")
				scores[10] -= 2;
			justCollided = true;
		}
	}
	//Passengers
	else if (checkExistence(passengersArray, 10, taxiStartXAxis - x, taxiStartYAxis))
	{
		if (justCollided == false)
		{
			scores[10] -= 5;
			justCollided = true;
		}
	}
	//Cars
	else if (checkExistence(carsArray, 50, taxiStartXAxis - x, taxiStartYAxis))
	{
		if (justCollided == false)
		{
			if (taxiColor == "yellow")
				scores[10] -= 2;
			else if (taxiColor == "red")
				scores[10] -= 3;
			justCollided = true;
		}
	}
	else
	{
		taxiDirection = "left";
		taxiStartXAxis -= x;
		justCollided = false;
		verticalTaxi = false;
		carOvertake();
	}
}
void moveTaxiRight(float x)
{
	if (checkExistence(buildingArray, 154, taxiStartXAxis + x, taxiStartYAxis))
	{
		scores[10] = scores[10];
	}
	else if (checkExistence(obstaclesArray, 14, taxiStartXAxis + x, taxiStartYAxis))
	{
		if (justCollided == false)
		{
			if (taxiColor == "yellow")
				scores[10] -= 4;
			else if (taxiColor == "red")
				scores[10] -= 2;
			justCollided = true;
		}
	}
	else if (checkExistence(passengersArray, 10, taxiStartXAxis + x, taxiStartYAxis))
	{
		if (justCollided == false)
		{
			scores[10] -= 5;
			justCollided = true;
		}
	}
	else if (checkExistence(carsArray, 50, taxiStartXAxis + x, taxiStartYAxis))
	{
		if (justCollided == false)
		{
			if (taxiColor == "yellow")
				scores[10] -= 2;
			else if (taxiColor == "red")
				scores[10] -= 3;
			justCollided = true;
		}
	}
	else
	{
		taxiDirection = "right";
		taxiStartXAxis += x;
		verticalTaxi = false;
		justCollided = false;
		carOvertake();
	}
}
void moveTaxiUp(float x)
{
	if (checkExistence(buildingArray, 154, taxiStartXAxis, taxiStartYAxis + x))
	{
		scores[10] = scores[10];
	}
	else if (checkExistence(obstaclesArray, 14, taxiStartXAxis, taxiStartYAxis + x))
	{
		if (justCollided == false)
		{
			if (taxiColor == "yellow")
				scores[10] -= 4;
			else if (taxiColor == "red")
				scores[10] -= 2;
			justCollided = true;
		}
	}
	else if (checkExistence(passengersArray, 10, taxiStartXAxis, taxiStartYAxis + x))
	{
		if (justCollided == false)
		{
			scores[10] -= 5;
			justCollided = true;
		}
	}
	else if (checkExistence(carsArray, 50, taxiStartXAxis, taxiStartYAxis + x))
	{
		if (justCollided == false)
		{
			if (taxiColor == "yellow")
				scores[10] -= 2;
			else if (taxiColor == "red")
				scores[10] -= 3;
			justCollided = true;
		}
	}
	else
	{
		taxiDirection = "up";
		taxiStartYAxis += x;
		verticalTaxi = true;
		justCollided = false;
		carOvertake();
	}
}
void moveTaxiDown(float x)
{
	if (checkExistence(buildingArray, 154, taxiStartXAxis, taxiStartYAxis - x))
	{
		scores[10] = scores[10];
	}
	else if (checkExistence(obstaclesArray, 14, taxiStartXAxis, taxiStartYAxis - x))
	{
		if (justCollided == false)
		{
			if (taxiColor == "yellow")
				scores[10] -= 4;
			else if (taxiColor == "red")
				scores[10] -= 2;
			justCollided = true;
		}

	}
	else if (checkExistence(passengersArray, 10, taxiStartXAxis, taxiStartYAxis - x))
	{
		if (justCollided == false)
		{
			scores[10] -= 5;
			justCollided = true;
		}
	}
	else if (checkExistence(carsArray, 50, taxiStartXAxis, taxiStartYAxis - x))
	{
		if (justCollided == false)
		{
			if (taxiColor == "yellow")
				scores[10] -= 2;
			else if (taxiColor == "red")
				scores[10] -= 3;
			justCollided = true;
		}
	}
	else
	{
		taxiDirection = "down";
		justCollided = false;
		taxiStartYAxis -= x;
		verticalTaxi = true;
		carOvertake();
	}
}


//Random direction selection except previous direction.
string randomDirectionExcept(string direction)
{
	string Directions[] = { "left","right","up","down" };
	string randomDirection = direction;
	string randomSelected;
	do
	{
		randomSelected = Directions[rand() % 4];
	} while (randomSelected == randomDirection);
	return randomSelected;
}



void drawMenu1()
{
	DrawString(7, 15, "S- START", colors[RED]);
	DrawString(7, 12, "L- LEADERBOARD", colors[RED]);
	DrawString(7, 9, "Q- QUIT", colors[RED]);
}
void drawMenu2()
{
	DrawString(7, 15, "R- RED TAXI", colors[RED]);
	DrawString(7, 12, "Y- YELLOW TAXI", colors[RED]);
	DrawString(7, 9, "ENTER- RANDOM TAXI", colors[RED]);
}
void drawEnd()
{
	DrawString(7, 15, "Your Score: " + to_string(score), colors[RED]);
	if (score >= 100)
		DrawString(7, 14, "You Win!", colors[RED]);
	else
		DrawString(7, 14, "You Lose!", colors[RED]);
	DrawString(7, 12, "Q- Quit", colors[RED]);
}

void drawLeaderBoard()
{
	DrawString(7, 18, "LEADERBOARD", colors[RED]);
	DrawString(3, 16, "No.", colors[RED]);	DrawString(6, 16, "Name", colors[RED]); DrawString(12, 16, "Score", colors[RED]);
	int lineHeightY = 15;
	for (int i = 0; i < 10; i++)
	{
		string nameandScore = to_string(i + 1) + ".       " + names[i] + "   " + to_string(scores[i]);
		if (names[i] != "")
		{
			lineHeightY--;
			DrawString(3, lineHeightY, to_string(i + 1), colors[RED]);	DrawString(6, lineHeightY, names[i], colors[RED]); DrawString(12, lineHeightY, to_string(scores[i]), colors[RED]);

		}
	}
}
void drawNameInput()
{
	DrawString(7, 15, "ENTER YOUR NAME", colors[RED]);
	DrawString(7, 14, names[10], colors[BLACK]);
}

void GameDisplay()/**/ {
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0.5/*Red Component*/, 0.5,	//148.0/255/*Green Component*/,
		0.5/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors
	string currentScore = "Score: " + to_string(scores[10]);
	string currentTime = "Time: " + to_string(seconds);

	if (displayThisScreen == "menu1")
		drawMenu1();
	else if (displayThisScreen == "menu2")
		drawMenu2();
	else if (displayThisScreen == "name")
		drawNameInput();
	else if (displayThisScreen == "game")
	{//Draw Score
		DrawString(9, 20.2, currentScore, colors[RED]);
		DrawString(15, 20.2, currentTime, colors[RED]);
		//Draws lines on board
		drawBoard();
		//Draws obstacles(Trees)
		drawObstacles();
		//Draws potential passengers
		drawPassengers();
		//Draws buildings(black squares)
		drawBuildings();
		//Draws Green Square DropLocation
		drawDropLocation(currentDropLocationX, currentDropLocationY);
		//Draw Other Cars
		drawCars();
		//Draws user taxi
		if (verticalTaxi)
			drawTaxiVertical();
		else
			drawTaxiHorizontal();
		//

	}
	else if (displayThisScreen == "end")
	{
		drawEnd();
	}
	else if (displayThisScreen == "leaderboard")
	{
		drawLeaderBoard();
	}
	glutSwapBuffers(); // do not modify this line...
}



/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (displayThisScreen == "game")
	{
		if (key == GLUT_KEY_LEFT && taxiStartXAxis > 0)
		{
			moveTaxiLeft(taxiSpeed);
		}
		else if (key == GLUT_KEY_RIGHT && taxiStartXAxis < 19)
		{
			moveTaxiRight(taxiSpeed);
		}
		else if (key == GLUT_KEY_UP && taxiStartYAxis < 19)
		{
			moveTaxiUp(taxiSpeed);
		}
		else if (key == GLUT_KEY_DOWN && taxiStartYAxis > 0)
		{
			moveTaxiDown(taxiSpeed);
		}
		/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
		* this function*/

		glutPostRedisplay();
	}





}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 113/* Q key ASCII*/) {
		if (displayThisScreen != "name")
			exit(1); // exit the program when escape key is pressed.
	}
	if (key == 's')
	{
		displayThisScreen == "menu1" ? displayThisScreen = "menu2" : displayThisScreen;
	}
	if (key == 'l')
	{
		displayThisScreen == "menu1" ? displayThisScreen = "leaderboard" : displayThisScreen;
	}
	if (key == 'r')
	{
		if (displayThisScreen == "menu2")
		{
			taxiColor = "red";
			taxiSpeed = 0.5;
			displayThisScreen = "name";
			key = NULL;
		}

	}
	if (key == 'y')
	{
		if (displayThisScreen == "menu2")
		{
			taxiColor = "yellow";
			taxiSpeed = 1;
			displayThisScreen = "name";
			key = NULL;
		}
	}
	if (key == 13 /*Enter key ascii*/)
	{
		if (displayThisScreen == "menu2")
		{
			taxiColor = taxiColors[rand() % 2];
			if (taxiColor == "yellow")
			{
				taxiSpeed = 1.0;
			}
			else if (taxiColor == "red")
			{
				taxiSpeed = 0.5;
			}
			displayThisScreen = "name";
			key = NULL;
		}
		else if (displayThisScreen == "name")
		{
			displayThisScreen = "game";
		}

	}
	if (displayThisScreen == "name")
	{
		if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z'))
			names[10].push_back(key);
	}

	if (key == 32 /*Spacebar to pick up passenger */) {
		//Drop
		if (taxiStartXAxis == currentDropLocationX && taxiStartYAxis == currentDropLocationY)
		{
			numberOfPassengersDropped++;
			scores[10] += 10;
			if (numberOfPassengersDropped % 2 == 0 && numberOfPassengersDropped < 20)
			{
				addCar();
				//Update speed
				speed -= 100;
			}
			//Next two lines erase drop location since passenger has been dropped.
			currentDropLocationX = -1;
			currentDropLocationY = -1;
			passengerInCar = false; //Dropped passenger.
		}
		//Pickup
		else if (passengerAdjacent(taxiStartXAxis, taxiStartYAxis) && passengerInCar == false)
		{
			for (int i = 0; i < 10; i += 2)
			{
				int x = passengersArray[i];
				int y = passengersArray[i + 1];

				if ((x + 1 == taxiStartXAxis && y == taxiStartYAxis) || (x - 1 == taxiStartXAxis && y == taxiStartYAxis) || (x == taxiStartXAxis && y + 1 == taxiStartYAxis) || (x == taxiStartXAxis && y - 1 == taxiStartYAxis))
				{
					replaceXYCoordinates(passengersArray, x, y, 10); //Erases picked passenger and spawns new passenger.
					generateDropLocation(x, y); //Passed picked up location as parameter so drop location isn't same as pickup location.
					passengerInCar = true;
				}
			}
		}
	}

	glutPostRedisplay();
}






void randomizeEveryFlag()
{
	for (int i = 0; i < 20; i++)
	{
		flags[i] = randomDirectionExcept(flags[i]);
	}
}


void completelyRandomizeDirection(int m)
{
	if (displayThisScreen == "game")
	{
		if (speed2 < 300)
			speed2 = 300;
		randomizeEveryFlag();
	}
	//// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(speed2, completelyRandomizeDirection, 0);
}


void countTime(int m)
{
	if (displayThisScreen == "game")
		seconds++;


	bool end = true;
	if (seconds == 180 && end)
	{
		displayThisScreen = "end";
		score = scores[10];
		addHighScore(scores, names);
		end = false;
	}
	glutTimerFunc(1000, countTime, 0);
}



void MouseClicked(int button, int state, int x, int y) {

	glutPostRedisplay();
}
int main(int argc, char* argv[]) {


	int width = 800, height = 600; // i have set my window size to be 800 x 600

	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Rush Hour"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...


	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters

	glutMouseFunc(MouseClicked);

	//Generating random coordinates here, calling function here so it doesn't get recalled due to glutPostRedisplay();
/*generateRandomObstacleCoordinates();*/
	generateRandomCoordinatesForBuilding(buildingArray, 154);
	generateRandomCoordinates(obstaclesArray, 14);
	generateRandomCoordinates(passengersArray, 10);

	/*generateRandomPassengerCoordinates();*/
	generateRandomCoordinates(carsArray, 10); //Size 2 as we initially only need to generate a single coordinate for the first car.
	generateRandomColors();
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, AutoCarMovement, 0);
	glutTimerFunc(10000.0, completelyRandomizeDirection, 0);
	glutTimerFunc(1000, countTime, 0);
	//
	// 
	//File handling
	readHighScores(scores, names);
	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}

/*
 * our gateway main function
 * */
#endif /* RushHour_CPP_ */
