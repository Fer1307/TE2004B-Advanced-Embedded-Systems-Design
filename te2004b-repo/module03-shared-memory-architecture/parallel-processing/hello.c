# include <stdio.h>
# include <omp.h>
# define NUM_THREADS 2000 //we make from 1 hilo to many in this case to 20

int main(void)
{
    omp_set_num_threads(NUM_THREADS);
# pragma omp parallel
{
    int id = omp_get_thread_num();
    printf("Procesadores(%d)", id);
    printf("Multiples(%d)", id);
    printf("en accion(%d)\n", id);
}
    return 0;
}
