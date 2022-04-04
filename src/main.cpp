#include "config.h"
#include "cookie-factory.h"
#include "tty_colors.h"
#include "CLI/CLI11.hpp"


programOptions settings;

int main(int argc, char *argv[]) {
    CLI::App app{PROJECT_DESCRIPTION, PROJECT_NAME};
    auto appName = app.get_name();
    app.footer(fmt::format("Example:  \n  {} --json=vars.json --out=generated directory/ file1 file2", appName));

    app.add_option("-j,--json", settings.jsonFile, "JSON file with substitutions, or set the $CF_JSON_TEMPLATE")
            ->check(CLI::ExistingFile)
            ->required()
            ->group("Important")
            ->capture_default_str()
            ->envname("CF_JSON_TEMPLATE");

    app.add_option("-o,--out", settings.outputDirectory, "Output directory, or set $CF_OUTPUT_DIR")
            ->check(CLI::ExistingDirectory)
            ->required()
            ->capture_default_str()
            ->group("Important")
            ->envname("CF_OUTPUT_DIR");

    // TODO: Positional arguments

    app.add_flag("-d,--debug", settings.verbose, "Show whats going on")
            ->disable_flag_override()
            ->group("Misc");

    app.add_flag("-n,--no-action,", settings.noActions, "Don't write to disk")
            ->disable_flag_override()
            ->group("Misc");

    app.set_version_flag("-v,--version", std::string(PROJECT_VER))->group("Misc");
    app.set_help_flag("-h,--help", "Print this help message and exit")->group("Misc");

    app.add_flag("-p,--print", "Print configuration and exit")->group("");

    // Show help if no options
    if(argc==1) {
        fmt::print("{}", app.help("", CLI::AppFormatMode::All));
        return EXIT_SUCCESS;
    }

    try {
        app.parse(argc, argv);                                                                                   \
    } catch (const CLI::ParseError &e) {
        fmt::print("\nERROR:\n");
        app.exit(e);
        return e.get_exit_code();
    }

    if (app.get_option("--print")->as<bool>()) {  // NEW: print configuration and exit
        std::cout << app.config_to_str(true, false);
    }

    process();
    return EXIT_SUCCESS;
}
