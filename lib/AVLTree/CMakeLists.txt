add_library(AVLTree STATIC avlTree.c)
target_link_libraries(AVLTree PUBLIC commonTypes)
target_include_directories(AVLTree PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
