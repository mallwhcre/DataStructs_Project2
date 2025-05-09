add_library(FileParsing STATIC fileParsing.c)
target_link_libraries(FileParsing PUBLIC commonTypes)
target_include_directories(FileParsing PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})