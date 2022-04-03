#include <iostream>
#include <cxxopts.hpp>

#include "config.h"
#include "cookie-factory.h"
#include "tty_colors.h"

// Forward declarations
cxxopts::ParseResult parse_args(int argc, char *argv[]);


int main(int argc, char *argv[]) {
    auto result = parse_args(argc, argv);
    process();
    return EXIT_SUCCESS;
}


cxxopts::ParseResult parse_args(int argc, char **argv) {
    try {
        cxxopts::Options options(PROJECT_NAME, PROJECT_DESCRIPTION);
        options.add_options()("v,verbose", "Verbose output", cxxopts::value(settings.verbose));
        options.add_options()("h,help", "Show program help");
        options.add_options()("p,paths", "paths to compile", cxxopts::value(settings.paths));
        options.add_options()("s,subs", "substitution file", cxxopts::value(settings.subs));

        options.parse_positional({"paths"});
        options.positional_help("json paths ...");

        auto result = options.parse(argc, argv);

        if (result.count("paths") == 0) {
            printError("No directories or files given.");
            exit(EXIT_FAILURE);
        }

        if (result.count("subs") == 0) {
            printError("No substitute file given.");
            exit(EXIT_FAILURE);
        }

        // help
        auto show_help = result["help"].as<bool>();
        if (show_help) {
            auto help_text = options.help();
            fmt::print("{}", help_text);
            exit(EXIT_SUCCESS);
        }

        return result;
    } catch (const cxxopts::OptionException &e) {
        auto err = e.what();
        printError("Error parsing options: {}.", err);
        exit(EXIT_FAILURE);
    }
}
