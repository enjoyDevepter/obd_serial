# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

include_directories(src/main/cpp)
include_directories(${CMAKE_SOURCE_DIR}/src/main/cpp/include)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

# 添加.so动态库
#add_library(sqlite
#        SHARED
#        IMPORTED)
#add_library(utils
#        SHARED
#        IMPORTED)
#add_library(c++
#        SHARED
#        IMPORTED)
#add_library(cutils
#        SHARED
#        IMPORTED)
#add_library(vndksupport
#        SHARED
#        IMPORTED)
#add_library(backtrace
#        SHARED
#        IMPORTED)
#add_library(base
#        SHARED
#        IMPORTED)
#
#add_library(unwind
#        SHARED
#        IMPORTED)
#add_library(lzma
#        SHARED
#        IMPORTED)
#
#
#set_target_properties(
#        vndksupport
#        PROPERTIES IMPORTED_LOCATION
#        ${CMAKE_SOURCE_DIR}/src/main/jnilibs/${ANDROID_ABI}/libvndksupport.so)
#
#
#set_target_properties(
#        cutils
#        PROPERTIES IMPORTED_LOCATION
#        ${CMAKE_SOURCE_DIR}/src/main/jnilibs/${ANDROID_ABI}/libcutils.so)
#
#set_target_properties(
#        sqlite
#        PROPERTIES IMPORTED_LOCATION
#        ${CMAKE_SOURCE_DIR}/src/main/jnilibs/${ANDROID_ABI}/libsqlite.so)
#
#set_target_properties(
#        utils
#        PROPERTIES IMPORTED_LOCATION
#        ${CMAKE_SOURCE_DIR}/src/main/jnilibs/${ANDROID_ABI}/libutils.so)
#
#set_target_properties(
#        c++
#        PROPERTIES IMPORTED_LOCATION
#        ${CMAKE_SOURCE_DIR}/src/main/jnilibs/${ANDROID_ABI}/libc++.so)
#
#set_target_properties(
#        backtrace
#        PROPERTIES IMPORTED_LOCATION
#        ${CMAKE_SOURCE_DIR}/src/main/jnilibs/${ANDROID_ABI}/libbacktrace.so)
#
#set_target_properties(
#        base
#        PROPERTIES IMPORTED_LOCATION
#        ${CMAKE_SOURCE_DIR}/src/main/jnilibs/${ANDROID_ABI}/libbase.so)
#
#set_target_properties(
#        unwind
#        PROPERTIES IMPORTED_LOCATION
#        ${CMAKE_SOURCE_DIR}/src/main/jnilibs/${ANDROID_ABI}/libunwind.so)
#
#set_target_properties(
#        lzma
#        PROPERTIES IMPORTED_LOCATION
#        ${CMAKE_SOURCE_DIR}/src/main/jnilibs/${ANDROID_ABI}/liblzma.so)

#添加两个预编译库
#add_library(openssl-crypto
#        STATIC
#        IMPORTED)
#
#set_target_properties(openssl-crypto
#        PROPERTIES IMPORTED_LOCATION
#        ${CMAKE_SOURCE_DIR}/src/main/cpp/libs/libcrypto.a)
#
#add_library(openssl-ssl
#        STATIC
#        IMPORTED)
#
#set_target_properties(openssl-ssl
#        PROPERTIES IMPORTED_LOCATION
#        ${CMAKE_SOURCE_DIR}/src/main/cpp/libs/libssl.a)

add_library( # Sets the name of the library.
        t6_serial

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/OBDBusiness.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)


# 链接头文件
target_include_directories(
        t6_serial
        PRIVATE
        # serial 需要的头文件
        ${CMAKE_SOURCE_DIR}/../jniLibs/include
)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        t6_serial
        # Links the target library to the log library
        # included in the NDK.
        # openssl-ssl openssl-crypto sqlite utils c++ cutils vndksupport
        # ${log-lib} sqlite utils c++ cutils vndksupport backtrace base unwind lzma )
        ${log-lib})