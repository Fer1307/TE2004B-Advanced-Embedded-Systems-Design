/*
==========================================================================
Actividad:  Biblioteca de transformaciones de imágenes
Materia:    Diseño de Sistemas Embebidos Avanzados
            Módulo 3: Arquitectura de memoria compartida
Profesor:   Emmanuel Torres Ríos
Alumno:     Luis Fernando Salazar Hernández-A01738527

Descripción:
            -Programa de prueba de la biblioteca img_lib.h. Lee la cabecera de la imagen de entrada y aplica las seis transformaciones:
            inversión horizontal y vertical (a color y en escala de grises) y
            desenfoque con un kernel definido (a color y en escala de grises).

==========================================================================
 */

 #include "img_lib.h"

 int main(void)
 {
     char entrada[80] = "sample.bmp";
     int kernel = 15;     // Tamaño del kernel de desenfoque (impar)
 
     read_header(entrada);
 
     // Inversiones: (nombre de salida, imagen de entrada)
     inv_hor_color("inv_hor_color", entrada);
     inv_hor_bn("inv_hor_bn", entrada);
     inv_ver_color("inv_ver_color", entrada);
     inv_ver_bn("inv_ver_bn", entrada);
 
     // Desenfoques: (imagen de entrada, nombre de salida, kernel)
     blur_color(entrada, "blur_color", kernel);
     blur_bn(entrada, "blur_bn", kernel);
 
     return 0;
 }