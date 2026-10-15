import time


A = [2, 4 ,3, 7, 9, 3, 5, 9, 12, 15, 3, 6, 18, 6, 25, 12, 5, 8, 22, 15 ]

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

insertion_sort()
print (A)
print ("Tiempo: ", time )