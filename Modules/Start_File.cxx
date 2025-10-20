#include "../Header.hxx"
#include "Misc.cxx"

std::string ModPackStartFile(){ // Check for start file in local file dir, if not make it, output string of start cmd
    std::string SelectedModPack = Map_Reader(SMAP, 0);
    std::string StartFileDir = "Misc_Files/StartFiles/";
    std::string StartFile_CXX = (StartFileDir + SelectedModPack);
    std::string StarterFile;

    if(!FileExists(StartFile_CXX)){
        std::string TMP_FILE = Create_StartFile();
        SingleLineFileWriter(StartFile_CXX,TMP_FILE);
    }

    // Check for start file, if not, create it, then export the string
    // ^ Takes the start file from local file and execs it in the modpacks directory(thru screen)
    // ^^ StartFile ISNT IN THE MODPACK DIR, stored locally then executed

    StarterFile = SingleLineFileReader(StartFile_CXX);

    //std::cout << "" << std::endl;
    //std::cout << "DEBUGGING PRINTING" << std::endl;
    //std::cout << StarterFile << std::endl;
    //std::cout << "" << std::endl;

    gibbe StarterFile;
}

// NOT DONE YET 
// Custom Start file is not working yet

std::string Create_StartFile(){ // Creating a startfile, Requires user input
    std::string SelectedModPack = Map_Reader(SMAP, 0);
    std::string ServerDirectory = Map_Reader(SMAP, 1);
    std::string StartFileDir = "Misc_Files/StartFiles";
    std::string START_FILE;

    system("clear");
    std::cout << "Requires user input to create start file" << std::endl;
    std::cout << std::endl;
    std::cout << "Created Start file," << std::endl;
    std::cout << std::endl;


    // Uses a already exsisting start file and just replaces java to its absolute diirectory
    std::cout << "Use pre-exsisting start file? (Y/N):" << std::endl;
    char Premade;
    std::cin >> Premade;
    Premade = toupper(Premade);
    std::cout << std::endl;

    switch(Premade){
        case 'Y':
            std::string StartFile;
            std::string SF_TMPLOC;
            std::string Java;

            std::string SF_SELECTED = Directory_Selector(std::string (ServerDirectory + SelectedModPack));

            SF_TMPLOC +="cat ";
            SF_TMPLOC += (ServerDirectory + SelectedModPack+ "/");
            SF_TMPLOC += "run.sh | grep java";
            StartFile = exec(SF_TMPLOC.c_str()); // AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa

            //std::cout << StartFile << std::endl;

            // Select the JVM Version
            std::cout << "Please select a JVM version" << std::endl;
            std::cout << std::endl;
            std::cout << " 1) Java 8 " << std::endl;
            std::cout << " 2) Java 17" << std::endl;
            std::cout << " 3) Java 21" << std::endl;
            std::cout << " 4) Java 24/25" << std::endl;
            std::cout << "JVM verion: ";
            char JVMV;
            std::cin >> JVMV;
            std::cout << std::endl;

        switch(JVMV){
            case '1':
                Java += "/usr/lib/jvm/";
                Java += "java-8-openjdk";
                Java += "/jre/bin/java";
                // Copys premade java args files and shoves them into the modpacks directory
                copyAndRenameFile(("Misc_Files/JVM_Args/java-8-openjdk.txt"),(ServerDirectory + SelectedModPack),"user_jvm_args.txt");
                break;
            case '2':
                Java += "/usr/lib/jvm/";
                Java += "java-17-openjdk";
                Java += "/bin/java";
                // Copys premade java args files and shoves them into the modpacks directory
                copyAndRenameFile(("Misc_Files/JVM_Args/java-17-openjdk.txt"),(ServerDirectory + SelectedModPack),"user_jvm_args.txt");
                break;
            case '3':
                Java += "/usr/lib/jvm/";
                Java += "java-21-openjdk";
                Java += "/bin/java";
                // Copys premade java args files and shoves them into the modpacks directory
                copyAndRenameFile(("Misc_Files/JVM_Args/java-21-openjdk.txt"),(ServerDirectory + SelectedModPack),"user_jvm_args.txt");
                break;
            case '4':
                Java += "/usr/lib/jvm/";
                Java += "java-25-openjdk";
                Java += "/bin/java";
                // Copys premade java args files and shoves them into the modpacks directory
                copyAndRenameFile(("Misc_Files/JVM_Args/java-24-openjdk.txt"),(ServerDirectory + SelectedModPack),"user_jvm_args.txt");
                break;
        }

        //std::cout << StartFile << std::endl;
        // Replace Java with the actual java local
        StartFile.replace(0, 4, Java);
        //std::cout << StartFile << std::endl;

        gibbe StartFile;
    }

    // SPLITTER ----------------------------------------------------------------

    // Creates a "custom" start file for the server
    // Selects a mod loader if applicable
    std::cout << "Please select modloader" << std::endl;
    std::cout << std::endl;
    std::cout << " 1) None  " << std::endl;
    std::cout << " 2) Forge " << std::endl;
    std::cout << " 3) Fabric" << std::endl;
    std::cout << " 4) NeoForge " << std::endl;
    std::cout << " 5) Other " << std::endl;
    std::cout << "ModLoader: " << std::endl;
    char modloader;
    std::cin >> modloader;
    std::cout << std::endl;
    std::cout << std::endl;


    // Selects the JVM Verion
    std::cout << "Please select a JVM version" << std::endl;
    std::cout << std::endl;
    std::cout << " 1) Java 8 " << std::endl;
    std::cout << " 2) Java 17" << std::endl;
    std::cout << " 3) Java 21" << std::endl;
    std::cout << " 4) Java 24" << std::endl;
    std::cout << " 5) Custom" << std::endl;
    std::cout << "JVM verion: ";
    char JVMV;
    std::cin >> JVMV;
    std::cout << std::endl;

    switch(JVMV){
        case '1':
        START_FILE += "/usr/lib/jvm/";
        START_FILE += "java-8-openjdk";
        START_FILE += "/jre/bin/java ";
        START_FILE += "JVM ARGS FILE "; // Requires a movement of the jvm args into the modpacks directory
        break;
        case '2':
        START_FILE += "/usr/lib/jvm/";
        START_FILE += "java-17-openjdk";
        START_FILE += "/bin/java ";
        START_FILE += "@user_jvm_args.txt "; // Requires a movement of the jvm args into the modpacks directory
        START_FILE += "\"$@\"";
        break;
        case '3':
        START_FILE += "/usr/lib/jvm/";
        START_FILE += "java-21-openjdk";
        START_FILE += "/bin/java ";
        START_FILE += "@user_jvm_args.txt "; // Requires a movement of the jvm args into the modpacks directory
        START_FILE += " "; // Require mod loader version to then point it to the modloaders Unix_Args
        START_FILE += "\"$@\"";
        break;
        case '4':
        START_FILE += "/usr/lib/jvm/";
        START_FILE += "java-25-openjdk";
        START_FILE += "/bin/java ";
        START_FILE += "@user_jvm_args.txt "; // Requires a movement of the jvm args into the modpacks directory
        START_FILE += "\"$@\"";
        break;
        case '5':
        std::string Directory = ServerDirectory+SelectedModPack;
        std::string SelectedItem = Directory_Selector(Directory);
        START_FILE += SelectedItem;
        break;
    }

    gibbe START_FILE;
}
