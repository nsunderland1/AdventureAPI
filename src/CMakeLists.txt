set(SOURCES GameState.cpp GameTree.cpp GameLoader.cpp) 

add_library(advapi ${SOURCES})
target_include_directories(advapi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
