cmake_minimum_required(VERSION 3.10)

project(minilottery VERSION 1.0)

FILE(GLOB C_SOURCE src/*.c)
add_executable(minilottery ${C_SOURCE}) 

target_link_libraries(minilottery
	sodium
)

set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")
include_directories(include)

install(TARGETS minilottery
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib)
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_GENERATOR RPM)
include(CPack)
