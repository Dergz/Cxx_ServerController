#include "../Header.hxx"

void SZController(int,std::string);



void SZController(int InOpt){
    std::string SelectedModPack = Map_Reader(SMAP, 0);
    std::string ServerDirectory = Map_Reader(SMAP, 1);
    std::string Archives = Map_Reader(SMAP, 2);
    std::string NewPacks = Map_Reader(SMAP, 3);

    system("clear");

    switch(InOpt){
    case 1:
        // Archiving
        break;
    case 2:
        // New Packs
        break;
    }
}



void SZComp(std::string);

void SZComp(std::string){
    std::cout << " Entering Compression " << std::endl;
}