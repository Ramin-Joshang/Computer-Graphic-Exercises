# 🎢 3D Spiral with Frustum and Camera Rotation

> **Practice #:** 8
> **Language:** C++
> **Graphics Library:** OpenGL (GLEW + FreeGLUT)

---

## 🧩 Description

This OpenGL program renders a **3D helix** (`z = t`, `x = R cos(t)`, `y = R sin(t)`) using `GL_LINE_STRIP`. The camera can be rotated along all three axes and the perspective projection (frustum) parameters can be adjusted **interactively**.

---

## 🎯 Features

* 🌀 Draws a smooth 3D **helix** with `glVertex3f(x, y, z)`
* 🎮 Interactive camera rotation: yaw, pitch, and roll
* 🔍 Real-time adjustment of **`glFrustum`** parameters
* 🔄 Reset scene with a single key
* 🖱️ Redraws in response to window resizing or key events

---

## 🕹️ Controls

### 🔁 Camera Rotation

| Key | Action            |
| --- | ----------------- |
| `W` | Rotate up (X−)    |
| `S` | Rotate down (X+)  |
| `A` | Rotate left (Y−)  |
| `D` | Rotate right (Y+) |
| `Q` | Roll left (Z−)    |
| `E` | Roll right (Z+)   |

### 🔧 Frustum Adjustment

| Key | Action         |
| --- | -------------- |
| `8` | Increase top   |
| `2` | Decrease top   |
| `6` | Increase right |
| `4` | Decrease right |
| `9` | Increase near  |
| `1` | Decrease near  |

### 🔄 Scene Control

| Key   | Action                   |
| ----- | ------------------------ |
| `R`   | Reset camera and frustum |
| `ESC` | Exit program             |

---

## 🧾 Dependencies

* **GLEW** - OpenGL Extension Wrangler
* **FreeGLUT** - OpenGL Utility Toolkit
* **OpenGL (GL/GLU)**

Ensure the following libraries are linked:

```
glew32.lib
freeglut.lib
opengl32.lib
glu32.lib
```

---

## 🧠 Concepts Practiced

* Drawing in 3D using `glVertex3f`
* Perspective projection with `glFrustum`
* Manual camera rotation via `glRotatef`
* Real-time scene interaction and updates
* Coordinate transformations in OpenGL

---

## 📁 File Overview

```bash
/practice-9-helix/
├── main.cpp         # OpenGL 3D helix with interactive controls
├── README.md        # Project documentation
```

---

## 🧠 Author

**Ramin Joshang**