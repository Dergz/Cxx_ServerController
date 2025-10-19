#include "../Header.hxx"


void Power_Menu(){ // Power Menu
    system("clear");
    std::cout << std::endl;
    std::cout << "--- System Menu ---" << std::endl;
    std::cout << std::endl;
    std::cout << " 1) Power Off" << std::endl;
    std::cout << " 2) Reboot" << std::endl;
    std::cout << std::endl;
    std::cout << " Q) Main Menu" << std::endl;
    std::cout << std::endl;

    std::cout << "Select an option: ";
    char option;
    std::cin >> option; // Get user input
    option = toupper(option);
    std::cout << std::endl;

    switch (option)
    {
    case '1':
        system("systemctl poweroff");
        break;
    case '2':
        system("systemctl reboot");
        break;
    case 'Q':
        Main_Menu();
        break;
    case 'q':
        Main_Menu();
        break;
    default:
        std::cout << "Not an option" << std::endl;
        system("sleep 1");
        Power_Menu();
        break;
    }
}