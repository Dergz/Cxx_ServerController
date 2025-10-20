#include "../Header.hxx"

// Takes in a command in CMD.c_str() format and return its output
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;

    // Use function pointer type explicitly to avoid GCC attribute warning
    using pipe_ptr = std::unique_ptr<FILE, int(*)(FILE*)>;

    pipe_ptr pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen failed!");
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}

// Shrug tbh X3
struct FileCloser {
    void operator()(FILE* file) const {
        if (file) pclose(file);
    }
};

// Doesnt actually get pid just return if it detects the procces in the /proc directory
int getPidOfProcess(const std::string& processName) {
    for (const auto& entry : std::filesystem::directory_iterator("/proc")) {
        if (!entry.is_directory()) continue;

        std::string pidStr = entry.path().filename().string();

        // Skip non-numeric directories
        if (!std::all_of(pidStr.begin(), pidStr.end(), ::isdigit)) continue;

        std::ifstream commFile(entry.path() / "comm");
        if (!commFile.is_open()) continue;

        std::string name;
        std::getline(commFile, name);

        if (name == processName) {
            return 1;  // Found a matching process
        }
    }

    return -1;  // No matching process found
}
