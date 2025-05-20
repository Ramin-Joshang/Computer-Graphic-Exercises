# 📍 Interactive Point & Line Drawer

> **Practice #:** 15
> **Language:** C++
> **Libraries:** OpenGL (GLEW + FreeGLUT)

---

## 📌 Description

This program allows users to **draw points and lines interactively** on a 2D canvas using the mouse.

* Left-click to add points.
* Every two consecutive points are connected by a line segment automatically.
* Right-click closes the program.

---

## 🧠 Features

* ✅ Draw points on the canvas by clicking the left mouse button.
* ✅ Connect every pair of consecutive points with a line automatically.
* ✅ Display all drawn points and lines persistently.
* ✅ Simple coordinate system matching the window size for intuitive drawing.
* ✅ Exit the program with right-click or ESC key.

---

## ⌨️ Controls

| Key / Mouse Button   | Action                                      |
| -------------------- | ------------------------------------------- |
| `Left Mouse Button`  | Add a point (and draw line if second point) |
| `Right Mouse Button` | Exit the program                            |
| `ESC`                | Exit the program                            |

---

## ⚙️ How It Works

* The coordinate system is mapped to the window's pixel dimensions using orthographic projection.
* On each left mouse click, the program stores the point.
* If it is the second point in a pair, a line connecting the last two points is drawn.
* Points and lines are stored in vectors and drawn every frame.
* Right-click or pressing ESC exits the application.

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