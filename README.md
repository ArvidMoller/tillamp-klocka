```markdown
# Clock and Temperature Project

This project measures time and temperature using an **RTC DS3231** and an analog temperature sensor module. The time is displayed on a **1306 OLED screen**, while the temperature is mapped to a **9g servo motor** for a visual representation.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Code Overview](#code-overview)
- [Contributing](#contributing)
- [License](#license)

---

## Overview

This project integrates real-time clock data and temperature readings, displaying the time on an OLED screen and mapping temperature to a servo motor. It uses a DS3231 RTC module for timekeeping and an analog temperature sensor connected to an Arduino. Additionally, it includes a timer function that can be started and stopped with a button.

## Features

- **Time Display**: Shows the current time on a 1306 OLED display.
- **Temperature Display**: Maps the temperature from an analog sensor to a servo motor.
- **Timer**: Includes a start/stop timer feature to show elapsed time.
- **User Interaction**: Switch between time display and timer mode using a potentiometer.

## Hardware Requirements

- Arduino-compatible board
- DS3231 RTC Module
- 1306 OLED Display
- Analog Temperature Sensor
- 9g Servo Motor
- Potentiometer
- Button for timer control
- Connecting wires

## Installation

1. **Clone the repository**:
    ```bash
    git clone https://github.com/your-username/Clock-and-Temp-Project.git
    ```

2. **Open the project in the Arduino IDE**.

3. **Install required libraries** if not already installed:
    - `RTClib` for DS3231
    - `Wire` for I2C communication
    - `U8glib` for OLED display support
    - `Servo` for servo motor control

4. **Connect the components** following the pin configuration in the code:
    - Temperature Sensor on `A0`
    - Potentiometer on `A1`
    - Button on digital pin `8`
    - Servo motor on digital pin `9`

5. **Upload the code** to the Arduino board.

## Usage

- **Switch Modes**: Turn the potentiometer to toggle between time display and timer mode.
- **Timer**: Press the button to start or stop the timer. The elapsed time is shown on the OLED screen.
- **Temperature Display**: The temperature sensor value is mapped to a servo motor, visually representing the temperature.

## Code Overview

### Key Functions

- **`getTime()`**: Reads time from the DS3231 RTC module and returns a formatted string (hh:mm:ss).
- **`getTemp()`**: Reads analog input from the temperature sensor and calculates temperature using the Steinhart-Hart equations.
- **`oledWrite(x, y, text)`**: Displays text at specified coordinates on the OLED screen.
- **`servoWrite(val)`**: Maps a temperature value to a servo angle, providing a visual cue for temperature levels.
- **`timer()`**: Starts or stops a timer and displays elapsed time in hh:mm:ss format.
- **`stateSwitch()`**: Toggles the timer's state on button press.

## Contributing

Contributions are welcome! Please fork the repository, create a branch for your changes, and submit a pull request.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more information.

---

Enjoy working with your Clock and Temperature Display project!
```