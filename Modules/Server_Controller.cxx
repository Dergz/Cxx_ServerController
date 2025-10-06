// MODULE, Controlls & Manipulates ModPacks
#include "../Base_Includes.cxx" //Lib Includes


// Establishes the functions so they can be called out of order
vector<string> Server_Lister(int);
void Server_Menu();
string Server_Selector();

void Server_Menu()
{ // ModPack menu

    // Sets selected server incase its not set (on runtime)
    // optional<string> Selected_Server;
    // if (!Selected_Server) {
    //    cout << "Server is NOT Selected";
    //    string Selected_Server = "Null";
    //}

    system("clear");
    cout << endl;
    cout << "--- ModPack Controller ---" << endl;
    cout << endl;
    cout << "Selected Server: " << endl; //Change to read settings for a selected Modpack
    cout << endl;
    cout << " M) Select ModPack" << endl; //Make constantant via a file
    cout << " O) ModPack Options" << endl;
    cout << " S) Start Server" << endl;
    cout << " E) Server Session" << endl;
    cout << endl;
    cout << " Q) Exit" << endl;
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
        cout << "Def tripped" << endl;
        Server_Menu();
        break;
    }
}

vector<string> Server_Lister(int SUO)
{                                          // reads the directory containing modspacks and puts them into a vector
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

string Server_Selector()
{                                           // Selects the modpack and assigns it to a var for menu usage
    vector ModPackNames = Server_Lister(1); // Gets serverlist and bot vars / outputs it
    cout << "Please select a server: ";
    int MPC;
    cin >> MPC;
    cout << "Selected Pack: ";
    string Selected_Server = ModPackNames[MPC];
    cout << Selected_Server << endl;
    cout << endl;
    return Selected_Server;
}