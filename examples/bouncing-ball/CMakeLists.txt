cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

set(PROJECT_NAME sh1106_bouncing_ball)

project(${PROJECT_NAME} C CXX ASM)

pico_sdk_init()

# Add your source files here
add_executable(${PROJECT_NAME}
    main.cpp
)

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${SH1106_PATH})

# Add source files
target_sources(${PROJECT_NAME} PRIVATE ${SH1106_PATH}/sh1106.cpp ${SH1106_PATH}/framebuffer.cpp)

# Link required libraries
target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_i2c)

# Enable USB and UART output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# Generate additional outputs (uf2, hex, bin, etc.)
pico_add_extra_outputs(${PROJECT_NAME})
