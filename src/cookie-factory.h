#ifndef COOKIE_FACTORY_COOKIE_FACTORY_H
#define COOKIE_FACTORY_COOKIE_FACTORY_H

#include <string>
#include <vector>

typedef std::vector<std::string> vectorOfStrings;

// Configure options
struct programOptions {
    bool verbose = false;
    bool noActions = false;
    vectorOfStrings jsonFile;
    vectorOfStrings templatePaths;
    std::string outputDirectory;
    std::string baseDirectory;
};

extern programOptions settings;

// Function prototypes
void process();

#endif //COOKIE_FACTORY_COOKIE_FACTORY_H
