#include "../Header.hxx"
#include <array>
#include <algorithm>
#include <fstream>

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



int copyAndRenameFile(const std::string& sourceFilePath, const std::string& destinationDir, const std::string& newFileName) {
    try {
        // Convert strings to paths
        std::filesystem::path sourcePath(sourceFilePath);
        std::filesystem::path destDirPath(destinationDir);
        std::filesystem::path destFilePath = destDirPath / newFileName;

        // Check source file
        if (!std::filesystem::exists(sourcePath) || !std::filesystem::is_regular_file(sourcePath)) {
            std::cerr << "Error: Source file does not exist or is not a regular file.\n";
            return -1;
        }

        // Create destination directory if it doesn't exist
        if (!std::filesystem::exists(destDirPath)) {
            std::filesystem::create_directories(destDirPath);
        }

        // Copy the file with overwrite option
        std::filesystem::copy_file(
            sourcePath,
            destFilePath,
            std::filesystem::copy_options::overwrite_existing
        );

        std::cout << "Success: File copied and renamed to: " << destFilePath << "\n";
        return 1;

    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << "\n";
        return -1;
    } catch (const std::exception& e) {
        std::cerr << "General error: " << e.what() << "\n";
        return -1;
    }
}