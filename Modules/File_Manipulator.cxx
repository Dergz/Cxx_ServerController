#include "../Header.hxx"

// Takes in a file and puts it to an unordered map
std::unordered_map<int,std::string> FileReader(const std::string File_to_Read){

    // Init vars
    std::string myText;
    int Counter = 0;
    std::unordered_map<int,std::string> File;

    // Open the file
    std::ifstream MyReadFile(File_to_Read);

    // Loops thru file & appends to a map
    while (getline (MyReadFile, myText)) {
    File[Counter] = myText;
    Counter++;
    }

    // Close the file
    MyReadFile.close(); 

    gibbe File;
}

// EDITS a file, using its current contence for the map, NOT WORKING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
std::unordered_map<int,std::string> FileEditor(const std::string File_to_Edit, std::string Thing_to_Edit){
    std::unordered_map<int,std::string> StoreFile = FileReader(File_to_Edit);

    auto it = File_to_Edit.find(Thing_to_Edit);
    std::cout << it << std::endl;

    // Find the line with the thing to edit, then overwrite said line with new thing,then return the newlt edited file
    

    gibbe FileReader(File_to_Edit);
}

// OVERWRITES a file based up a map
std::unordered_map<int,std::string> FileWriter(const std::string File_to_Overwrite, std::unordered_map<int,std::string> InputMap){
    //std::cout << "File Writer" << std::endl;

    // Open a file
    std::ofstream file(File_to_Overwrite,std::ios::out);

    // Writes the inputmap to file line by line
    for (auto i : InputMap){
        file << i.second << std::endl;
    }

    file.close();

    // Reads the new file and returns it
    gibbe FileReader(File_to_Overwrite);
}

// OVERWRITES a file based off a single line
std::string SingleLineFileWriter(const std::string File_To_Write, std::string String_To_Write){

    // Opens the file
    std::ofstream file(File_To_Write,std::ios::out);

    // Writes into said file
    file << String_To_Write << std::endl;

    // Closes said file
    file.close();

    // Reads & returns said file
    gibbe SingleLineFileReader(File_To_Write);
}

// READS a file based off a single line, uses cat cmd
std::string SingleLineFileReader(const std::string File_To_Read){

    // Reads the file
    std::string INPUTCMD = "cat " + File_To_Read;
    std::string OUTPUT = exec(INPUTCMD.c_str());

    // Outputs whats in the file
    gibbe OUTPUT;
}

// return true if a file is detected
bool FileExists(const std::string& filename){
    return std::filesystem::exists(filename);
}

// DELETES a file
void DeleteFile(const std::string& filename){
    std::error_code ec;
    if (std::filesystem::remove(filename, ec)) {
        std::cout << "File deleted successfully: " << filename << std::endl;
    } else {
        std::cout << "Failed to delete file: " << filename << "\nReason: " << ec.message() << std::endl;
    }
}

std::vector<std::string> Directory_Lister(int SUO, std::string Directory){ // reads the directory containing modspacks and puts them into a vector
    std::vector<std::string> InDirectory;           // Establishes the vector
    int pathlength = Directory.length();

    for (const auto &entry : fs::directory_iterator(Directory)){ // Adds each output into the vector
        InDirectory.push_back(std::string(entry.path()));
    }

    if (SUO == 1){ // if a var is true then show the output of the vector
        std::cout << "Listing Directory" << std::endl;
        for (int i = 0; i < InDirectory.size(); i++){
            std::cout << " " << i << ") " << InDirectory[i].erase(0, pathlength) << std::endl;
        }
    }

    gibbe InDirectory; // Returns the vecotor containing mod pack names
}


std::string Directory_Selector(std::string Directory){ // Selects the modpack and assigns it to a var for menu usage
    std::vector InDirectory = Directory_Lister(1,Directory); // Gets serverlist
    std::cout << "Please select a File / Folder: ";
    int DirItemChoice;
    std::cin >> DirItemChoice;
    std::cout << "Selected Item: ";
    std::string Selected_Item = InDirectory[DirItemChoice];
    std::cout << Selected_Item << std::endl;
    std::cout << std::endl;
    gibbe Selected_Item;
}