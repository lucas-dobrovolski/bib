#include <stdio.h>
#include <stdlib.h>
////////////////////////////////////////////////////////////////////////
double  F(double t, double y){
    return y;
}
////////////////////////////////////////////////////////////////////////
void rk4( double (*ec_dif)(double, double), double *t0,
          double *y0, double dt, double *y_next){
    
    double k1, k2, k3, k4;

    k1 = dt * ec_dif(*t0, *y0);
    k2 = dt * ec_dif(*t0 + dt / 2, *y0 + k1 / 2);
    k3 = dt * ec_dif(*t0 + dt / 2, *y0 + k2 / 2);
    k4 = dt * ec_dif(*t0 + dt, *y0 + k3);

    *y_next = *y0 + (1.0 / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4);        

    *t0 += dt;
}
/////////////////////////////    MAIN     //////////////////////////////////

int main(){     // PARAMETROS
    int N = 5;
    double t0 = 0.0;
    double y0 = 1.0;
    double dt = 0.01;
    double y_next;


    printf("Ingrese el número de pasos: ");
    scanf("%d", &N);
    
    printf("Ingrese el valor inicial de t: ");
    scanf("%lf", &t0);
    
    printf("Ingrese el valor inicial de y: ");
    scanf("%lf", &y0);
    
    printf("Ingrese el paso de tiempo (dt): ");
    scanf("%lf", &dt);
    

    // RESERVO MEMORIA
    double* t_arr = (double*)malloc(N * sizeof(double));
    double* y_arr = (double*)malloc(N * sizeof(double));

    t_arr[0] = t0; // CONDICIONES INICIALES
    y_arr[0] = y0;

    for (int i = 0; i < N; i++){    // CALCULAR CON RK4
        rk4(F, &t0, &y0, dt, &y_next);
        y0 = y_next;
        t_arr[i] = t0;
        y_arr[i] = y_next;
    }

    FILE *file = fopen("resultados.csv", "w");  // ABRIR ARCHIVO
    if (file == NULL) {
        printf("Error al abrir el archivo para escribir.\n");
        free(t_arr);
        free(y_arr);
        return 1; // Salir si no se pudo abrir el archivo
    }

    fprintf(file, "t,y\n"); // ENCABEZADOS
    for (int i = 0; i < N; i++) { // VALORES
        fprintf(file, "%f,%f\n", t_arr[i], y_arr[i]);
    }

    fclose(file); // Cierro el archivo    

    free(t_arr);
    free(y_arr);

    return 0;
}