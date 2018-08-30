#
# (c) Oliver Michel 2018
#

cmake_minimum_required(VERSION 3.5)
project(concurrent_queues)

set(CMAKE_CXX_STANDARD 14)


set(CXXOPTS_VERSION 2.0.0)
if(NOT EXISTS ${CMAKE_HOME_DIRECTORY}/ext/include/cxxopts/cxxopts.h)
    file(DOWNLOAD
            https://raw.githubusercontent.com/jarro2783/cxxopts/v${CXXOPTS_VERSION}/include/cxxopts.hpp
            ${CMAKE_HOME_DIRECTORY}/ext/include/cxxopts/cxxopts.h)
endif()

if (NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/ext/include/moodycamel/concurrentqueue.h)
    file(DOWNLOAD
            https://raw.githubusercontent.com/cameron314/concurrentqueue/v1.0.0-beta/concurrentqueue.h
            ${CMAKE_CURRENT_LIST_DIR}/ext/include/moodycamel/concurrentqueue.h)
endif ()

add_executable(queue1 src/queue1_main.cc src/queue_performance.h src/queue1.h)

add_executable(queue2 src/queue2_main.cc src/queue_performance.h src/queue2.h)

add_executable(queue3 src/queue3_main.cc src/queue_performance.h src/queue3.h)

add_executable(queue4 src/queue4_main.cc src/queue_performance.h src/queue4.h)

add_executable(queue5 src/queue5_main.cc src/queue_performance.h src/queue5.h)

add_executable(moodycamel_queue src/moodycamel_queue_main.cc src/queue_performance.h)

add_executable(queue5_detail src/queue5_detail_main.cc src/queue_performance.h src/queue5.h)

include_directories(ext/include PUBLIC)
link_libraries(pthread)
