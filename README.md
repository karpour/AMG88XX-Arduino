# Arduino AMG88XX library
AMG88XX library for Arduino/Genuino v0.2. 
This library allows interfacing of an AMG88XX infrared thermopile array with an Arduino. It should be easily portable.

## Features supported
 * Reading temperature values as °C
 * Reading internal thermistor value in °C
 * Setting power mode (Normal, Sleep, Stand-by)
 * Setting frame rate (1FPS or 10FPS)
 * Setting moving average processing option
 * Putting the AMG88xx into sleep mode

## Features currently not supported
 * Interrupt handling

## Usage
Connect module to default SDA and SCL pins
```c++
Wire.setClock(400000);
Wire.begin();
wakeUp();
delay(15000); // AMG needs ~15 seconds to stabilize after waking up

float data[64];

readValues(data); // Temperatures in °C
```

## Todo
 * Wrap into class