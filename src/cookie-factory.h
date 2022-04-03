#ifndef COOKIE_FACTORY_COOKIE_FACTORY_H
#define COOKIE_FACTORY_COOKIE_FACTORY_H

#include <string>
#include <vector>

// Configure options
static struct programOptions {
    bool verbose = false;
    std::vector<std::string> subs;
    std::vector<std::string> paths;
} settings;

// Function prototypes
void process();

#endif //COOKIE_FACTORY_COOKIE_FACTORY_H
