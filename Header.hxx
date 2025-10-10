#ifndef Header
#define Header


//Library includes
#include <iostream>     //lib for user inputs
#include <string>       //lib for strings
#include <vector>       //lib for vector
#include <fstream>      //lib to interact w/ files
#include <filesystem>   //lib to interface fs
#include <ncurses.h>    //lib for ncurses
#include <stdlib.h>     //lib for sys cmds
#include <optional>     //lib for optional
#include <limits>       
#include <sys/stat.h>
#include <unordered_map>
#include <bits/stdc++.h>
#include <unistd.h>


//Sets defs
namespace fs = std::filesystem; //sets fs namespace
typedef std::pair<std::string, std::string> pairss;


//--- SPLITTER ---


//Global_Funcs
void Mapping_INIT();
std::string Map_Reader(std::unordered_map<int,std::string>, int);
std::unordered_map<int,std::string> Map_Changer(std::unordered_map<int,std::string>, int, std::string);

//Controller
void Main_Menu();
void Power_Menu();
float PVersion();
//int main();

//Server_Controller
std::vector<std::string> Server_Lister(int);
void Server_Menu();
void Server_Selector();

//Grab Var From Anywhere
extern std::unordered_map<int,std::string> SMAP;
extern std::string Server_Dir;

#endif
