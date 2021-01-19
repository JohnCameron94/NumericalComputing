/**************************************************************************************************************************************
				FILE HEADER / COVER HEADER
File: ass1.c
Version: 1.0
Student: Johnathon Cameron
Student # : 040725586
Course: Numerical Computing
Course # : CST_8233_300 (Lecture)
Lab # : 302
Assignment #: Assignment 1
Assignment Name: Maclaurin Series Approximation
Professor: Abdullah Kadri
Due Date: 2019-09-29
Submission Date: 2019-09-28

Description: To find the Maclaurin series approximation with t(seconds) within a range of 0.0 to 2.0 and the series of terms between 0 and 5
(6th term to find the truncation if user enters 5 terms. Formula D(t) = e^-tcos(t).
*****************************************************************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*function declaration*/
int print_formatted(double,double,double,double,double);
int print_formatted_table_headers();
double calculate_exact(double);
double exact_error(double, double);
double truncation_error(double, double);
int calc_maclaurin_series(int terms, double range);

/*********************************************************************************************************************
Function : main
Author: Johnathon Cameron
Function in : none
Function out : int
Purpose: main function that handles user interaction
User interaction: User must select a valid option, or else will get reprompte.
User must also follow the condition stated by the console when prompte to enter in the amount of series
or the range of t (no more then 5 series and must be greater then 0 and range between 0.0 and 2.0)
**********************************************************************************************************************/

int main() {

	/*While user doesn't quit running is true*/
	int RUNNING = 1;

	while (RUNNING) {

		int options = 0, terms = 0;
		double range = 0.0;
		printf("Evaluate the Maclaurin Series approximation to exp(-t)*cost(t)\n");


		printf("1.Evaluate the series\n2.quit");
		scanf(" %d", &options);

		/*Switch case for user input*/
		switch (options) {
		case 1:
			do {
				printf("Please Enter the number of terms in the series (max 5 terms)");
				scanf(" %d", &terms);
			} while (terms < 0 || terms > 5);

			do {
				printf("Please Enter the range of t to evaluate in 10 increments(0.0<t+2.0)");
				scanf(" %lf", &range);
			} while (range < 0.0 || range > 2.0);

			calc_maclaurin_series(terms, range);
			break;

		case 2:

			RUNNING = 0;
			break;

			/*Default if user enters invalid option*/
		default:
			printf("Must Enter a valid option\n");
		}
	}

	return 0;

}


/****************************************************************************************************************************************
Function: calc_maclaurin_series
Version: 1.0
Author: Johnathon Cameron
Parameter in : int terms, double range
Function out : int 
Purpose: Calculate the maclaurin approximation to the equation D(t) = e^-tcos(t), condition statements depending on the amount of terms and the range that the user wants.
Calculates 5 values: 
						- t
						- Series

Inside other functions: 
						- Exact (use of another function called:calculate_exact(double)
						- Exact Error (%) (use of another function called : exact_error(double,double))
						- Truncation Error(%) (use of another function called : truncation_error(double,double)

*******************************************************************************************************************************************/
int calc_maclaurin_series(int terms, double range) {
	
	/*Variable declaration for calculation*/
	double t, exact, series, fTrunc, exact_err, trunc_error,count;/*count is the increment*/

	/*All values must start at 0*/
	fTrunc = 0;
	t = 0;
	exact = 0;
	series = 0;
	exact_err = 0;
	trunc_error = 0;
	count = 0;
	
	/*For the first term when t is 0*/
	series = 1;
	exact = exp((-t)) * cos(t);

	print_formatted_table_headers();
	print_formatted(t, series, exact, exact_err, trunc_error);

	for (int i = 1; i <= 10; i++) {
		/*t increment after every loop*/
		count =range / 10;
		t = t + count;

		/* switch case controlling the amount of terms, inputted by the user(int terms)*/
		switch (terms) {
		case 1:
			//D(t) = 1-t
			series = 1;
			fTrunc = -t;
			break;

		case 2:
			
			//D(t) = 1-t
			series = 1-t;
			//term 3
			fTrunc = (t * t * t) / 3;
			break;

		case 3:
			//D(t) = 1-t + (1/3t^3)
			series = 1-t + (t*t*t)/3;
			//term 4
			fTrunc = -(t * t * t * t) / 6;
			break;

		case 4:
			//D(t) = 1-t + (1/3t^3) - (1/6t^4)
			series = 1-t + (t*t*t)/3 - (t*t*t*t)/6;
			//term 5
			fTrunc = (t * t * t * t * t) / 30;
			break;
		
		case 5:
			//D(t) = 1-t + (1/3t^3) - (1/6t^4)  + (1/30t^5)
			series = 1 - t + (t * t * t) / 3 - (t * t * t * t) / 6 + (t * t * t * t * t) / 30;
			//term 7 
			fTrunc = -(t * t * t * t * t * t * t) / 630;
		}


		/*Calculation functions (other functions) */
		exact = calculate_exact(t);
		exact_err = exact_error(exact,series);
		trunc_error = truncation_error(fTrunc,series);

		print_formatted(t, series, exact, exact_err, trunc_error);
		
		
	}

	return 0;
}

/******************************************************************************************************************
Function:calculate_exact
Author:  Johnathon Cameron
Version : 1.0
Function in : double
Function out : double
Purpose: return the value of the exact value so the exact_error function
can consume as well as the calc_maclaurin_series function
*******************************************************************************************************************/
double calculate_exact(double t) {

	/*formula*/
	double exact = exp(-t)* cos(t);
	
	return exact;
}

/******************************************************************************************************************
Function: truncation_error
Version: 1.0
Author:  Johnathon Cameron
Function in: double, double
Function out : double
Purpose: Function use to return the answers to the
Exact error equation 100*(exact - series)/exact.
returns it to the calc_maclaurin_series where it is consumed.
*******************************************************************************************************************/
double exact_error(double exact, double series) {

	/*formula*/
	double exact_err = 100 * (exact - series) / exact;
	return exact_err;
}

/******************************************************************************************************************
Function: truncation_error
Version : 1.0
Author:  Johnathon Cameron
Function in: double, double
Function out: double
Purpose: Function use to return the answers to the 
truncation error equation 100*<first truncated term>/<series>.
returns it to the calc_maclaurin_series where it is consumed.
********************************************************************************************************************/
double truncation_error(double fTrunc, double series){
	
	/*Formula*/
	double trunc_err = 100 * fTrunc / series;
	return trunc_err;
}

/*******************************************************************************************************************
Function: print_formatted_table_headers
Version : 1.0
Function in: none
Function out : int
Purpose: print headers values for alignment
********************************************************************************************************************/
int print_formatted_table_headers() {
	
	printf("   t                   Series                 Exact                  Exact Error            Trunc. Error\n");

	return 0;
}

/********************************************************************************************************************
Function: print_formatted_table_headers
Version : 1.0
Author : Johnathon Cameron
Function in : none
Function out: int
Purpose : print headers values for alignment
*********************************************************************************************************************/
int print_formatted(double t, double series, double exact, double exact_error, double trunc_error) {
	
		printf("%12.3e          %12.5e           %12.5e           %12.5e           %12.5e \n", t, series, exact, exact_error, trunc_error);
		return 0;
}

