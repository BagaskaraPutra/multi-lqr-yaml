find_package(Eigen3 3.4 REQUIRED)
find_package(yaml-cpp REQUIRED)

# cpp files
set(LQR_SOURCE_FILES
${CMAKE_CURRENT_SOURCE_DIR}/src/multiLqrManager.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/dlqr.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/continuousLtiStateSpace.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/discreteLtiStateSpace.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/stateSpaceUtils.cpp
)

add_library(multilqr_lib ${LQR_SOURCE_FILES})

target_include_directories(multilqr_lib PUBLIC
  ${YAML_CPP_INCLUDE_DIR}
  ${Eigen_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include/enums
  ${CMAKE_CURRENT_SOURCE_DIR}/include/interfaces
)

target_link_libraries(multilqr_lib PUBLIC
  ${YAML_CPP_LIBRARIES}
  # ${Eigen3_LIBRARIES}
  Eigen3::Eigen
)