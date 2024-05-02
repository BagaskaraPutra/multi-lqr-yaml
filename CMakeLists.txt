cmake_minimum_required(VERSION 2.8.3)
project(multi-lqr-yaml)

add_compile_options(-std=c++17)

find_package(Eigen3 3.4 REQUIRED)
find_package(yaml-cpp REQUIRED)

add_subdirectory(lqr)

set(COMMON_LINK_LIBRARIES 
  ${YAML_CPP_LIBRARIES}
  Eigen3::Eigen
  multilqr_lib
)

set(COMMON_INCLUDE_DIRECTORIES
  ${PROJECT_BINARY_DIR}
  ${YAML_CPP_INCLUDE_DIR}
  ${Eigen_INCLUDE_DIRS}
)

add_subdirectory(examples)