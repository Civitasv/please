add_library(please please.cc table.cc)

target_include_directories(please PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>)