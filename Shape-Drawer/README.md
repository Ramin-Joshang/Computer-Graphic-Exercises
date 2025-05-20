# 🖌️ Interactive Shape Drawer (Circles & Rectangles)

> **Practice #:** 14
> **Language:** C++
> **Libraries:** OpenGL (GLEW + FreeGLUT)

---

## 📌 Description

This program lets users **draw circles and rectangles interactively** on a 2D canvas using the mouse.
Users can switch between drawing circles or rectangles and select different colors from a right-click menu.
Multiple shapes can be drawn and displayed simultaneously.
The last drawn shape can be deleted with Backspace.

---

## 🧠 Features

* ✅ Draw circles or rectangles by click-dragging with the mouse.
* ✅ Real-time preview of the shape while drawing.
* ✅ Choose shape type (circle or rectangle) from right-click menu.
* ✅ Choose shape color from a variety of options via right-click menu.
* ✅ Maintain and display multiple colored shapes on the canvas.
* ✅ Undo feature: remove the last drawn shape with Backspace.
* ✅ Simple 2D orthographic projection and coordinate conversion.

---

## ⌨️ Controls

| Key / Mouse Button                | Action                                |
| --------------------------------- | ------------------------------------- |
| `Left Mouse Button` (hold & drag) | Draw the selected shape interactively |
| `Right Mouse Button`              | Open menu to choose shape or color    |
| `Backspace`                       | Delete the last drawn shape           |
| `ESC`                             | Exit the program                      |

---

## ⚙️ How It Works

* Coordinates are mapped to a 100x100 orthographic projection.
* On mouse press, the starting corner (or center for circle) is recorded.
* On dragging, the endpoint is updated, resizing the shape dynamically.
* On mouse release, the shape is finalized and stored with its type and color.
* The display callback renders all stored shapes with their individual colors.
* Right-click menu lets users pick the shape type (circle/rectangle) and color.
* Pressing Backspace deletes the last drawn shape.

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