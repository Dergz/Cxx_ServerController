// MODULE, Controlls & Manipulates ModPacks
#include "../Base_Includes.cxx" //Lib Includes

// Establishes the functions so they can be called out of order
vector<string> Server_Lister(int);
void Server_Menu();
string Server_Selector();

void Server_Menu(){ // ModPack menu, Char Based Options

    // Consider an input test to make sure check isnt always running?
    // Run Check of settings file to set the last used modpack
    // ^ If check returns null then have the user select a modpack

    system("clear");
    cout << endl;
    cout << "--- ModPack Controller ---" << endl;
    cout << endl;
    cout << "Selected Server: " << endl;    // Make constantant via settings
    cout << endl;
    cout << " M) Select ModPack" << endl;
    cout << " O) ModPack Options" << endl;  // ModPack settings, file in modpackdir, jvm ver, start file, etc (Settings setup if none)
    cout << " S) Start Server" << endl;     // Starts a modpack, run check for setting to start, if not run settings setup
    cout << " E) Server Session" << endl;   // Screens into the running server
    cout << endl;
    cout << " Q) Exit" << endl;             // Returns to the main menu
    cout << endl;

    cout << "Select an option: ";
    char option;
    cin >> option; // Get user input
    option = toupper(option);
    cout << endl;

    switch (option)
    {
    case 'M':
        Server_Selector(); 
        Server_Menu();
        break;
    case 'O':
        cout << "02";
        break;
    case 'S':
        cout << "O3";
        break;
    case 'E':
        cout << "O4";
        break;
    case 'Q':
        system("clear");
        break;
    default:
        cout << "Not an option" << endl;
        system("sleep 1");
        system("clear");
        Server_Menu();
        break;
    }
}



vector<string> Server_Lister(int SUO){ // reads the directory containing modspacks and puts them into a vector
    vector<string> ModPackNames;           // Establishes the vector
    string path = "/home/skarf/Suwuver/ModPacks/"; // Replace with a var so modpack dir can be changed
    int pathlength = path.length();

    for (const auto &entry : fs::directory_iterator(path))
    { // Adds each output into the vector
        ModPackNames.push_back(string(entry.path()));
    }

    if (SUO == 1)
    { // if a var is true then show the output of the vector
        cout << "Listing ModPacks In Directory" << endl;
        for (int i = 0; i < ModPackNames.size(); i++)
        {
            cout << " " << i << ") " << ModPackNames[i].erase(0, pathlength) << endl;
        }
    }

    return ModPackNames; // Returns the vecotor containing mod pack names
}



string Server_Selector(){ // Selects the modpack and assigns it to a var for menu usage
    vector ModPackNames = Server_Lister(1); // Gets serverlist
    cout << "Please select a server: ";
    int MPC;
    cin >> MPC;
    cout << "Selected Pack: ";
    string Selected_Server = ModPackNames[MPC];
    cout << Selected_Server << endl;
    cout << endl;
    return Selected_Server;
}