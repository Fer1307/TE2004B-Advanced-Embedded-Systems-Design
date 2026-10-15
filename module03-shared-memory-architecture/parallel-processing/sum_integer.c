# include <stdio.h>
# include <time.h>



int main(void)
{
    clock_t start = clock();


    long N = 100000000;
    double delta_x = 1.0 /N;
    double sum = 0.0;
    for (long i=0; i<N; i++)
    {
        double x = (i + 0.5) * delta_x;
        sum += 4.0 / (1.0 + x  * x);
    }
    double pi = delta_x * sum;

    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;


    printf("Aproximación de pi: %.15f \n", pi);
    printf("Tiempo de ejecucion: %.9f segundos\n", time_taken);

    return 0;
}