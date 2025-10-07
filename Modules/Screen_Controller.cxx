#include "../Base_Includes.cxx"

void Server_Starter(string SelectedModPack);
void Enter_Screen(string SelectedModPack);
int Screen_Controller(string SelectedModPack, string ModPackDir);
void ModPack_Settings();

void Server_Starter(string SelectedModPack, string ModPackDir){ //Main ModPack Controller, Tie Together
    cout << "Starting Server" << endl;
    cout << "Selected Pack: " << SelectedModPack << endl;
    cout << "Server Direct: " << ModPackDir << endl;
    Screen_Controller(SelectedModPack,ModPackDir);
}

int Screen_Controller(string SelectedModPack, string ModPackDir){
    cout << "Screen opening for : " << SelectedModPack << endl;

    // Starts the screen session
    string TMP1("screen -S ");
    TMP1 += SelectedModPack;
    TMP1 += "  -dm";
    system(TMP1.c_str());

    // Enters the directory of the modpack
    string TMP2("screen -r ");
    TMP2 += SelectedModPack;
    TMP2 += " -X stuff ";
    


    system(TMP2.c_str());
    system("sleep 1");

    // Starts the mod pack
    system("sleep 1");
    system("sleep 1");

    // Wipe Screen
    system("clear");

    // Test if screen session is started
    // ^ If is running then return true, else false
    //  ^ If false == error

    // From Bash Scripts
    //screen -S "$Selected_Server" -dm
    //screen -r "$Selected_Server" -X stuff $"cd $ModPack_Folder \n"
    //sleep 1
    //screen -r "$Selected_Server" -X stuff $"$NRs\n"
    //sleep 1
}