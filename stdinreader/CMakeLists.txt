add_executable(stdinreader stdinreader.cpp)

target_compile_options(stdinreader PUBLIC -fsanitize=signed-integer-overflow)
target_link_libraries(stdinreader LINK_PUBLIC Dsmr)

