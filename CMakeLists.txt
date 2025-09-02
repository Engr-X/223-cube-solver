cmake_minimum_required(VERSION 3.10)

project(223CubeSolver VERSION 1.0.0 LANGUAGES C)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

#set(CMAKE_C_COMPILER "D:/Coding/compilers/Mingw-13.2.0/bin/gcc.exe") #Remember to change me :)
set(CMAKE_C_FLAGS_RELEASE "-Ofast")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall")

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/3rd_party/cJSON/include)


add_library(CJSON_LIB ${PROJECT_SOURCE_DIR}/3rd_party/cJSON/src/cJSON.c)
add_library(UTILS_C ${PROJECT_SOURCE_DIR}/src/utils.c)
add_library(CUBE_MOVE_C ${PROJECT_SOURCE_DIR}/src/move.c)
add_library(BFS_SOLVER_C ${PROJECT_SOURCE_DIR}/src/bfs_solver.c)
add_library(DFS_SOLVER_C ${PROJECT_SOURCE_DIR}/src/dfs_solver.c)
add_library(CUBE_SOLVER_C ${PROJECT_SOURCE_DIR}/src/cube_solver.c)
add_executable(223CubeSolver ${PROJECT_SOURCE_DIR}/src/main.c)

target_link_libraries(223CubeSolver
    CJSON_LIB
    UTILS_C
    CUBE_MOVE_C
    CUBE_SOLVER_C
    BFS_SOLVER_C
    DFS_SOLVER_C
)

set_target_properties(223CubeSolver PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

target_link_libraries(223CubeSolver m)