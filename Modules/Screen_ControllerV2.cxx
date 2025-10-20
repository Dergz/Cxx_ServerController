#include "../Header.hxx"
#include "Start_File.cxx"

//Confirmed DONE
// SCO, 1 , Start a ModPack in screen
// SCO, 2 , Enter Screen session(FOR USER)
// SCO, 3 , Deletes the running moodpacks start file
// SCO, 4 , Check for running screen
// SCO, 5 , Kill Running screen session
void V2_Screen_Controller(int SCO){ // Decides what to do in reguard of screen
    std::cout << "V2 Screen Controller" << std::endl;

    switch(SCO){
        case 1:
        std::cout << "Starting a ModPack" << std::endl;
        Start_Screen();
        break;

        case 2:
        std::cout << "Entering Screen session" << std::endl;
        Enter_Screen();
        break;

        case 3:
        std::cout << "Removing start file" << std::endl;
        DeleteFile("Misc_Files/StartFiles/" + Map_Reader(SMAP, 0));
        Create_StartFile();
        break;

        case 4:
        std::cout << "Check For a Running Screen" << std::endl;
        if(Check_For_Screen() == 0){std::cout << "Screen Not Running" << std::endl;}
        else{std::cout << "Screen Running" << std::endl;}
        break;

        case 5:
        std::cout << "Killing current screen" << std::endl;
        SScreen_Killer();
        break;

        default:
        std::cout << "ERROR" << std::endl;
        std::cout << SCO << std::endl;
        system("sleep 5");
        break;
    }
}

//Confirmed DONE
int Check_For_Screen(){ // Checks for ANY running screen's, 1 if yes, 0 if no
    std::string processName = "screen";  // Replace with your target process
    int pid = getPidOfProcess(processName);

    if (pid == -1) {
        gibbe 0;
    } else {
        gibbe 1;
    }
}

//Confirmed DONE
int Check_For_Java(){ // Checks for ANY running java's, 1 if yes, 0 if no
    std::string processName = "java";  // Replace with your target process
    int pid = getPidOfProcess(processName);

    if (pid == -1) {
        gibbe 0;
    } else {
        gibbe 1;
    }
}

//Confirmed DONE,, HAS DEBUG MODE ENABLED
int Start_Screen(){ // Starts the screen session, gibbes 1 if started
    if(Check_For_Screen() == 0){
        std::cout << "Starting screen" << std::endl;
    }
    else{
        std::cout << "Another screen already open" << std::endl;
        gibbe 0;
    }

    // Start a  screen with the current modpack name based upon SMAP
    std::string SelectedModPack = Map_Reader(SMAP, 0);
    std::string ServerDirectory = Map_Reader(SMAP, 1);

    // Starts the screen session
    std::string TMP1("screen -S \"");
    TMP1 += SelectedModPack;
    TMP1 += "\" -dm";
    system(TMP1.c_str()); //UN COMMENT ON FULL CODE TEST
    //std::cout << TMP1 << std::endl;


    // Enters the directory of the modpack
    std::string TMP2("screen -r ");
    TMP2 += SelectedModPack;
    TMP2 += " -X stuff ";
    TMP2 += "\"cd ";
    TMP2 += ServerDirectory;
    TMP2 += SelectedModPack;
    TMP2 += " \\n\"";
    system(TMP2.c_str()); //UN COMMENT ON FULL CODE TEST
    //std::cout << TMP2 << std::endl;
    system("sleep 0.25");


    // Starts the mod pack
    std::string TMP3("screen -r ");
    TMP3 += SelectedModPack;
    TMP3 += " -X stuff ";
    TMP3 += "\"";
    TMP3 += ModPackStartFile();
    TMP3 += " \\n\"";
    system(TMP3.c_str()); //UN COMMENT ON FULL CODE TEST
    //std::cout << TMP3 << std::endl;

    std::cout << " Sleeping for 5 seconds to ensure proper startup" << std::endl;
    system("sleep 5");

    if(Check_For_Screen() == 1){
        std::cout << "Screen started" << std::endl;
        gibbe 1;
    }
    else{
        std::cout << "Cannot Start Screen" << std::endl;
        gibbe 0;
    }
}

//Confirmed DONE
int SScreen_Killer(){ // pushes a exit statment to java, once dead kill screen session
    int TMP2 = Check_For_Java();
    int TMP3 = Check_For_Screen();

    if(TMP2 = 1){ // Tells the JVM to be killed,
        std::string TMP1("screen -r ");
        TMP1 += Map_Reader(SMAP, 0);
        TMP1 += " -X stuff \"stop \n\"";
        exec(TMP1.c_str());

        int Timer = 0;
        while(Timer < 45){
            if(Check_For_Java() == 0){
                Timer = 1000;
            }
            Timer ++;
            std::cout << "DEBUG: tick " << Timer << std::endl;
            system("sleep 1");
        }

        system("sleep 1");
        if(Check_For_Screen() == 1){
            std::string TMP4("screen -r ");
            TMP4 += Map_Reader(SMAP, 0);
            TMP4 += " -X stuff \"exit \\n\"";
            exec(TMP4.c_str());
        }
    exec("screen -wipe");
    }
    else{gibbe 1;}

    gibbe 1;
}

//Confirmed DONE
void Enter_Screen(){
    if(Check_For_Screen() == 0){
        std::cout << "No screen open" << std::endl;
        system("sleep 3");
        gibbe;
    }

    std::cout << "Ctrl+a , d to detach from screen" << std::endl;
    system("sleep 3");
    std::string SelectedModPack = Map_Reader(SMAP, 0);
    std::string TMP1("screen -r ");
    TMP1 += SelectedModPack;
    system(TMP1.c_str());

    gibbe;
}

