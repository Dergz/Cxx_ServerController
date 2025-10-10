#include "Header.hxx"

int main(){ // Starts the script
    Mapping_INIT();
    system("sleep 5"); //Debug sleep
    system("clear");
    Main_Menu();
    return 0;
}


float PVersion(){ // Establishes the programs current version, jsut to be fancy
    const float PVer = 0.6;
    return PVer;
}


void Main_Menu(){ // Scripts Main Menu
    system("clear");
    float PVer = PVersion();
    cout << "Program Version: V" << PVer << endl;
    cout << endl;
    cout << endl;
    cout << "##########################" << endl;
    cout << "###                    ###" << endl;
    cout << "###  Server Contoller  ###" << endl;
    cout << "###                    ###" << endl;
    cout << "##########################" << endl;
    cout << endl;
    cout << "--- Server Options ---" << endl;
    cout << endl;
    cout << " C) ModPack Controller" << endl;
    cout << " N) New ModPack Setup" << endl;
    cout << " A) ModPack Archiving" << endl;
    cout << " E) Edit Script Option" << endl;
    cout << " S) System Options" << endl;
    cout << endl;
    cout << " Q) Quit" << endl;
    cout << endl;

    cout << "Select an option: ";
    char option;
    cin >> option; // Get user input
    option = toupper(option);
    cout << endl;

    switch (option)
    {
    case 'C':
        Server_Menu();
        break;
    case 'N':
        cout << "02";
        break;
    case 'A':
        cout << "O3";
        break;
    case 'E':
        cout << "O4";
        break;
    case 'S':
        Power_Menu();
        break;
    case 'Q':
        cout << "Exiting program" << endl;
        break;
    default:
        cout << "Not an option" << endl;
        system("sleep 1");
        system("clear");
        Main_Menu();
        break;
    }
}


void Power_Menu(){ // Power Menu
    system("clear");
    cout << endl;
    cout << "--- System Power Menu ---" << endl;
    cout << endl;
    cout << " 1) Power Off" << endl;
    cout << " 2) Reboot" << endl;
    cout << endl;
    cout << " Q) Main Menu" << endl;
    cout << endl;

    cout << "Select an option: ";
    char option;
    cin >> option; // Get user input
    option = toupper(option);
    cout << endl;

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
        cout << "Not an option" << endl;
        system("sleep 1");
        Power_Menu();
        break;
    }
}