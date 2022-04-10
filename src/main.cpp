#include "config.h"
#include "cookie-factory.h"
#include "tty_colors.h"
#include "CLI/CLI11.hpp"


programOptions settings;

class myFormatter : public CLI::Formatter {
public:
    std::string make_option_opts(const CLI::Option *) const override { return ""; }
};

int main(int argc, char *argv[]) {
    CLI::App app{PROJECT_DESCRIPTION, PROJECT_NAME};
    app.formatter(std::make_shared<myFormatter>());

    auto appName = app.get_name();
    app.footer(fmt::format("Example:  \n  {} vars.json file.txt.tpl > file.txt", appName));

    app.add_option("json", settings.jsonFile, "JSON file with substitutions")
            ->check(CLI::ExistingFile)
            ->required()
            ->capture_default_str();

    app.add_option("template", settings.templatePath, "Template file")
            ->check(CLI::ExistingFile)
            ->required()
            ->capture_default_str();


    app.set_version_flag("-v,--version", std::string(PROJECT_VER))->group("");
    app.set_help_flag("-h,--help", "Print this help message and exit")->group("");
    app.add_flag("-p,--print", "Print configuration and exit")->group("");

    // Show help if no options
    if (argc == 1) {
        fmt::print("{}", app.help("", CLI::AppFormatMode::All));
        return EXIT_SUCCESS;
    }

    try {
        app.parse(argc, argv);                                                                                   \

    } catch (const CLI::ParseError &e) {
        fmt::print("{}: {}\n", app.get_name(), app.get_description());
        fmt::print("\nERROR:\n");
        app.exit(e);
        return e.get_exit_code();
    }

    if (app.get_option("--print")->as<bool>()) {
        std::cout << app.config_to_str(true, false);
    }

    process(settings);
    return EXIT_SUCCESS;
}
