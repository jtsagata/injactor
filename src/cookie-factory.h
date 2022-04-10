#ifndef COOKIE_FACTORY_COOKIE_FACTORY_H
#define COOKIE_FACTORY_COOKIE_FACTORY_H

#include <string>
#include <vector>
#include <filesystem>

typedef std::vector<std::string> vectorOfStrings;

// Configure options
struct programOptions {
    std::string jsonFile;
    std::string templatePath;
};


// Function prototypes
void process(const programOptions &options);


#endif //COOKIE_FACTORY_COOKIE_FACTORY_H
