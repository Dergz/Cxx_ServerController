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

