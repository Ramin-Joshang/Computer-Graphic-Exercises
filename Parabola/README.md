# 📐 Practice 8: Rotated Parabola Drawing

> **Practice #:** 7
> **Language:** C++
> **Graphics Library:** OpenGL (GLEW + FreeGLUT)

---

## 🧩 Description

This OpenGL program visualizes a **parabola** that can be rotated in **four directions** interactively:

* Right-facing
* Up-facing
* Left-facing (inverted)
* Down-facing

With each press of the **spacebar**, the orientation of the parabola changes in a cyclic order.

---

## 🎯 Features

* ✏️ Draws a smooth **parabola** using line segments (`GL_LINE_STRIP`)
* ↩️ **Rotates** the curve in four directions on user input
* 🎨 Colored and centered within a normalized coordinate system
* 📐 Scales parabola smoothly using a normalized loop variable

---

## 💡 Orientation Modes

| Direction | `direction` Value | Behavior        |
| --------- | ----------------- | --------------- |
| Right     | `0`               | Opens **up**    |
| Up        | `1`               | Opens **right** |
| Left      | `2`               | Opens **down**  |
| Down      | `3`               | Opens **left**  |

Each mode changes how `x` and `y` are calculated using the parabola equation `y = x²`.

---

## 🕹️ Controls

| Key     | Action                    |
| ------- | ------------------------- |
| `Space` | Rotate parabola direction |
| `ESC`   | Exit program              |

---

## 🧾 Dependencies

* **GLEW** - OpenGL Extension Wrangler
* **FreeGLUT** - OpenGL Utility Toolkit
* **OpenGL (GL/GLU)**

Ensure you're linking the following:

```
glew32.lib
freeglut.lib
opengl32.lib
glu32.lib
```

---

## 🧠 Concepts Practiced

* Parametric plotting of mathematical curves
* Directional transformation of functions
* User interaction through `glutKeyboardFunc()`
* Basic 2D coordinate transformations
* OpenGL drawing pipeline using immediate mode

---

## 📁 File Structure

```bash
/rotated-parabola/
├── main.cpp         # Your OpenGL C++ source
├── README.md        # This file
```

---

## 🧠 Author

**Ramin Joshang**