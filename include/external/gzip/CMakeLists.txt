add_subdirectory("zlib")

add_library(gzip STATIC "gzstream.cpp" "gzstream.hpp")

target_link_libraries(gzip PUBLIC zlibstatic)