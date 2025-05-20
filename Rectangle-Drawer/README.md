# ▫️ Interactive Rectangle Drawer

> **Practice #:** 13.1
> **Language:** C++
> **Libraries:** OpenGL (GLEW + FreeGLUT)

---

## 📌 Description

This program allows users to **interactively draw rectangles** on a 2D canvas using the mouse.
Clicking and dragging the left mouse button defines the start and end points of a new rectangle.
Multiple rectangles can be drawn and displayed simultaneously.
Users can delete the last drawn rectangle using the Backspace key.

---

## 🧠 Features

* ✅ Draw rectangles interactively by click-dragging with the mouse.
* ✅ Real-time preview of the rectangle during drawing.
* ✅ Maintain and display multiple rectangles on the canvas.
* ✅ Undo feature: remove the last drawn rectangle with Backspace.
* ✅ Simple 2D orthographic projection and coordinate conversion.

---

## ⌨️ Controls

| Key                               | Action                             |
| --------------------------------- | ---------------------------------- |
| `Left Mouse Button` (hold & drag) | Draw a new rectangle interactively |
| `Backspace`                       | Delete the last drawn rectangle    |
| `ESC`                             | Exit the program                   |

---

## ⚙️ How It Works

* The coordinate system is mapped to a 100x100 orthographic projection.
* On mouse press, the start point is recorded as one corner of the rectangle.
* As the mouse moves (dragging), the opposite corner is updated in real-time.
* On mouse release, the rectangle is finalized and stored in an array.
* The display callback renders all existing rectangles and the currently drawn rectangle if any.
* Pressing Backspace marks the last rectangle as deleted and removes it from rendering.

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