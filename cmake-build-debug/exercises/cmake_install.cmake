# Install script for directory: C:/Users/dkWiSkHe/OneDrive - LEGO/Desktop/Graphics Programming/graphics-programming-2025/exercises

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/ITU-graphics-programming")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/Program Files/JetBrains/CLion 2024.2.1/bin/mingw/bin/objdump.exe")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/dkWiSkHe/OneDrive - LEGO/Desktop/Graphics Programming/graphics-programming-2025/cmake-build-debug/exercises/exercise00/cmake_install.cmake")
  include("C:/Users/dkWiSkHe/OneDrive - LEGO/Desktop/Graphics Programming/graphics-programming-2025/cmake-build-debug/exercises/exercise01/cmake_install.cmake")
  include("C:/Users/dkWiSkHe/OneDrive - LEGO/Desktop/Graphics Programming/graphics-programming-2025/cmake-build-debug/exercises/exercise02/cmake_install.cmake")
  include("C:/Users/dkWiSkHe/OneDrive - LEGO/Desktop/Graphics Programming/graphics-programming-2025/cmake-build-debug/exercises/exercise03/cmake_install.cmake")
  include("C:/Users/dkWiSkHe/OneDrive - LEGO/Desktop/Graphics Programming/graphics-programming-2025/cmake-build-debug/exercises/exercise04/cmake_install.cmake")
  include("C:/Users/dkWiSkHe/OneDrive - LEGO/Desktop/Graphics Programming/graphics-programming-2025/cmake-build-debug/exercises/exercise05/cmake_install.cmake")

endif()

