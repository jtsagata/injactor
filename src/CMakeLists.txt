configure_file( config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h @ONLY)

add_executable(${PROJECT_NAME} main.cpp cookie-factory.h cookie-factory.cpp)
target_sources(${PROJECT_NAME} PRIVATE tty_colors.h)

target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/config.h)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(${PROJECT_NAME} cxxopts)
target_link_libraries(${PROJECT_NAME} fmt::fmt)
