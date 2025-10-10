#include "Header.hxx"
#include "Modules/Mapping.cxx"
#include "Modules/Server_Controller.cxx"

int main(){ // Starts the script
    std::cout << "-- DEBUG PRINTING --" << std::endl;
    Mapping_INIT();
    system("sleep 0.25"); //Debug sleep
    Main_Menu();
    system("clear");
    return 0;
}


float PVersion(){ // Establishes the programs current version, jsut to be fancy
    const float PVer = 0.9;
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
    std::cout << " C) ModPack Controller" << std::endl;
    std::cout << " N) New ModPack Setup" << std::endl;
    std::cout << " A) ModPack Archiving" << std::endl;
    std::cout << " E) Edit Script Option" << std::endl;
    std::cout << " S) System Options" << std::endl;
    std::cout << std::endl;
    std::cout << " Q) Quit" << std::endl;
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


void Power_Menu(){ // Power Menu
    system("clear");
    std::cout << std::endl;
    std::cout << "--- System Menu ---" << std::endl;
    std::cout << std::endl;
    std::cout << " 1) Power Off" << std::endl;
    std::cout << " 2) Reboot" << std::endl;
    std::cout << std::endl;
    std::cout << " Q) Main Menu" << std::endl;
    std::cout << std::endl;

    std::cout << "Select an option: ";
    char option;
    std::cin >> option; // Get user input
    option = toupper(option);
    std::cout << std::endl;

    switch (option)
    {
    case '1':
        system("systemctl poweroff");
        break;
    case '2':
        system("systemctl reboot");
        break;
    case 'Q':
        Main_Menu();
        break;
    case 'q':
        Main_Menu();
        break;
    default:
        std::cout << "Not an option" << std::endl;
        system("sleep 1");
        Power_Menu();
        break;
    }
}