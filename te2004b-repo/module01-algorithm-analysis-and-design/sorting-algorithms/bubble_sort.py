import time

A = [2, 4 ,3, 7, 9, 3, 5, 9, 12, 15, 3, 6, 18, 6, 25, 12, 5, 8, 22, 15 ]
start = time.perf_counter()

def bubble_sort():
    n = len (A)
    for i in range (0, n-1):
        
        for j in range (n-1, i, -1):

            if A[j] < A[j-1]:
                A[j], A[j-1] = A[j-1], A[j]

end = time.perf_counter()
time = end - start

bubble_sort()
print(A)
print ("Tiempo: ", time )
