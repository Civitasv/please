add_library(libplease please.cc table.cc config.cc)

target_include_directories(libplease PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>)

# json library
include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.1/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(libplease PUBLIC nlohmann_json::nlohmann_json)

add_executable(please run.cc)
target_include_directories(please PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>)
target_link_libraries(please PUBLIC libplease)
