#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
    FILE *image = fopen("sample.bmp", "rb");

    if (image == NULL)
    {
        printf("Error al abrir la imagen.\n");
        return 1;
    }

    // Histogramas RGB
    int histR[256] = {0};
    int histG[256] = {0};
    int histB[256] = {0};

    // Datos importantes del BMP
    uint32_t offset;
    int32_t width;
    int32_t height;
    uint16_t bitsPerPixel;

    // Leer offset donde comienzan los pixeles
    fseek(image, 10, SEEK_SET);
    fread(&offset, sizeof(uint32_t), 1, image);

    // Leer ancho
    fseek(image, 18, SEEK_SET);
    fread(&width, sizeof(int32_t), 1, image);

    // Leer alto
    fseek(image, 22, SEEK_SET);
    fread(&height, sizeof(int32_t), 1, image);

    // Leer bits por pixel
    fseek(image, 28, SEEK_SET);
    fread(&bitsPerPixel, sizeof(uint16_t), 1, image);

    printf("Ancho: %d\n", width);
    printf("Alto: %d\n", height);
    printf("Bits por pixel: %u\n", bitsPerPixel);
    printf("Offset de pixeles: %u\n", offset);

    // Aceptar BMP de 24 o 32 bits
    if (bitsPerPixel != 24 && bitsPerPixel != 32)
    {
        printf("Solo se admiten imagenes BMP de 24 o 32 bits.\n");
        fclose(image);
        return 1;
    }

    int bytesPerPixel = bitsPerPixel / 8;

    // Calcular padding de cada fila
    int rowBytes = width * bytesPerPixel;
    int padding = (4 - (rowBytes % 4)) % 4;

    printf("Bytes por pixel: %d\n", bytesPerPixel);
    printf("Padding por fila: %d bytes\n", padding);

    // Ir al inicio real de los datos de imagen
    fseek(image, offset, SEEK_SET);

    unsigned char r, g, b, a;

    // Recorrer todos los pixeles
    for (int y = 0; y < abs(height); y++)
    {
        for (int x = 0; x < width; x++)
        {
            b = fgetc(image);
            g = fgetc(image);
            r = fgetc(image);

            if (bytesPerPixel == 4)
            {
                a = fgetc(image);

                // Contar solo si el pixel es visible
                if (a > 0)
                {
                    histR[r]++;
                    histG[g]++;
                    histB[b]++;
                }
            }
            else
            {
                // En imágenes de 24 bits no existe alfa
                histR[r]++;
                histG[g]++;
                histB[b]++;
            }
        }

        for (int p = 0; p < padding; p++)
        {
            fgetc(image);
        }
    }

    fclose(image);

    // Verificar cantidad total de pixeles
    long totalR = 0;
    long totalG = 0;
    long totalB = 0;

    for (int i = 0; i < 256; i++)
    {
        totalR += histR[i];
        totalG += histG[i];
        totalB += histB[i];
    }

    long totalEsperado = (long)width * abs(height);

    printf("\nPixeles esperados: %ld\n", totalEsperado);
    printf("Total R: %ld\n", totalR);
    printf("Total G: %ld\n", totalG);
    printf("Total B: %ld\n", totalB);

    // Crear archivo CSV
    FILE *histograma = fopen("histograma.csv", "w");

    if (histograma == NULL)
    {
        printf("Error al crear histograma.csv\n");
        return 1;
    }

    fprintf(histograma, "Intensidad,Rojo,Verde,Azul\n");

    for (int i = 0; i < 256; i++)
    {
        fprintf(histograma,
                "%d,%d,%d,%d\n",
                i,
                histR[i],
                histG[i],
                histB[i]);
    }

    fclose(histograma);

    printf("\nHistograma generado correctamente en histograma.csv\n");

    return 0;
}