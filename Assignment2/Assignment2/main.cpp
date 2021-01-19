/**************************************************************************************************************************************
				FILE HEADER / COVER HEADER
File: main.cpp
Version: 1.0
Student: Johnathon Cameron
Student # : 040725586
Course: Numerical Computing
Course # : CST_8233_300 (Lecture)
Lab # : 302
Assignment #: Assignment 2
Assignment Name: Maclaurin Series Approximation
Professor: Abdullah Kadri
Due Date: 2019-11-15
Submission Date: 2019-11-14

Description: To find the Maclaurin series approximation with t(seconds) within a range of 0.0 to 2.0 and the series of terms between 0 and 5
(6th term to find the truncation if user enters 5 terms. Formula D(t) = e^-tcos(t).
*****************************************************************************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
using namespace std; /*Global Namespace*/

/********~~~~~~~~~~GLOBAL VARIABLES ~~~~~~~********/
vector <double> tranCount;
vector <int> years;
vector<string> name;
vector<double> tranFitted;
double a1 = 0;
double a0 = 0;
/*************************************************/


/*********************************************************************************************************************
Function : createTranFittedColumn()
Author: Johnathon Cameron
Function in : none
Function out : int
Purpose: Create the fitted data for the non linear equation
**********************************************************************************************************************/
void createTranFittedColumn() {
	//loop through the unfitted data and create the fitted data
	for (unsigned int i = 0; i < years.size(); i++) {
		//push fitted data to the back of vector
		tranFitted.push_back(log(tranCount[i]));
	}
}
/*********************************************************************************************************************
Function : transistor_count()
Author: Johnathon Cameron
Function in : int year
Function out : double transistor_count
Purpose: calculate the transitor count from the transistor_count = a * exp(b(year-1970)
**********************************************************************************************************************/
double transistor_count(int  year) {
	//calculate result;
	double transistor_count = a0 * exp(a1 * (year - 1970));
	return transistor_count;
}
/*********************************************************************************************************************
Function : calculate_rate()
Author: Johnathon Cameron
Function in : int year
Function out : return double
Purpose: used to calculate the rate increase transistor/year
**********************************************************************************************************************/
double calculate_rate(int year) {
	double rate = a0 * a1 * exp(a1 * (year - 1970));
	return rate;
}
/*********************************************************************************************************************
Function : linear_regression_fit()
Author: Johnathon Cameron
Function in : none
Function out : none
Purpose: Calculation  of the equation y(tranCount) =  a0 + a1x. Calculated the linear regression fit equation
for the data from the file data.txt
**********************************************************************************************************************/
void linear_regression_fit() {
	//local variables
	double  sum_t = 0, sum_zi = 0, sum_tsqrd = 0, sum_tizi = 0, sum_tt = 0, sum_y = 0;
	//creating fitted data column
	createTranFittedColumn();
	//size of vectors all equivalent
	int n = years.size();

	for (int i = 0; i < n; i++) {
		//sumation of yi
		sum_y += tranCount[i];
		//summation ti
		sum_t += years[i];
		//summation zi
		sum_zi += tranFitted[i];
		//summation tizi
		sum_tizi += years[i] * tranFitted[i];
		//sumation (ti)^2
		sum_tt += pow(years[i], 2);
	}
	//ti^2 result
	sum_tsqrd = pow(sum_t, 2);

	//~~~~~~~~~~A1~~~~~~~~~~//
	//equation n*tizi - zi * ti / n*ti^2-(ti)^2
	double numerator = (n * sum_tizi) - (sum_zi * sum_t);
	//denomitor
	double denominator = (n * sum_tt) - sum_tsqrd;
	//a1 result
	a1 = numerator / denominator;

	//result
	double result = 0;
	result = sum_zi / n - a1 * (sum_t - 1970 * n) / n;
	//store a0 answer in a0
	a0 = exp(result);
	//Print statement
	cout << "Linear Regression Fit: transistor count = " << a0 << "*expo( " << a1 << "*(year-1970)" << endl;

}
/*********************************************************************************************************************
Function : display
Author: Johnathon Cameron
Function in : none
Function out : none
Purpose: Display the data imported from the file data.txt
**********************************************************************************************************************/
void display() {
	//ouput precision set to 3
	cout.precision(3);
	//file output
	cout << "Year:" << setw(20) << "TranCount:" << setw(20) << "NAME:" << endl;
	//loop through data retrieved from file setting width to 20
	for (unsigned int i = 0; i < years.size(); i++) {
		cout << years[i] << setw(20);
		cout << scientific << tranCount[i];
		cout << setw(20) << name[i] << endl;
	}

	//display record amount
	cout << "There are " << years.size() << " records" << endl;
	//display linear regression
}
/*********************************************************************************************************************
Function : load_file()
Author: Johnathon Cameron
Function in : String for the file name
Function out : none
Purpose: Loads the data from the file and changes all the string data to double, int or string value
**********************************************************************************************************************/
bool load_file(string file) {
	bool success = false;
	//input file stream
	ifstream inFile;
	//string variables
	string line, s;
	//int value and lineCount
	double value, lineCount = 0;

	//open file inputed by the user
	inFile.open(file);
	//if file successfully opened
	if (inFile.is_open()) {

		//while it is not end of file
		while (!inFile.eof()) {

			//get file line
			getline(inFile, line);
			//input string stream
			istringstream ss(line);
			//counter
			int counter = 0;
			//get line with delimiter ','
			while (getline(ss, s, ',')) {

				//if counter is 0 then years is the first data to input
				if (counter == 0) {
					//parse to integer
					value = atof(s.c_str());
					//push to back of vector
					years.push_back(value);
					//if counter is 2 then tranCount is the third data to be inputted
				}
				else if (counter == 2) {
					//parse to integer
					value = atof(s.c_str());
					//push to back of vector
					tranCount.push_back(value);
				}
				else
					//else its the string name
					name.push_back(s);
				//increment counter
				counter++;
			}
		}
		//return true if file loaded successfully
		success = true;
		return success;
		//if ever file doesn't open
	}
	else {
		cout << "INVALID FILE NAME...or Cannot find file" << endl;
	}
	//return failed
	return success;
}
/*********************************************************************************************************************
Function : sub_menu()
Author: Johnathon Cameron
Function in : none
Function out : none
Purpose: Function used to display the sub menu to the user once he decides which data to pull from a file. Gives the
user the option to extrapolate the data from the year he/she inputs.
**********************************************************************************************************************/
void sub_menu() {
	//user input holder
	char sub_response;
	//boolean to go back to main menu
	bool backToMainMenu = false;

	//while user doesn't want to go back to main menu
	while (!backToMainMenu) {
		//user prompte holder
		int year = 0;
		//sub menu
		cout << "\nSUB-MENU \n1.Extrapolation\n2.Main Menu" << endl;
		cin >> sub_response;
		//users response
		switch (sub_response) {

		case '1':
			//prompt user for year
			cout << "Please Enter Year to extrapolate to:" << endl;
			//Make sure the data is correct
			if (cin >> year) {}
			else if (cin.fail()) {
				cout << "Invalid Year Entry";
				cin.clear();
				cin.ignore();
				break;
			}
			//calculator transistor count
			cout << "Year = " << year << endl;
			cout << "Transitor count = " << transistor_count(year) << endl;
			cout << "Rate = " << calculate_rate(year) << endl;
			break;

		case '2': backToMainMenu = true; break;
			//if user enters incorrect values
		default: cout << "Enter Valid Option" << endl;
		}
	}
}
/*********************************************************************************************************************
Function : main_menu
Author: Johnathon Cameron
Function in : none
Function out : non
Purpose: main_menu is a function meant to prompt the user to the main menu of a program and insert a txt file
in which he wants to import the data from. Takes control of the linear_regression_fit(). User cannot get to sub menu
without loading a file
**********************************************************************************************************************/
void main_menu() {
	//user response holder
	char response;
	//boolean to let user quit program when wanted
	bool quit = false;
	//file name entered by user
	string file;
	//title
	cout << "LEAST_SQUARES LINEAR REGRESSION" << endl;

	while (!quit) {
		//main menu
		cout << "MENU" << endl;
		cout << "1. Exponential Fit \n2. Quit" << endl;
		cin >> response;

		bool success = false;
		switch (response) {
			//prompt user to enter file name
		case '1':
			cout << "Please Enter Name of File: " << endl;
			cin >> file;

			//prompt the user until valid file is entered
			if (load_file(file)) {
				//display file records

				display();
				linear_regression_fit();
				//after file is loaded and calculations done user enters the sub-menu
				sub_menu();
			}
			break;

			//case to exit program
		case '2':
			cout << "Exiting Program....." << endl;
			quit = true;
			break;
			//handle invalid responses from user
		default:
			cout << "Invalid Option" << endl;
		}
	}
}
/*********************************************************************************************************************
Function : main
Author: Johnathon Cameron
Function in : none
Function out : int
Purpose: main functions handles the main menu attributes prompts the user to the main menu
**********************************************************************************************************************/
int main() {
	//prompt user to the main menu
	main_menu();
	return 0;
}