#include <sys/stat.h>
#include "Utility.h"

bool fileExists(const std::string &filename) {
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1) {
        return true;
    }
    return false;
}