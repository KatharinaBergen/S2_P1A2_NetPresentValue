/*
Author: Kat Bergen

Body: create a programm to calculate the net present value based on user input

Version: 1
Date: 03.11.2020
*/

#include "NPV.h"
#include <random>
#include <functional>
#include <iostream>

using std::cout;
using std::cin;


//Constructors

NPV::NPV() {}

NPV::NPV(double& irate) {
    //create 10 random investments and add to vector this.inv
    std::default_random_engine e{};
    std::uniform_int_distribution<int> distr{ 0, 100000 };
    auto ri = bind(distr, e);

    for (int i{ 0 }; i < 10; i++)
    {
        this->inv.push_back(ri());
    }

    //set irate of instance to irate passed
    this->irate = 1+irate/100;
}

NPV::NPV(std::vector<int>& inv, double& irate) {
    this->inv = inv;
    this->irate = 1 + irate / 100;
}

//Methods

double NPV::calculateNPV() {
    double result{};
    double intermediate{};
    double myProblem{};

    for (int i{ 0 }; i < inv.size(); i++)
    {
        myProblem = this->inv.at(i);
        intermediate = (this->inv.at(i) / pow(this->irate, i + 1));
        //for each element in the inv vector, the net value at t=0 is calculated and added to result
        result += (this->inv.at(i) / pow(this->irate, i+1)); 
    }

    return result;
}



///////////////////////Helper methods///////////////////////

double userInputIrate() {
    char input{};
    double irate{ };

    cout << "Please add the investment rate in %. Be sure to use a '.' and not a ',' if you wish to add a decimal point value.\n>";
    cin >> input;
    if (!cin) { throw std::runtime_error{ "incorrect interest rate at userInputIrate()" }; }
    cin.putback(input);
    cin >> irate;

    return irate;
}

std::vector<int> userInputInvestments() {
    std::vector<int> investments{};
    char input{};
    int investment{ };

    cout << "\nPlease now subsequently add the investments in Euro. You may add as many investments as you wish. \n";

    while (input != 'q') {
        cout << ">";

        cin >> input;
        if (!cin) { throw std::runtime_error{ "incorrect investment at userInputInvestments()" }; }

        if (input != 'q') {
            cin.putback(input);
            cin >> investment;

            investments.push_back(investment);
        }
        
        cout << "\nYou may now add another investment. If you are finished with adding investments, please type 'q' and press enter.\n";
    }


    return investments;
}

void tests() {

    bool isCorrect{ true };

    //test 1
    double irate1{ 10 };
    std::vector<int> investments1{ 0 };
    double expectedResult1{ 0 }; 
    NPV myNPV1{ NPV(investments1, irate1) };

    if (expectedResult1 != myNPV1.calculateNPV()) {
        cout << "\nTest number 1 failed";
        isCorrect = false;
    }

    //test 2
    double irate2{ 10 };
    std::vector<int> investments2{ 1 };
    double expectedResult2{ 0.90909090909090906 };
    NPV myNPV2{ NPV(investments2, irate2) };

    if (expectedResult2 != myNPV2.calculateNPV()) {
        cout << "\nTest number 2 failed";
        isCorrect = false;
    }

    //test 3
    double irate3{ 10 };
    std::vector<int> investments3{ 76621,63484,7831,98723,98751,13779,80201,24492,35139,54168 };
    double expectedResult3{ 352896.70977355284 };
    NPV myNPV3{ NPV(investments3, irate3) };

    if (expectedResult3 != myNPV3.calculateNPV()) {
        cout << "\nTest number 3 failed";
        isCorrect = false;
    }

    //test 4
    double irate4{ 5 };
    std::vector<int> investments4{ 76621,63484,7831,98723,98751,13779,80201,24492,35139,54168 };
    double expectedResult4{ 435674.57226831908 };
    NPV myNPV4{ NPV(investments4, irate4) };

    if (expectedResult4 != myNPV4.calculateNPV()) {
        cout << "\nTest number 4 failed";
        isCorrect = false;
    }

    //test 5
    double irate5{ 5 };
    std::vector<int> investments5{ -76621,63484,7831,98723,98751,13779,80201,24492,35139,54168};
    double expectedResult5{ 289729.81036355713 };
    NPV myNPV5{ NPV(investments5, irate5) };

    if (expectedResult5 != myNPV5.calculateNPV()) {
        cout << "\nTest number 5 failed";
        isCorrect = false;
    }

    //test 6
    double irate6{ 5 };
    std::vector<int> investments6{ -76621,63484,7831,98723,98751,13779,80201,-24492,35139,-54168};
    double expectedResult6{ 190066.60481835227 };
    NPV myNPV6{ NPV(investments6, irate6) };

    if (expectedResult6 != myNPV6.calculateNPV()) {
        cout << "\nTest number 6 failed";
        isCorrect = false;
    }

    //test 7
    double irate7{ 5 };
    std::vector<int> investments7{ -76621,-63484 };
    double expectedResult7{ -130554.24036281178 };
    NPV myNPV7{ NPV(investments7, irate7) };
    
    if (expectedResult7 != myNPV7.calculateNPV()) {
        cout << "\nTest number 7 failed";
        isCorrect = false;
    }

    //test 8
    double irate8{ 5 };
    std::vector<int> investments8{  };
    double expectedResult8{ 0 };
    NPV myNPV8{ NPV(investments8, irate8) };

    if (expectedResult8 != myNPV8.calculateNPV()) {
        cout << "\nTest number 8 failed";
        isCorrect = false;
    }

    //test 9
    double irate9{ 0 };
    std::vector<int> investments9{ 76621,63484,7831,98723,98751,13779,80201,24492,35139,54168 };
    double expectedResult9{ 553189 };
    NPV myNPV9{ NPV(investments9, irate9) };

    if (expectedResult9 != myNPV9.calculateNPV()) {
        cout << "\nTest number 9 failed";
        isCorrect = false;
    }

    //test 10
    double irate10{ -10 };
    std::vector<int> investments10{ 76621,63484,7831,98723,98751,13779,80201,24492,35139,54168 };
    double expectedResult10{ 988513.50632794388 };
    NPV myNPV10{ NPV(investments10, irate10) };
    double actualResult{ myNPV10.calculateNPV() };

    if (expectedResult10 != myNPV10.calculateNPV()) {
        cout << "\nTest number 10 failed";
        isCorrect = false;
    }

    if (isCorrect) {
        cout << "\nAll tests have passed successfully.\n";
    }
}