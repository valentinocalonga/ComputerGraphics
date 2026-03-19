# 🎨 Computer Graphics Exercises

![Language](https://img.shields.io/badge/language-C%2B%2B-blue)
![IDE](https://img.shields.io/badge/IDE-Visual%20Studio%202022-purple)
![Library](https://img.shields.io/badge/library-GLM-green)
![Status](https://img.shields.io/badge/status-work%20in%20progress-yellow)
![Purpose](https://img.shields.io/badge/purpose-academic%20learning-orange)

> 🚧 This repository is a work in progress and will evolve over time with new exercises, experiments, and implementations related to Computer Graphics.

This repository collects **academic and experimental implementations** of fundamental Computer Graphics concepts developed using **C++ and GLM** during the **BSc Computer Engineering (SUPSI)** learning path.

---

## 📚 Topics Covered

- Object → World transformations  
- Affine transformations (scaling, rotation, translation)  
- Transformation composition  
- Perspective projection  
- Homogeneous coordinates  
- Clip space  
- Normalized Device Coordinates (NDC)  
- Viewport transformation  
- Screen space mapping  
- Basic geometric visualization  

---

## 📂 Project Structure

```
ComputerGraphics
│
│
├── S02_BasicRasterization
│   ├── S02_BasicRasterization.cpp
│   ├── S02_BasicRasterization.vcxproj
│   ├── S02_BasicRasterization.vcxproj.filters
│   └── plot_serie2.png
├── external
│   └── glm
│
├── ComputerGraphics.sln
└── README.md
```

The **GLM library** is included locally to ensure full project portability and reproducibility.

Each exercise is implemented as an **independent Visual Studio C++ project** with its own entry point (`main.cpp`).  
This allows running and testing each graphics pipeline stage separately.

---

## 🧠 Learning Objectives

The goal of this repository is to develop a **deep understanding of the geometric graphics pipeline**, including:

- Mathematical modeling of 3D transformations  
- Correct ordering of affine transformations  
- Role of homogeneous coordinates  
- Perspective projection behavior  
- Mapping from 3D space to 2D screen space  
- Visual validation of numerical results  

---

## 🛠 Technologies

- **C++17**
- **GLM – OpenGL Mathematics Library**
- **Visual Studio 2022 Community**
- **GeoGebra** (used for geometric validation and plotting)

---

## 👨🏻‍💻 Author

**Valentino Calonga**  
BSc Computer Engineering – SUPSI  

