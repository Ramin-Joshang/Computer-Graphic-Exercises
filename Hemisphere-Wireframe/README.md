# 🌗 Hemisphere Wireframe Renderer

> **Practice #:** 10
> **Language:** C++
> **Libraries:** OpenGL (GLEW + FreeGLUT)

---

## 📌 Description

This program renders a **wireframe hemisphere** composed of multiple triangle strips.
It uses spherical coordinates to generate vertex positions on the hemisphere surface,
and allows interactive rotation and adjustment of the mesh resolution.

---

## 🧠 Features

* ✅ Render hemisphere as wireframe with triangle strips.
* ✅ Adjustable mesh resolution via parameters `p` and `q`.
* ✅ Real-time rotation around X, Y, and Z axes controlled by keyboard.
* ✅ Uses perspective frustum projection.
* ✅ Clean and simple 3D transformation pipeline.

---

## ⌨️ Controls

| Key     | Action                                        |
| ------- | --------------------------------------------- |
| `a`/`d` | Rotate around X axis                          |
| `w`/`s` | Rotate around Y axis                          |
| `z`/`e` | Rotate around Z axis                          |
| `p`/`P` | Decrease/Increase horizontal resolution (`p`) |
| `q`/`Q` | Decrease/Increase vertical resolution (`q`)   |
| `ESC`   | Exit program                                  |

---

## ⚙️ How It Works

* The hemisphere surface is generated using spherical coordinates:

  $$
  \begin{cases}
  x = R \cdot \cos(\theta) \cdot \cos(\phi) \\
  y = R \cdot \sin(\theta) - \text{offset} \\
  z = R \cdot \cos(\theta) \cdot \sin(\phi)
  \end{cases}
  $$

  where $\theta$ varies from 0 to $\pi/2$ (hemisphere latitude),
  and $\phi$ varies from 0 to $2\pi$ (longitude).

* The program draws several sets of triangle strips between latitude bands (`j`) and around longitude (`i`).

* The user can change resolution by modifying `p` (number of longitude slices) and `q` (latitude divisions), which affect smoothness.

* Rotation angles around X, Y, Z axes are applied before rendering to view the hemisphere from different perspectives.

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