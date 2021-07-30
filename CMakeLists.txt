cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE ~/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

project(APITest)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBOOST_LOG_DYN_LINK")
set(CMAKE_CXX_STANDARD 20)

file(GLOB ALPACA_LIB src/alpaca/*.cpp)

include_directories(includes)

find_package(glog CONFIG REQUIRED)
find_package(restc-cpp CONFIG REQUIRED)
find_package(Boost COMPONENTS coroutine context REQUIRED )
find_path(CPP_HTTPLIB_INCLUDE_DIRS "httplib.h")
find_path(PICOSHA2_INCLUDE_DIRS "picosha2.h")

add_executable(APITest main.cpp
        #${ALPACA_LIB}
        includes/alpaca/response.h includes/alpaca/resp_reflection.h src/alpaca/alpaca.cpp
        includes/alpaca/alpaca.h src/coinbase/coinbase.cpp includes/coinbase/coinbase.h
        includes/coinbase/response.h includes/coinbase/resp_reflection.h includes/broker.h)

target_link_libraries(APITest PRIVATE ${Boost_LIBRARIES}
        restc-cpp -lpthread -lboost_log
        -lboost_coroutine -lboost_context glog::glog)

target_include_directories(APITest PRIVATE ${CPP_HTTPLIB_INCLUDE_DIRS} ${PICOSHA2_INCLUDE_DIRS})