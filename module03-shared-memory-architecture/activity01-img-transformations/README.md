# Actividad 1 · Biblioteca de transformaciones de imágenes

Biblioteca en C (`img_lib.h`) que aplica seis transformaciones a imágenes **BMP de 24 bits** y registra cada operación en `output_log.txt`.

| Función | Transformación |
|---|---|
| `inv_hor_color(mask, path)` | Inversión horizontal (espejo) a color |
| `inv_hor_bn(mask, path)` | Inversión horizontal en escala de grises |
| `inv_ver_color(mask, path)` | Inversión vertical a color (el último píxel pasa a ser el primero) |
| `inv_ver_bn(mask, path)` | Inversión vertical en escala de grises |
| `blur_color(input_path, name_output, kernel_size)` | Desenfoque de caja a color, en dos pasadas |
| `blur_bn(input_path, name_output, kernel_size)` | Desenfoque de caja en escala de grises |
| `read_header(path)` | Imprime ancho, alto y bits por píxel |

## Resultados (kernel 15)

| Original | `inv_hor_color` | `inv_ver_color` | `blur_color` |
|:---:|:---:|:---:|:---:|
| <img src="docs/sample.png" width="140"> | <img src="docs/inv_hor_color.png" width="140"> | <img src="docs/inv_ver_color.png" width="140"> | <img src="docs/blur_color.png" width="140"> |
| | **`inv_hor_bn`** | **`inv_ver_bn`** | **`blur_bn`** |
| | <img src="docs/inv_hor_bn.png" width="140"> | <img src="docs/inv_ver_bn.png" width="140"> | <img src="docs/blur_bn.png" width="140"> |

Las imágenes completas están en [`img/`](img/) y la imagen de entrada es [`sample.bmp`](sample.bmp) (858 × 1080 píxeles).

## Consideraciones de implementación

- **Relleno de fila:** en BMP cada fila mide un múltiplo de 4 bytes. Con 858 píxeles de ancho hay 2 bytes de relleno por fila; la biblioteca los calcula con `(ancho*3 + 3) & ~3`, los salta al leer y los escribe en 0, así que funciona con cualquier ancho.
- **Lectura acotada:** los píxeles se leen con ciclos `for` de tamaño `ancho × alto`, sin leer más allá de los datos ni escribir fuera de los arreglos.
- **Índices válidos:** el espejo recorre cada fila de `ancho - 1` a `0`.
- **Escala de grises:** `0.21·R + 0.72·G + 0.07·B`, escrito en los tres canales para conservar el formato de 24 bits.
- **Desenfoque separable:** una pasada horizontal y una vertical (`2·kernel` sumas por píxel en lugar de `kernel²`); en los bordes solo se promedian los vecinos que existen.

## Compilación y ejecución

```bash
mkdir img
gcc main.c -o img_lib
./img_lib        # en Windows: .\img_lib.exe
```

La carpeta `img/` debe existir antes de ejecutar. `output_log.txt` se abre en modo de agregar, así que conviene borrarlo antes de cada corrida.

## Reporte

[`docs/act1_img_transformations.pdf`](docs/act1_img_transformations.pdf): descripción, metodología, resultados y conclusiones de la actividad.
