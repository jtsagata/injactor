/* * ctheme - ctheme color generator and switcher
 * Copyright (C) 2019 Ioannis Tsagkatakis
 *
 * This file is part of ctheme.
 *
 * ctheme is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * ctheme is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with ctheme.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef COOKIE_FACTORY_TTY_COLORS_H
#define COOKIE_FACTORY_TTY_COLORS_H

#include <fmt/color.h>
#include <fmt/core.h>

#include <filesystem>
#include <set>
#include <string>
#include <unistd.h>


inline bool isColorTerm() {
    using stringSet = std::set<std::string>;
    static const stringSet terms = {"xterm", "xterm-256", "xterm-256color", "vt100",
                                    "color", "ansi", "cygwin", "linux"};

    auto term = std::getenv("TERM");
    if (term) {
        return !(terms.find(term) == terms.end());
    } else {
        return false;
    }
}

enum class reportType {
    Error,
    Info
};

static const std::map<reportType, fmt::text_style> ttyReportStyles{
        {reportType::Error, fmt::emphasis::bold | fg(fmt::color::red)},
        {reportType::Info,  fmt::emphasis::bold | fg(fmt::color::yellow)},
};

static const std::map<reportType, std::string_view> ttyReportNames{
        {reportType::Error, "Error"},
        {reportType::Info,  "Info"},
};


template<typename... T>
FMT_INLINE void ttyReport(std::FILE *f, reportType type, fmt::format_string<T...> fmt, T &&... args) {
    if (isatty(fileno(f)) && isColorTerm()) {
        fmt::print(f, ttyReportStyles.at(type), "{}: ",  ttyReportNames.at(type));
    } else {
        fmt::print(f, "{}: ",  ttyReportNames.at(type));
    }
    fmt::print(f, fmt, args...);
    fmt::print(f, "\n");
}

template<typename... T>
FMT_INLINE void printError(fmt::format_string<T...> fmt, T &&... args) {
    ttyReport(stdout, reportType::Error, fmt, args...);
}

template<typename... T>
FMT_INLINE void printInfo(fmt::format_string<T...> fmt, T &&... args) {
    ttyReport(stdout, reportType::Info, fmt, args...);
}


#endif // COOKIE_FACTORY_TTY_COLORS_H
