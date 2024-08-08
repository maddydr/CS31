//
//  main.cpp
//  project2
//
//  Created by Maddy Delos Reyes on 10/8/22.
//

#include <iostream>
#include <string>
using namespace std;

int main()
{
    // get user name
    cout << "Name: ";
    string name;
    getline(cin, name);
    // error message if input no name
    if (name == "")
    {
        cout << "---" << endl << "You must enter a name" << endl;
        return 1;
    }
    
    // get user income
    cout << "Taxable income: ";
    double income;
    cin >> income;
    cin.ignore(10000, '\n');
    // error message if input is negative
    if (income < 0)
    {
        cout << "---" << endl << "The taxable income must not be negative" << endl;
        return 2;
    }
    
    // get user occupation
    cout << "Occupation: ";
    string occupation;
    getline(cin, occupation);
    // error message if input no occupation
    if (occupation == "")
    {
        cout << "---" << endl << "You must enter an occupation" << endl;
        return 3;
    }
    
    // get user number of children
    cout << "Number of children: ";
    int children;
    cin >> children;
    // error message if number is negative
    if (children < 0)
    {
        cout << "---" << endl << "The number of children must not be negative" << endl;
        return 4;
    }
    
    // tax calculations
    double tax = 0;
    double bracket1 = 0;
    if (income < 55000)
        tax = income * .04;
    // only want to tax the first 55k chunk, not touch 70k portion
    else
    {
        bracket1 = 55000 * .04;
        // if next income chunk is less than 70k, tax all leftover money by next bracket
        if ((income - 55000) < 70000)
        {
            if (occupation == "nurse" || occupation == "teacher")
                tax = bracket1 + ((income - 55000) * .05);
            else
                tax = bracket1 + ((income - 55000) * .07);
        }
        
    }
   
    // calculate tax bracket with 125k or more
    if (income >= 125000)
    {
        if (occupation == "nurse" || occupation == "teacher")
            tax = bracket1 + (70000 * .05);
        else
            tax = bracket1 + (70000 * .07);

        tax = (income - 125000) * .093 + tax;
    }
    // only discount for people who make less than 125k
    else
    {
        tax = tax - (200 * children);
    }
    
    // print out what person owes
    if (tax < 0)
    {
        cout << "---" << endl << name << " would pay $0.00" << endl;
    }
    else
    {
        cout.setf(ios::fixed);
        cout.precision(2);
        cout << "---" << endl << name << " would pay $" << tax << endl;

    }
    
    
    return 0;
}
