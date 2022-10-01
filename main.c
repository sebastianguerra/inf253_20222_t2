#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "certamen.h"




void ejecutar_alternativa_simple(tPregunta* pregunta){
    tEnunciadoAlternativa* enunciado = (tEnunciadoAlternativa*) pregunta->enunciado;
    printf("Enunciado: %s\n", enunciado->enunciado);
    printf("Alternativas: \n");
    for(int j = 0; j < enunciado->n_alternativas; j++){
        printf("\t%d) %s\n", j+1, enunciado->alternativas[j]);
    }
    // printf("Alternativa correcta: %d\n", enunciado->alternativa_correcta);
    printf("Ingrese su respuesta: ");
    int* respuesta = (int*) malloc(sizeof(int));
    scanf("%d", respuesta);
    pregunta->respuesta = respuesta;
}
void ejecutar_alternativa_multiple(tPregunta* pregunta){
    tEnunciadoAlternativaMultiple* enunciado = (tEnunciadoAlternativaMultiple*) pregunta->enunciado;
    printf("Enunciado: %s\n", enunciado->enunciado);
    printf("Alternativas: \n");
    for(int j = 0; j < enunciado->n_alternativas; j++){
        printf("%d. %s\n", j+1, enunciado->alternativas[j]);
    }
//     printf("Alternativas correctas: \n");
//     for(int j = 0; j < enunciado->n_correctas; j++){
//         printf("%d. %d\n", j+1, enunciado->alternativa_correcta[j]);
//     }
    printf("Ingrese sus respuestas: ");
    int* respuesta = (int*) malloc(sizeof(int) * enunciado->n_alternativas);
    bool leyendo = true;
    for(int j = 0; j < enunciado->n_alternativas; j++){
        if (leyendo){
            scanf("%d", &respuesta[j]);
            if(getc(stdin) == '\n')
                leyendo = false;
        } else {
            respuesta[j] = -1;
        }
    }
    pregunta->respuesta = respuesta;
}
void ejecutar_verdadero_falso(tPregunta* pregunta){
    tEnunciadoVerdaderoFalso* enunciado = (tEnunciadoVerdaderoFalso*) pregunta->enunciado;
    printf("Enunciado: %s\n", enunciado->enunciado);
    // printf("Respuesta: %s\n", enunciado->respuesta?"Verdadero":"Falso");
    printf("Ingrese su respuesta [V/F]: ");
    bool* respuesta = (bool*) malloc(sizeof(bool));
    char c;
    scanf(" %c", &c);
    *respuesta = c == 'V' || c == 'v';
    pregunta->respuesta = respuesta;
}
void ejecutar_completar(tPregunta* pregunta){
    tEnunciadoCompletar* enunciado = (tEnunciadoCompletar*) pregunta->enunciado;
    printf("Enunciado: \n");
    for(int j = 0; j < enunciado->n_textos; j++){
        printf("%s\n", enunciado->textos[j]);
    }
    // printf("Respuestas: \n");
    // for(int j = 0; j < enunciado->n_textos-1; j++){
    //     printf("%s\n", enunciado->respuestas[j]);
    // }
    printf("Ingrese sus respuestas: \n");
    char** respuesta = (char**) malloc(sizeof(char*) * (enunciado->n_textos-1));
    for(int j = 0; j < enunciado->n_textos-1; j++){
        respuesta[j] = (char*) malloc(sizeof(char) * 100);
        scanf("%[^\n]", respuesta[j]);
        getc(stdin);
    }
    pregunta->respuesta = respuesta;
}




void ejecutar_certamen(tCertamen* certamen){
    for(int i = 0; i < largoCertamen(*certamen); i++){
        tPregunta* pregunta = leerPregunta(certamen, i);

        printf("\n");
        printf("Pregunta %d: %s\n", i+1, pregunta->tipo);

        if ( strcmp(pregunta->tipo, "AlternativaSimple"  ) == 0 ){
            ejecutar_alternativa_simple(pregunta);
        } else

        if ( strcmp(pregunta->tipo, "AlternativaMultiple") == 0 ){
            ejecutar_alternativa_multiple(pregunta);
        } else

        if ( strcmp(pregunta->tipo, "VerdaderoFalso"     ) == 0 ){
            ejecutar_verdadero_falso(pregunta);
        }else

        if ( strcmp(pregunta->tipo, "Completar"          ) == 0 ){
            ejecutar_completar(pregunta);
        }

        printf("\n");
    }
}



bool revisar_alternativa_simple(void* _enunciado, void* _respuesta){
    tEnunciadoAlternativa* enunciado = (tEnunciadoAlternativa*) _enunciado;
    int* respuesta = (int*) _respuesta;
    return enunciado->alternativa_correcta == *respuesta;
}
bool revisar_alternativa_multiple(void* _enunciado, void* _respuesta){
    tEnunciadoAlternativaMultiple* enunciado = (tEnunciadoAlternativaMultiple*) _enunciado;
    int* respuesta = (int*) _respuesta;
    for(int i = 0; i < enunciado->n_correctas; i++){
        if (enunciado->alternativa_correcta[i] != respuesta[i]){
            return false;
        }
    }
    return true;
}
bool revisar_verdadero_falso(void* _enunciado, void* _respuesta){
    tEnunciadoVerdaderoFalso* enunciado = (tEnunciadoVerdaderoFalso*) _enunciado;
    bool* respuesta = (bool*) _respuesta;
    return enunciado->respuesta == *respuesta;
}
bool revisar_completar(void* _enunciado, void* _respuesta){
    tEnunciadoCompletar* enunciado = (tEnunciadoCompletar*) _enunciado;
    char** respuesta = (char**) _respuesta;
    for(int i = 0; i < enunciado->n_textos-1; i++){
        if (strcmp(enunciado->respuestas[i], respuesta[i]) != 0){
            return false;
        }
    }
    return true;
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

    printf("Puntaje: %d/%d\n", nCorrectasCertamen(*certamen), largoCertamen(*certamen));

    for(int i = 0; i < largoCertamen(*certamen); i++){
        tPregunta* pregunta = leerPregunta(certamen, i);
        printf("\n\nPregunta %d: %s:\n", i+1, pregunta->tipo);

        if ( strcmp(pregunta->tipo, "AlternativaSimple"   ) == 0 ){
            tEnunciadoAlternativa* enunciado = (tEnunciadoAlternativa*) pregunta->enunciado;
            int* respuesta = (int*) pregunta->respuesta;

            printf("Enunciado: %s\n", enunciado->enunciado);
            printf("Alternativa elegida:\n");
            printf("%d\n", *respuesta);
        } else

        if ( strcmp(pregunta->tipo, "AlternativaMultiple" ) == 0 ){
            tEnunciadoAlternativaMultiple* enunciado = (tEnunciadoAlternativaMultiple*) pregunta->enunciado;
            int* respuesta = (int*) pregunta->respuesta;

            printf("Enunciado: %s\n", enunciado->enunciado);
            printf("Alternativas elegidas:\n");
            for(int j = 0; respuesta[j] != -1; j++){
                printf("%d\n", respuesta[j]);
            }
        } else

        if ( strcmp(pregunta->tipo, "VerdaderoFalso"      ) == 0 ){
            tEnunciadoVerdaderoFalso* enunciado = (tEnunciadoVerdaderoFalso*) pregunta->enunciado;
            bool* respuesta = (bool*) pregunta->respuesta;

            printf("Enunciado: %s\n", enunciado->enunciado);
            printf("Respuesta: %s\n", *respuesta?"Verdadero":"Falso");
        } else

        if ( strcmp(pregunta->tipo, "Completar"           ) == 0 ){
            tEnunciadoCompletar* enunciado = (tEnunciadoCompletar*) pregunta->enunciado;
            char** respuesta = (char**) pregunta->respuesta;

            printf("Enunciado: ");
            for(int j = 0; j < enunciado->n_textos; j++){
                printf(" %s ", enunciado->textos[j]);
                if (j < enunciado->n_textos-1){
                    printf("__%s__", respuesta[j]);
                }
            }
            printf("\n");
        }
    }

    
    // Libera toda la memoria
    for (int i = 0; i < largoCertamen(*certamen); i++){
        tPregunta* pregunta = leerPregunta(certamen, i);
        if ( strcmp(pregunta->tipo, "AlternativaSimple"   ) == 0 ){
            tEnunciadoAlternativa* enunciado = (tEnunciadoAlternativa*) pregunta->enunciado;
            for(int j = 0; j < enunciado->n_alternativas; j++){
                free(enunciado->alternativas[j]);
            }
            free(enunciado->alternativas);


            free(pregunta->respuesta);


            free(enunciado);
        } else

        if ( strcmp(pregunta->tipo, "AlternativaMultiple" ) == 0 ){
            tEnunciadoAlternativaMultiple* enunciado = (tEnunciadoAlternativaMultiple*) pregunta->enunciado;
            free(enunciado->alternativa_correcta);
            for(int j = 0; j < enunciado->n_alternativas; j++){
                free(enunciado->alternativas[j]);
            }
            free(enunciado->alternativas);


            free(pregunta->respuesta);


            free(enunciado);
        } else

        if ( strcmp(pregunta->tipo, "VerdaderoFalso"      ) == 0 ){
            tEnunciadoVerdaderoFalso* enunciado = (tEnunciadoVerdaderoFalso*) pregunta->enunciado;


            free(pregunta->respuesta);


            free(enunciado);
        } else

        if ( strcmp(pregunta->tipo, "Completar"           ) == 0 ){
            tEnunciadoCompletar* enunciado = (tEnunciadoCompletar*) pregunta->enunciado;
            for(int j = 0; j < enunciado->n_textos-1; j++){
                free(enunciado->respuestas[j]);
            }
            free(enunciado->respuestas);
            for(int j = 0; j < enunciado->n_textos; j++){
                free(enunciado->textos[j]);
            }
            free(enunciado->textos);

            char** respuesta = (char**) pregunta->respuesta;


            for(int j = 0; j < enunciado->n_textos-1; j++){
                free(respuesta[j]);
            }
            free(respuesta);


            free(enunciado);
        }
    }
    free(certamen->preguntas);
    free(certamen);
    
    fclose(stdin);
    fclose(stdout);
    

    return 0;
}
