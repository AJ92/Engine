# Install script for directory: C:/Users/AJ/Desktop/bullet-2.82-r2704/src

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/BULLET_PHYSICS")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Debug")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/btBulletCollisionCommon.h;C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/btBulletDynamicsCommon.h;C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/Bullet-C-Api.h")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "C:/Program Files (x86)/BULLET_PHYSICS/include/bullet" TYPE FILE FILES
    "C:/Users/AJ/Desktop/bullet-2.82-r2704/src/btBulletCollisionCommon.h"
    "C:/Users/AJ/Desktop/bullet-2.82-r2704/src/btBulletDynamicsCommon.h"
    "C:/Users/AJ/Desktop/bullet-2.82-r2704/src/Bullet-C-Api.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/vmInclude.h")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath" TYPE FILE FILES "C:/Users/AJ/Desktop/bullet-2.82-r2704/src/vectormath/vmInclude.h")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/scalar/boolInVec.h;C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/scalar/floatInVec.h;C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/scalar/mat_aos.h;C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/scalar/quat_aos.h;C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/scalar/vec_aos.h;C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/scalar/vectormath_aos.h")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/scalar" TYPE FILE FILES
    "C:/Users/AJ/Desktop/bullet-2.82-r2704/src/vectormath/scalar/boolInVec.h"
    "C:/Users/AJ/Desktop/bullet-2.82-r2704/src/vectormath/scalar/floatInVec.h"
    "C:/Users/AJ/Desktop/bullet-2.82-r2704/src/vectormath/scalar/mat_aos.h"
    "C:/Users/AJ/Desktop/bullet-2.82-r2704/src/vectormath/scalar/quat_aos.h"
    "C:/Users/AJ/Desktop/bullet-2.82-r2704/src/vectormath/scalar/vec_aos.h"
    "C:/Users/AJ/Desktop/bullet-2.82-r2704/src/vectormath/scalar/vectormath_aos.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/sse/boolInVec.h;C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/sse/floatInVec.h;C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/sse/mat_aos.h;C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/sse/quat_aos.h;C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/sse/vec_aos.h;C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/sse/vecidx_aos.h;C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/sse/vectormath_aos.h")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "C:/Program Files (x86)/BULLET_PHYSICS/include/bullet/vectormath/sse" TYPE FILE FILES
    "C:/Users/AJ/Desktop/bullet-2.82-r2704/src/vectormath/sse/boolInVec.h"
    "C:/Users/AJ/Desktop/bullet-2.82-r2704/src/vectormath/sse/floatInVec.h"
    "C:/Users/AJ/Desktop/bullet-2.82-r2704/src/vectormath/sse/mat_aos.h"
    "C:/Users/AJ/Desktop/bullet-2.82-r2704/src/vectormath/sse/quat_aos.h"
    "C:/Users/AJ/Desktop/bullet-2.82-r2704/src/vectormath/sse/vec_aos.h"
    "C:/Users/AJ/Desktop/bullet-2.82-r2704/src/vectormath/sse/vecidx_aos.h"
    "C:/Users/AJ/Desktop/bullet-2.82-r2704/src/vectormath/sse/vectormath_aos.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("C:/Users/AJ/Desktop/bullet-2.82-r2704/src/BulletSoftBody/cmake_install.cmake")
  INCLUDE("C:/Users/AJ/Desktop/bullet-2.82-r2704/src/BulletCollision/cmake_install.cmake")
  INCLUDE("C:/Users/AJ/Desktop/bullet-2.82-r2704/src/BulletDynamics/cmake_install.cmake")
  INCLUDE("C:/Users/AJ/Desktop/bullet-2.82-r2704/src/LinearMath/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

