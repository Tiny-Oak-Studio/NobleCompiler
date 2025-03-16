#include <fstream>
#include <chrono>
#include "Compiler.h"

using namespace Noble::Compiler;

/**
 * @param fileName The name of the file whose contents we want to read
 * @param fileBuffer Reference to a string where the file contents are stored
 * @return The contents of the file, unformatted, as a std::string
 */
bool ReadFile(const std::string& fileName, std::string& fileBuffer)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "Failed to open file '" << fileName << "'\n";
        return false;
    }
    file.seekg(0, std::ios::end);
    const long size = file.tellg();
    std::string buffer(size, ' ');
    file.seekg(0);
    file.read(&buffer[0], size);
    fileBuffer = buffer;
    return true;
}

int main(const int argc, char** argv)
{
    //If argc == 1, no arguments were provided
    if (argc == 1)
    {
        std::cout << "Usage: 'noblec filename.extension'\n";
        return 0;
    }

    //Start compile timer
    typedef std::chrono::high_resolution_clock clock;
    typedef std::chrono::duration<float> duration;
    const clock::time_point start = clock::now();

    //Assume each arg is the name of a file to be compiled
    for (int i = 1; i < argc; ++i)
    {
        std::string fileContents;
        if (!ReadFile(argv[i], fileContents))
        {
            return -1;
        }
        const std::string fileTitle = argv[i];
        const std::string fileName = fileTitle.substr(0, fileTitle.find_first_of('.'));

        if (Compiler compiler; !compiler.Compile(fileContents, fileName))
        {
            std::cout << "Error compiling '" << argv[i] << "'\n";
            return -1;
        }
    }

    const duration elapsed = clock::now() - start;
    std::cout << "Compilation succeeded in " << elapsed.count() << "s\n";
    return 0;
}
