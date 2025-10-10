#include "../Header.hxx"

// Full swap over to using the settings file w/in the program subfolders
// ^ Supply modpack directory in settings folder, parsing that for needs
// ^ Potentially use auto filled out bash files from previous project

void Server_Starter(std::string SelectedModPack);    //Starts the server init process
void Server_Killer(std::string SelectedModPack);     //Kills the running JVM
void Enter_Screen(std::string SelectedModPack);      //Enters the screen running the jvm
bool Screen_Controller(std::string SelectedModPack, std::string ModPackDir);   //Actually inits the server
void ModPack_Settings(std::string SelectedModPack, std::string ModPackDir);   //ModPack Settings maker
std::string ModPackStartFile(std::string SelectedModPack, std::string ModPackDir); //The file to start the jvm
bool IsServerRunning(); //Checks if a java instance is running

// Not in proper running order nor all stiched together
void Server_Starter(std::string SelectedModPack, std::string ModPackDir){ // Main ModPack Controller, Tie Together
    std::cout << "Starting Server" << std::endl;
    std::cout << "Selected Pack: " << SelectedModPack << std::endl;
    std::cout << "Server Direct: " << ModPackDir << std::endl;
    ModPack_Settings(SelectedModPack,ModPackDir);   // Sets / Checks for settings
    Screen_Controller(SelectedModPack,ModPackDir);  // Starts the jvm
}

// Done, Still in debug mode
bool Screen_Controller(std::string SelectedModPack, std::string ModPackDir){ // Starts the modpack in a screen session
    std::cout << "Screen opening for : " << SelectedModPack << std::endl;

    // Starts the screen session
    std::string TMP1("screen -S \"");
    TMP1 += SelectedModPack;
    TMP1 += "\" -dm";
    // system(TMP1.c_str()); //UN COMMENT ON FULL CODE TEST
    std::cout << TMP1 << std::endl;


    // Enters the directory of the modpack
    std::string TMP2("screen -r \"");
    TMP2 += SelectedModPack;
    TMP2 += "\" -X stuff ";
    TMP2 += "\"cd ";
    TMP2 += ModPackDir;
    TMP2 += " \\n\"";
    // system(TMP2.c_str()); //UN COMMENT ON FULL CODE TEST
    std::cout << TMP2 << std::endl;
    system("sleep 1");


    // Starts the mod pack
    std::string TMP3("screen -r ");
    TMP3 += SelectedModPack;
    TMP3 += "\" -X stuff ";
    TMP3 += ModPackStartFile(SelectedModPack, ModPackDir);
    TMP3 += " \\n\"";
    // system(TMP3.c_str()); //UN COMMENT ON FULL CODE TEST
    std::cout << TMP3 << std::endl;

    system("sleep 10");
    system("clear");

    // Checks to ensure server is started
    bool TMP4 = IsServerRunning();
    return TMP4;
}

// Currently loops till program is dead, but just want to return if the process is detected
bool IsServerRunning(){ // Checks if jvm is running
    // Ensures java started, if not return false
    // Currently loops till program is dead
    std::string TMP1("pgreg -x ");
    TMP1 += "java"; // java works but isnt case sensitive
    int TMP2 = system(TMP1.c_str()); //UN COMMENT ON FULL CODE TEST

    bool TMP3;
    if (TMP2 > 0){
        bool TMP3 = true;
    }
    else{
        bool TMP3 = false;
    }

    std::cout << TMP3 << std::endl;
    return TMP3;
}

// Missing File Filler, Still has debug, figure out settings hierarchy
void ModPack_Settings(std::string SelectedModPack,std::string ModPackDir){
    std::cout << "Checking for settings" << std::endl;
    bool Settings_Check;

    // Check for settings file , doesnt return if it actually there yet
    std::string TMP1 = ModPackDir;
    TMP1 += "/settings.txt";
    if(std::filesystem::exists(TMP1)){
        std::cout << " exists\n"; // Debug
        bool Settings_Check = true;}
    else;{
        std::cout << " does not exist\n"; // Debug
        bool Settings_Check = false;}

    // if settings are good, exit
    if (Settings_Check){
        return;
    }
    // If settings arent done fill them out

    std::ofstream outfile (TMP1);
    outfile << "Test ModPack Settings File" << std::endl;
    outfile.close();


    return;
}


