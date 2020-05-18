cmake_minimum_required(VERSION 3.0.0)

if (MSVC)
# set(CMAKE_C_COMPILER "clang-cl.exe")
# set(CMAKE_CXX_COMPILER "clang-cl.exe")
else()
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(javascript_engine)

if (MSVC)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /EHa /Od /Gz /FA /MDd /std:c++17 /W4 -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /EHa /O1 /Gz /MD /std:c++17 /W4 -Wno-unused-parameter")
else()
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g0 -O0 -std=c++17 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g0 -O0 -std=c++17 -Wall")
endif()

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set( EXTERNAL_LIB ${PROJECT_SOURCE_DIR}/externals)
set( V8 ${EXTERNAL_LIB}/v8)
set( V8RES ${EXTERNAL_LIB}/v8/resource)
if (MSVC)
set( V8LIB ${EXTERNAL_LIB}/v8/lib/x64)
else()
set( V8LIB ${EXTERNAL_LIB}/v8/lib/osx)
endif()

include_directories(${V8}/src/include)
include_directories(${EXTERNAL_LIB}/boost)
link_directories(${V8LIB})

file( GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp" )
add_executable(javascript_engine ${SOURCES})

if (MSVC)
target_link_libraries(javascript_engine icui18n.dll.lib icuuc.dll.lib v8.dll.lib v8_libbase.dll.lib v8_libplatform.dll.lib)
else()
target_link_libraries(javascript_engine icui18n icuuc v8 v8_libbase v8_libplatform)
endif()

if (MSVC)
    target_compile_options(javascript_engine PUBLIC -DEXE -DWIN)
else()
    target_compile_options(javascript_engine PUBLIC -DSTACK_TRACE -DEXE -DBOOST_STACKTRACE_USE_ADDR2LINE -D_GNU_SOURCE -DOSX)
endif()

if (MSVC)
file(GLOB DLL_FILES ${V8LIB}/*.dll)
else()
file(GLOB DLL_FILES ${V8LIB}/*.dylib)
endif()

file(COPY ${DLL_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${V8RES}/natives_blob.bin DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${V8RES}/icudtl.dat DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if (MSVC)
file(COPY ${V8RES}/win/snapshot_blob.bin DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
else()
file(COPY ${V8RES}/osx/snapshot_blob.bin DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()
