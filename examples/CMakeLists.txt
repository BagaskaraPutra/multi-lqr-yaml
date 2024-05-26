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

# Single LQR gain with config reloading
add_executable(singleLqrReload singleLqrReload.cpp)
target_link_libraries(singleLqrReload PUBLIC
  ${COMMON_LINK_LIBRARIES}
)
target_include_directories(singleLqrReload PUBLIC
  ${COMMON_INCLUDE_DIRECTORIES}
)

# Multiple LQR gains with config reloading
add_executable(multiLqrReload multiLqrReload.cpp)
target_link_libraries(multiLqrReload PUBLIC
  ${COMMON_LINK_LIBRARIES}
)
target_include_directories(multiLqrReload PUBLIC
  ${COMMON_INCLUDE_DIRECTORIES}
)