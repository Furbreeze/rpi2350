# cmake project setup

cmake_minimum_required(VERSION 3.12)

set(HARDCODED_YOUR_LIB_FOLDER /home/whatever/libfolder)

set(ENV{PICO_SDK_PATH} ${HARDCODED_YOUR_LIB_FOLDER}/pico-sdk)
set(ENV{FREERTOS_KERNEL_PATH} ${HARDCODED_YOUR_LIB_FOLDER}/FreeRTOS-Kernel)
set(ENV{FREERTOS_PORT_PATH} ${CMAKE_CURRENT_LIST_DIR}/packages/RP2350_ARM_NTZ)
set(PICO_TINYUSB_PATH ${HARDCODED_YOUR_LIB_FOLDER}/pico-sdk/lib/tinyusb)
set(PICOTOOL_FETCH_FROM_GIT_PATH ${HARDCODED_YOUR_LIB_FOLDER}/picotool)


set(NAME Springbok)
set(PICO_BOARD pico2)
set(PICO_PLATFORM rp2350)

# include pico sdk
include("$ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake")

# config project, clang setup
project(${NAME} C ASM CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# include free rtos
SET(FREERTOS_KERNEL_PATH "$ENV{FREERTOS_KERNEL_PATH}")
SET(FREERTOS_PORT_PATH "$ENV{FREERTOS_PORT_PATH}")
SET(FREERTOS_CONFIG_FILE_DIRECTORY "$ENV{FREERTOS_PORT_PATH}")


include("${FREERTOS_CONFIG_FILE_DIRECTORY}/non_secure/freertos_config.cmake")

add_subdirectory(${FREERTOS_PORT_PATH} FREERTOS_KERNEL)
add_subdirectory(src)
