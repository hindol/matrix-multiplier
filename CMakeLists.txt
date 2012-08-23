project(MatrixMultiplier)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

include_directories("/home/hindol/Desktop/Intel Assignments/MatrixMultiplier/CBLAS/include")
link_directories(   "/home/hindol/Desktop/Intel Assignments/MatrixMultiplier/CBLAS/lib"
                    "/home/hindol/Desktop/Intel Assignments/MatrixMultiplier/BLAS")

aux_source_directory(. SRC_LIST)
file(GLOB HDR_LIST "*.h")

add_executable(${PROJECT_NAME} ${SRC_LIST} ${HDR_LIST})
target_link_libraries(${PROJECT_NAME} rt cblas_LINUX blas_LINUX gfortran)
