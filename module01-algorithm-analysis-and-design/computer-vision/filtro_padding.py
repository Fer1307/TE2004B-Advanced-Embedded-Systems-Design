import time
import numpy as np
import cv2
import matplotlib.pyplot as plt


# ============================================================
# 1. INSERTION SORT
# ============================================================

def insertion_sort(A):
    n = len(A)

    for i in range(1, n):
        key = A[i]
        j = i - 1

        while j >= 0 and A[j] > key:
            A[j + 1] = A[j]
            j = j - 1

        A[j + 1] = key


# ============================================================
# 2. BUBBLE SORT
# ============================================================

def bubble_sort(A):

    n = len(A)

    for i in range(0, n - 1):

        for j in range(n - 1, i, -1):

            if A[j] < A[j - 1]:
                A[j], A[j - 1] = A[j - 1], A[j]


# ============================================================
# 3. CARGAR LA IMAGEN Y CONVERTIR A ESCALA DE GRISES
# ============================================================

img_bgr = cv2.imread("./coins.jpeg")

img_gray = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2GRAY)

print("Dimensiones:", img_gray.shape)
print("Tipo de dato:", img_gray.dtype)

# Mostrar imagen original en escala de grises
plt.imshow(img_gray, cmap="gray", vmin=0, vmax=255)
plt.title("Imagen original en escala de grises")
plt.axis("off")
plt.show()


# ============================================================
# 5. FILTRO DE MEDIANA
# ============================================================

def median_filter(img, window_size, sort_method):

    # Obtener dimensiones de la imagen
    rows_img = img.shape[0]
    cols_img = img.shape[1]

    # La ventana debe tener tamaño impar
    if window_size % 2 == 0:
        raise ValueError("El tamaño de la ventana debe ser impar")

    # Crear matriz para la imagen de salida
    rows_out = rows_img - window_size + 1
    cols_out = cols_img - window_size + 1

    img_out = np.zeros(
        (rows_out, cols_out),
        dtype=np.uint8
    )

    # RECORRIDO DE LA IMAGEN

    # Recorrer todas las filas
    for row in range(rows_out):

        # Recorrer todas las columnas
        for column in range(cols_out):

            # Crear arreglo donde guardaremos los valores
            window_values = []

            # RECORRIDO DE LA VENTANA
            for k in range(window_size):

                for l in range(window_size):

                    # Obtener el valor del píxel correspondiente
                    pixel = img[
                        row + k,
                        column + l
                    ]

                    # Guardar el píxel dentro del arreglo
                    window_values.append(int(pixel))

            # ORDENAR LOS VALORES DE LA VENTANA
            if sort_method == "insertion":
                insertion_sort(window_values)

            elif sort_method == "bubble":
                bubble_sort(window_values)

            else:
                raise ValueError(
                    "sort_method debe ser 'insertion' o 'bubble'"
                )

            # OBTENER LA MEDIANA
            median_index = len(window_values) // 2
            median = window_values[median_index]

            # GUARDAR LA MEDIANA EN LA MATRIZ DE SALIDA
            img_out[row, column] = median

    # Regresar imagen filtrada
    return img_out


# ============================================================
# 6. FILTRO CON INSERTION SORT
# ============================================================

start = time.perf_counter()

resultado_insertion = median_filter(
    img_gray,
    7,
    "insertion"
)

end = time.perf_counter()

time_insertion = end - start

print("Tiempo Insertion Sort:", time_insertion, "segundos")


# ============================================================
# 7. FILTRO CON BUBBLE SORT
# ============================================================

start = time.perf_counter()

resultado_bubble = median_filter(
    img_gray,
    7,
    "bubble"
)

end = time.perf_counter()

time_bubble = end - start

print("Tiempo Bubble Sort:", time_bubble, "segundos")


# ============================================================
# 8. VISUALIZACIÓN
# ============================================================

fig, ax = plt.subplots(1, 3, figsize=(15, 5))

# Imagen original
ax[0].imshow(
    img_gray,
    cmap="gray",
    vmin=0,
    vmax=255
)

ax[0].set_title("Original")
ax[0].axis("off")


# Resultado con Insertion Sort
ax[1].imshow(
    resultado_insertion,
    cmap="gray",
    vmin=0,
    vmax=255
)

ax[1].set_title(
    f"Insertion Sort\n{time_insertion:.4f} s"
)

ax[1].axis("off")


# Resultado con Bubble Sort
ax[2].imshow(
    resultado_bubble,
    cmap="gray",
    vmin=0,
    vmax=255
)

ax[2].set_title(
    f"Bubble Sort\n{time_bubble:.4f} s"
)

ax[2].axis("off")


plt.tight_layout()
plt.show()