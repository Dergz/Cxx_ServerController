#include "../Header.hxx"

void Server_Starter(){
    std::cout << "Starting server Init process" << std::endl;
    std::cout << "Selected Server: " << Map_Reader(SMAP, 0) << std::endl;
    std::cout << "Server Directory: " << Map_Reader(SMAP, 1) << std::endl;
    std::cout << std::endl;
    Screen_Controller();
    std::cout << std::endl;
    Test_For_JavaInst();

    system("Sleep 20");
    Server_Menu();
}

void Screen_Controller(){
    std::string SelectedModPack = Map_Reader(SMAP, 0);
    std::string ServerDirectory = Map_Reader(SMAP, 1);

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
    TMP2 += ServerDirectory;
    TMP2 += " \\n\"";
    // system(TMP2.c_str()); //UN COMMENT ON FULL CODE TEST
    std::cout << TMP2 << std::endl;
    system("sleep 1");


    // Starts the mod pack
    std::string TMP3("screen -r ");
    TMP3 += SelectedModPack;
    TMP3 += "\" -X stuff ";
    TMP3 += ModPackStartFile();
    TMP3 += " \\n\"";
    // system(TMP3.c_str()); //UN COMMENT ON FULL CODE TEST
    std::cout << TMP3 << std::endl;
}

void Test_For_JavaInst(){
    if ( system("pidof java") == 0 ){
        std::cout << "Server is running" << std::endl;
    }
    else{
        std::cout << "Server Didnt Start" << std::endl;
    }
}

int TFJI_int(){
    int TMP1;
    if ( system("pidof java") == 0 ){
        //std::cout << "DS:TRUE" << std::endl;
        TMP1 = 1;
    }
    else{
        //std::cout << "DS:FALSE" << std::endl;
        TMP1 = 0;
    }
    system("clear");
    return TMP1;
}

std::string ModPackStartFile(){ // NOT DONE YET
    //should store settings file withing the program folder not the modpacks
    // read from a file, if not there then make said file

    std::string SelectedModPack = Map_Reader(SMAP, 0);
    std::string ServerDirectory = Map_Reader(SMAP, 1);

    std::cout << "Debugging:" << std::endl;

    return "DEBUG";

}

void Screen_Killer(){ // pushes a exit statment to java, once dead kill screen session
    std::cout << "Killing running serevr" << std::endl;

    int TMP2 = TFJI_int();
    int TMP3 = 0;

    if(TMP2 >= 1){
        std::cout << "Server Shutdown Started" << std::endl;
        TMP3 = 1;
    }
    else{
        std::cout << "No running Server" << std::endl;
        return;
    }

    if(TMP3 = 1){
        int Timer = 0;

        std::string TMP1("screen -r ");
        TMP1 += Map_Reader(SMAP, 0);
        TMP1 += "\" -X stuff exit \\n\"";
        system(TMP1.c_str());

        while(Timer < 120){
            if(TFJI_int == 0){
                Timer = 1000;
            }
            Timer ++;
            system("sleep 1");
        }
        std::cout << "Server Killed" << std::endl;
    }

    return;
}