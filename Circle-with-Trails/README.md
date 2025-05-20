# 🌀 Circle Animation with Trail (Without Vector)

> **Practice #:** 5.2
> **Language:** C++
> **Graphics Library:** OpenGL (GLEW + FreeGLUT)

---

## 📌 Description

This project demonstrates a **pulsating circle animation** enhanced with **trailing outlines** to simulate motion blur or echo. The animation is performed without using C++ STL containers like `std::vector`, instead relying on a fixed-size array.

---

## ✨ Features

* ✅ Filled **pulsating circle** rendered using `GL_TRIANGLE_FAN`
* ✅ **Trail effect** using `GL_LINE_LOOP` with transparency
* ✅ Manages trail data using a fixed-length `CircleStep` array
* ✅ Bidirectional pulsing: radius oscillates between `minRadius` and `maxRadius`
* ✅ Uses blending for smooth fading of trails

---

## 🧠 Key Concepts

* **Alpha blending** for trail transparency
* **Fixed-size circular buffer logic** for trail history
* **GL\_BLEND** + `glBlendFunc()` for semi-transparent drawing
* **Timer-based animation** using `glutTimerFunc()`

---

## ⌨️ Controls

| Key   | Action           |
| ----- | ---------------- |
| `ESC` | Exit the program |

---

## 📊 Behavior

* Radius starts at **45.0**, shrinks to **3.0**, then expands again in a loop.
* Every frame, a new trail circle is added with semi-transparent outline.
* Maximum trail count is **100** (adjustable via `MAX_TRAILS`).

---

## 🧾 Sample Output Behavior

```
- Circle pulsates inward and outward
- Semi-transparent outlines trail behind to emphasize motion
- Responsive and clean animation at consistent pace
```

---

## ⚙️ Requirements

* **C++ Compiler** (C++11 or newer)
* **GLEW**
* **FreeGLUT**
* **OpenGL (GL/GLU)**

---

## ⚒️ Build Instructions

Ensure these libraries are linked:

```
glew32.lib
freeglut.lib
opengl32.lib
glu32.lib
```

Example headers:

```cpp
#include <GL/glew.h>
#include <GL/freeglut.h>
```

---

## 💡 Notes

* All trail data is manually managed in a raw array, simulating a simple buffer system.
* Uses `GLUT_DOUBLE` for flicker-free rendering via double buffering.

---

## 👨‍💻 Author

**Ramin Joshang**
