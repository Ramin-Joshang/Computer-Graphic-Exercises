# 🟣 Pulsating Circle – OpenGL Animation

> **Practice #:** 5.1
> **Language:** C++
> **Graphics Library:** OpenGL (GLEW + FreeGLUT)

---

## 📌 Description

This project animates a **pulsating circle** (regular polygon with 100 vertices) by dynamically changing its radius over time, creating a breathing-like effect. The animation is achieved using a timer function that updates the radius and redraws the circle at approximately 60 FPS.

---

## ✨ Features

* ✅ Smooth **circle scaling animation** (expanding and shrinking radius)
* ✅ Centered at `(50, 50)` in a 2D orthographic projection
* ✅ Adjustable radius range: **10.0** to **45.0**
* ✅ Pause/resume functionality using `SPACE`
* ✅ Clean and simple visual style

---

## 🧠 Key Concepts

* **GL\_TRIANGLE\_FAN** for efficient filled circle drawing
* **Timer-based animation** via `glutTimerFunc(16, ...)` (\~60 FPS)
* **Trigonometry** (`cos`, `sin`) to calculate vertex positions
* **State toggling** for pausing/resuming animation

---

## ⌨️ Controls

| Key     | Action                        |
| ------- | ----------------------------- |
| `SPACE` | Pause/Resume radius animation |
| `ESC`   | Exit the program              |

---

## 🧾 Output Behavior

```
100-sided polygon simulates a breathing or pulsating circle effect
Radius cycles between 10 and 45 units smoothly and indefinitely
```

---

## 📦 Requirements

* **C++ Compiler** (C++11 or higher)
* **GLEW**
* **FreeGLUT**
* **OpenGL**

---

## ⚙️ Build Instructions (Windows - Visual Studio)

1. Link the following libraries:

   ```
   glew32.lib
   freeglut.lib
   opengl32.lib
   glu32.lib
   ```

2. Ensure `glew32.dll` is in your working directory.

3. Header includes:

   ```cpp
   #include <GL/glew.h>
   #include <GL/freeglut.h>
   ```

---

## 🧑‍💻 Author

**Ramin Joshang**
