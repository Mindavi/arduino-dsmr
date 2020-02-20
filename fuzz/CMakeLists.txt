add_executable(fuzz fuzz.cpp)

target_link_libraries(fuzz LINK_PUBLIC Dsmr)
target_compile_options(fuzz PUBLIC -O1 -g)
target_link_options(fuzz PUBLIC -O1 -g)
