#------------------------------------------------
# env config
#------------------------------------------------

CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
MESSAGE(STATUS "CMAKE_VERSION:${CMAKE_VERSION}")

SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)
SET(Demo_VERSION_MAJOR 1)
SET(Demo_VERSION_MINOR 0)

#IF ("$ENV{QNX_HOST}" STREQUAL "")
#    MESSAGE(FATAL_ERROR "QNX_HOST environment variable not set")
#ENDIF()

IF ((${COMPILER} STREQUAL "qcc") AND ("$ENV{QNX_TARGET}" STREQUAL "")) 
    MESSAGE(FATAL_ERROR "QNX_TARGET enviroment variable not set")
ELSEIF(${COMPILER} STREQUAL "qcc") 
    SET(QNX_HOST "$ENV{QNX_HOST}")
    SET(QNX_TARGET "$ENV{QNX_TARGET}")
ELSEIF("$ENV{QNX_TARGET}" STRGREATER "")
    MESSAGE(FATAL_ERROR "QNX_TARGET eviroment variable must not be set with gcc compiler")
ENDIF()

#IF ("$ENV{QNX_TARGET}" STREQUAL "")
#    MESSAGE(FATAL_ERROR "QNX_TARGET environment variable not set")
#ENDIF()

OPTION(BOARD_OR_VM "determine where to run(BOARD set ON)" ON)
IF (${BOARD_OR_VM})
    MESSAGE(STATUS "BOARD_OR_VM IS ON, run on BOARD")
    SET(ARCH gcc_ntoaarch64le)
    SET(QCC_NTOARCH aarch64le)
ELSE()
    MESSAGE(STATUS "BOARD_OR_VM IS OFF, run on VM")
    SET(ARCH gcc_ntox86_64)
    SET(QCC_NTOARCH x86_64)
ENDIF()


MESSAGE(STATUS "QNX_HOST:${QNX_HOST}")
MESSAGE(STATUS "QNX_TARGET:${QNX_TARGET}")
MESSAGE(STATUS "ARCH:${ARCH}")
MESSAGE(STATUS "QCC_NTOARCH:${QCC_NTOARCH}")

#************************************************
# set compiler and compiler options
#************************************************
# for gcc
#************************************************
IF (${COMPILER} STREQUAL "gcc")
    SET(CMAKE_C_COMPILER "gcc")
    SET(CMAKE_C_COMPILER_TARGET "${ARCH}")
    SET(CMAKE_CXX_COMPILER "g++")
    SET(CMAKE_CXX_COMPILER_TARGET "${ARCH}")
    SET(CMAKE_LINKER   "ld" )
#************************************************
# for qcc
#***********************************************
ELSE()
    SET(CMAKE_C_COMPILER "${QNX_HOST}/usr/bin/qcc")
    SET(CMAKE_C_COMPILER_TARGET "${ARCH}")
    SET(CMAKE_CXX_COMPILER "${QNX_HOST}/usr/bin/qcc")
    SET(CMAKE_CXX_COMPILER_TARGET "${ARCH}")
    SET(CMAKE_LINKER       "${QNX_HOST}/usr/bin/nto${QCC_NTOARCH}-ld"     CACHE PATH "QNX linker program" FORCE)
#************************************************
ENDIF()
SET(CMAKE_C_FLAGS "$ENV{CMAKE_C_FLAGS} -Wall -g -fPIC -fprofe -ftest-cover -fmessage-length=0 -fno-builtin -O0")
SET(CMAKE_CXX_FLAGS "$ENV{CMAKE_CXX_FLAGS} -Wall -g -std=c++11 -fprofile -ftest-coverage -fPIC -D_GLIBCXX_USE_CXX11_ABI=0 -U__STRICT_ANSI__ -lang-c++")
MESSAGE(STATUS "CMAKE_C_COMPILER ${CMAKE_C_COMPILER}")
MESSAGE(STATUS "CMAKE_CXX_COMPILER ${CMAKE_CXX_COMPILER}")
MESSAGE(STATUS "CMAKE_C_COMPILER ${CMAKE_C_COMPILER}")
MESSAGE(STATUS "CMAKE_CXX_COMPILER ${CMAKE_CXX_COMPILER}")
MESSAGE(STATUS "CMAKE_LINKER ${CMAKE_LINKER}")
MESSAGE(STATUS "CMAKE_C_FLAGS:${CMAKE_C_FLAGS}")
MESSAGE(STATUS "CMAKE_CXX_FLAGS:${CMAKE_CXX_FLAGS}")

#************************************************
# add QTestDemo project include and link directories
#************************************************

PROJECT(screenposition)
SET(TARGET_NAME TestApp)
SET(TARGET_SO_NAME screenposition)

MESSAGE(STATUS "PROJECT_NAME:${PROJECT_NAME}")
MESSAGE(STATUS "TARGET_NAME:${TARGET_NAME}")
MESSAGE(STATUS "TARGET_SO_NAME:${TARGET_SO_NAME}")
MESSAGE(STATUS "PROJECT_SOURCE_DIR:${PROJECT_SOURCE_DIR}")
MESSAGE(STATUS "PROJECT_BINARY_DIR:${PROJECT_BINARY_DIR}")

SET(QCAR_INC_BS "${PROJECT_SOURCE_DIR}/include")
SET(QCAR_INC_SND_FILE "${PROJECT_SOURCE_DIR}/include/ScreenPosition/PositionSender")
SET(QCAR_INC_MSG_FILE "${PROJECT_SOURCE_DIR}/include/ScreenPosition/Message")
SET(QCAR_INC_REV_FILE "${PROJECT_SOURCE_DIR}/include/ScreenPosition/PositionReceiver")
SET(QCAR_INC_QUEUE_FILE "${PROJECT_SOURCE_DIR}/include/ScreenPosition/PositionReceiver/queue")
IF (${COMPILER} STREQUAL "gcc")
    SET(QCAR_INC_PLT_FILE "${PROJECT_SOURCE_DIR}/include/ScreenPosition/Platform/Linux")
ELSE()
    SET(QCAR_INC_PLT_FILE "${PROJECT_SOURCE_DIR}/include/ScreenPosition/Platform/QNX")
ENDIF()
#SET(QCAR_INC_BUSI ${PROJECT_SOURCE_DIR}/include/mybusi)
SET(BOOST_INC_PATH "/home/wm/code/boost-libs/include")
SET(QCAR_INCLUDE_PATH
    ${QCAR_INC_SND_FILE}
    ${QCAR_INC_BS}
    ${QCAR_INC_QUEUE_FILE}
    ${QCAR_INC_MSG_FILE}
    ${QCAR_INC_REV_FILE}
    ${QCAR_INC_PLT_FILE}
    ${BOOST_INC_PATH})
MESSAGE(STATUS "QCAR_INCLUDE_PATH: ${QCAR_INCLUDE_PATH}")
IF (${COMPILER} STREQUAL "qcc")
    SET(QNX_HOST_INCLUDE ${QNX_HOST}/usr/lib/gcc/x86_64-pc-nto-qnx7.0.0/5.4.0/include)
    SET(QNX_TARGET_INCLUDE ${QNX_TARGET}/usr/include ${QNX_TARGET}/usr/include/c++/v1)
ENDIF()
INCLUDE_DIRECTORIES(${QCAR_INCLUDE_PATH} ${QNX_HOST_INCLUDE} ${QNX_TARGET_INCLUDE})

#************************************************
# add sub directory
#************************************************
#ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/src/ScreenPosition)

# used for shared so
#AUX_SOURCE_DIRECTORY(${PROJCT_SOURCE_DIR}/src/ScreenPosition DUMP_SRCS)
FILE(GLOB_RECURSE MS_SRCS "${PROJECT_SOURCE_DIR}/src/ScreenPosition/Message/*.cpp")
FILE(GLOB_RECURSE PS_SRCS "${PROJECT_SOURCE_DIR}/src/ScreenPosition/PositionSender/*.cpp")
FILE(GLOB_RECURSE PR_SRCS "${PROJECT_SOURCE_DIR}/src/ScreenPosition/PositionReceiver/*.cpp")
IF (${COMPILER} STREQUAL "gcc")
    FILE(GLOB_RECURSE PLT_SRCS "${PROJECT_SOURCE_DIR}/src/ScreenPosition/Platform/Linux/*.cpp")
ELSE()
    FILE(GLOB_RECURSE PLT_SRCS "${PROJECT_SOURCE_DIR}/src/ScreenPosition/Platform/QNX/*.cpp")
ENDIF() 
SET(SP_SRCS
    ${MS_SRCS}
    ${PS_SRCS}
    ${PR_SRCS}
    ${PLT_SRCS})
#***********************************************
# add source files 
#**********************************************
AUX_SOURCE_DIRECTORY("${PROJECT_SOURCE_DIR}/src" SOURCE_FILES) 
#************************************************
# add libs
#************************************************

# add project libs
#SET(PROJECT_SUB_DIR_LIBS mybusi)
#MESSAGE(STATUS "PROJECT_SUB_DIR_LIBS:" ${PROJECT_SUB_DIR_LIBS})

#SET(PROJECT_SHARED_LIB "dumptofile")
#MESSAGE(STATUS "PROJECT_SHARED_LIB:" ${PROJECT_SHARED_LIB})

SET(FRAME_WORK_LIB ${TARGET_SO_NAME})
MESSAGE(STATUS "FRAME_WORK_LIB:" ${FRAME_WORK_LIB})


#************************************************
# add executable and library out put path
#************************************************

#************************************************
# dynamic lib build and generate
#************************************************
SET(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/${PLAT_FORM}/lib/")
MESSAGE(STATUS "LIBRARY_OUTPUT_PATH " ${LIBRARY_OUTPUT_PATH})
ADD_LIBRARY(${TARGET_SO_NAME} SHARED ${SP_SRCS})
#for code coverage
#target_compile_options(${TARGET_SO_NAME} PRIVATE -Wall -g -std=c++11 -fprofile -ftest-coverage -fPIC -D_GLIBCXX_USE_CXX11_ABI=0 -U__STRICT_ANSI__ -lang-c++)
target_compile_options(${TARGET_SO_NAME} PRIVATE -Wall -g -std=c++11 -fPIC -D_GLIBCXX_USE_CXX11_ABI=0 -U__STRICT_ANSI__ -lang-c++)

SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/${PLAT_FORM}/bin/")
MESSAGE(STATUS "EXECUTABLE_OUTPUT_PATH " ${EXECUTABLE_OUTPUT_PATH})
#target_compile_options(${TARGET_NAME} -ftest-coverage -fprofile)
ADD_EXECUTABLE(${TARGET_NAME} ${SOURCE_FILES})
#for code coverage
#target_compile_options(${TARGET_NAME} PRIVATE -Wall -g -std=c++11 -fprofile -ftest-coverage -fPIC -D_GLIBCXX_USE_CXX11_ABI=0 -U__STRICT_ANSI__ -lang-c++)
target_compile_options(${TARGET_NAME} PRIVATE -Wall -g -std=c++11 -fPIC -D_GLIBCXX_USE_CXX11_ABI=0 -U__STRICT_ANSI__ -lang-c++)
#for coverage
#TARGET_LINK_LIBRARIES(${TARGET_NAME} -Wl,--start-group ${PROJECT_SUB_DIR_LIBS} ${FRAME_WORK_LIB} ${PROJECT_SHARED_LIB} gcov -Wl,--end-group)
TARGET_LINK_LIBRARIES(${TARGET_NAME} -Wl,--start-group ${PROJECT_SUB_DIR_LIBS} ${FRAME_WORK_LIB} ${PROJECT_SHARED_LIB} -Wl,--end-group)

#************************************************
# headers out put
#************************************************
FILE(GLOB SEND_DIR "${PROJECT_SOURCE_DIR}/include/ScreenPosition/PositionSender/*.h")
FILE(COPY ${SEND_DIR} DESTINATION "${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}/PositionSender")
FILE(GLOB RECV_DIR "${PROJECT_SOURCE_DIR}/include/ScreenPosition/PositionReceiver/*h")
FILE(COPY ${RECV_DIR} DESTINATION "${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}/PositionReceiver")
