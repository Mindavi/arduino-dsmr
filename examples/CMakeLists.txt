add_executable(minimal minimal_parse/minimal_parse.cpp)
add_executable(parse parse/parse.cpp)

target_link_libraries(minimal LINK_PUBLIC Dsmr)
target_link_libraries(parse LINK_PUBLIC Dsmr)

