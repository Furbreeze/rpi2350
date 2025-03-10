add_executable(${NAME}
    main.c
	usb_descriptors.c
)

target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(${NAME} 
	pico_stdlib
	tinyusb_device
	tinyusb_bsp
	tinyusb_board
	FreeRTOS-Kernel-Heap4
	freertos_config
)

pico_add_extra_outputs(${NAME})
