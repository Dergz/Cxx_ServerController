#include "Header.hxx"
#include "Modules/Mapping.cxx"
#include "Modules/Server_Controller.cxx"
#include "Modules/SysMenus.cxx"
#include "Modules/File_Manipulator.cxx"

int main(int argc, char * argv[]){ // Starts the script
    std::cout << "-- DEBUG PRINTING --" << std::endl;
    Mapping_INIT();

    //Read for last selected ModPack
    const std::string File_to_Read = "Misc_Files/Previos_Modpack.txt";
    std::unordered_map<int,std::string> TMPFRM = FileReader(File_to_Read);
    SMAP = Map_Changer(SMAP, 0, TMPFRM.at(0));
    
    std::cout << std::endl;
    for (const auto &i : SMAP){
        std::cout << i.first << ": " << i.second << std::endl;
    }

    system("sleep 0.25"); //Debug sleep
    Main_Menu();
    system("clear");
    return 0;
}


float PVersion(){ // Establishes the programs current version, jsut to be fancy
    const float PVer = 0.12;
    return PVer;
}


void Main_Menu(){ // Scripts Main Menu
    system("clear");
    float PVer = PVersion();
    std::cout << "Program Version: V" << PVer << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "##########################" << std::endl;
    std::cout << "###                    ###" << std::endl;
    std::cout << "###  Server Contoller  ###" << std::endl;
    std::cout << "###                    ###" << std::endl;
    std::cout << "##########################" << std::endl;
    std::cout << std::endl;
    std::cout << "--- Server Options ---" << std::endl;
    std::cout << std::endl;
    std::cout << " C) ModPack Controller" << std::endl; //ModPack controller
    std::cout << " N) New ModPack Setup" << std::endl;  //Triggers Start_File creation
    std::cout << " A) ModPack Archiving" << std::endl;  //7Zips a pack and moves it to archives folder
    std::cout << " E) Edit Script Option" << std::endl; //Changes Scripts Option
    std::cout << " S) System Options" << std::endl;     //System panels
    std::cout << std::endl;
    std::cout << " Q) Quit" << std::endl;   //Exits scripts
    std::cout << std::endl;

    std::cout << "Select an option: ";
    char option;
    std::cin >> option; // Get user input
    option = toupper(option);
    std::cout << std::endl;

    switch (option)
    {
    case 'C':
        Server_Menu();
        break;
    case 'N':
        std::cout << "02";
        break;
    case 'A':
        std::cout << "O3";
        break;
    case 'E':
        std::cout << "O4";
        break;
    case 'S':
        Power_Menu();
        break;
    case 'Q':
        std::cout << "Exiting program" << std::endl;
        break;
    default:
        std::cout << "Not an option" << std::endl;
        system("sleep 1");
        system("clear");
        Main_Menu();
        break;
    }
}
