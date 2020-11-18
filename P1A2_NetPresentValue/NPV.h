/*
Author: Kat Bergen

Header: create a programm to calculate the net present value based on user input

Version: 1
Date: 03.11.2020
*/

#include <vector>
#ifndef NPV_H
#define NPV_H

class NPV {

private:
	std::vector<int> inv{}; //investments vector
	double irate{}; //investment rate 0 to 1

public:
	NPV(); //Standardconstructor
	NPV(double&); //testing constructor
	NPV(std::vector<int>&, double&); //user input constructor
	
	double calculateNPV(); // calculate the net present value
	
};

///////////////////////Helper methods///////////////////////

double userInputIrate(); //user input investment rate
std::vector<int> userInputInvestments(); //user input investments 
void tests();

#endif // !NPV_H
