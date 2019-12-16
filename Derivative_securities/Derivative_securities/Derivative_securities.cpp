// Derivative_securities.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <numeric>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

void discount_factor(void) {

	//this method is just a general method to be used for calculating the discount factor

	double interest;
	// time in years
	double time;

	double df;

	cout << "interest rate: ";
	cin >> interest;
	interest = interest / 100;
	cout << "time in years: ";
	cin >> time;

	df = 1 / (pow((1 + interest), time));
	
	cout.precision(3);
	cout << "discount factor: " << df << endl;
}

void MVH(void) {
	/* 
	this method will be specifically aimed towards the question on the week 3 quiz regarding MVH in the 
	question we are given the standard deviation of the prices as percentages and a correlation coefficient
	*/

	/* 
	the normal equation for calculating MVH is

		y* = - cov(Ft, Pt)/ var(Ft)

	the method we will use is a bit different as it takes into account the variables we have at hand
	*/
	
	//the total size of the underlying
	double size_t;
	//size of the future contract
	double size_f;

	// the variances of the prices of both commodities
	// var_A is the variance of the main commodity in this case grape juice
	double var_A;
	double var_B;

	double correlation;

	double MVH;

	cout << "enter total size: ";
	cin >> size_t;

	cout << "enter size of the future contract: ";
	cin >> size_f;


	cout << "enter the variance of A";
	cin >> var_A;
	var_A = var_A / 100;

	cout << "enter the variance of B";
	cin >> var_B;
	var_B = var_B / 100;

	cout << "enter the correlation coefficiant: ";
	cin >> correlation;

	MVH = (size_t / size_f) * correlation * (var_B / var_A);

	MVH = round(MVH);

	cout << "The amount of futures contracts is: " << MVH << endl;

}

void swap_rates(void) {

	int i;
	cout << "enter amount of terms: ";
	cin >> i;

	double term;
	double disc;

	vector<double> discount;

	for (int j = 0; j < i; j++) {
		cout << "interest rate for term " << j + 1 << ": ";
		cin >> term;
		term = term / 100;
		disc = 1 / pow((1 + term), j + 1);
		discount.push_back(disc);

	}

	auto num = 1 - discount.back();
	auto denom = accumulate(discount.begin(), discount.end(), 0.0);
	auto zero_rate = (num / denom) * 100;


	cout << fixed;
	cout.precision(2);
	cout << "rate where swap equals zero: " << zero_rate << endl;
}

void One_period_option(void) {

	double S;
	cout << "enter the price of the stock: ";
	cin >> S;
	double R;
	cout << "enter the value of R: ";
	cin >> R;
	double u;
	cout << "enter the value of u: ";
	cin >> u;
	double d = 1 / u;
	double Strike;
	cout << "enter the Strike rate: ";
	cin >> Strike;

	double up = u * S;
	double down = d * S;

	double price_up = max(up - Strike, 0.0);
	double price_down = max(0.0, down - Strike);

	double option_up = ((R - d) / (u - d))* price_up;
	double option_down = ((u - R) / (u - d))* price_down;

	double price = (1 / R)*(option_up + option_down);

	cout << fixed;
	cout.precision(2);
	cout << "value of the option is: " << price << endl;

	/* 
	this portion of the method will be used to calculate the cash that you need to invest in the cash account
	Initially we have that we need to solve a simultaneous equation but given that R will always be the same for
	each equation it lends itself nicely to substitution via elimination

	our equations are as follows:

		where A = Price of the stock when it is up
		where B = Price of the stock when it is down

		Ax + Ry = Cu
		Bx + Ry = Cd

	from here we can isolate the X value and then plug that back into one of the formulas to find the value of y

	*/

	// Isolating the values of each side of the equation to find X
	double left_side = (S*(u - R)) - (S*(d - R));
	double right_side = price_up - price_down;
	//This will give us the value of X or the amount of stock we are buying.
	double X = right_side / left_side;

	// Similar to the line above where we isolate each side of the equation it is meant to aid in readability
	double cash_intr = (price_up - ((Strike + (S*(u - R)))*X));
	// here we isolate the value of y that gives us the amount of cash that we need to invest
	double cash = cash_intr / R;

	cout.fixed;
	cout.precision(3);
	cout << "The amount that needs to be invested in the cash account is: " << cash << endl;
}


int main(){ 

//One_period_option();
//swap_rates();
//discount_factor();
//MVH();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
