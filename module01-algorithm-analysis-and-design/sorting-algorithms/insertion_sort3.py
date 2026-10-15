import random
import time

A = random.randint(1,10)
B = random.randint(1, 100)
C = random.randint(1, 1000)
D = random.randint(1, 10000)

start = time.perf_counter()

def insertion_sort():
    for i in range(1, len (A)):
        key = A[i]
        j = i-1
        while (j >= 0 and A[j]> key):
            A[j+1] = A[j]
            j = j-1
        
        A [j+1] = key


end = time.perf_counter()
time = end - start

def insertion_sort2():
    for i in range(1, len (B)):
        key = B[i]
        j = i-1
        while (j >= 0 and B[j]> key):
            B[j+1] = B[j]
            j = j-1
        
        B [j+1] = key

def insertion_sort3():
    for i in range(1, len (C)):
        key = C[i]
        j = i-1
        while (j >= 0 and C[j]> key):
            C[j+1] = C[j]
            j = j-1
        
        C [j+1] = key

def insertion_sort4():
    for i in range(1, len (D)):
        key = D[i]
        j = i-1
        while (j >= 0 and D[j]> key):
            D[j+1] = D[j]
            j = j-1
        
        D [j+1] = key

insertion_sort()
insertion_sort2()
insertion_sort3()
insertion_sort4()
print (A, B, C, D)
print ("Tiempo: ", time )
