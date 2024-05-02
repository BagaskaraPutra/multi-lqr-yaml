cmake_minimum_required(VERSION 2.8.3)
project(multi-lqr-yaml_examples)

# Single LQR gain
add_executable(singleLqr singleLqr.cpp)
target_link_libraries(singleLqr PUBLIC
  ${COMMON_LINK_LIBRARIES}
)
target_include_directories(singleLqr PUBLIC
  ${COMMON_INCLUDE_DIRECTORIES}
)

# Multiple LQR gains
add_executable(multiLqr multiLqr.cpp)
target_link_libraries(multiLqr PUBLIC
  ${COMMON_LINK_LIBRARIES}
)
target_include_directories(multiLqr PUBLIC
  ${COMMON_INCLUDE_DIRECTORIES}
)
