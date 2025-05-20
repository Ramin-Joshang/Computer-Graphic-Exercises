# 🌗 Interactive Circle Drawer

> **Practice #:** 13.1
> **Language:** C++
> **Libraries:** OpenGL (GLEW + FreeGLUT)

---

## 📌 Description

This program allows users to **interactively draw circles** on a 2D canvas using the mouse.
Clicking and dragging the left mouse button defines the center and radius of a new circle.
Multiple circles can be drawn and are displayed simultaneously.
Users can delete the last drawn circle using the Backspace key.

---

## 🧠 Features

* ✅ Draw circles interactively by click-dragging with the mouse.
* ✅ Real-time preview of the circle radius during drawing.
* ✅ Maintain and display multiple circles on the canvas.
* ✅ Undo feature: remove the last drawn circle with Backspace.
* ✅ Simple 2D orthographic projection and coordinate conversion.

---

## ⌨️ Controls

| Key                               | Action                          |
| --------------------------------- | ------------------------------- |
| `Left Mouse Button` (hold & drag) | Draw a new circle interactively |
| `Backspace`                       | Delete the last drawn circle    |
| `ESC`                             | Exit the program                |

---

## ⚙️ How It Works

* The coordinate system is mapped to a 100x100 orthographic projection.
* On mouse press, the start point is recorded as the circle center.
* As the mouse moves (dragging), the radius is updated in real-time based on the cursor distance from the center.
* On mouse release, the circle is finalized and stored in an array.
* The display callback renders all existing circles and the currently drawn circle if any.
* Pressing Backspace marks the last circle as deleted and removes it from rendering.

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
   #include <GL/glext.h>
   ```

3. Ensure `glew32.dll` is accessible.

4. Compile and run.

---

## 👤 Author

**Ramin Joshang**