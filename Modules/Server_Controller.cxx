// MODULE, Controlls & Manipulates ModPacks
#include "../Header.hxx"
#include "Screen_ControllerV2.cxx"

void Server_Menu(){ // ModPack menu, Char Based Options
    std::string ISRUNNING;
    if(Check_For_Java() == 1){ISRUNNING = "true";}
    else{ISRUNNING = "false";}

    system("clear");
    std::cout << std::endl;
    std::cout << "--- ModPack Controller ---" << std::endl;
    std::cout << std::endl;
    std::cout << "Selected Server: " << Map_Reader(SMAP, 0) << std::endl;    // Make constantant via settings
    std::cout << "Is Server Running: " << ISRUNNING << std::endl;
    std::cout << std::endl;
    std::cout << " M) Select ModPack" << std::endl;     // Changes the active ModPack
    std::cout << " R) Redo Start File" << std::endl;    // Redoes the start file
    std::cout << " S) Start Server" << std::endl;       // Starts a modpack, run check for setting to start, if not run settings setup
    std::cout << " E) Screen Session" << std::endl;     // Screens into the running server
    std::cout << " K) Kill Screen session" << std::endl;     // Kills currently running pack
    std::cout << std::endl;
    std::cout << " Q) Exit" << std::endl;               // Returns to the main menu
    std::cout << std::endl;

    //std::cout << "DEBUG:" << std::endl;
    //for (auto i : SMAP){
    //    std::cout << i.first << ": " << i.second << std::endl;
    //}
    //std::cout << std::endl;

    std::cout << "Select an option: ";
    char SMOption;
    std::cin >> SMOption;
    SMOption = toupper(SMOption);
    std::cout << std::endl;

    switch (SMOption){
    case 'M':
        Quick_Check();
        break;
    case 'R':
        V2_Screen_Controller(3);
        Server_Menu();
        break;
    case 'S':
        V2_Screen_Controller(1);
        Server_Menu();
        break;
    case 'E':
        V2_Screen_Controller(2);
        Server_Menu();
        break;
    case 'K':
        V2_Screen_Controller(5);
        Server_Menu();
        break;
    case 'Q':
        Main_Menu();
        break;
    default:
        std::cout << "Not an option" << std::endl;
        system("sleep 1");
        Server_Menu();
        break;
    }
    gibbe;
}



std::vector<std::string> Server_Lister(int SUO){ // reads the directory containing modspacks and puts them into a vector
    std::vector<std::string> ModPackNames;           // Establishes the vector
    auto it = SMAP.find(1);
    std::string Server_Dir = it->second;
    int pathlength = Server_Dir.length();

    for (const auto &entry : fs::directory_iterator(Server_Dir)){ // Adds each output into the vector
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

    //SMAP[0] = Selected_Server;
    SMAP.at(0) = Selected_Server;

    // Puts the modpack into the the Previous_Modpack.txt for cross session saving
    std::string File_to_Write = "Misc_Files/Previos_Modpack.txt";
    std::ofstream File(File_to_Write);
    File << Selected_Server;
    File.close();
}

void Quick_Check(){// Ensures no server is active before changing the directory
    if(Check_For_Java() == 1){
        std::cout << "A Modpack is current Running" << std::endl;
        std::cout << "Please kill running pack before changing" << std::endl;
        system("sleep 3");
        Server_Menu();
        return;
    }
    else{
        std::cout << "No Server Running, allowing change" << std::endl;
        Server_Selector();
        system("sleep 3");
        Server_Menu();
        return;
    }
    return;
}