cmake_minimum_required(VERSION 3.0)

project(LOGS)

if(COMMAND cmake_policy)
           cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

add_executable(test_debug test_log.cpp)
set_target_properties(test_debug PROPERTIES COMPILE_FLAGS "-Wall")
target_link_libraries(test_debug logs pthread)

add_executable(test_release test_log.cpp)
set_target_properties(test_release PROPERTIES COMPILE_FLAGS "-Wall -DNDEBUG -O3")
target_link_libraries(test_release pthread)

include_directories(
  ../src
)

install(FILES traces.cfg DESTINATION ${CMAKE_BINARY_DIR})
