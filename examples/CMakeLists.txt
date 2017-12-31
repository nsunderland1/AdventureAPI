add_executable(advapiTest test.cpp)
target_link_libraries(advapiTest LINK_PUBLIC advapi)

set(ADVFILES testgame.adv) 

foreach(advfile ${ADVFILES})
    add_custom_command(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${advfile}"
        COMMAND cmake -E copy
            "${CMAKE_CURRENT_SOURCE_DIR}/${advfile}"
            "${CMAKE_CURRENT_BINARY_DIR}/${advfile}"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${advfile}"
    )
    list(APPEND advfiles_dest "${advfile}")
endforeach(advfile)

add_custom_target(CopyPatterns ALL DEPENDS ${advfiles_dest})
