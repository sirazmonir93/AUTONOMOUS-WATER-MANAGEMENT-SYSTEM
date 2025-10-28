# AUTONOMOUS-WATER-MANAGEMENT-SYSTEM
**Summary**

The "Autonomous Water Management System" is a sophisticated and innovative project developed by a team of students at the Islamic University of Technology. It addresses the critical global issues of water scarcity, wastage from tank overflows, and underutilization of rainwater. The system represents a paradigm shift in water conservation by seamlessly integrating sensor technology, IoT connectivity, and intelligent automation to create a holistic, efficient, and user-aware water management solution.

**1\. Problem Statement and Core Objectives**

The project is motivated by several pressing challenges:

- **Water Wastage:** Unnoticed overflow during the manual filling of water tanks contributes significantly to water scarcity.
- **Underutilized Rainwater:** The failure to harness naturally pure rainwater exacerbates the depletion of underground water reserves.
- **Water Quality Deterioration:** Neglected water storage tanks can become contaminated, posing health risks.

To combat these issues, the system sets forth clear, measurable objectives:

- **Wastage Reduction:** Prevent overflow through real-time monitoring and automated pump control.
- **Quality Monitoring:** Use a TDS (Total Dissolved Solids) sensor to monitor water purity and alert users when cleaning is necessary.
- **Smart Pump Control:** Automate the water pump based on real-time tank levels and external conditions.
- **Weather-Responsive Operation:** Integrate live weather data to optimize filling schedules, prioritizing the use of anticipated rainwater.
- **Adaptive Management:** Dynamically adjust water levels based on consumption rates and forecasted weather.

**2\. System Architecture and Key Components**

The system is built around an **ESP8266** microcontroller, which serves as the central brain, providing Wi-Fi connectivity for data acquisition. The hardware ecosystem includes:

- **Sensors:**
  - **HC-SR04 Ultrasonic Sensor:** Measures water level in the tank by calculating distance using ultrasonic pulses.
  - **Gravity Analog TDS Sensor:** Assesses water quality by measuring the concentration of dissolved solids.
- **Actuators:**
  - **12V DC Water Pump:** Responsible for moving water into the tank.
  - **5V Relay:** Acts as a switch, allowing the low-power Arduino to safely control the high-power water pump. A **2N2222 NPN BJT transistor** is used as a relay driver for robust operation.
- **Communication Modules:**
  - **GSM Module (SIM800):** Enables cellular communication to send SMS alerts to the user for critical events (e.g., high TDS levels).
  - **ESP8266 Wi-Fi Module:** Fetches real-time weather data from the **OpenWeatherMap API**.
- **User Interface:**
  - **I2C LCD Display (16x2):** Provides a real-time, at-a-glance view of system parameters like TDS, water level, and weather data.

**3\. Methodology and Working Procedure**
![AUTONOMOUS WATER MANAGEMENT SYSTEM report-13](https://github.com/user-attachments/assets/7279d473-2828-4f53-9f59-0041ab612bd7)

The system operates through a continuous, automated loop:

- **Initialization:** All components (GSM, Wi-Fi, sensors, relay, LCD) are initialized upon startup.
- **Data Acquisition:**
  - **Water Level:** The ultrasonic sensor periodically fires pulses and measures the echo to calculate the distance to the water surface, which is then converted to a percentage level.
  - **Water Quality:** The TDS sensor takes an analog reading, providing a value that indicates the purity of the water.
  - **Weather Data:** Every 10 seconds, the system queries the OpenWeatherMap API via Wi-Fi to get data on temperature, humidity, and crucially, **cloud cover** (as a predictor of rain).
- **Intelligent Decision-Making & Control:**
  - **Pump Control Logic:** The core automation. The pump is turned **ON** if the water level falls below **20%** and turned **OFF** if it rises above **90%**, effectively preventing overflow.
  - **Weather Integration:** The system considers the cloud cover percentage. If rain is likely (high cloud cover), it may adjust its pumping strategy to conserve energy and municipal water, anticipating rainwater collection.
- **User Alert System:**
  - **SMS Alerts:** If the TDS value exceeds a pre-set threshold (e.g., 300), indicating poor water quality, the GSM module automatically sends an SMS to a designated phone number (e.g., "Time to Clean up your tank!"). A flag prevents duplicate alerts until the issue is resolved.
  - **LCD Display:** Cycles through different screens, displaying TDS, water level, temperature, humidity, wind speed, and "feels like" temperature, making all critical data locally accessible.
- **Continuous Monitoring:** This entire process runs in a loop, ensuring the system dynamically adapts to changing conditions.
![AUTONOMOUS WATER MANAGEMENT SYSTEM report-15](https://github.com/user-attachments/assets/ee09a5ed-c16b-4c8e-8681-3c4958cf9968)

**4\. Implementation and Code Structure**

The code is written for the Arduino IDE and leverages several libraries for functionality (SoftwareSerial, ESP8266WiFi, Arduino_JSON, LiquidCrystal_I2C). Key functions include:

- setup(): Handles the initialization of all hardware and network connections.
- loop(): The main operational loop that manages data retrieval, sensor reading, pump control, and user notifications.
- httpGETRequest(): Manages the communication with the OpenWeatherMap API to fetch weather data.
- updateSerial(): Facilitates communication between the Arduino and the GSM module.
![AUTONOMOUS WATER MANAGEMENT SYSTEM report-14](https://github.com/user-attachments/assets/bb8a719a-8d4d-4bf4-98ef-84d0bda153c8)

**5\. Budget Analysis**

The project demonstrates cost-effectiveness, with a total estimated cost of **2,720 Bangladeshi Taka (BDT)**. The major expenses include the TDS sensor (1,000 BDT), water pumps (590 BDT), ESP8266 board (350 BDT), and HC-SR04 sensor (300 BDT).

**6\. Conclusion and Significance**

The Autonomous Water Management System successfully delivers a comprehensive, context-aware solution for modern water resource challenges. Its significance lies in:

- **Holistic Approach:** It doesn't just automate a single task but addresses the entire cycle of water usage, conservation, and quality maintenance.
- **Data-Driven Intelligence:** By integrating live weather forecasts, the system moves beyond simple threshold-based automation to a more sophisticated, predictive model.
- **Proactive User Engagement:** The SMS alert system ensures users are informed and can take corrective action, fostering a proactive relationship with their water resource.
- **Proof of Concept for IoT:** The project stands as a robust example of how IoT principles can be applied to create sustainable, efficient, and intelligent systems for real-world problems.
![Uploading AUTONOMOUS WATER MANAGEMENT SYSTEM report-17.jpg…]()

In essence, this project is a testament to the power of integrating sensor technology, data analytics, and automation to optimize resource utilization and promote environmental sustainability.
