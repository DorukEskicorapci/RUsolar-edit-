<div align="center">
    <h1 align="center">
       <img src="data:image/webp;base64,UklGRp4DAABXRUJQVlA4IJIDAABwFACdASpgAGAAPm0ylUekIqIhKrK5WIANiWQA1IoBPD/rXG+cReCOCsLL2dTgPFH6WvmA/Vn9nffO9BX+d9QD+7/4DrAPQA8sb9s/hG/cD/h/8D2k5rD2L7F5kTnPH9SuGiGXZaBS4cQ2x4ZQK61R7YUrfcn8z56d5KqFKGo0ImgspBwnirsy5lKBq2h8vfbtzUFytpIfidVoU0uSFmmI7R/3+0tU0EOv0c4AAP74fLPQFbYHu77jSZweAAEdng0N2sp+Jf9WNJQSc/9uL6LzFvJaYagZIGjA+fp85YTNDBjQzL/n48Xbg+ldEDtQMDz0Zl1/a+grzYKq7MCFz76Xql1TJ+AaNrPy63C0KXo4sQUhL+BnAgS0ZfOTUAVK57YD2ulsusn09nQjExtIDWtk8oPYJVnGef6qsI7OMLfyRGELkLrfCwcX2+4JR7UeD+A0BPVcymv7cqoAJO+0flw5uQduVjTeaMNKRJP0heCNohzAYF3H/5p8HeYPKcr6OU4u6Pk06FS5ceswYiMpREcXI4YFvorub/Qwsz9YES7VPph4sBZEETw7Shilgts2LXI4qjcWOPD849Lukfr+yX8A3XxDW6P3+crWDAy1FUj5sfCd4IRN1ZnXbxeY+9KA1C+Qccsuk78rx+392on0OQ0Q2TKiq4QXWZ6GgdP+CIa6RIOLTFb0SauDkHBhP81tpE6h13uiIcvLYSxbZly0I69dzSrzQHZXnoiAzUm8aTQhuSPxuSlqf2vhw8jJAxKaJ4WUsHq9EBl1OVQ1FtzSn57dkBuQyhjBf1P3Nv/X8PfSKdNfhux5EOYDCm2q5QsTyZ5vkfkcBhjO6YKrHRkR2EbEEG/2UXfKm43dgFBUyEnCUn2tmBsbHAI6EzuMfj7c4R3LeNuenGxUawgyf+afb8v/Jg0l8kTQ998pB3Dgd4IIuN9a/y5jh6171lXmY0TpXtKPVc+iK6NdgJlPGdvkM1yB1aZvd//wCUdPbHLRsnPoN0lmef5ONvEjsNzWEakXfgXI2xIHZlQe/xN8gk2Uz5NzDjb4AB1H97nYl0qXdlh3ik9pUmjYyNxnK+UVuiGCB2IU8DIQTbcGd79AXZOqqq90Az7/Z5bQ8RicmkRlwy+NVU7EQGoo5Nlwhs4hcyuLIsrr3WyMt4oZhpk1yvZUb0XQAnImC/g/yS/JzPUDA5uG8Ba//0ub76knE5nAniYAAAAAAA==" style="width: 30px; height: 30px; border-radius: 50%"> Rutgers Solar Car - Software 3
    </h1>
    <p align="center">
        This is the official Git repo for developing the main embedded software that will be used for Rutgers Solar Car 2025
    </p>
    <a href="https://github.com/Rutgers-Solar-Car/Software-3/issues/new">Report a Beetle</a>
    &middot;
    <a href="https://github.com/Rutgers-Solar-Car/Software-3/issues/new?labels=enhancement">Request Your Cool Ideas</a>
</div>

# About the Rutgers Solar Car
🚗 ☀️ ☀️ 🚀
> The Rutgers Solar Car Team is a passionate, student-led engineering group driven by the ambition to compete in the American Solar Challenge.  

> We’re actively seeking donations, tools, and new team members to help us build a renowned organization, providing hands-on experience in renewable energy and electric vehicle innovation.

* Our official website: https://www.rusolarcar.com/
* Rutgers getINVOLVED: https://rutgers.campuslabs.com/engage/organization/solarcarteam
* LinkedIn: https://www.linkedin.com/company/rusolarcarteam/
* YouTube: https://www.youtube.com/channel/UCl-Kh9JVnpcMu9IEECp17pw
* Instagram: https://www.instagram.com/rusolarcarteam/
* Twitter: https://twitter.com/rusolarcarteam
* Facebook: https://www.facebook.com/rusolarcarteam/
# Project Overview
This project is the embedded software for our Rutgers Solar Car 2025 (and beyond), developed using `C` for the `STM32` microcontroller. The software mainly manages the following:
* Communication between devices and sensors using `CAN` bus technology.
* Power Distribution and Management from our primary battery and secondary battery to the rest of the car.
* Handle displaying telemetry data to the driver.
* Handle collecting telemetry data from sensors, and send off to our backend server for analysing and statistics.

# Architecture
We currently  using these technologies and aim to use the following:
* Programming langage: `C`
* MCU: `STM32`
* Communication: `CAN Bus`, `UART`
* Peripheral: `GPIO`, `Timers`

# Dependencies
We're using these software to develop, version control our software:
* `STM32CubeIDE`: This is the official IDE to develop our STM32 boards, you can also use other IDEs such as Visual Code to develop STM32, but STM32CubeIDE offers more features that are needed for only STM32 specifications. You can download STM32CubeIDE [here](https://www.st.com/en/development-tools/stm32cubeide.html).
* `HAL`: We use `HAL` as a main CAN Bus library. It is used as an inteface to initialise, manage, and communicate with CAN. Proper `HAL` library will be automatically generated and inserted when you activate CAN Bus on STM32 in STM32CubeIDE
* `Git & Github`: We use `Git` to handle version control our codebase. You're here!

# Getting Started
## C warm up
If you are not familiar with C (you are from other programming language's realms such as Python, Javascript or C++), then it's okay. `C` is very similar to other languages in terms of function call, data types, code flows, branching, and expressions (honestly other languages were developed based on C, you can even name one of them that you're maybe very familar with - `Java`). Here are some links we found helpful to get you started with `C`:
* [The GNU C Reference Manual](https://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html)
* [C for Java Programmers](https://www.cs.rochester.edu/u/ferguson/csc/c/c-for-java-programmers.pdf)
* [C Style Guidelines](https://www.cs.umd.edu/~nelson/classes/resources/cstyleguide/)

## Hardware Setup
We are developing our own PCB board for STM32, so at the moment, you can't play with it yet. In the meantime, you can grasp your understanding with `CAN`,`STM32`, and basic embedded systems using these following:
* STM32 Nucleo Development Board
* USB-to-MicroUSB Cable (used to connect STM32 Nucleo to a computer, so we can upload our code from STM32CubeIDE to it)
* A `CAN` Bus Transceiver (the STM32 Nucleo can't transmit `CAN` signals on its own, that's why we need a `CAN` Bus Transceiver)
* A breadboard
* Jumpers wires (you may need Male-to-Male, Male-to-Female, Female-to-Female)
* LEDs
* Resistors (100-120 Ohm)
> 💡 **Note:** You may need one more board (STM32 or Arduino with CAN or whatever) to start communication with CAN bus. You can experience CAN bus on just one STM32 board, but it may requires more set up. And it would reflex real-life scenarios better.

## Software Setup
> ⚠️ **Note**: Whie this project is intended for our own designed PCB board, not for a STM32 Nucleo Development Board, it should work the same way on your STM32 Nucleo.

1. Download and Install STM32CubeIDE [here](https://www.st.com/en/development-tools/stm32cubeide.html)
2. Clone the repository:
```
git clone https://github.com/Rutgers-Solar-Car/Software-3
```
3. Open STM32CubeIDE. Go to `File -> Open Projects from File System...`. Click on `Directory` and select the repo's directory. If your repo comes from a `zip` file, then select `Archive`, then select the zip file. Now your project is imported into STM32CubeIDE.
4. The `.ioc` file from the repo should have been configured correctly to work with `CAN`. If not, you have to configure it by clicking on the `.ioc` file. The STM32CubeIDE will display a new window that allows you to visually interact with the STM32 microcontroller. You can follow some tutorials we provided here to work with `CAN`:
    * [CAN Protocol in STM32](https://controllerstech.com/can-protocol-in-stm32/)
    * [CAN Bit Timing Explained](https://gettobyte.com/can-bit-timing-explained/?srsltid=AfmBOorZLiz25VZomcWaLpLxyKnRQvbbvHyFLbpjRT7smE0NWV89M7Pe)
5. Connect your STM32 Nucleo Board to your computer via a USB-to-MicroUSB cable.
6. Build project `Project -> Build Project`
7. Click `Run -> Run` or `Debug` if your STM32 Nucleo supports `ST-Link` (check your board's manual for more detail).

# 📖 Folders Structure
📂 `.metadata/` *This folder holds information that the IDE such as log files. These files are not important and can be regenerated when you're in the STM32CubeIDE.*  
📂 `Template/` *This folder is our core focus*  
├── 📂`.settings/` *Only for IDE's usage*  
├── 📂`Core/` *This is most important folder. It contains our main codebase*  
│─── 📂`Inc/` *Include folder. It contains C header files*  
│──────`can.h` *Contains CAN parameters definitions, CAN message and device structures, CAN function signatures to init, handle error, send and receive CAN messages*  
│──────`can_params.h` *Contains CAN parameters definitions*  
│──────`main.h` *Contains peripheral definitions and other stuffs that IDE generated. This file should NOT be edited. The IDE will wipe out your changes when you regenerate code anyway, so don't waste your time here. Reading it is fine*  
│──────`stm32f7xx_hal_conf.h` *Same as main.h file. It is IDE-generated. Contains HAL library variables and functions definition. You can read this file to understand what HAL library offers to manage CAN Bus, but don't edit it*  
│──────`stm32f7xx_it.h` *Same as stm32f7xx_hal_conf.h, should NOT be edited*  
│─── 📂`Src/` *This folder contains our code implementations*  
│──────`can.c` *Our implementation for CAN Bus*  
│──────`can_params.c` *Our implementation for CAN Bus*  
│──────`main.c` *Entry file to start the microcontroller, init peripheral including CAN. You can change this file as long as you're inside the USER BEGIN-USER END blocks*  
│──────`stm32f7xx_hal_msp.c` *IDE-Generated, should NOT be changed*  
│──────`stm32f7xx_it.c` *IDE-Generated, should NOT be changed*  
│──────`syscalls.c` *IDE-Generated, should NOT be changed*  
│──────`sysmem.c` *IDE-Generated, should NOT be changed*  
│──────`system_stm32f7xx.c` *IDE-Generated, should NOT be changed*  
│─── 📂`Startup/` *IDE-Generated, should NOT be changed*  
├── 📂 `Debug/` *Contain information about debugging. It is IDE-generated and should NOT be changed*  
├── 📂 `Drivers/` *Contain information about drivers. It is IDE-generated and should NOT be changed*  
├── `.cproject` *IDE-Generated, should NOT be changed*  
├── `.mxproject` *IDE-Generated, should NOT be changed*  
├── `.project` *IDE-Generated, should NOT be changed*  
├── `STM32F767ZITX_FLASH.ld` *IDE-Generated, should NOT be changed*  
├── `STM32F767ZITX_RAM.ld` *IDE-Generated, should NOT be changed*  
├── `Template.ioc` *IDE-Generated, should NOT be changed. After you're done interacting with the microcontroller such as activating a peripheral, the action will be stored here*  
`LICENSE` *Don't care about this one*

# Troubleshooting
* *I don't receive any CAN message to STM32 Nucleo board, or my device doesn't receive any CAN message from STM32 Nucleo board??? 😠*
> Make sure your connection between devices and CAN Transceiver is correct. Check if your wires going to wrong pins, check if you wrongly swapped the CAN_H and CAN_L pins.  Your STM32CubeIDE could be wrongly configured to "redirect" your CAN pins to other pins. Check the board's manual for pins layout. Pin's labels are easily seen from under of the board, but when you flip it up to connect, you may mistaken which side the pin is located.

> Check if the board, CAN Transceivers are properly powered on (do you see any LED light up?). CAN Transceiver could not have any indicated LEDs, make sure you connect it's VCC and 5V (or 3V3) to the correct pins on the board. One way to check is to have wires from your's board VCC and 5V connected to a breadboard, and use a LED. If the LED lights up, that means your board is currently powering your transceiver.  

> Make sure you have 100-Ohm or 120-Ohm resistors at each end of the CAN Bus.  

> Make sure the `Buad Rate` of all devices are **the same**. CAN Transceiver will intercept messages incorrectly if your device fire up messages at a different rate. Your device's library can mislabeled some certain baud rates such as `666K` but it's actually `500K`. Check out different combinations to see what works.  

> Remove all CAN filters. Some CAN filters can block your device's ID.  

> If your STM32 supports `ST-Link`, you can use that to debug your program at run-time in STM32CubeIDE.  

> Electromagnetic interference might effect the CAN Bus. Make sure you don't run it near other devices that might emit a strong electromagnetic field.
# General QAs
- ⬜️ Add QA

# ✅ TODOs:
- ⬜️ Add assertments
- ⬜️ C linting library?
- ⬜️ Add unit tests

## Repo:
- ⬜️ Add `.gitignores`

### Readme
- ⬜️ Add STM32 CAN Bus basic tutorial
- ⬜️ Add more questions and troubleshootings

# License
This project is licensed under the **MIT License**.

# 👥 Contributors
* 💠 [ncorrea210](https://github.com/ncorrea210) - Software Team Lead
* 💠 [cyfinfaza](https://github.com/cyfinfaza) - Hardware Team Lead
* [bquangDinh](https://github.com/bquangDinh) - Team Member