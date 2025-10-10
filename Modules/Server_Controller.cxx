// MODULE, Controlls & Manipulates ModPacks
#include "../Header.hxx"

void Server_Menu(){ // ModPack menu, Char Based Options
    system("clear");
    std::cout << std::endl;
    std::cout << "--- ModPack Controller ---" << std::endl;
    std::cout << std::endl;
    std::cout << "Selected Server: " << Map_Reader(SMAP, 0) << std::endl;    // Make constantant via settings
    std::cout << std::endl;
    std::cout << " M) Select ModPack" << std::endl;
    std::cout << " O) ModPack Options" << std::endl;  // ModPack settings, file in modpackdir, jvm ver, start file, etc (Settings setup if none)
    std::cout << " S) Start Server" << std::endl;     // Starts a modpack, run check for setting to start, if not run settings setup
    std::cout << " E) Server Session" << std::endl;   // Screens into the running server
    std::cout << std::endl;
    std::cout << " Q) Exit" << std::endl;             // Returns to the main menu
    std::cout << std::endl;

    std::cout << "DEBUG:" << std::endl;
    for (auto i : SMAP){
        std::cout << i.first << ": " << i.second << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Split_Debug" << std::endl;

    std::cout << "Select an option: ";
    char option;
    std::cin >> option; // Get user input
    option = toupper(option);
    std::cout << std::endl;

    switch (option){
    case 'M':
        Server_Selector(); 
        Server_Menu();
        break;
    case 'O':
        std::cout << "02";
        Server_Menu();
        break;
    case 'S':
        std::cout << "O3";
        break;
    case 'E':
        std::cout << "O4";
        break;
    case 'Q':
        system("clear");
        Main_Menu();
        break;
    default:
        std::cout << "Not an option" << std::endl;
        system("sleep 1");
        system("clear");
        Server_Menu();
        break;
    }
}



std::vector<std::string> Server_Lister(int SUO){ // reads the directory containing modspacks and puts them into a vector
    std::vector<std::string> ModPackNames;           // Establishes the vector
    std::string path = "/home/skarf/Suwuver/ModPacks/"; // Replace with a var so modpack dir can be changed
    int pathlength = path.length();

    for (const auto &entry : fs::directory_iterator(path)){ // Adds each output into the vector
        ModPackNames.push_back(std::string(entry.path()));
    }

    if (SUO == 1){ // if a var is true then show the output of the vector
        std::cout << "Listing ModPacks In Directory" << std::endl;
        for (int i = 0; i < ModPackNames.size(); i++){
            std::cout << " " << i << ") " << ModPackNames[i].erase(0, pathlength) << std::endl;
        }
    }

    return ModPackNames; // Returns the vecotor containing mod pack names
}



void Server_Selector(){ // Selects the modpack and assigns it to a var for menu usage
    std::vector ModPackNames = Server_Lister(1); // Gets serverlist
    std::cout << "Please select a server: ";
    int MPC;
    std::cin >> MPC;
    std::cout << "Selected Pack: ";
    std::string Selected_Server = ModPackNames[MPC];

    std::cout << Selected_Server << std::endl;
    std::cout << std::endl;

    //SMAP[0] = Selected_Server;
    SMAP.at(0) = Selected_Server;
}