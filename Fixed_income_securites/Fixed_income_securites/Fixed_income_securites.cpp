// Fixed_income_securites.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

using namespace std;
void present_value(void)
{

	double interest;
	int payments;
	double payment_amount;
	//double total_payment;


	cout << "Please enter an interest rate: ";
	cin >> interest;

	cout << "Please enter the amount of payments: ";
	cin >> payments;

	cout << "Please enter the payment amount: ";
	cin >> payment_amount;


	vector<double> discount(payments);

	vector<int> t(payments);

	iota(t.begin(), t.end(), 0);

	transform(t.begin(), t.end(), discount.begin(), [&interest](int t) {return 1 / pow((1 + interest), t); });

	double total = accumulate(discount.begin(), discount.end(), 0.0);

	cout << fixed;
	cout.precision(2);
	cout << "Present value: " << total * payment_amount / 1000000 << " million" << endl;
}

void fcontract_intermediate(void)
{
	double initial_price;
	double current_price;
	double interest;
	// this is the rate of which is compounded
	int compound_rate;

	cout << "please enter the initial price: ";
	cin >> initial_price;

	cout << "please enter the current price: ";
	cin >> current_price;

	cout << "please enter the interest rate: ";
	cin >> interest;

	cout << "please enter the rate at which the interest is compounded: ";
	cin >> compound_rate;

	double time_0 = initial_price * pow((1 + (interest / compound_rate)), 2);
	double time_t = current_price * (1 + (interest / compound_rate));

	double discount_factor = (1 / (1 + (interest / compound_rate)));

	double  forward_price = (time_t - time_0)*discount_factor;

	cout << "intermediate price is: " << forward_price << endl;
}

void fcontract()
{
	// this function is for calculating the value of a forward contract at a theoretical point in time
	double price;
	double interest;
	// this value is how many times interest is applied annually
	int compound_rate;
	//theoretical time
	int theoretical_time;

	cout << "enter a price: ";
	cin >> price;

	cout << "enter an interest rate: ";
	cin >> interest;

	cout << "enter a compound rate: ";
	cin >> compound_rate;

	cout << "enter a theoretical time: ";
	cin >> theoretical_time;

	double value = price * pow((1 + (interest / compound_rate)), theoretical_time);

	cout << "theoretical value for forward contract is: " << value << endl;

}

int main()
{
	//present_value();
	//fcontract_intermediate();
	//fcontract();
	return 0;
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
