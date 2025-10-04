#include "Base_Includes.cxx"    //Lib Includes
#include "Linker.cxx"           //Includes Linker.cxx for linking modules

void Main_Menu(){
    system("clear");
    const float PVer = 0.2;
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
    cout << " S) ModPack Selection" << endl;
    cout << " N) New ModPack Setup" << endl;
    cout << " A) ModPack Archiving" << endl;
    cout << " E) Edit Script Option" << endl;
    cout << " P) Server Power Options" << endl;
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
    case 'S':
        Server_Menu();
        //Main_Menu();
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
    case 'P':
        cout << "O5";
        break;
    case 'Q':
        cout << "Exiting program" << endl;
        break;
    default:
        cout << "Def tripped" << endl;
        system("clear");
        Main_Menu();
        break;
    }
}

int main(){
    system("clear");
    Main_Menu();
    return 0;
}
