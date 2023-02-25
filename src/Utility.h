#include <iostream>
#include <fstream>

/**
 * @brief Check if file already exists
 * Utility function
 *
 * @param filename
 * @return true file with name "filename" exists
 * @return false no matching file found
 */
bool fileExists(const std::string &filename);