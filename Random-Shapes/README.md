# 🎇 Optimized Random Shapes – OpenGL Animation

> **Practice #:** 3
> **Language:** C++
> **Libraries:** OpenGL (GLEW + FreeGLUT)

---

## 📌 Description

This project creates an animated display of **500 randomized 2D shapes** using OpenGL. Each shape has a unique type, color, velocity, and rotation, creating a vibrant, dynamic screen saver-like effect.

---

## ✨ Features

* ✅ Randomized shape types: points, lines, polygons, triangle fans/strips, etc.
* ✅ Independent motion and rotation for each shape.
* ✅ Bouncing within a 100×100 orthographic view box.
* ✅ Randomized sizes, colors, and number of polygon sides.
* ✅ Dynamic, frame-based animation using `glutTimerFunc()`.

---

## 🔁 Animation Logic

* **Shapes move** with individual velocities.
* When they hit the viewport boundaries, they **bounce** back and **change color**.
* Shapes like polygons rotate continuously using a small per-frame `rotationSpeed`.

---

## 🧠 Key Concepts Used

* **Orthographic projection** with `glOrtho(0, 100, 0, 100, -1, 1)`.
* **Randomization** using `rand()` and custom `randomFloat()` function.
* **Timers** for smooth real-time animation:

  ```cpp
  glutTimerFunc(30, update, 0);
  ```
* Shape types include:

  * `GL_POINTS`
  * `GL_LINES`, `GL_LINE_STRIP`, `GL_LINE_LOOP`
  * `GL_TRIANGLES`, `GL_TRIANGLE_STRIP`, `GL_TRIANGLE_FAN`
  * `GL_POLYGON`

---

## 🔧 Controls

| Key   | Action       |
| ----- | ------------ |
| `ESC` | Exit program |

---

## 📦 Requirements

* **C++ Compiler** (C++11+)
* **GLEW**
* **FreeGLUT**
* **OpenGL**

---

## ⚙️ Build Instructions (Windows - Visual Studio)

1. Link against:

   ```
   glew32.lib
   freeglut.lib
   opengl32.lib
   glu32.lib
   ```

2. Ensure `glew32.dll` is available at runtime.

3. Include necessary headers:

   ```cpp
   #include <GL/glew.h>
   #include <GL/freeglut.h>
   #include <GL/glext.h>
   ```

---

## 📁 File Summary

| File       | Description                                    |
| ---------- | ---------------------------------------------- |
| `main.cpp` | Contains full shape logic and drawing routines |

---

## 👤 Author

**Ramin Joshang**

