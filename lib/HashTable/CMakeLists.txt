add_library(HashTable STATIC hashTable.c)
target_link_libraries(HashTable PUBLIC commonTypes)
target_include_directories(HashTable PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
 