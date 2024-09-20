#include <fstream>
#include <chrono>
#include "Compiler.h"

using namespace Noble::Compiler;

/**
 * @param fileName The name of the file whose contents we want to read
 * @return The contents of the file, unformatted, as a std::string
 */
std::string ReadFile(const std::string& fileName)
{
    std::ifstream file(fileName);
    file.seekg(0, std::ios::end);
    const long size = file.tellg();
    std::string buffer(size, ' ');
    file.seekg(0);
    file.read(&buffer[0], size);
    return buffer;
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
        const std::string fileContents = ReadFile(argv[i]);
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
