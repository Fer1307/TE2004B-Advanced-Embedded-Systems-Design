#  Algoritmo y código de primer ejemplo de convolución bidimensional
# Diseño de sistemas embebidos avanzados-Módulo 1
# Profesor: Cesar Torres Huitzil
# Alumno: Luis Fernando Salazar Hernández-A01738527
# Fecha: 22/09/2026


# Algorithm Correlation2D(A, W) #
# #
#Input:  Array A[N][M], Array W[n][m] #
#Output: Array S[N-n+1][M-m+1] #

# for i ← 0 to N - n do #
#     for j ← 0 to M - m do #
#         sum ← 0 #
#
#         for k ← 0 to n - 1 do #
#             for l ← 0 to m - 1 do #
#                 sum ← sum + A[i+k][j+l] * W[k][l] #
#             end for #
#         end for #
#
#         S[i][j] ← sum #
#     end for #
# end for #
#
# return S #





A = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
]

W = [
    [1, 1],
    [1, 1]
]

# Obtencion de las dimensiones de las matrices
N = len(A)
M = len(A[0])

n = len(W)
m = len(W[0])

# Calculo y contruccion de la salida
rows_out = N - n + 1
columns_out = M - m + 1
output = []
for i in range(rows_out):
    fila = [0] * columns_out
    output.append(fila)


for i in range(rows_out):
    for j in range(rows_out):
        sum = 0

        for k in range(n):
            for l in range(m):
                sum += A[i + k][j + l] * W[k][l]
        
        output[i][j] = sum

print(output)

