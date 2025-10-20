#include "../Header.hxx"

void updateSystem(){
    system("clear");
    std::cout << std::endl;
    std::cout << "--- System Update ---" << std::endl;
    std::cout << std::endl;

    // Check if screen is installed
    if (system("command -v screen >/dev/null 2>&1") != 0)
    {
        std::cout << "Error: 'screen' is not installed. Please install it with:" << std::endl;
        std::cout << "  sudo pacman -S screen" << std::endl;
        std::cout << std::endl;
        std::cout << "Press Enter to return to the menu...";
        std::cin.ignore();
        std::cin.get();
        Power_Menu();
        return;
    }

    // Check if yay is installed
    if (system("command -v yay >/dev/null 2>&1") != 0)
    {
        std::cout << "Error: 'yay' is not installed. Please install it with:" << std::endl;
        std::cout << "  sudo pacman -S yay" << std::endl;
        std::cout << std::endl;
        std::cout << "Press Enter to return to the menu...";
        std::cin.ignore();
        std::cin.get();
        Power_Menu();
        return;
    }

    // Verify passwordless sudo for pacman
    std::cout << "Checking sudo configuration..." << std::endl;

    // This works even if sudo -n isn't supported: it will only refresh credentials if passwordless sudo works
    int sudoCheck = system("timeout 2 sudo -v >/dev/null 2>&1");

    if (sudoCheck != 0)
    {
        std::cout << std::endl;
        std::cout << "Passwordless sudo is not correctly configured for pacman." << std::endl;
        std::cout << "To enable automatic updates, add this line using 'sudo visudo':" << std::endl;
        std::cout << std::endl;
        std::cout << "  " << getenv("USER") << " ALL=(ALL) NOPASSWD: /usr/bin/pacman" << std::endl;
        std::cout << std::endl;
        std::cout << "Then rerun this option." << std::endl;
        std::cout << std::endl;
        std::cout << "Press Enter to return to the menu...";
        std::cin.ignore();
        std::cin.get();
        Power_Menu();
        return;
    }

    std::cout << "Starting system update in background (screen: update_system)..." << std::endl;

    // Clean up any previous session or flag
    system("screen -S update_system -X quit >/dev/null 2>&1");
    system("rm -f /tmp/update_done");

    // Start update (yay handles sudo internally when needed)
    system("screen -dmS update_system bash -c 'yay -Syu --noconfirm; touch /tmp/update_done'");

    bool done = false;
    std::cout << "Updating";
    std::cout.flush();

    while (!done)
    {
        FILE *file = fopen("/tmp/update_done", "r");
        if (file)
        {
            fclose(file);
            done = true;
        }
        else
        {
            std::cout << ".";
            std::cout.flush();
            system("sleep 5");
        }
    }

    // Cleanup any remaining screen session safely
    system("screen -S update_system -X quit >/dev/null 2>&1");
    system("screen -wipe >/dev/null 2>&1");
    system("rm -f /tmp/update_done");

    std::cout << std::endl;
    std::cout << "System update completed successfully." << std::endl;
    std::cout << std::endl;
    std::cout << "Press Enter to return to the menu...";
    std::cin.ignore();
    std::cin.get();
    Power_Menu();
}




void Power_Menu(){ // Power Menu
    system("clear");
    std::cout << std::endl;
    std::cout << "--- System Menu ---" << std::endl;
    std::cout << std::endl;
    std::cout << " 1) Power Off" << std::endl;
    std::cout << " 2) Reboot" << std::endl;
    std::cout << " 3) Update System" << std::endl;
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
    case '3':
        updateSystem();
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