# 🔺 Growing/Shrinking Polygon – OpenGL Animation

> **Practice #:** 4
> **Language:** C++
> **Graphics Library:** OpenGL (GLEW + FreeGLUT)

---

## 📌 Description

This project demonstrates a simple **animated polygon** that dynamically grows from **3 to 100 sides** and then shrinks back to a triangle. It runs in real-time using OpenGL and provides a smooth geometric transformation animation.

---

## ✨ Features

* ✅ Polygon starts as a triangle (3 sides)
* ✅ Increases by 1 side every 100ms until it becomes a 100-sided shape
* ✅ Then reverses direction and decreases back to 3 sides
* ✅ Continues looping infinitely
* ✅ Centered at (50, 50) with a fixed radius of 40 units
* ✅ Smooth transitions using `glutTimerFunc()`

---

## 🧠 Key Concepts Used

* **Trigonometric vertex generation** using `cos()` and `sin()` to construct polygons.
* **GL\_TRIANGLE\_FAN** primitive for continuous, filled polygons.
* **Orthographic projection** via `glOrtho(0, 100, 0, 100, -1, 1)`.
* **Animation via recursion**:

  ```cpp
  glutTimerFunc(100, animate, 0);
  ```

---

## ⌨️ Controls

| Key   | Action       |
| ----- | ------------ |
| `ESC` | Exit program |

---

## 🧾 Sample Output Behavior

```
3-sided triangle → ... → 100-sided circle-like shape → ... → triangle → repeat
```

The shape appears to "breathe" in and out, shifting smoothly between a polygon and a near-perfect circle.

---

## 📦 Requirements

* **C++ Compiler** (C++11 or higher)
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

2. Place `glew32.dll` in the working directory.

3. Include:

   ```cpp
   #include <GL/glew.h>
   #include <GL/freeglut.h>
   #include <GL/glext.h>
   ```

---

## 🧑‍💻 Author

**Ramin Joshang**
