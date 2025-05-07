add_library(FileParsing STATIC fileParsing.c)

target_include_directories(FileParsing PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})