# esp32-telemetry-display

## Short description:
The project is an **ESP32** microcontroller that wirelessly fetches telemetry data from car's ECU using a *Bluetooth* **ELM327** interface, then displays real time info on the display.


## Main functionalities:
    Real time **engine temp** data
    Real time **DPF regeneration status**, warns user 30km before an expected regen (using the average distance between regens)
    Real time display of any DTC's that may occur, logging them on the internal memory and the possibility of deleting them from ECU
    Average consumption, number of kilometers and time spent on the current trip
    Automatic 0-100km/h time recording
    Other real time parameters such as RPM, speed, range, boost pressure, EGT(we use EGT info to confirm if a regen is active)


The fact that we are using data from the **OBD II** port, means that it will work on any car newer than the year 2004.


## Necessary materials:
    ESP32 Wroom32 development board
    ELM327 v1.5 Bluetooth diagnosis module, chip PIC18F25K80
    TFT SPI 2.4 inch touch display, driver ST7789V
    Passive buzzer module
    Breadboard for testing
    Jumper cables
    Micro USB cable for code uploading
    Car charger to power the board
    Custom case


## What to study:
    Communication (Car > ELM327 > ESP32):
        'BluetootSerial.h'
        'ELMduino'
    Display (ESP32 > Display):
        'TFT_eSPI'
    Touch:
        'XPT2046_Touchscreen'

