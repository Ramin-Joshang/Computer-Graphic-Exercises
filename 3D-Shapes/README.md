# 🌗 OpenGL 3D Shapes Demo

> **Practice #:** 11
> **Language:** C++
> **Libraries:** OpenGL (GLEW + FreeGLUT)

---

## 📌 Description

This program demonstrates rendering of various **2D shapes and curves** using OpenGL.
The shapes include sine curve, ellipse, letter 'A', number '8', torus approximation, cone, parabola-like slide curve, crescent moon, cube, and rectangular prism.
Users can switch between shapes interactively using keyboard arrow keys.

---

## 🧠 Features

* ✅ Render multiple 2D shapes and curves as line strips or loops.
* ✅ Includes parametric curves like sine wave and ellipse.
* ✅ Approximates complex shapes such as a torus and crescent moon.
* ✅ Interactive shape switching using keyboard left/right arrow keys.
* ✅ Responsive window resizing with proper aspect ratio maintenance.

---

## ⌨️ Controls

| Key           | Action                   |
| ------------- | ------------------------ |
| `Left Arrow`  | Switch to previous shape |
| `Right Arrow` | Switch to next shape     |
| `ESC`         | Exit the program         |

---

## ⚙️ How It Works

* Shapes are drawn using OpenGL primitives such as `GL_LINE_STRIP`, `GL_LINE_LOOP`, and `GL_TRIANGLE_FAN`.
* Parametric equations for curves like sine, ellipse, and circle are used to compute vertices dynamically.
* Complex shapes like the torus are approximated by looping over angles and connecting points with line strips.
* The scene redraws on window resize, keeping the aspect ratio intact using orthographic projection (`gluOrtho2D`).
* Keyboard input switches the currently displayed shape via cycling an index variable.

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
   ```

3. Ensure `glew32.dll` is accessible.

4. Compile and run.

---

## 👤 Author

**Ramin Joshang**