#include "Base_Includes.cxx"    //Lib Includes

vector<string> Server_Lister();

void Server_Menu(){
    system("clear");
    cout << endl;
    cout << "--- ModPack Controller ---" << endl;
    cout << endl;
    cout << " M) Select ModPack" << endl;
    cout << " O) ModPack Options" << endl;
    cout << " S) Start Server" << endl;
    cout << " E) Server Session" << endl;
    //cout << " 5) OPTION" << endl;
    cout << endl;
    cout << " Q) Exit" << endl;
    cout << endl;

    cout << "Select an option: ";
    char option;
    cin >> option; // Get user input
    cout << endl;

    switch (option)
    {
    case 'M':
        cout << "O1";
        break;
    case '2':
        Server_Lister();
        break;
    case '3':
        cout << "O3";
        break;
    case '4':
        cout << "O4";
        break;
    case 'Q':
        system("clear");
        break;
    default:
        cout << "Def tripped" << endl;
        Server_Menu();
        break;
    }
}

vector<string> Server_Lister(){
    vector<string> ModPackNames;
    //Reads a directory and lists all files and directories within
    string path = "/home/skarf/Suwuver/ModPacks/";
    cout << "Scanning Directory for ModPacks" << endl;
    for (const auto & entry : fs::directory_iterator(path))
        ModPackNames.push_back(entry.path());
    for (int i = 0; i < ModPackNames.size(); i++) {
        cout << " " << i << ") " << ModPackNames[i] << endl;
    }
    return ModPackNames;
}