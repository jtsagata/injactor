#include <filesystem>
#include <fmt/core.h>
#include <inja.hpp>

#include "cookie-factory.h"
#include "tty_colors.h"


using namespace nlohmann;
using namespace inja;

namespace fs = std::filesystem;

bool compileTemplate(const programOptions &settings) {
    Environment env;

    // pwd function
    std::string pwd = fs::current_path().string();
    env.add_callback("pwd",0,[pwd](Arguments args){ return pwd; });

    // env function
    env.add_callback("env",1,[](Arguments args){
        std::string env = args.at(0)->get<std::string>();
        auto res = std::getenv(env.c_str());
        return res ? res :  "";
    });

    // path_exists function
    env.add_callback("path_exists",1,[](Arguments args){
        std::string arg = args.at(0)->get<std::string>();
        return fs::exists(fs::path(arg));
    });



    auto result = env.render_file_with_json_file(settings.templatePath, settings.jsonFile);

    env.render_file_with_json_file(settings.templatePath, settings.jsonFile);
    fmt::print("{}", result);
    return true;
}


void process(const programOptions &settings) {
    auto path = std::filesystem::path(settings.templatePath);
    if (std::filesystem::exists(path)) {
        if (std::filesystem::is_directory(path)) {
            printError("filename: {} is a directory", path);
            exit(EXIT_FAILURE);
        } else if (fs::is_regular_file(path)) {
            compileTemplate(settings);
        } else if (fs::is_symlink(path)) {
            printError("Filename: {} is symlink", path);
            exit(EXIT_FAILURE);
        } else {
            printError("File {} is not a file or directory.", path);
            exit(EXIT_FAILURE);
        }
    } else {
        printError("File {} does not exist.", path);
        exit(EXIT_FAILURE);
    }

}


