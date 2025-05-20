# 🔍 Orthographic Projection Manipulation – Interactive Triangle

> **Practice #:** 2
> **Language:** C++
> **Libraries:** OpenGL (GLEW + FreeGLUT)

---

## 📌 Description

This OpenGL project demonstrates **interactive orthographic projection manipulation** using keyboard inputs. A simple orange triangle is rendered in a 2D orthographic space, and the projection boundaries can be adjusted in real-time.

---

## 🎯 Features

* ✅ Renders a triangle using `GL_LINE_LOOP`.
* ✅ Uses orthographic projection with `glOrtho()`.
* ✅ View volume parameters can be changed via keyboard.
* ✅ Real-time updates on key press.
* ✅ Cyan background with thick orange triangle outline.

---

## 🧠 How It Works

### Projection Setup

```cpp
glOrtho(left, right, top, bottom, near, far);
```

* Default view volume:

  ```
  left = 0.0, right = 100.0
  top = 0.0, bottom = 100.0
  near = -1.0, far = 1.0
  ```

### User Interaction

When a key is pressed:

* `orthoTop`, `orthoRight`, or `orthoNear` is modified.
* The viewport is resized and `glOrtho()` is recalculated.
* The triangle is redrawn according to the new projection settings.

---

## ⌨️ Controls

| Key   | Action                      |
| ----- | --------------------------- |
| `W`   | Increase top plane          |
| `Z`   | Decrease top plane          |
| `A`   | Increase right plane        |
| `D`   | Decrease right plane        |
| `R`   | Increase near plane         |
| `S`   | Decrease near plane         |
| `P`   | Reset projection to default |
| `ESC` | Exit application            |

---

## 🧱 Build Requirements

* **C++11 or higher**
* **GLEW**
* **FreeGLUT**
* **OpenGL**

---

## ⚙️ Linking (Windows - Visual Studio)

Ensure the following libraries are linked:

```
glew32.lib
freeglut.lib
opengl32.lib
glu32.lib
```

Headers:

```cpp
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
```

---

## 📁 File Summary

| File                   | Description                                   |
| ---------------------- | --------------------------------------------- |
| `experimentPoints.cpp` | Main source file with drawing and input logic |

---

## 👤 Author

**Ramin Joshang**