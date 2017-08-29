# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

add_library(native-lib
            SHARED
            src/main/cpp/native-lib.cpp
            src/main/cpp/AndroidSysInfo.cpp
            src/main/cpp/AndroidSysInfo.h)

find_library( log-lib
              log )

set(distribution_DIR ${CMAKE_SOURCE_DIR}/../../../../libs)

#add arcsoft
add_library(ArcSoftSpotlight
            SHARED
            IMPORTED)
set_target_properties(ArcSoftSpotlight
                      PROPERTIES IMPORTED_LOCATION
                      ../../../../libs/armeabi-v7a/libArcSoftSpotlight.so)
include_directories(libs/include/arcsoft)

#add facepp
add_library(MegviiFacepp
            SHARED
            IMPORTED)
set_target_properties(MegviiFacepp
                      PROPERTIES
                      IMPORTED_LOCATION
                      ../../../../libs/armeabi-v7a/libMegviiFacepp-0.4.7.so)
include_directories(libs/include/facepp)

#add self
add_library(FacialLandmarkDetector SHARED IMPORTED )
set_target_properties(FacialLandmarkDetector
                      PROPERTIES
                      IMPORTED_LOCATION
                      ../../../../libs/armeabi-v7a/libFacialLandmarkDetector.so)
include_directories(libs/include/self)

target_link_libraries( native-lib
                       ArcSoftSpotlight
                       MegviiFacepp
                       FacialLandmarkDetector
                       ${log-lib} )