# 🏀 Bouncing Ball Animation

> **Practice #:** 9
> **Language:** C++
> **Libraries:** OpenGL (GLEW + FreeGLUT)

---

## 📌 Description

This project simulates a **bouncing ball** in a 2D orthographic space. The ball moves horizontally with constant velocity, affected vertically by gravity. It bounces off the floor with a diminishing velocity due to a bounce factor, and gradually comes to rest. The ball also rotates based on horizontal velocity, providing a natural rolling effect.

---

## 🧠 Features

* ✅ Realistic bouncing behavior with gravity and energy loss.
* ✅ Horizontal movement with constant velocity.
* ✅ Rotation of the ball proportional to movement speed.
* ✅ Automatic reset after the ball stops.
* ✅ Uses wireframe sphere rendering (`glutWireSphere`).
* ✅ Depth testing enabled for proper 3D rendering.

---

## ⌨️ Controls

| Key   | Action       |
| ----- | ------------ |
| `ESC` | Exit Program |

---

## ⚙️ How It Works

* The ball’s position (`posX`, `posY`) and velocity (`velX`, `velY`) are updated every 50 ms.
* Gravity constantly affects vertical velocity.
* When the ball hits the floor, its vertical velocity inverts and decreases by a bounce factor (energy loss).
* When vertical velocity becomes small enough, the ball stops moving and resets after 3 seconds.
* The ball rotates around the Z-axis proportional to the horizontal velocity to simulate rolling.
* Orthographic projection is used to keep consistent 2D coordinates.
* Uses `glutTimerFunc` for smooth periodic updates.

---

## 📦 Requirements

* C++11 or higher compiler
* **OpenGL**
* **GLEW**
* **FreeGLUT**

---

## 🧱 Build Instructions (Windows – Visual Studio)

1. Link against:

   ```
   glew32.lib
   freeglut.lib
   opengl32.lib
   glu32.lib
   ```

2. Include headers:

   ```cpp
   #include <GL/glew.h>
   #include <GL/freeglut.h>
   #include <GL/glext.h>
   ```

3. Ensure `glew32.dll` is accessible.

4. Compile and run.

---

## 👤 Author

**Ramin Joshang**