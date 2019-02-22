cmake_minimum_required(VERSION 3.5)

project(HW11L21-BulkServer)
set(EXECUTE_FILE_NAME bulk_server)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cmake/GetGitRevisionDescription)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/async)

find_package(Boost COMPONENTS system REQUIRED)
find_package(Threads REQUIRED)

add_executable(${EXECUTE_FILE_NAME} src/main.cpp)

target_include_directories(${EXECUTE_FILE_NAME} PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/bulk/include
    ${CMAKE_CURRENT_SOURCE_DIR}/async/include
    ${Boost_INCLUDE_DIR}
)

target_link_libraries(${EXECUTE_FILE_NAME} 
	async
	${Boost_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT}
)

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
