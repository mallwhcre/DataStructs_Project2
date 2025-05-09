add_library(commonTypes STATIC commonTypes.c)
target_include_directories(commonTypes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})