#Top level CMakeLists.txt
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project ("SneakyMUD")

list(APPEND SOURCE_FILES 
	"src/Server.cpp"
	"src/Tickable.cpp"
	"src/Event/Event.cpp"
	"src/IO/IOHandler.cpp"
	"src/IO/Configuration.cpp"
	"src/IO/Net/Net235.cpp"
	"src/IO/Net/PIDContainer.cpp"
	"src/IO/Net/Connection.cpp"
	"src/IO/Net/NetworkHandler.cpp"
	"src/World/World.cpp"
	"src/World/Entity/Entity.cpp"
	"src/World/Entity/StaticEntity.cpp"
	"src/World/Entity/Location.cpp"
	"src/World/Entity/Boundary.cpp"
	"src/World/Entity/GroundItem.cpp"
)

#SneakyMud
add_library(SneakyLib ${SOURCE_FILES})
target_link_directories(SneakyLib PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

#yaml
add_subdirectory("include/external/yaml")
target_link_libraries(SneakyLib PUBLIC yaml-cpp)

add_executable(${CMAKE_PROJECT_NAME} "src/SneakyMUD.cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} SneakyLib)

add_subdirectory("tests")