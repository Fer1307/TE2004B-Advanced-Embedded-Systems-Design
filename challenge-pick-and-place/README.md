# Reto · *Pick and place* con visión computacional

Sistema de *pick and place* con el manipulador **UFactory Lite 6**, una **Raspberry Pi**, **MATLAB**, **ThingSpeak** y visión computacional.

| Componente | Función |
|---|---|
| Raspberry Pi | Procesamiento local, ejecución de los algoritmos y control del manipulador en tiempo real. |
| MATLAB | Diseño y simulación de los algoritmos de visión computacional y de las trayectorias cinemáticas. |
| ThingSpeak | Analítica IoT en la nube para monitorear y registrar el conteo de ciclos. |

## Plan de entregables

| Entregable | Descripción | Estado |
|---|---|---|
| 1 | Propuesta de solución | En desarrollo |
| 2 | Solución mejorada y validación del algoritmo | Pendiente |
| 3 | Demostración del sistema completo en el Día de la Ingeniería | Pendiente |

## Avances

Primeros pasos con la Raspberry Pi desde MATLAB, en [`matlab/`](matlab/):

| Archivo | Descripción |
|---|---|
| `basico.m` | Conexión a la Raspberry Pi con `raspi()` y control del LED integrado desde MATLAB. |
| `blinkLED.m` | Parpadeo del LED como función lista para generar código C con MATLAB Coder y ejecutarse de forma independiente en la Raspberry Pi (`deploy`). |
| `edgeDetectionrpi.m` | Detección de bordes en tiempo real con la cámara de la Raspberry Pi: convolución con kernels Sobel horizontal y vertical, magnitud del gradiente y umbral. |

Antes de ejecutar, sustituye `<IP_RASPBERRY_PI>`, `<usuario>` y `<contrasena>` por los datos de tu Raspberry Pi.

```matlab
board = targetHardware('Raspberry Pi (64bit)');
deploy(board, 'edgeDetectionrpi')
```
