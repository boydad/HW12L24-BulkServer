cmake_minimum_required(VERSION 3.5)

project(HW11L21-BulkServer)
set(EXECUTE_FILE_NAME bulk_server)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cmake/GetGitRevisionDescription)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/async)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/bulk/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/async/include)

add_executable(${EXECUTE_FILE_NAME} src/main.cpp)

target_link_libraries(${EXECUTE_FILE_NAME} async)

set_target_properties(${EXECUTE_FILE_NAME} PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

# install(TARGETS ${EXECUTE_FILE_NAME} DESTINATION bin)

install(TARGETS ${EXECUTE_FILE_NAME} DESTINATION bin)

set(CPACK_PACKAGE_NAME ${EXECUTE_FILE_NAME})
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION ${VERSION_SHORT})
set(CPACK_PACKAGE_CONTACT xxx@xxx.xx)

include(CPack)
