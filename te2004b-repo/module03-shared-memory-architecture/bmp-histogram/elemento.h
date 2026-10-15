#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void htg(const char *mask)
{
    FILE *image = fopen(mask, "rb");
    if (image == NULL)
    {
        printf("Error al abrir la imagen.\n");
        return;
    }

    int histR[256] = {0}, histG[256] = {0}, histB[256] = {0};
    uint32_t offset;
    int32_t width, height;
    uint16_t bpp;

    // Leer encabezado BMP
    fseek(image, 10, SEEK_SET); fread(&offset, 4, 1, image);
    fseek(image, 18, SEEK_SET); fread(&width, 4, 1, image);
                                fread(&height, 4, 1, image);
    fseek(image, 28, SEEK_SET); fread(&bpp, 2, 1, image);

    if (bpp != 24 && bpp != 32)
    {
        printf("Solo BMP de 24 o 32 bits.\n");
        fclose(image);
        return;
    }

    int bytesPP = bpp / 8;
    int padding = (4 - (width * bytesPP) % 4) % 4;
    unsigned char px[4];

    // Recorrer pixeles (orden BGR)
    fseek(image, offset, SEEK_SET);
    for (int y = 0; y < abs(height); y++)
    {
        for (int x = 0; x < width; x++)
        {
            fread(px, 1, bytesPP, image);
            histB[px[0]]++;
            histG[px[1]]++;
            histR[px[2]]++;
        }
        fseek(image, padding, SEEK_CUR);
    }
    fclose(image);

    // Guardar histograma
    FILE *out = fopen("histograma.csv", "w");
    if (out == NULL)
    {
        printf("Error al crear histograma.csv\n");
        return;
    }
    fprintf(out, "Intensidad,Rojo,Verde,Azul\n");
    for (int i = 0; i < 256; i++)
        fprintf(out, "%d,%d,%d,%d\n", i, histR[i], histG[i], histB[i]);
    fclose(out);

    printf("Histograma generado en histograma.csv\n");
}

#endif