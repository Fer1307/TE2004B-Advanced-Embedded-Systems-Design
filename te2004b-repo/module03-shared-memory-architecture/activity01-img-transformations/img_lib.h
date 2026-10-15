/*
 * ==========================================================================
  * Actividad:  Biblioteca de transformaciones de imágenes
 *  Materia:    Diseño de Sistemas Embebidos Avanzados
 *              Módulo 3: Arquitectura de memoria compartida
 *  Profesor:   Emmanuel Torres Ríos
 *  Alumno:     Luis Fernando Salazar Hernández
 *  Matrícula:  A01738527
 *
 *  Descripción:
 *    Biblioteca para imágenes BMP de 24 bits que realiza las siguientes
 *    transformaciones:
 *      - inv_hor_color : inversión horizontal a color
 *      - inv_hor_bn    : inversión horizontal en escala de grises
 *      - inv_ver_color : inversión vertical a color
 *      - inv_ver_bn    : inversión vertical en escala de grises
 *      - blur_color    : desenfoque a color con un kernel definido
 *      - blur_bn       : desenfoque en escala de grises con un kernel definido
 *
 *    Cada imagen resultante se guarda en ./img/<nombre>.bmp y cada función
 *    agrega su registro de localidades leídas y escritas en output_log.txt.
 * ==========================================================================
 */

#ifndef IMG_LIB_H
#define IMG_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Lee la cabecera de un BMP e imprime su ancho, alto y bits por pixel
extern void read_header(char path[80]){

    FILE *image;
    image = fopen(path,"rb");
    if (!image) {
        printf("Error abriendo %s\n", path);
        return;
    }

    unsigned char xx[54];
    for(int i=0; i<54; i++) xx[i] = fgetc(image);
    fclose(image);

    long ancho = (long)xx[21]*16777216+(long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    long alto = (long)xx[25]*16777216+(long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];
    long bpp = (long)xx[29]*256+(long)xx[28];

    printf("Ancho: %ld  Alto: %ld  Bits por pixel: %ld\n", ancho, alto, bpp);
}

// Invierte horizontalmente (espejo) un BMP de 24 bits conservando el color
extern void inv_hor_color(char mask[10], char path[80]){

    FILE *image, *outputImage;
    char add_char[80] = "./img/";
    strcat(add_char, mask);
    strcat(add_char, ".bmp");
    printf("%s\n", add_char);
    image = fopen(path,"rb");          //Original Image
    outputImage = fopen(add_char,"wb");

    if (!image || !outputImage) {
        printf("Error abriendo archivos.\n");
        return;
    }

    long ancho, alto;
    unsigned char xx[54];
    for(int i=0; i<54; i++) {
      xx[i] = fgetc(image);
      fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
    }
    ancho = (long)xx[21]*16777216+(long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[25]*16777216+(long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];
    int padding = ((ancho * 3 + 3) & (~3)) - ancho * 3;   //Bytes de relleno por fila

    unsigned char* arr_in_b = (unsigned char*)malloc(ancho*alto*sizeof(unsigned char));
    unsigned char* arr_in_g = (unsigned char*)malloc(ancho*alto*sizeof(unsigned char));
    unsigned char* arr_in_r = (unsigned char*)malloc(ancho*alto*sizeof(unsigned char));

    // Lectura de pixeles
    long j = 0;
    for (int i = 0; i < alto; i++) {
        for (int x = 0; x < ancho; x++) {
            arr_in_b[j] = fgetc(image);
            arr_in_g[j] = fgetc(image);
            arr_in_r[j] = fgetc(image);
            j++;
        }
        for (int p = 0; p < padding; p++) fgetc(image);   //Salta el relleno
    }

    // Escribir pixeles invertidos
    for (int i = 0; i < alto; i++) {
        for (int y = ancho - 1; y >= 0; y--) {
            long index = (i * ancho) + y;
            fputc(arr_in_b[index], outputImage);
            fputc(arr_in_g[index], outputImage);
            fputc(arr_in_r[index], outputImage);
        }
        for (int p = 0; p < padding; p++) fputc(0, outputImage);
    }

    // Escritura en archivo de registro
    FILE *outputLog = fopen("output_log.txt", "a");
    if (outputLog == NULL) {
        fprintf(stderr, "Error: No se pudo crear o abrir el archivo de registro.\n");
        fclose(image);
        fclose(outputImage);
        return;
    }
    printf("inversion de imagen horizontal a colores\n");

    fprintf(outputLog, "Función: inv_hor_color, con %s\n", path);
    fprintf(outputLog, "Localidades totales leídas: %ld\n", ancho * alto);
    fprintf(outputLog, "Localidades totales escritas: %ld\n", ancho * alto);
    fprintf(outputLog, "-------------------------------------\n");
    fclose(outputLog);

    free(arr_in_b);
    free(arr_in_g);
    free(arr_in_r);
    fclose(image);
    fclose(outputImage);
}

// Convierte un BMP de 24 bits a escala de grises y lo invierte horizontalmente (espejo)
extern void inv_hor_bn(char mask[10], char path[80]){

    FILE *image, *outputImage;
    char add_char[80] = "./img/";
    strcat(add_char, mask);
    strcat(add_char, ".bmp");
    printf("%s\n", add_char);
    image = fopen(path,"rb");          //Original Image
    outputImage = fopen(add_char,"wb");

    if (!image || !outputImage) {
        printf("Error abriendo archivos.\n");
        return;
    }

    long ancho, alto;
    unsigned char r, g, b;               //Pixel
    unsigned char xx[54];
    for(int i=0; i<54; i++) {
      xx[i] = fgetc(image);
      fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
    }
    ancho = (long)xx[21]*16777216+(long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[25]*16777216+(long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];
    int padding = ((ancho * 3 + 3) & (~3)) - ancho * 3;   //Bytes de relleno por fila

    unsigned char* arr_gris = (unsigned char*)malloc(ancho*alto*sizeof(unsigned char));

    // Lectura de pixeles y conversion a grises
    long j = 0;
    for (int i = 0; i < alto; i++) {
        for (int x = 0; x < ancho; x++) {
            b = fgetc(image);
            g = fgetc(image);
            r = fgetc(image);
            arr_gris[j] = 0.21*r+0.72*g+0.07*b;
            j++;
        }
        for (int p = 0; p < padding; p++) fgetc(image);   //Salta el relleno
    }

    // Escribir pixeles invertidos
    for (int i = 0; i < alto; i++) {
        for (int y = ancho - 1; y >= 0; y--) {
            unsigned char pixel = arr_gris[(i * ancho) + y];
            fputc(pixel, outputImage);
            fputc(pixel, outputImage);
            fputc(pixel, outputImage);
        }
        for (int p = 0; p < padding; p++) fputc(0, outputImage);
    }

    // Escritura en archivo de registro
    FILE *outputLog = fopen("output_log.txt", "a");
    if (outputLog == NULL) {
        fprintf(stderr, "Error: No se pudo crear o abrir el archivo de registro.\n");
        fclose(image);
        fclose(outputImage);
        return;
    }
    printf("inversion de imagen horizontal a escala de grises\n");

    fprintf(outputLog, "Función: inv_hor_bn, con %s\n", path);
    fprintf(outputLog, "Localidades totales leídas: %ld\n", ancho * alto);
    fprintf(outputLog, "Localidades totales escritas: %ld\n", ancho * alto);
    fprintf(outputLog, "-------------------------------------\n");
    fclose(outputLog);

    free(arr_gris);
    fclose(image);
    fclose(outputImage);
}

// Invierte verticalmente un BMP de 24 bits conservando el color (el ultimo pixel de la imagen pasa a ser el primero)
extern void inv_ver_color(char mask[10], char path[80]){

    FILE *image, *outputImage;
    char add_char[80] = "./img/";
    strcat(add_char, mask);
    strcat(add_char, ".bmp");
    printf("%s\n", add_char);
    image = fopen(path,"rb");          //Original Image
    outputImage = fopen(add_char,"wb");

    if (!image || !outputImage) {
        printf("Error abriendo archivos.\n");
        return;
    }

    long ancho, alto;
    unsigned char xx[54];
    for(int i=0; i<54; i++) {
      xx[i] = fgetc(image);
      fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
    }
    ancho = (long)xx[21]*16777216+(long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[25]*16777216+(long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];
    int padding = ((ancho * 3 + 3) & (~3)) - ancho * 3;   //Bytes de relleno por fila

    unsigned char* arr_in_b = (unsigned char*)malloc(ancho*alto*sizeof(unsigned char));
    unsigned char* arr_in_g = (unsigned char*)malloc(ancho*alto*sizeof(unsigned char));
    unsigned char* arr_in_r = (unsigned char*)malloc(ancho*alto*sizeof(unsigned char));

    // Lectura de pixeles
    long j = 0;
    for (int i = 0; i < alto; i++) {
        for (int x = 0; x < ancho; x++) {
            arr_in_b[j] = fgetc(image);
            arr_in_g[j] = fgetc(image);
            arr_in_r[j] = fgetc(image);
            j++;
        }
        for (int p = 0; p < padding; p++) fgetc(image);   //Salta el relleno
    }

    // Escribir pixeles del ultimo al primero
    long index = ancho * alto - 1;
    for (int i = 0; i < alto; i++) {
        for (int y = 0; y < ancho; y++) {
            fputc(arr_in_b[index], outputImage);
            fputc(arr_in_g[index], outputImage);
            fputc(arr_in_r[index], outputImage);
            index--;
        }
        for (int p = 0; p < padding; p++) fputc(0, outputImage);
    }

    // Escritura en archivo de registro
    FILE *outputLog = fopen("output_log.txt", "a");
    if (outputLog == NULL) {
        fprintf(stderr, "Error: No se pudo crear o abrir el archivo de registro.\n");
        fclose(image);
        fclose(outputImage);
        return;
    }
    printf("inversion de imagen vertical a colores\n");

    fprintf(outputLog, "Función: inv_ver_color, con %s\n", path);
    fprintf(outputLog, "Localidades totales leídas: %ld\n", ancho * alto);
    fprintf(outputLog, "Localidades totales escritas: %ld\n", ancho * alto);
    fprintf(outputLog, "-------------------------------------\n");
    fclose(outputLog);

    free(arr_in_b);
    free(arr_in_g);
    free(arr_in_r);
    fclose(image);
    fclose(outputImage);
}

// Convierte un BMP de 24 bits a escala de grises y lo invierte verticalmente (el ultimo pixel de la imagen pasa a ser el primero)
extern void inv_ver_bn(char mask[10], char path[80]){

    FILE *image, *outputImage;
    char add_char[80] = "./img/";
    strcat(add_char, mask);
    strcat(add_char, ".bmp");
    printf("%s\n", add_char);
    image = fopen(path,"rb");          //Original Image
    outputImage = fopen(add_char,"wb");

    if (!image || !outputImage) {
        printf("Error abriendo archivos.\n");
        return;
    }

    long ancho, alto;
    unsigned char r, g, b;               //Pixel
    unsigned char xx[54];
    for(int i=0; i<54; i++) {
      xx[i] = fgetc(image);
      fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
    }
    ancho = (long)xx[21]*16777216+(long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[25]*16777216+(long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];
    int padding = ((ancho * 3 + 3) & (~3)) - ancho * 3;   //Bytes de relleno por fila

    unsigned char* arr_gris = (unsigned char*)malloc(ancho*alto*sizeof(unsigned char));

    // Lectura de pixeles y conversion a grises
    long j = 0;
    for (int i = 0; i < alto; i++) {
        for (int x = 0; x < ancho; x++) {
            b = fgetc(image);
            g = fgetc(image);
            r = fgetc(image);
            arr_gris[j] = 0.21*r+0.72*g+0.07*b;
            j++;
        }
        for (int p = 0; p < padding; p++) fgetc(image);   //Salta el relleno
    }

    // Escribir pixeles del ultimo al primero
    long index = ancho * alto - 1;
    for (int i = 0; i < alto; i++) {
        for (int y = 0; y < ancho; y++) {
            unsigned char pixel = arr_gris[index];
            fputc(pixel, outputImage);
            fputc(pixel, outputImage);
            fputc(pixel, outputImage);
            index--;
        }
        for (int p = 0; p < padding; p++) fputc(0, outputImage);
    }

    // Escritura en archivo de registro
    FILE *outputLog = fopen("output_log.txt", "a");
    if (outputLog == NULL) {
        fprintf(stderr, "Error: No se pudo crear o abrir el archivo de registro.\n");
        fclose(image);
        fclose(outputImage);
        return;
    }
    printf("inversion de imagen vertical a escala de grises\n");

    fprintf(outputLog, "Función: inv_ver_bn, con %s\n", path);
    fprintf(outputLog, "Localidades totales leídas: %ld\n", ancho * alto);
    fprintf(outputLog, "Localidades totales escritas: %ld\n", ancho * alto);
    fprintf(outputLog, "-------------------------------------\n");
    fclose(outputLog);

    free(arr_gris);
    fclose(image);
    fclose(outputImage);
}

// Desenfoca un BMP de 24 bits a color promediando cada pixel con sus vecinos (kernel_size impar: 3, 5, 7, ...)
extern void blur_color(const char* input_path, const char* name_output, int kernel_size) {
    FILE *image, *outputImage;
    char output_path[100] = "./img/";
    strcat(output_path, name_output);
    strcat(output_path, ".bmp");
    printf("%s\n", output_path);
    image = fopen(input_path, "rb");
    outputImage = fopen(output_path, "wb");

    if (!image || !outputImage) {
        printf("Error abriendo archivos.\n");
        return;
    }

    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, image);
    fwrite(header, sizeof(unsigned char), 54, outputImage);

    int width = *(int*)&header[18];
    int height = *(int*)&header[22];
    int row_padded = (width * 3 + 3) & (~3);

    unsigned char** input_rows = (unsigned char**)malloc(height * sizeof(unsigned char*));
    unsigned char** output_rows = (unsigned char**)malloc(height * sizeof(unsigned char*));
    unsigned char** temp_rows = (unsigned char**)malloc(height * sizeof(unsigned char*));

    for (int i = 0; i < height; i++) {
        input_rows[i] = (unsigned char*)malloc(row_padded);
        output_rows[i] = (unsigned char*)malloc(row_padded);
        temp_rows[i] = (unsigned char*)malloc(row_padded);
        fread(input_rows[i], sizeof(unsigned char), row_padded, image);
    }

    int k = kernel_size / 2;

    // Paso intermedio: desenfoque horizontal
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int sumB = 0, sumG = 0, sumR = 0, count = 0;

            for (int dx = -k; dx <= k; dx++) {
                int nx = x + dx;
                if (nx >= 0 && nx < width) {
                    int idx = nx * 3;
                    sumB += input_rows[y][idx + 0];
                    sumG += input_rows[y][idx + 1];
                    sumR += input_rows[y][idx + 2];
                    count++;
                }
            }

            int index = x * 3;
            temp_rows[y][index + 0] = sumB / count;
            temp_rows[y][index + 1] = sumG / count;
            temp_rows[y][index + 2] = sumR / count;
        }

        // Copiar padding sin modificar
        for (int p = width * 3; p < row_padded; p++) {
            temp_rows[y][p] = input_rows[y][p];
        }
    }

    // Paso final: desenfoque vertical
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int sumB = 0, sumG = 0, sumR = 0, count = 0;

            for (int dy = -k; dy <= k; dy++) {
                int ny = y + dy;
                if (ny >= 0 && ny < height) {
                    int idx = x * 3;
                    sumB += temp_rows[ny][idx + 0];
                    sumG += temp_rows[ny][idx + 1];
                    sumR += temp_rows[ny][idx + 2];
                    count++;
                }
            }

            int index = x * 3;
            output_rows[y][index + 0] = sumB / count;
            output_rows[y][index + 1] = sumG / count;
            output_rows[y][index + 2] = sumR / count;
        }

        // Copiar padding sin modificar
        for (int p = width * 3; p < row_padded; p++) {
            output_rows[y][p] = temp_rows[y][p];
        }
    }

    // Escritura final
    for (int i = 0; i < height; i++) {
        fwrite(output_rows[i], sizeof(unsigned char), row_padded, outputImage);
        free(input_rows[i]);
        free(temp_rows[i]);
        free(output_rows[i]);
    }

    // Escritura en archivo de registro
    FILE *outputLog = fopen("output_log.txt", "a");
    if (outputLog == NULL) {
        fprintf(stderr, "Error: No se pudo crear o abrir el archivo de registro.\n");
        fclose(image);
        fclose(outputImage);
        return;
    }
    printf("Desenfoque de imagen a colores\n");

    fprintf(outputLog, "Función: blur_color, con %s\n", input_path);
    fprintf(outputLog, "Localidades totales leídas: %d\n", width * height);
    fprintf(outputLog, "Localidades totales escritas: %d\n", width * height);
    fprintf(outputLog, "-------------------------------------\n");
    fclose(outputLog);

    free(input_rows);
    free(temp_rows);
    free(output_rows);
    fclose(image);
    fclose(outputImage);
}

// Convierte un BMP de 24 bits a escala de grises y lo desenfoca promediando cada pixel con sus vecinos (kernel_size impar: 3, 5, 7, ...)
extern void blur_bn(const char* input_path, const char* name_output, int kernel_size) {
    FILE *image, *outputImage;
    char output_path[100] = "./img/";
    strcat(output_path, name_output);
    strcat(output_path, ".bmp");
    printf("%s\n", output_path);
    image = fopen(input_path, "rb");
    outputImage = fopen(output_path, "wb");

    if (!image || !outputImage) {
        printf("Error abriendo archivos.\n");
        return;
    }

    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, image);
    fwrite(header, sizeof(unsigned char), 54, outputImage);

    int width = *(int*)&header[18];
    int height = *(int*)&header[22];
    int row_padded = (width * 3 + 3) & (~3);

    unsigned char** input_rows = (unsigned char**)malloc(height * sizeof(unsigned char*));
    unsigned char** output_rows = (unsigned char**)malloc(height * sizeof(unsigned char*));
    unsigned char** temp_rows = (unsigned char**)malloc(height * sizeof(unsigned char*));

    for (int i = 0; i < height; i++) {
        input_rows[i] = (unsigned char*)malloc(row_padded);
        output_rows[i] = (unsigned char*)malloc(row_padded);
        temp_rows[i] = (unsigned char*)malloc(row_padded);
        fread(input_rows[i], sizeof(unsigned char), row_padded, image);

        // Conversion de la fila a escala de grises
        for (int x = 0; x < width; x++) {
            int idx = x * 3;
            unsigned char pixel = 0.21*input_rows[i][idx + 2]+0.72*input_rows[i][idx + 1]+0.07*input_rows[i][idx + 0];
            input_rows[i][idx + 0] = pixel;
            input_rows[i][idx + 1] = pixel;
            input_rows[i][idx + 2] = pixel;
        }
    }

    int k = kernel_size / 2;

    // Paso intermedio: desenfoque horizontal
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int sum = 0, count = 0;

            for (int dx = -k; dx <= k; dx++) {
                int nx = x + dx;
                if (nx >= 0 && nx < width) {
                    sum += input_rows[y][nx * 3];
                    count++;
                }
            }

            int index = x * 3;
            temp_rows[y][index + 0] = sum / count;
            temp_rows[y][index + 1] = sum / count;
            temp_rows[y][index + 2] = sum / count;
        }

        // Copiar padding sin modificar
        for (int p = width * 3; p < row_padded; p++) {
            temp_rows[y][p] = input_rows[y][p];
        }
    }

    // Paso final: desenfoque vertical
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int sum = 0, count = 0;

            for (int dy = -k; dy <= k; dy++) {
                int ny = y + dy;
                if (ny >= 0 && ny < height) {
                    sum += temp_rows[ny][x * 3];
                    count++;
                }
            }

            int index = x * 3;
            output_rows[y][index + 0] = sum / count;
            output_rows[y][index + 1] = sum / count;
            output_rows[y][index + 2] = sum / count;
        }

        // Copiar padding sin modificar
        for (int p = width * 3; p < row_padded; p++) {
            output_rows[y][p] = temp_rows[y][p];
        }
    }

    // Escritura final
    for (int i = 0; i < height; i++) {
        fwrite(output_rows[i], sizeof(unsigned char), row_padded, outputImage);
        free(input_rows[i]);
        free(temp_rows[i]);
        free(output_rows[i]);
    }

    // Escritura en archivo de registro
    FILE *outputLog = fopen("output_log.txt", "a");
    if (outputLog == NULL) {
        fprintf(stderr, "Error: No se pudo crear o abrir el archivo de registro.\n");
        fclose(image);
        fclose(outputImage);
        return;
    }
    printf("Desenfoque de imagen a escala de grises\n");

    fprintf(outputLog, "Función: blur_bn, con %s\n", input_path);
    fprintf(outputLog, "Localidades totales leídas: %d\n", width * height);
    fprintf(outputLog, "Localidades totales escritas: %d\n", width * height);
    fprintf(outputLog, "-------------------------------------\n");
    fclose(outputLog);

    free(input_rows);
    free(temp_rows);
    free(output_rows);
    fclose(image);
    fclose(outputImage);
}

#endif