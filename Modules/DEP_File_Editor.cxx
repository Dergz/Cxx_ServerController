// MODULE, Controlls & Manipulates A File (Ment for Settings file)
#include "../Base_Includes.cxx" //Lib Includes


// READING FILE MUST BE SPECIFIED OR IN MAIN DIRECTORY OF CONTROLLER
// Establishes the functions so they can be called out of order
pairss File_Reader(string,string);          // What file and thing to find, Return what the setting is,, Abit redundant but oh well
pairss File_Writer(string,string,string);   // What file and thing to change and what to change it too, Return what the setting now is
int File_Determine_Line(string,string);     // What file and what setting, Returns what line its on
void Default_Settings();                    // Ensures the setting file exsists, if not create and set def values



void TMP_TEST(){ // TESTING IF LINE GRABBER WORKS
    cout << "TESTING FILE FUNCTIONS; " << endl;
    string FileName = "Modules/test_input.txt";
    string Setting = "Anot";
    int TMP_INT = File_Determine_Line(string(FileName), string(Setting));
    cout << "LINE DETECTOR: "<< TMP_INT << endl;
    cout;
}



// Reads a file and determines what input is set too
pairss File_Reader(string FileName,string Setting){
    pairss Output;      // Contains setting name and its set value, Is whats returned
    int SettingLine = File_Determine_Line(FileName,Setting);    // Line containing that setting


    ifstream file(FileName); //Ex code, to be changed, CHANGE MEEEE
    if (file.is_open()) {
        //Do something with line
        //while ( getline (file,SettingLine) ){
        while( getline(ifstream&& input, string& str )){
            cout << SettingLine << '\n';
        }
        file.close();
    }
    else {
        cerr << "Oopsie doopsie" << endl; //maybe change to cout?
    }


    // Last Line
    return Output;
}



// Reads a file, then writes the setting
pairss File_Writer(string FileName,string Setting,string NewInput){
    pairss Output;      // Contains setting name and its set value, Is whats returned
    int SettingLine = File_Determine_Line(FileName,Setting);    // Line containing that setting
    cout << "Line is: " << SettingLine << endl; //DEBUG



    // Last Line
    return Output;
}



// Determines what line something is on, IF -1 ERROR OUT
int File_Determine_Line(string FileName,string Setting){
    // Open the file for reading
    ifstream file(FileName); 
    if (!file.is_open()){
        cout << "Unable to open file: " << FileName << endl;
        return -1; // indicate error opening file
    }

    string line;
    int lineNum = 0;

    // Read file line-by-line and look for the Setting as a substring
    while (getline(file, line)) {
        cout << "DEBUG: entered loop, cycle: " << lineNum << endl;
        ++lineNum;
        if (line.find(Setting) != string::npos) {
            // Found the setting on this line (1-based)
            file.close();
            return lineNum;
        }
    }

    // Not found
    file.close();
    cout << "Element not found";
    return -1;
}



//Checks for settings file, if not there then create and set defaults
void Default_Settings(){

}

