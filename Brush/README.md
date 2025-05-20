# 🖌️ Brush

> **Practice #:** 16
> **Language:** C++
> **Libraries:** OpenGL (GLEW + FreeGLUT)

---

## 📌 Description

This program enables users to **draw freehand strokes** on a 2D canvas using the mouse.
Press and hold the left mouse button to start drawing; moving the mouse creates a continuous stroke.
Multiple strokes can be drawn and are displayed persistently.
Right-click or ESC key exits the program.

---

## 🧠 Features

* ✅ Freehand drawing with smooth continuous lines.
* ✅ Store and display multiple separate strokes.
* ✅ Real-time rendering of the current stroke while drawing.
* ✅ Coordinate system matches the window pixels for intuitive drawing.
* ✅ Exit program with right-click or ESC key.

---

## ⌨️ Controls

| Key / Mouse Button                | Action                 |
| --------------------------------- | ---------------------- |
| `Left Mouse Button` (hold + drag) | Draw a freehand stroke |
| `Right Mouse Button`              | Exit the program       |
| `ESC`                             | Exit the program       |

---

## ⚙️ How It Works

* The coordinate system is mapped to the window's pixel dimensions via orthographic projection.
* On pressing the left mouse button, a new stroke starts collecting points.
* Moving the mouse while holding the button adds points to the current stroke.
* Releasing the button finalizes and stores the stroke.
* All strokes are drawn as line strips, with the current stroke rendered dynamically.

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