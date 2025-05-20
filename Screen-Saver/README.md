# 🎨 Animated Bezier Curves – Screen Saver

> **Practice #:** 1
> **Language:** C++
> **Libraries:** OpenGL (GLEW + FreeGLUT)

---

## 📌 Description

This project creates a screen saver-style animation of **50 colorful cubic Bézier curves**. Each curve evolves in real-time, with control points moving, bouncing off the edges, and continuously updating the rendered curves.

---

## 🧠 Features

* ✅ 50 independently animated Bézier curves.
* ✅ Unique randomized control points, velocities, and colors.
* ✅ Control points bounce when hitting the 2D boundary (0–100).
* ✅ Smooth rendering using line strips and the Bézier cubic equation.
* ✅ Real-time animation with `glutTimerFunc()`.
* ✅ Interactivity:

  * Pause/resume with the **spacebar**.
  * Exit the program with the **ESC** key.

---

## 📐 Bézier Curve Details

Each cubic Bézier curve is defined using the equation:

```
B(t) = (1 - t)^3·P0 + 3(1 - t)^2·t·P1 + 3(1 - t)·t^2·P2 + t^3·P3
```

* `P0` to `P3`: Control points (randomly initialized)
* `t`: Parametric value from 0 to 1 (evaluated at 50 points)
* Curves are redrawn every frame, updating the control points' positions based on velocity and boundaries.

---

## ⌨️ Controls

| Key        | Action           |
| ---------- | ---------------- |
| `SPACEBAR` | Pause/Resume     |
| `ESC`      | Exit Application |

---

## ⚙️ How It Works

* Randomly generates initial control points (`cp[4][2]`) and velocities (`vel[4][2]`).
* On each timer callback:

  * Updates all control points by adding velocity.
  * Inverts velocity if a point hits boundary (0 or 100).
  * Redraws all 50 Bézier curves using 50 interpolated points each.
* Uses `glColor3fv()` for colorful rendering and `glLineWidth()` for visual clarity.

---

## 📦 Requirements

* C++11 or higher compiler
* **OpenGL**
* **GLEW**
* **FreeGLUT**

---

## 🧱 Build Instructions (Windows – Visual Studio)

1. Link against the following libraries:

   ```
   glew32.lib
   freeglut.lib
   opengl32.lib
   glu32.lib
   ```
2. Ensure headers are included:

   ```
   glew.h
   freeglut.h
   glext.h
   ```
3. Ensure `glew32.dll` is available in your project or executable path.
4. Compile and run the project.

---

## 👤 Author

**Ramin Joshang**

---
