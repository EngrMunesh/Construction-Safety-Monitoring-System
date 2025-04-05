# 🏗️ Construction Safety Monitoring System

A microcontroller-based smart monitoring system developed to enhance safety measures at construction sites. This system detects multiple environmental hazards—including fire, proximity to rooftop edges, and unsafe temperature and humidity levels—through integrated sensors. It delivers real-time audio-visual alerts and includes a manual override feature for emergency control.

---

## 📌 Project Overview

Construction sites are inherently high-risk environments, with frequent incidents involving falls, fires, and extreme weather conditions. To mitigate these risks, this system utilizes **Arduino Uno** and a set of calibrated sensors to continuously monitor critical safety parameters. Alerts are communicated through **RGB LEDs** and a **buzzer**, with each hazard represented by a distinct LED color.

This project was developed as part of the *Construction Information Technology Project* at Budapest University of Technology and Economics.

---

## 🚨 System Features

### 🔥 Flame Detection
- Detects the presence of open flames using a flame sensor  
- **Triggers**: Buzzer + Green Blinking LED

### 🛑 Rooftop Edge Perimeter Warning
- Laser emitter forms a virtual perimeter along rooftop edges  
- If the beam is crossed: **Buzzer + Red Blinking LED**

### 🌡️ Temperature Monitoring
- Detects temperature exceeding safe working limits  
- **Triggers**: Buzzer + Blue Blinking LED

### 💧 Humidity Monitoring
- Detects humidity levels beyond OSHA-defined thresholds  
- **Triggers**: Buzzer + Blue Blinking LED

### 🖲️ Manual Override Button
- Allows immediate deactivation of all alerts after verifying safety  
- Ensures human control in dynamic site conditions

---

## 🔧 Hardware Components

- Arduino Uno Microcontroller  
- Flame Sensor  
- Laser Emitter + Photoresistor Module  
- Temperature and Humidity Sensor (DHT11)  
- RGB LED Module  
- Passive Buzzer  
- Push Button  

---

## 🧠 System Architecture

Each sensor feeds data to the Arduino Uno, which processes the inputs and triggers the appropriate outputs:

- **Green LED** → Fire Alert  
- **Red LED** → Rooftop Boundary Breach  
- **Blue LED** → Temperature or Humidity Warning  
- **Buzzer** → Audible Alert for All Hazard Types

---

## 🛠️ Setup Instructions

### Hardware
- Connect all sensors and modules according to the pin configuration in `Code.ino`  
- Ensure proper power supply and stable connections

### Software
- Upload `Code.ino` to Arduino Uno via the Arduino IDE  
- Monitor serial output for real-time data

### Testing & Calibration
- Simulate each hazard (e.g., flame, laser beam interruption) in a safe environment  
- Adjust thresholds if necessary for site-specific needs

---

## 📁 Documentation

- **[`Documentation.docx`](./Documentation.docx)** – Detailed system design, components, installation, and testing strategy  
- **[`Presentation.pptx`](./Presentation.pptx)** – Visual summary for project demonstration  
- **[`Code.ino`](./Code.ino)** – Full source code for system operation

---

## 👨‍💼 Project Team

- **Munesh Kumar** – VGU6PB  
- **Petra Hédl** – SUX9GX  
- **Mirna Makhlouf** – X70AKT  

**Instructor**: Dr. Arpad Barsi  
**Institution**: Budapest University of Technology and Economics  
**Course**: Construction Information Technology Project

---

## 📎 License

This project is developed for academic purposes and may be reused with proper attribution.

---

## 🙏 Acknowledgments

Special thanks to our supervisor **Dr. Arpad Barsi** for continuous guidance, and to all peers who supported the development and testing of this system.

