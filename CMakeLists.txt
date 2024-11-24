cmake_minimum_required(VERSION 3.5.0)
project(bayan VERSION 0.1.0 LANGUAGES C CXX)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS filesystem regex) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(bayan main.cpp) 
    target_link_libraries(bayan ${Boost_LIBRARIES})
endif()