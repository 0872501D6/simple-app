cmake_minimum_required(VERSION 2.8)

project(Simple-App CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++1y -pedantic -Wextra")
find_package(Boost 1.58 COMPONENTS system thread REQUIRED)

set(CROW_DIR "crow")
set(CROW_INCLUDE_DIR "${CROW_DIR}/include")

include_directories("${CROW_INCLUDE_DIR}")
add_executable(main main.cc)
target_link_libraries(main ${Boost_LIBRARIES})

# copy html from submodule to build folder
set(HTML_FROM_SUBMODULE "../assets/html")
set(HTML_IN_BUILD "html")
file(REMOVE_RECURSE "${HTML_IN_BUILD}")
add_custom_command(TARGET main POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${HTML_FROM_SUBMODULE} ${HTML_IN_BUILD})
