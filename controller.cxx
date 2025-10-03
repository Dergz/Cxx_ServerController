#include "Base_Includes.cxx"    //Lib Includes
#include "Linker.cxx"           //Includes Linker.cxx for linking modules

void Main_Menu(){
    cout << endl;
    cout << "##########################" << endl;
    cout << "###                    ###" << endl;
    cout << "###  Server Contoller  ###" << endl;
    cout << "###                    ###" << endl;
    cout << "##########################" << endl;
    cout << endl;
    cout << "--- Server Options ---" << endl;
    cout << endl;
    cout << " 1) ModPack Selection" << endl;
    cout << " 2) New ModPack Setup" << endl;
    cout << " 3) ModPack Archiving" << endl;
    cout << " 4) Edit Script Option" << endl;
    cout << " 5) Server Power Options" << endl;
    cout << endl;
    cout << " 6) Quit" << endl;
    cout << endl;

    cout << "Select an option: ";
    int option;
    cin >> option; // Get user input
    cout << endl;

    switch (option)
    {
    case 1:
        Server_Menu();
        Main_Menu();
        break;
    case 2:
        Directory_Lister();
        break;
    case 3:
        cout << "O3";
        break;
    case 4:
        cout << "O4";
        break;
    case 5:
        cout << "O5";
        break;
    case 6:
        cout << "O6";
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
