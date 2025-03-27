cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(fool C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_BOARD pico)
set(PICO_BOOT_STAGE2_FILE ${PICO_SDK_PATH}/src/rp2040/boot_stage2/boot2_generic_03h.S)

pico_sdk_init()

add_executable(fool
  fool.c
  ws2812.pio
 )
pico_generate_pio_header(fool ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio)

# set the optimization level
set(CMAKE_C_FLAGS_RELEASE "-O1")  

# enable printf via USB serial
pico_enable_stdio_usb(fool 1)
# disable UART
pico_enable_stdio_uart(fool 0)

# create map, bin, hex and uf2
pico_add_extra_outputs(fool)
target_link_libraries(fool pico_stdlib hardware_pio)
