# This is a copy of <FREERTOS_KERNEL_PATH>/portable/ThirdParty/GCC/RP2040/FREERTOS_KERNEL_import.cmake

# This can be dropped into an external project to help locate the FreeRTOS kernel
# It should be include()ed prior to project(). Alternatively this file may
# or the CMakeLists.txt in this directory may be included or added via add_subdirectory
# respectively.

# ensure kernel path set
if (DEFINED ENV{FREERTOS_KERNEL_PATH} AND (NOT FREERTOS_KERNEL_PATH))
    set(FREERTOS_KERNEL_PATH $ENV{FREERTOS_KERNEL_PATH})
    message("Using FREERTOS_KERNEL_PATH from environment ('${FREERTOS_KERNEL_PATH}')")
endif ()

# ensure port path set
if (DEFINED ENV{FREERTOS_PORT_PATH} AND (NOT FREERTOS_PORT_PATH))
    set(FREERTOS_PORT_PATH $ENV{FREERTOS_PORT_PATH})
    message("Using FREERTOS_PORT_PATH from environment ('${FREERTOS_PORT_PATH}')")
endif ()

# clean up file names
get_filename_component(FREERTOS_KERNEL_PATH "${FREERTOS_KERNEL_PATH}" REALPATH BASE_DIR "${CMAKE_BINARY_DIR}")
get_filename_component(FREERTOS_PORT_PATH "${FREERTOS_PORT_PATH}" REALPATH BASE_DIR "${CMAKE_BINARY_DIR}")

# ensure kernel path exists
if (NOT EXISTS ${FREERTOS_KERNEL_PATH})
    message(FATAL_ERROR "Directory '${FREERTOS_KERNEL_PATH}' not found")
endif()

# ensure port path exists
if (NOT EXISTS ${FREERTOS_KERNEL_PATH})
    message(FATAL_ERROR "Directory '${FREERTOS_KERNEL_PATH}' not found")
endif()

# check for CMakeLists
if (NOT EXISTS ${FREERTOS_PORT_PATH}/CMakeLists.txt)
    message(FATAL_ERROR "Directory '${FREERTOS_PORT_PATH}' does not contain a '${PICO_PLATFORM}' port.")
endif()

add_subdirectory(${FREERTOS_PORT_PATH} FREERTOS_KERNEL)
