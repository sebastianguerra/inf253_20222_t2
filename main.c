#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "certamen.h"

void ejecutar_certamen(tCertamen* certamen){
    // prueba que la informacion se haya almacenado correctamente en la estructura certamen
    for(int i = 0; i < certamen->n_preguntas; i++){
        tPregunta pregunta = certamen->preguntas[i];
        printf("Pregunta %d: %s\n", i+1, pregunta.tipo);
        if ( strcmp(pregunta.tipo, "AlternativaSimple") == 0 ){
            tEnunciadoAlternativa* enunciado = (tEnunciadoAlternativa*) pregunta.enunciado;
            printf("Enunciado: %s\n", enunciado->enunciado);
            printf("Alternativas: \n");
            for(int j = 0; j < enunciado->n_alternativas; j++){
                printf("%d. %s\n", j+1, enunciado->alternativas[j]);
            }
            printf("Alternativa correcta: %d\n", enunciado->alternativa_correcta);
        }
        if ( strcmp(pregunta.tipo, "AlternativaMultiple") == 0 ){
            tEnunciadoAlternativaMultiple* enunciado = (tEnunciadoAlternativaMultiple*) pregunta.enunciado;
            printf("Enunciado: %s\n", enunciado->enunciado);
            printf("Alternativas: \n");
            for(int j = 0; j < enunciado->n_alternativas; j++){
                printf("%d. %s\n", j+1, enunciado->alternativas[j]);
            }
            printf("Alternativas correctas: \n");
            for(int j = 0; j < enunciado->n_correctas; j++){
                printf("%d. %d\n", j+1, enunciado->alternativa_correcta[j]);
            }
        }
        if ( strcmp(pregunta.tipo, "VerdaderoFalso") == 0 ){
            tEnunciadoVerdaderoFalso* enunciado = (tEnunciadoVerdaderoFalso*) pregunta.enunciado;
            printf("Enunciado: %s\n", enunciado->enunciado);
            printf("Respuesta: %s\n", enunciado->respuesta==1?"Verdadero":"Falso");
        }
        if ( strcmp(pregunta.tipo, "Completar") == 0 ){
            tEnunciadoCompletar* enunciado = (tEnunciadoCompletar*) pregunta.enunciado;
            printf("Enunciado: \n");
            for(int j = 0; j < enunciado->n_textos; j++){
                printf("%s\n", enunciado->textos[j]);
            }
            printf("Respuestas: \n");
            for(int j = 0; j < enunciado->n_textos-1; j++){
                printf("%s\n", enunciado->respuestas[j]);
            }
        }
        printf("\n\n");
    }


}


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

        if (strcmp(tipo, "AlternativaSimple") == 0){
            char enunciado[128];
            fscanf(CERTAMEN_TXT, "%[^\n]\n", enunciado);

            int n_alternativas;
            fscanf(CERTAMEN_TXT, "%d\n", &n_alternativas);

            char **alternativas = (char**) malloc(sizeof(char*) * n_alternativas);
            for (int j = 0; j < n_alternativas; j++){
                char alternativa[128];
                fscanf(CERTAMEN_TXT, "%[^\n]\n", alternativa);
                alternativas[j] = (char*) malloc(sizeof(char) * (strlen(alternativa)+1));
                strcpy(alternativas[j], alternativa);
            }


            int correcta;
            fscanf(CERTAMEN_TXT, "%d", &correcta);

            tEnunciadoAlternativa *enunciadoAlternativa = (tEnunciadoAlternativa*) malloc(sizeof(tEnunciadoAlternativa));
            strcpy(enunciadoAlternativa->enunciado, enunciado);
            enunciadoAlternativa->n_alternativas = n_alternativas;
            enunciadoAlternativa->alternativas = alternativas;
            enunciadoAlternativa->alternativa_correcta = correcta;


            enunciados[i] = (void*) enunciadoAlternativa;
            continue;
        }
        if (strcmp(tipo, "AlternativaMultiple") == 0){
            char enunciado[128];
            fscanf(CERTAMEN_TXT, "%[^\n]\n", enunciado);

            int n_alternativas;
            fscanf(CERTAMEN_TXT, "%d\n", &n_alternativas);

            char **alternativas = (char**) malloc(sizeof(char*) * n_alternativas);
            for (int j = 0; j < n_alternativas; j++){
                char alternativa[128];
                fscanf(CERTAMEN_TXT, "%[^\n]\n", alternativa);
                alternativas[j] = (char*) malloc(sizeof(char) * (strlen(alternativa)+1));
                strcpy(alternativas[j], alternativa);
            }

            int n_correctas;
            fscanf(CERTAMEN_TXT, "%d\n", &n_correctas);

            int *correctas = (int*) malloc(sizeof(int) * n_correctas);
            for (int j = 0; j < n_correctas; j++){
                int correcta;
                fscanf(CERTAMEN_TXT, "%d\n", &correcta);
                correctas[j] = correcta;
            }

            tEnunciadoAlternativaMultiple *enunciadoAlternativaMultiple = (tEnunciadoAlternativaMultiple*) malloc(sizeof(tEnunciadoAlternativaMultiple));
            strcpy(enunciadoAlternativaMultiple->enunciado, enunciado);
            enunciadoAlternativaMultiple->n_alternativas = n_alternativas;
            enunciadoAlternativaMultiple->alternativas = alternativas;
            enunciadoAlternativaMultiple->n_correctas = n_correctas;
            enunciadoAlternativaMultiple->alternativa_correcta = correctas;


            enunciados[i] = (void*) enunciadoAlternativaMultiple;
            continue;
        }
        if (strcmp(tipo, "VerdaderoFalso") == 0){
            char enunciado[128];
            fscanf(CERTAMEN_TXT, "%[^\n]\n", enunciado);

            char correcta;
            fscanf(CERTAMEN_TXT, "%c\n", &correcta);

            tEnunciadoVerdaderoFalso *enunciadoVerdaderoFalso = (tEnunciadoVerdaderoFalso*) malloc(sizeof(tEnunciadoVerdaderoFalso));
            strcpy(enunciadoVerdaderoFalso->enunciado, enunciado);
            enunciadoVerdaderoFalso->respuesta = correcta=='V'?1:0;


            enunciados[i] = (void*) enunciadoVerdaderoFalso;
            continue;
        }
        if (strcmp(tipo, "Completar") == 0){
            int n_textos;
            fscanf(CERTAMEN_TXT, "%d\n", &n_textos);

            char **textos = (char**) malloc(sizeof(char*) * n_textos);
            for (int j = 0; j < n_textos; j++){
                char texto[128];
                fscanf(CERTAMEN_TXT, "%[^\n]\n", texto);
                textos[j] = (char*) malloc(sizeof(char) * (strlen(texto)+1));
                strcpy(textos[j], texto);
            }

            char **respuestas = (char**) malloc(sizeof(char*) * n_textos);
            for (int j = 0; j < n_textos-1; j++){
                char respuesta[128];
                fscanf(CERTAMEN_TXT, "%[^\n]\n", respuesta);
                respuestas[j] = (char*) malloc(sizeof(char) * (strlen(respuesta)+1));
                strcpy(respuestas[j], respuesta);
            }

            tEnunciadoCompletar *enunciadoCompletar = (tEnunciadoCompletar*) malloc(sizeof(tEnunciadoCompletar));
            enunciadoCompletar->n_textos = n_textos;
            enunciadoCompletar->textos = textos;
            enunciadoCompletar->respuestas = respuestas;



            enunciados[i] = (void*) enunciadoCompletar;
            continue;
        }
    }
    fclose(CERTAMEN_TXT);



    tCertamen* certamen = crearCertamen(n);

    for(int i = 0; i < n; i++){
        tPregunta* pregunta;
        if ( strcmp(tipos[i], "AlternativaSimple") == 0 ){
            pregunta = crearPregunta(certamen, tipos[i], enunciados[i], NULL);
        }
        if ( strcmp(tipos[i], "AlternativaMultiple") == 0 ){
            pregunta = crearPregunta(certamen, tipos[i], enunciados[i], NULL);
            
        }
        if ( strcmp(tipos[i], "VerdaderoFalso") == 0 ){
            pregunta = crearPregunta(certamen, tipos[i], enunciados[i], NULL);
        }
        if ( strcmp(tipos[i], "Completar") == 0 ){
            pregunta = crearPregunta(certamen, tipos[i], enunciados[i], NULL);
        }

        asignarPregunta(certamen, i, pregunta);
    }

    ejecutar_certamen(certamen);

    return 0;
}
