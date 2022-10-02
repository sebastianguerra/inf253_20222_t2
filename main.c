#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "certamen.h"



int main() {
    FILE *CERTAMEN_TXT = fopen("certamen.txt", "r");
    if (CERTAMEN_TXT == NULL) {
        printf("Error opening file 'certamen.txt'");
        return 1;
    }

    int n;
    fscanf(CERTAMEN_TXT, "%d\n", &n);

    void* enunciados[n];
    char tipos[n][64];
    for (int i = 0; i < n; i++) {
        char tipo[64];
        fscanf(CERTAMEN_TXT, "%s\n", tipo);
        strcpy(tipos[i], tipo);

        enunciados[i] = leer_enunciado(CERTAMEN_TXT, tipo);
    }
    fclose(CERTAMEN_TXT);



    tCertamen* certamen = crearCertamen(n);

    for(int i = 0; i < n; i++){
        tPregunta* pregunta;
        if ( strcmp(tipos[i], "AlternativaSimple"   ) == 0 ){
            pregunta = crearPregunta(certamen, tipos[i], enunciados[i], revisar_alternativa_simple);
        } else

        if ( strcmp(tipos[i], "AlternativaMultiple" ) == 0 ){
            pregunta = crearPregunta(certamen, tipos[i], enunciados[i], revisar_alternativa_multiple);    
        } else

        if ( strcmp(tipos[i], "VerdaderoFalso"      ) == 0 ){
            pregunta = crearPregunta(certamen, tipos[i], enunciados[i], revisar_verdadero_falso);
        } else

        if ( strcmp(tipos[i], "Completar"           ) == 0 ){
            pregunta = crearPregunta(certamen, tipos[i], enunciados[i], revisar_completar);
        }

        asignarPregunta(certamen, i, pregunta);
    }

    ejecutar_certamen(certamen);

    printf("\nPuntaje: %d/%d\n", nCorrectasCertamen(*certamen), largoCertamen(*certamen));


    
    // Libera toda la memoria
    liberar_certamen(certamen);
    
    
    fclose(stdin);
    fclose(stdout);
    

    return 0;
}
