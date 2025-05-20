# 🌪️ Animated Spiral Drawing

> **Practice #:** 6
> **Language:** C++
> **Graphics Library:** OpenGL (GLEW + FreeGLUT)

---

## 🧩 Description

This OpenGL project demonstrates an **animated spiral** that:

* Gradually draws itself from the center outward.
* **Rotates continuously** even after being fully drawn.
* Creates a **mesmerizing spiral effect** with smooth lines and real-time animation.

---

## ✨ Features

* 🌀 **Spiral with 30 turns**, drawn incrementally from the center outward.
* 🧭 **Smooth rotation** using angle offset updated over time.
* 🎨 Fully adjustable parameters for turns, radius, speed, and resolution.
* 🧵 Anti-aliased (`GL_LINE_SMOOTH`) spiral for a crisp appearance.
* 🧮 Procedural generation — each point is calculated on the fly.

---

## ⚙️ Configuration

| Parameter       | Value | Description                       |
| --------------- | ----- | --------------------------------- |
| `TOTAL_POINTS`  | 3000  | Resolution of spiral (smoothness) |
| `TURNS`         | 30    | Number of full spiral turns       |
| `MAX_RADIUS`    | 250.0 | Outer radius of the spiral        |
| `MIN_RADIUS`    | 10.0  | Inner radius (starting point)     |
| `rotationSpeed` | 0.5   | Speed of spiral rotation          |

---

## 📊 Behavior

* Spiral is incrementally drawn by updating `drawProgress`.
* Once drawing is complete (`drawProgress >= 1.0`), the spiral continues rotating.
* Continuous animation via `glutTimerFunc()` at \~60 FPS.

---

## ⌨️ Controls

| Key | Action                              |
| --- | ----------------------------------- |
| N/A | No interaction; automatic animation |

---

## 💡 Concepts Practiced

* Parametric equations: `x = r cos(θ)`, `y = r sin(θ)`
* Dynamic animation using time-stepped updates
* Smooth line rendering via OpenGL hints
* Procedural drawing without pre-storing vertex data

---

## 🧾 Dependencies

* GLEW
* FreeGLUT
* OpenGL (GL, GLU)

Ensure you link:

```
glew32.lib
freeglut.lib
opengl32.lib
glu32.lib
```

---

## 🖼️ Sample Output

The final output is a smooth, colorful spiral that slowly rotates in place after being fully drawn.

---

## 🧠 Author

**Ramin Joshang**
