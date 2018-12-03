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
target_include_directories(queue1 PUBLIC ext/include)
target_link_libraries(queue1 pthread)

add_executable(queue2 src/queue2_main.cc src/queue_performance.h src/queue2.h)
target_include_directories(queue2 PUBLIC ext/include)
target_link_libraries(queue2 pthread)

add_executable(queue4 src/queue4_main.cc src/queue_performance.h src/queue4.h)
target_include_directories(queue4 PUBLIC ext/include)
target_link_libraries(queue4 pthread)

add_executable(queue5 src/queue5_main.cc src/queue_performance.h src/queue5.h)
target_include_directories(queue5 PUBLIC ext/include)
target_link_libraries(queue5 pthread)

add_executable(moodycamel_queue src/moodycamel_queue_main.cc src/queue_performance.h)
target_include_directories(moodycamel_queue PUBLIC ext/include)
target_link_libraries(moodycamel_queue pthread)

add_executable(queue5_detail src/queue5_detail_main.cc src/queue_performance.h src/queue5.h)
target_include_directories(queue5_detail PUBLIC ext/include)
target_link_libraries(queue5_detail pthread)

add_executable(queue5_batch src/queue5_batch_main.cc src/queue_performance.h src/queue5.h)
target_include_directories(queue5_batch PUBLIC ext/include)
target_link_libraries(queue5_batch pthread)

add_executable(queue5_pipeline src/queue5_pipeline_main.cc src/queue_performance.h src/queue5.h)
target_include_directories(queue5_pipeline PUBLIC ext/include)
target_link_libraries(queue5_pipeline pthread)
