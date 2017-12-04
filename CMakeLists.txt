cmake_minimum_required (VERSION 3.6)
project ("VectorGLPK")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")

include_directories(vectorglpk)

add_subdirectory(vectorglpk)

add_executable(VectorGLPKTest1 VectorGLPKTest1.cpp)

add_executable(VectorGLPKTest2 VectorGLPKTest2.cpp)

add_executable(VectorGLPKTest3 VectorGLPKTest3.cpp)

target_link_libraries(VectorGLPKTest1 VectorGLPK glpk)

target_link_libraries(VectorGLPKTest2 VectorGLPK glpk)

target_link_libraries(VectorGLPKTest3 VectorGLPK glpk)
