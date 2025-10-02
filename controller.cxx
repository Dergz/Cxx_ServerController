#include "Linker.cxx"   //Includes Linker.cxx for linking modules
#include <iostream>     //Lib for user inputs
#include <string>       //Lib for strings
#include <fstream>      //lib to interact w/ fs
#include <filesystem>   //lib to interface fs
namespace fs = std::filesystem; //sets fs namespace
using namespace std;    //sets namespace

void Main_Menu(){
    cout << "Server Contoller" << endl;
    cout << endl;
    cout << "--- Server Options ---" << endl;
    cout << endl;
    cout << " S) ModPack Selection" << endl;
    cout << " E) Edit Script Option" << endl;
    cout << " M) ModPack Setup" << endl;
    cout << " A) ModPack Archiving" << endl;
    cout << " P) Server Power Options" << endl;
    cout << endl;
    cout << " Q) Quit" << endl;
    cout << endl;

    cout << "Select an option: ";
    char option;
    cin >> option; // Get user input
    cout << endl;

    
    string path2 = "/home/skarf/Suwuver/ModPacks/";
    for (const auto & entry : fs::directory_iterator(path2))
        cout << entry.path() << endl;
}

int main(){
    Main_Menu();
}
