#include "../Header.hxx"

// Define the global SMAP (matches 'extern' in Header.hxx)
std::unordered_map<int,std::string> SMAP;

// Inits the "config" map
void Mapping_INIT(){
    // populate the global SMAP
    SMAP.clear();
    SMAP[0] = "Null";    // Current ModPack
    SMAP[1] = "X";       // Unassigned
    SMAP[2] = "Y";       // Unassigned

    for (const auto &i : SMAP){
        std::cout << i.first << ": " << i.second << std::endl;
    }
}


// Reads something out of the maping
std::string Map_Reader(std::unordered_map<int,std::string> SMAP, int Element){
    std::string OUTPUT;

    // Finding element with Element
    auto it = SMAP.find(Element);

    // Displays that element
    if (it != SMAP.end()){
        std::cout << it->first << ": " << it->second;
        std::string OUTPUT = it->second;
        return OUTPUT;
    }

    //Error Condition, should never trigger
    else std::cout << "Not Found";
    return "ERROR";
}


std::unordered_map<int,std::string> Map_Changer(std::unordered_map<int,std::string> SMAP, int Element, string NewElVal){

    // Finding element with Element
    auto it = SMAP.find(Element);

    // Displays that element
    if (it != SMAP.end()){
        std::cout << it->first << ": " << it->second;
    }

    // Updating value associated with key 2
    // using [] operator
    SMAP[Element] = NewElVal;
    cout << SMAP[Element] << endl;
    return SMAP;
}

