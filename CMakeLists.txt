CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(hello)

# find the FreeImage lib
find_path (FREEIMAGE_PATH FreeImage.h
    /usr/local/include
    /usr/include
)

find_library (FREEIMAGE_LIB_PATH freeimage
    /usr/lib
    /usr/local/lib
)

set (FREEIMAGE)
if ( FREEIMAGE_PATH AND FREEIMAGE_LIB_PATH )
    set (FREEIMAGE true)
else()
    message (FATAL_ERROR "Cann't find freeimage")
endif()

# fine the OpenGL lib
find_path (OPENGL_PATH gl.h
    /usr/local/include
    /usr/include
    /usr/local/include/GL
    /usr/include/GL
)

find_library (OPENGL_LIB_PATH GL
    /usr/lib
    /usr/local/lib
)

set (OPENGL)
if ( OPENGL_PATH AND OPENGL_LIB_PATH )
    set (OPENGL true)
else()
    message (FATAL_ERROR "Cann't find opengl")
endif()


# FreeImage and OpenGL Finded
if ( FREEIMAGE AND OPENGL )
    include_directories(${FREEIMAGE_PATH} ${OPENGL_PATH})
    add_executable(hello main.cpp)
    target_link_libraries(hello ${FREEIMAGE_LIB_PATH} ${OPENGL_LIB_PATH})
elseif ()
    message (FATAL_ERROR "FREEIMAGE not found")
endif ()

# message (STATUS "${FREEIMAGE_PATH} ${FREEIMAGE} ${OPENGL}")
