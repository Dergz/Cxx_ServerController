#include "../Header.hxx"

// Full swap over to using the settings file w/in the program subfolders
// ^ Supply modpack directory in settings folder, parsing that for needs
// ^ Potentially use auto filled out bash files from previous project

void Server_Starter(string SelectedModPack);    //Starts the server init process
void Server_Killer(string SelectedModPack);     //Kills the running JVM
void Enter_Screen(string SelectedModPack);      //Enters the screen running the jvm
bool Screen_Controller(string SelectedModPack, string ModPackDir);   //Actually inits the server
void ModPack_Settings(string SelectedModPack, string ModPackDir);   //ModPack Settings maker
string ModPackStartFile(string SelectedModPack, string ModPackDir); //The file to start the jvm
bool IsServerRunning(); //Checks if a java instance is running

// Not in proper running order nor all stiched together
void Server_Starter(string SelectedModPack, string ModPackDir){ // Main ModPack Controller, Tie Together
    cout << "Starting Server" << endl;
    cout << "Selected Pack: " << SelectedModPack << endl;
    cout << "Server Direct: " << ModPackDir << endl;
    ModPack_Settings(SelectedModPack,ModPackDir);   // Sets / Checks for settings
    Screen_Controller(SelectedModPack,ModPackDir);  // Starts the jvm
}

// Done, Still in debug mode
bool Screen_Controller(string SelectedModPack, string ModPackDir){ // Starts the modpack in a screen session
    cout << "Screen opening for : " << SelectedModPack << endl;

    // Starts the screen session
    string TMP1("screen -S \"");
    TMP1 += SelectedModPack;
    TMP1 += "\" -dm";
    // system(TMP1.c_str()); //UN COMMENT ON FULL CODE TEST
    cout << TMP1 << endl;


    // Enters the directory of the modpack
    string TMP2("screen -r \"");
    TMP2 += SelectedModPack;
    TMP2 += "\" -X stuff ";
    TMP2 += "\"cd ";
    TMP2 += ModPackDir;
    TMP2 += " \\n\"";
    // system(TMP2.c_str()); //UN COMMENT ON FULL CODE TEST
    cout << TMP2 << endl;
    system("sleep 1");


    // Starts the mod pack
    string TMP3("screen -r ");
    TMP3 += SelectedModPack;
    TMP3 += "\" -X stuff ";
    TMP3 += ModPackStartFile(SelectedModPack, ModPackDir);
    TMP3 += " \\n\"";
    // system(TMP3.c_str()); //UN COMMENT ON FULL CODE TEST
    cout << TMP3 << endl;

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
    string TMP1("pgreg -x ");
    TMP1 += "java"; // java works but isnt case sensitive
    int TMP2 = system(TMP1.c_str()); //UN COMMENT ON FULL CODE TEST

    bool TMP3;
    if (TMP2 > 0){
        bool TMP3 = true;
    }
    else{
        bool TMP3 = false;
    }

    cout << TMP3 << endl;
    return TMP3;
}

// Missing File Filler, Still has debug, figure out settings hierarchy
void ModPack_Settings(string SelectedModPack,string ModPackDir){
    cout << "Checking for settings" << endl;
    bool Settings_Check;

    // Check for settings file , doesnt return if it actually there yet
    string TMP1 = ModPackDir;
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

    ofstream outfile (TMP1);
    outfile << "Test ModPack Settings File" << std::endl;
    outfile.close();


    return;
}


