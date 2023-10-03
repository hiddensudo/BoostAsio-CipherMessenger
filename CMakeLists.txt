cmake_minimum_required(VERSION 3.10)
project(Network)

set(CMAKE_CXX_STANDARD 17)
find_package(Boost REQUIRED COMPONENTS system thread)

# Вкажіть шляхи до ваших директорій тут
include_directories(${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/Server ${PROJECT_SOURCE_DIR}/Client ${PROJECT_SOURCE_DIR}/Runfile ${PROJECT_SOURCE_DIR}/OneTimePad)

add_executable(server Runfile/mainServer.cpp)
target_sources(server PRIVATE Server/Server.cpp OneTimePad/OneTimePad.cpp)
target_link_libraries(server ${Boost_LIBRARIES} pthread)

add_executable(client Runfile/mainClient.cpp)
target_sources(client PRIVATE Client/Client.cpp OneTimePad/OneTimePad.cpp)
target_link_libraries(client ${Boost_LIBRARIES} pthread)
