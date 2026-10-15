# Módulo 3 · Arquitecturas de memoria compartida

**Profesor:** Dr. Emmanuel Torres Ríos

Este módulo estudia cómo aprovechar procesadores con varios núcleos que comparten la misma memoria: concurrencia y paralelismo, clasificación de computadoras, arquitectura del conjunto de instrucciones y programación multihilo con **OpenMP**. Como caso de aplicación se trabaja el procesamiento de imágenes BMP en C.

## Contenido

| Carpeta | Descripción |
|---|---|
| [`parallel-processing/`](parallel-processing/) | Programas con OpenMP: hilos en paralelo (`hello.c`), cálculo de π secuencial (`sum_integer.c`) y paralelo (`integer_parallel.c`). Incluye el reporte del **Benchmark** que compara tiempos de ejecución en una MacBook Air M1, una ASUS Vivobook Pro 15 y una ASUS TUF F16. |
| [`img2gray/`](img2gray/) | Conversión de BMP a escala de grises (`3_ImageGrises.c`) y cálculo del histograma RGB (`hist_image.c`), graficado con `hist.py` a partir de `histograma.csv`. |
| [`bmp-histogram/`](bmp-histogram/) | El histograma RGB empaquetado como biblioteca (`elemento.h`) con un programa de prueba (`demo_lib.c`). |
| [`activity01-img-transformations/`](activity01-img-transformations/) | **Actividad 1:** biblioteca de transformaciones de imágenes (`img_lib.h`) con reporte. |

## Compilación

```bash
# Programas con OpenMP
gcc -fopenmp integer_parallel.c -o integer_parallel

# Programas sin OpenMP
gcc hist_image.c -o hist_image
```

En macOS con Apple Clang, OpenMP requiere `libomp` (por ejemplo, con Homebrew) y las opciones `-Xpreprocessor -fopenmp -lomp`.
