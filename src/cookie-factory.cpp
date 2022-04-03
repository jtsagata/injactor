#include <filesystem>
#include <fmt/core.h>
#include <inja.hpp>

#include "cookie-factory.h"
#include "tty_colors.h"


using namespace nlohmann;
using namespace inja;

namespace fs = std::filesystem;

// Global inja environment
Environment env;

bool compileTemplate(const std::string_view varsFile, std::string_view inFile, std::string_view outFile) {
    auto varsPath = fs::path{varsFile};
    auto inPath = fs::path{inFile};
    auto outPath = fs::path{outFile};


    env.load_json(std::string{varsFile});

//    env.write_with_json_file(std::string{inFile}, , std::string{outFile});
    return true;
}

void processFile(const json &data, const fs::path &path, const fs::path &dir) {
    auto ext = path.extension();
    auto filename = path.filename();
    auto stem = path.stem();
    auto oldPath = fs::relative(path, fs::current_path());
    auto newPath = fs::relative(dir / filename, dir);

    printInfo("filename: {}, ext: {}, stem: {}", filename, ext, stem);
    printInfo("filename: {} ->  {}", oldPath, newPath);

    auto txt = env.render_file(path.string(), data);
    fmt::print("{}", txt);
}

void processDriver(const fs::path &path) {
    if (std::filesystem::is_directory(path)) {
        printInfo("TODO filename: {} is a directory", path);
        for(auto const &f : fs::recursive_directory_iterator(path)) {
            processDriver(f);
        }
    } else if (fs::is_regular_file(path)) {
        printInfo("TODO filename: {} is a regular file", path);
        // path transformation
    } else if (fs::is_symlink(path)) {
        printInfo("TODO filename: {} is symlink", path);
    } else {
        printError("File {} is not a file or directory.", path);
    }
}

void process() {
    std::string &outputDirectory = settings.outputDirectory;
    printInfo("Output directory: {}", outputDirectory);
    auto data = env.load_json(settings.jsonFile[0]);
    auto basePath = outputDirectory.length() > 0 ? fs::path(outputDirectory) : fs::current_path();

    for (const auto pathName: settings.templatePaths) {
        auto path = std::filesystem::path(pathName);
        if (std::filesystem::exists(path)) {
            processDriver(path);
        } else {
            printError("File {} does not exist.", pathName);
//            exit(EXIT_FAILURE);
        }
    }
}


