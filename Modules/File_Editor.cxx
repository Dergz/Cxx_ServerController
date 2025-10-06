// MODULE, Controlls & Manipulates A File (Ment for Settings file)
#include "../Base_Includes.cxx" //Lib Includes


// Establishes the functions so they can be called out of order
pairss File_Reader(string,string);          // What file and thing to find, Return what the setting is,, Abit redundant but oh well
pairss File_Writer(string,string,string);   // What file and thing to change and what to change it too, Return what the setting now is
int File_Determine_Line(string,string);     // What file and what setting, Returns what line its on
void Default_Settings();                    // Ensures the setting file exsists, if not create and set def values


// Reads a file and determines what input is set too
pairss File_Reader(string FileName,string Setting){
    pairss Output;      // Contains setting name and its set value, Is whats returned
    int SettingLine = File_Determine_Line(FileName,Setting);    // Line containing that setting

    ifstream file(FileName); //Ex code, to be changed
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            //Do something with line
        }
        file.close();
    }
    else {
        cerr << "Oopsie doopsie" << endl;
    }

    // Last Line
    return Output;
}


// Reads a file, then writes the setting
pairss File_Writer(string FileName,string Setting,string NewInput){
    pairss Output;      // Contains setting name and its set value, Is whats returned
    int SettingLine = File_Determine_Line(FileName,Setting);    // Line containing that setting



    // Last Line
    return Output;
}


// Determines what line something is on
int File_Determine_Line(string FileName,string Setting){
    int Output;

    // Last Line
    return Output;
}


//Checks for settings file, if not there then create and set defaults
void Default_Settings(){

}