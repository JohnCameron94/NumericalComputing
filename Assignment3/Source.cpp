/**************************************************************************************************************************************
												FILE HEADER 
File: Source.cpp
Version: 1.0
Student: Johnathon Cameron
Student # : 040725586
Course: Numerical Computing
Course # : CST_8233_300 (Lecture)
Lab # : 302
Assignment #: Assignment 3
Assignment Name: Eulers,Runge-Kutta approx. Method
Professor: Abdullah Kadri
Due Date: 2019-12-06
Submission Date: 2019-11-26
Description:Program created to calculate either using the eulers method or Runge-Kutta method to calculate the approximation of the y point at any x point.
using this equation :  0.1 * cos(4 * x) + 0.2 * sin(4 * x) + 2.9 * exp(-2 * x)
*****************************************************************************************************************************************/
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#define f(x,y) (0.1 * cos(4 * x)) + (0.2 * sin(4 * x)) + (2.9 * exp(-2 * x))/*macro defining the equation f(x,y)*/
using namespace std;/*using std namespace*/

/*********************************************************************************************************************
											FUNCTION HEADER
Function : df
Author: Johnathon Cameron
Function in : double,double
Function out :double
Purpose: Calculate the differential approximation cos(4*x) - 2*y
**********************************************************************************************************************/
double df(double x, double y) {
	return cos(4*x) - (2*y);
}
/*********************************************************************************************************************
											FUNCTION HEADER
Function : print_table_columns
Author: Johnathon Cameron
Function in : none
Function out : none
Purpose: Output function used to display the table headers (column headers) of the calculation steps.
**********************************************************************************************************************/
void print_table_columns() {
	cout<< "Time(seconds)" << setw(25) << "Exact Temp(C)" << setw(30) << "Estimated Temp(C)" << setw(27) << "Percentage Error(%)" <<endl;
}
/*********************************************************************************************************************
											FUNCTION HEADER
Function : percentage_error
Author: Johnathon Cameron
Function in : double,double
Function out : double
Purpose: Used to calculate the percentage error of both the approx calculation and the exact calculation for y
**********************************************************************************************************************/
double percentage_error(double approx, double exact) {
	//equation to calculate percentage
	return ((exact - approx) / approx) * 100;
}

/*********************************************************************************************************************
											FUNCTION HEADER
Function : eulers_method
Author: Johnathon Cameron
Function in : none
Function out : none
Purpose: Used to calculate the eulers method.
**********************************************************************************************************************/
void eulers_method(double h) {
	/*slope equation : cos(4*x) - (2*y)
	  x0= initial value of x
	  y0= initial value of y at x =0
	  yn= new value of y*/
	double slope=0, x0=0, y0=3, xn=0, yn=0;

	//temporary for increment


	//Display the table columns
	print_table_columns();
	//loop and perform calculation
	int n = 2 / h;

		//perform calculation
	for(int i = 0 ; i < n ; i ++){
			
		//slope
		slope = df(x0,y0);
		//y = previous y + h * slope
		yn = y0 + (h * (slope));
		//setting new y to previous
		y0 = yn;
		//incrementing h
		x0 += h;
		//print
		cout << setprecision(1) << fixed << x0 << setw(27) << setprecision(3) << fixed << f(x0, y0) << setw(26) << y0 << setw(26) << setprecision(2) << fixed << abs(percentage_error(f(x0, y0), y0)) << endl;
	}
}

/*********************************************************************************************************************
											FUNCTION HEADER
Function : runge_method
Author: Johnathon Cameron
Function in : none
Function out : int
Purpose: Function used to calculate the Runge-Kutta method.
**********************************************************************************************************************/
void runge_method(double h) {
	//4th order        init x0  init y0
	double k1, k2, k3, k4,x0=0,y0=3;
	int n = 2 / h;
	
	// Iterate for number of iterations 
	print_table_columns();
	for (int i = 1; i <= n; i++)
	{
		//Kutta range formula to find y
		k1 = h * df(x0, y0);
		k2 = h * df(x0 + 0.5 * h, y0 + 0.5 * k1);
		k3 = h * df(x0 + 0.5 * h, y0 + 0.5 * k2);
		k4 = h * df(x0 + h, y0 + k3);

		// next value of y
		y0 = y0 + (1.0 / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4);;

		// next x value 
		x0 = x0 + h;
		//print in table format
		cout << setprecision(1) << fixed << x0 << setw(27) << setprecision(3) << fixed << f(x0, y0) << setw(26) << y0 << setw(26) << setprecision(2) << fixed << abs(percentage_error(f(x0, y0), y0)) << endl;
	}
}
/*********************************************************************************************************************
											FUNCTION HEADER
Function : sub_menu
Author: Johnathon Cameron
Function in : none
Function out : double
Purpose: Function that prompts the user to enter the step size (h) of the ODE calculation. Step size entry must be :
																												-0.8
																												-0.2
																												-0.05
**********************************************************************************************************************/
double sub_menu() {
	//h
	double h;
	//boolean to check for valid input
	bool valid = false;

	//do atleast once
	do {
		//prompte user to enter step size
		cout << "Choose step size \"h\" (0.8,0.2,0.05)" << endl;
		cout << ">>"; cin >> h;
		//if user enters any none digit
		if (std::cin.fail()) {
			cout << "Invalid Entry, must enter number (0.8,0.2,0.05)" << endl;
			cin.clear();
			cin.ignore();
		//if user enters any number not within range
		}else if(h == 0.8 || h== 0.2 || h == 0.05){
			valid = true;
			
		//if invalid entry
		}else {
			cout << "Error Valid numbers are: 0.8,0.2 or 0.05" << endl;
			cin.ignore();
			cin.clear();
		}
			

	} while (!valid);//while not valid

	//retun step size
	return h;
}
/*********************************************************************************************************************
											FUNCTION HEADER
Function : main_menu
Author: Johnathon Cameron
Function in : N/A
Function out : bool
Purpose:main menu function used to prompt the user to the main menu and request a choice of which method the user would 
like to use to calculate the ODE. Or quit program.
**********************************************************************************************************************/
bool main_menu() {

	int response;
	bool RUNNING = true;
	
	//do atleast once until user enters correct input
	do {
		//loop while input is invalid
		cout << ">> Choose the method for solving ODE:\n1. Euler's Method\n2. Runge-Kutta 4th Order Method\n3. Quit Program " << endl;
		cout << ">>"; cin >> response;
		//if invalid input, clear istream
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
		}
		
	} while (cin.fail());
		
		//Main Menu switch case
		switch (response) {
			case 1: eulers_method(sub_menu()); break; /*eulers method calculation*/
			case 2: runge_method(sub_menu()); break;/*runge-kutta method*/
			case 3:return false;/*Quit Program*/
			default: cout << "Error...Invalid Option" << endl;/*Default invalid input case*/
		
		}

	return true;
}
/*********************************************************************************************************************
											FUNCTION HEADER
Function : run
Author: Johnathon Cameron
Function in : none
Function out : none
Purpose: Function used to run the program into a loop until the user decides to exit the program
**********************************************************************************************************************/
void run() {
	//bool
	bool RUNNING = true;
	//until user quits
	while (RUNNING) {
		RUNNING = main_menu();
	}
}
/*********************************************************************************************************************
											FUNCTION HEADER
Function : main
Author: Johnathon Cameron
Function in : none
Function out : int
Purpose: main function  calling run function, to initialize and run program, until user wishes to quit.
**********************************************************************************************************************/
int main() {
	//run program
	run();
	return 0;
}
