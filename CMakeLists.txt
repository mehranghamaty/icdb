cmake_minimum_required(VERSION 3.27)
project(lsm C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O3")

add_library(datastructures
        datastructures/filters/bloom_filter.c
        datastructures/filters/bloom_filter.h
        datastructures/heap/heap.c
        datastructures/heap/heap.h
        datastructures/bst/binarysearchtree.c
        datastructures/bst/binarysearchtree.h
        datastructures/lsm/lsm.c
        datastructures/lsm/lsm.h
        datastructures/support/bit_operations.c
        datastructures/support/bit_operations.h
        datastructures/support/hash_functions.c
        datastructures/support/hash_functions.h
        datastructures/support/node.h

        networking/networking.c
        networking/networking.h
        networking/thread_pool.c
        networking/thread_pool.h
        networking/handler.c
        networking/handler.h
        parsers/network_requests/parser.c
        parsers/network_requests/parser.h
        filemanager/wal/writeaheadlog.c
        filemanager/wal/writeaheadlog.h
        filemanager/sst/sortedstringtable.c
        filemanager/sst/sortedstringtable.h
        filemanager/level/lsm_level.c
        filemanager/level/lsm_level.h
        parsers/config/config_parser.c
        parsers/config/config_parser.h
        tables/table.c
        tables/table.h
        parsers/sql_parser/tokens.c
        parsers/sql_parser/tokens.h
)

add_executable(lsm_server drivers/driver_server.c)
target_link_libraries(lsm_server datastructures)

add_executable(lsm_client drivers/driver_client.c)
target_link_libraries(lsm_client datastructures)

add_executable(lsm_put_test experiments/multi_threaded_put.c)
target_link_libraries(lsm_put_test datastructures)