# 🕒 OpenGL Analog Clock with Rotating Digital Time Display

> **Practice #:** 12
> **Language:** C++
> **Libraries:** OpenGL (GLEW + FreeGLUT)

---

## 📌 Description

This project implements an analog clock using OpenGL and FreeGLUT. The clock features three hands representing hours, minutes, and seconds, along with a rotating digital time display box attached to the second hand.

---

## 🧠 Features

* ✅ Smooth and circular analog clock face.
* ✅ Hour marks from 1 to 12 rendered with bitmap fonts.
* ✅ Hour, minute, and second hands with accurate angles based on current time.
* ✅ Rotating black box on the second hand displaying digital time (`HH:MM:SS`).
* ✅ Real-time animation using a 60 FPS timer.

---

## ⚙️ How It Works

* Uses `time()` and `localtime()` to retrieve the system’s current time.
* Calculates rotation angles for each hand:

  * Hour hand: `360 - (hours * 30 + minutes * 0.5)`
  * Minute hand: `360 - minutes * 6`
  * Second hand: `360 - seconds * 6`
* Uses OpenGL transformations (`glRotatef`, `glTranslatef`, `glScalef`) to draw and rotate elements.
* Renders stroke-based vector text inside a black rectangle positioned on the second hand.

---

## 🚀 Usage

1. Make sure you have a C++ environment with OpenGL and GLUT/FreeGLUT installed.
2. Compile the program:

   ```bash
   g++ main.cpp -lGL -lGLU -lglut -lGLEW -o clock
   ```
3. Run it:

   ```bash
   ./clock
   ```

The window will show a live analog clock with a rotating digital time display.

---

## 🔍 Key Functions

| Function       | Description                                                |
| -------------- | ---------------------------------------------------------- |
| `drawCircle()` | Draws the circular clock face using line segments.         |
| `drawHand()`   | Draws a clock hand with given length, width, and rotation. |
| `drawText()`   | Renders a string using stroke fonts with rotation.         |
| `display()`    | Main rendering function called each frame.                 |
| `timer()`      | Updates the display at approximately 60 FPS.               |

---

## 📦 Requirements

* C++11 or higher compiler
* OpenGL
* GLEW
* FreeGLUT

---

## 👤 Author

**Ramin Joshang**

