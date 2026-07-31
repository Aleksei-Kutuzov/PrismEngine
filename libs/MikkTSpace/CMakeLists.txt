project(MikkTSpace C)

add_library(mikk_space STATIC mikktspace.c)

target_include_directories(mikk_space PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})