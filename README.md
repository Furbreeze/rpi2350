# RPI2350 + FreeRTOS + TinyUSB

Setup for getting rp2350 + FreeRTOS + TinyUSB all working together.

## STEPS

1. First clone [Pico SDK](https://github.com/raspberrypi/pico-sdk), [Pico Tool](https://github.com/raspberrypi/picotool), [FreeRTOS](https://github.com/raspberrypi/FreeRTOS-Kernel) into a central location, outside of this project. Ensure to use provided links
2. `cd` into pico sdk folder and run `git submodule update --init --recursive`
3. Update the `HARDCODED_YOUR_LIB_FOLDER` in `firmware/CMakeLists.txt` to point to central lib folder you set up in step 1
4. In the root of this project run the `build.sh` script
5. Build artifacts are in `build/src/`
6. Include any additional FreeRTOS or TinyUSB features you need in `src/CMakeLists.txt` in the `target_link_libraries` directive
