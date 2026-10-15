import numpy as np
import cv2
import matplotlib.pyplot as plt
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D

# Carga de imagen almacenada localmente
img_bgr = cv2.imread('./coins.jpeg')

# Análisis de la estructura
print(f"Dimensiones de la imagen: {img_bgr.shape}")
print(f"Tipo de dato: {img_bgr.dtype}")  # Fundamental para evitar errores de desbordamiento

# Conversión para visualización correcta
img_rgb = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2RGB)

# Visualización comparativa
fig, ax = plt.subplots(1, 2, figsize=(12, 6))
ax[0].imshow(img_bgr)
ax[0].set_title("Interpretación incorrecta (BGR)")
ax[1].imshow(img_rgb)
ax[1].set_title("Interpretación correcta (RGB)")
plt.show()

img_gray = cv2.cvtColor(img_rgb, cv2.COLOR_BGR2GRAY)
print(f"Dimensiones de la imagen: {img_gray.shape}")
print(f"Tipo de dato: {img_gray.dtype}")  # Fundamental para evitar errores de desbordamiento

plt.imshow(img_gray, cmap='gray')
plt.title("Escala de grises")
plt.show()


kernel_mask = (1/9) * np.array([
    [1, 1, 1],
    [1, 1, 1],
    [1, 1, 1]
])


def image_2D_convolution(img, padding, kernel):
    rowsImg = img.shape[0]
    colsImg = img.shape[1]
    rowsKernel = kernel.shape[0]
    colsKernel = kernel.shape[1]

    print("Image 2D convolution ...")
    print("Input image shape: ", img.shape)
    print("Kernel: ", kernel)

    if padding == True:
        rowsPadding = int((rowsKernel - 1) / 2)
        colsPadding = int((colsKernel - 1) / 2)
    else:
        rowsPadding = 0
        colsPadding = 0

    imgPadded = np.zeros((
        rowsImg + 2 * rowsPadding,
        colsImg + 2 * colsPadding
    ))

    imgPadded[
        rowsPadding : rowsImg + rowsPadding,
        colsPadding : colsImg + colsPadding
    ] = img

    print("Image padding: ", padding)
    print("Image padded shape: ", imgPadded.shape)

    # Contenedor para la imagen de salida
    rowsImgOut = int(rowsImg - rowsKernel + 2 * rowsPadding + 1)
    colsImgOut = int(colsImg - colsKernel + 2 * colsPadding + 1)

    ImgOut = np.zeros((rowsImgOut, colsImgOut))

    # Extraer ventanas o parches de la imagen
    for i in range(rowsImgOut):
        for j in range(colsImgOut):
            imgPatch = imgPadded[
                i : i + rowsKernel,
                j : j + colsKernel
            ]

            # Realizar el operador de ventana particular
            ImgOut[i, j] = (kernel * imgPatch).sum()

    # Retornar la imagen operada
    print("Convolved image shape: ", ImgOut.shape)

    return ImgOut

resultado = image_2D_convolution(img_gray, True, kernel_mask)
plt.imshow((resultado), cmap='gray',  vmin=0, vmax=255)
plt.show()




