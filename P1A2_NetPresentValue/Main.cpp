/*
Author: Kat Bergen

Task: create a programm to calculate the net present value based on user input

Version: 1
Date: 03.11.2020
*/

#include <exception>
#include <iostream>
#include "NPV.h"


int main() try
{
	double irate{ userInputIrate() };
	std::vector<int> investments{ userInputInvestments() };

	NPV mynpv{ NPV(investments, irate) };	
	
	std::cout << "\nat an annual interest rate of " << irate << "% the net present value of all investments is: " << mynpv.calculateNPV() << " euro.\n";

	/*tests();*/

	return 0;
}

catch (const std::exception& e)
{
	std::cerr << e.what();
	return -1;
}

catch (...)
{
	std::cerr << "unknown error";
	return -99;
}