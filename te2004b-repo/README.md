# TE2004B · Diseño de Sistemas Embebidos Avanzados

Repositorio de trabajo de la materia **Diseño de sistemas embebidos avanzados (TE2004B)**, Tecnológico de Monterrey, Campus Puebla, semestre agosto–diciembre 2026.

| | |
|---|---|
| **Alumno** | Luis Fernando Salazar Hernández · A01738527 |
| **Carrera** | Ingeniería en Robótica y Sistemas Digitales |
| **Periodo** | Agosto – diciembre 2026 |

La materia se divide en tres módulos que aportan las bases para el reto del bloque: un sistema *pick and place* que combina visión computacional, procesamiento embebido en una Raspberry Pi y control de un brazo robótico.

---

## Módulos

| Módulo | Profesor | De qué trata | Carpeta |
|---|---|---|---|
| **1. Análisis y diseño de algoritmos** | Dr. César Torres Huitzil | Complejidad y eficiencia de algoritmos, ordenamiento y primeros filtros de imagen (correlación 2D, mediana, padding). | [`module01-algorithm-analysis-and-design`](module01-algorithm-analysis-and-design/) |
| **2. Procesamiento digital de señales** | Dr. David Antonio Torres | Señales y sistemas en tiempo discreto, convolución, transformada Z, DFT/FFT y filtros digitales FIR e IIR aplicados a imágenes en MATLAB. | [`module02-digital-signal-processing`](module02-digital-signal-processing/) |
| **3. Arquitecturas de memoria compartida** | Dr. Emmanuel Torres Ríos | Concurrencia y paralelismo, clasificación de computadoras, OpenMP y procesamiento de imágenes BMP en C. | [`module03-shared-memory-architecture`](module03-shared-memory-architecture/) |

## Reto del bloque: *Pick and place* con visión computacional

Sistema de *pick and place* con el manipulador **UFactory Lite 6**, controlado desde una **Raspberry Pi**, con algoritmos diseñados en **MATLAB** y monitoreo en la nube con **ThingSpeak**.

| Componente | Función |
|---|---|
| Raspberry Pi | Procesamiento local, ejecución de los algoritmos y control del manipulador en tiempo real. |
| MATLAB | Diseño y simulación de los algoritmos de visión computacional y de las trayectorias cinemáticas. |
| ThingSpeak | Analítica IoT en la nube para monitorear y registrar el conteo de ciclos. |

**Entregables:** (1) propuesta de solución, (2) solución mejorada y validación del algoritmo, (3) demostración del sistema completo en el Día de la Ingeniería.

Avances y documentación en [`challenge-pick-and-place`](challenge-pick-and-place/).

---

## Estructura del repositorio

```
.
├── module01-algorithm-analysis-and-design/
│   ├── sorting-algorithms/          # Insertion Sort y Bubble Sort en Python
│   ├── computer-vision/             # Correlación 2D, filtro de mediana y padding
│   └── reports/                     # Actividad 01.1.3: análisis de algoritmos de ordenamiento
├── module02-digital-signal-processing/
│   ├── activity03-filter2d/         # Filtros 2D en MATLAB (motion blur, desenfoque, bordes)
│   └── examples/                    # Convolución 2D y cámara en MATLAB
├── module03-shared-memory-architecture/
│   ├── parallel-processing/         # OpenMP: cálculo de pi y benchmark de hilos
│   ├── img2gray/                    # Escala de grises e histograma RGB de imágenes BMP
│   ├── bmp-histogram/               # Biblioteca para el histograma de un BMP
│   └── activity01-img-transformations/  # Biblioteca de transformaciones de imágenes
└── challenge-pick-and-place/
    └── matlab/                      # Primeros pasos con la Raspberry Pi y detección de bordes
```

## Herramientas

C (GCC / MinGW-w64 y Apple Clang) · OpenMP · Python (NumPy, OpenCV, pandas, Matplotlib) · MATLAB (Image Processing Toolbox, MATLAB Coder, soporte para Raspberry Pi) · Raspberry Pi 4 · UFactory Lite 6 · ThingSpeak

## Actividad destacada

**[Módulo 3 · Actividad 1: Biblioteca de transformaciones de imágenes](module03-shared-memory-architecture/activity01-img-transformations/)**: seis transformaciones para imágenes BMP de 24 bits en C (inversión horizontal y vertical, desenfoque; a color y en escala de grises), con manejo del relleno de fila del formato BMP.

<p align="center">
  <img src="module03-shared-memory-architecture/activity01-img-transformations/docs/sample.png" width="150" alt="Original">
  <img src="module03-shared-memory-architecture/activity01-img-transformations/docs/inv_hor_color.png" width="150" alt="inv_hor_color">
  <img src="module03-shared-memory-architecture/activity01-img-transformations/docs/inv_ver_bn.png" width="150" alt="inv_ver_bn">
  <img src="module03-shared-memory-architecture/activity01-img-transformations/docs/blur_color.png" width="150" alt="blur_color">
</p>
