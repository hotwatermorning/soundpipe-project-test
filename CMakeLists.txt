cmake_minimum_required(VERSION 3.15)

project(soundpipe-test)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_LIST_DIR}/dependencies/Soundpipe/libsoundpipe.a
    COMMAND make clean && make
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/dependencies/Soundpipe
    )

add_custom_target(build-soundpipe
    DEPENDS ${CMAKE_CURRENT_LIST_DIR}/dependencies/Soundpipe/libsoundpipe.a
    )

add_library(Soundpipe
    INTERFACE
    )

target_include_directories(Soundpipe
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/dependencies/Soundpipe/h
    )

target_link_libraries(Soundpipe
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/dependencies/Soundpipe/libsoundpipe.a
    )

add_dependencies(Soundpipe build-soundpipe)

#################################################################

set(TARGET_NAME my-target)
add_executable(${TARGET_NAME})

target_sources(
    ${TARGET_NAME}
    PRIVATE
    src/main.cpp)

target_link_libraries(${TARGET_NAME}
    PRIVATE
    Soundpipe
    )

