// Just a test file for C++ basics

#include <iostream>     //Lib for user inputs
#include <string>       //Lib for strings?
#include <fstream>      //lib to interface fs
using namespace std;    //sets namespace

void testfunc(){
    //Outputing text / characters
    cout << "Hello World!\n";
    cout << 3*3 << endl;

    //Declairing a num vars
    int numtest = 15;
    cout << numtest << endl;

    //Declaring several vars
    int x = 5, y = 6, z = 50;
    cout << x + y + z << endl;

    //Declaring  a num that cannot be changed
    const int cnum = 10;
    cout << cnum << endl;

    //Getting user input and printing it
    int UNum; 
    cout << "Type a number: ";
    cin >> UNum; // Get user input 
    cout << "Your number is: " << UNum << endl;

    //Declairing and using bools
    bool isCodingFun = true;
    bool isFishTasty = false;
    cout << isCodingFun << endl;
    cout << isFishTasty << endl;

    //Declairing and using a  string
    string greeting = "Hello";
    cout << greeting << endl; 

    //auto, detect var type and sets it to such
    auto ANum = 5;
    cout << ANum << endl;

    //Basic Data Types:
    int myNum = 5;               // Integer (whole number)
    float myFloatNum = 5.99;     // Floating point number
    double myDoubleNum = 9.98;   // Floating point number
    char myLetter = 'D';         // Character
    bool myBoolean = true;       // Boolean
    string myText = "Hello";     // String 


    // FILE EXAMPLE
    // Create and open a text file
    ofstream MyFile("filename.txt");

    // Write to the file
    MyFile << "Files can be tricky, but it is fun enough!";

    // Close the file
    MyFile.close();
}