#ifndef Header
#define Header


//Library includes
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <optional>
#include <limits>
#include <sys/stat.h>
#include <unordered_map>
#include <bits/stdc++.h>
#include <unistd.h>
#include <set>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>
#include <sstream>
#include <cctype>
#include <algorithm>


//Sets defs
namespace fs = std::filesystem; //sets fs namespace
typedef std::pair<std::string, std::string> pairss;

//Hehe Sillies
#define owo std::cout
#define uwu std::endl
#define nyah std::string
#define nuhuh break;
#define X3 std::unordered_map
#define buldge std::cin
#define hole void
#define gibbe return
#define bottom switch
#define poly std::vector
#define nyar case
#define gay if
#define straight else
#define daddy system


//--- SPLITTER ---


//Mappings
void Mapping_INIT();
std::string Map_Reader(std::unordered_map<int,std::string>, int);
std::unordered_map<int,std::string> Map_Changer(std::unordered_map<int,std::string>, int, std::string);

//Controller
void Main_Menu();
float PVersion();

//SystemMenus
void Power_Menu();

//Misc
std::string exec(const char*);
int getPidOfProcess(const std::string&);
int copyAndRenameFile(const std::string&, const std::string&, const std::string&);

//Server_Controller
std::vector<std::string> Server_Lister(int);
void Server_Menu();
void Server_Selector();
void Quick_Check();

//Screen_ControllerV2
void V2_Screen_Controller(char);
int Check_For_Screen();
int Start_Screen();
int Check_For_Java();
int SScreen_Killer();
void Enter_Screen();

//Start_File
std::string ModPackStartFile();
std::string Create_StartFile();

//File_Manipulator
std::unordered_map<int,std::string> FileReader(const std::string);
std::unordered_map<int,std::string> FileWriter(const std::string,std::unordered_map<int,std::string>);
std::vector<std::string> Directory_Lister(int, std::string);
std::string Directory_Selector(std::string);
std::string SingleLineFileReader(const std::string);
std::string SingleLineFileWriter(const std::string, std::string);
bool FileExists(const std::string&);
void DeleteFile(const std::string&);

//Grab Var From Anywhere
extern std::unordered_map<int,std::string> SMAP;

#endif
