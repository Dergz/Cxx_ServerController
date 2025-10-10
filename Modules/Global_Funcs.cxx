#include "../Header.hxx"

// Inits the "config" map
std::unordered_map<int,std::string> Mapping_INIT_DEP(){
    std::unordered_map<int,std::string> ConfigMap ={
    {0, "Null"},    //Current ModPack
    {1, "X"},       //Unassigned
    {2, "Y"}        //Unassigned
    };

    for (auto i : ConfigMap){
        std::cout << i.first << ": " << i.second << std::endl;
    }


    std::cout << std::endl;
    std::cout << "Split_Debug" << std::endl;

    return ConfigMap;
}

void Mapping_INIT(){
    SMAP ={
    {0, "Null"},    //Current ModPack
    {1, "X"},       //Unassigned
    {2, "Y"}        //Unassigned
    };

    for (auto i : SMAP){
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

