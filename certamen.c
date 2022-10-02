#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "certamen.h"


// Crea un nuevo certamen vacio
tCertamen* crearCertamen(int n_preguntas){
    tCertamen* certamen = (tCertamen*) malloc(sizeof(tCertamen));

    certamen->n_preguntas = n_preguntas;
    certamen->preguntas = (tPregunta*) malloc(sizeof(tPregunta) * n_preguntas);

    return certamen;
}

// Crea una pregunta con el enunciado y funcion de revision dados
tPregunta* crearPregunta(   tCertamen* certamen,
                            char* tipo,
                            void* enunciado,
                            bool (*revisar)(void*, void*)){
    tPregunta* pregunta = (tPregunta*) malloc(sizeof(tPregunta));

    strcpy((char*)pregunta->tipo, tipo);
    pregunta->enunciado = enunciado;
    pregunta->respuesta = NULL;
    pregunta->revisar = revisar;

    return pregunta;
}

// Asigna la pregunta a la posicion n_pregunta del certamen
void asignarPregunta (  tCertamen* certamen,
                        int n_pregunta,
                        tPregunta* pregunta){
    certamen->preguntas[n_pregunta] = *pregunta;
    free(pregunta);
}

// Retorna la pregunta en la posicion n_pregunta del certamen
tPregunta* leerPregunta(tCertamen* certamen, int n_pregunta){
    return &certamen->preguntas[n_pregunta];
}

// Retorna el numero de respuestas correctas que tiene el certamen
int nCorrectasCertamen(tCertamen certamen){
    int n_correctas = 0;
    for (int i = 0; i < certamen.n_preguntas; i++){
        if (certamen.preguntas[i].revisar(certamen.preguntas[i].enunciado, certamen.preguntas[i].respuesta)){
            n_correctas++;
        }
    }
    return n_correctas;
}

// Retorna el numero de preguntas en un certamen
int largoCertamen(tCertamen certamen){
    return certamen.n_preguntas;
}

// Revisa si la respuesta a la pregunta es correcta
bool revisarAlternativaSimple(tPregunta pregunta){
    return pregunta.revisar(pregunta.enunciado, pregunta.respuesta);
}
bool revisarAlternativaMultiple(tPregunta pregunta){
    return pregunta.revisar(pregunta.enunciado, pregunta.respuesta);
}
bool revisarVerdaderoFalso(tPregunta pregunta){
    return pregunta.revisar(pregunta.enunciado, pregunta.respuesta);
}
bool revisarCompletar(tPregunta pregunta){
    return pregunta.revisar(pregunta.enunciado, pregunta.respuesta);
}












void* leer_enunciado_alternativa_simple(FILE* CERTAMEN_TXT){
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


    return (void*) enunciadoAlternativa;
}

void* leer_enunciado_alternativa_multiple(FILE* CERTAMEN_TXT){
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


    return (void*) enunciadoAlternativaMultiple;
}

void* leer_enunciado_verdadero_falso(FILE* CERTAMEN_TXT){
    char enunciado[128];
    fscanf(CERTAMEN_TXT, "%[^\n]\n", enunciado);

    char correcta;
    fscanf(CERTAMEN_TXT, "%c\n", &correcta);

    tEnunciadoVerdaderoFalso *enunciadoVerdaderoFalso = (tEnunciadoVerdaderoFalso*) malloc(sizeof(tEnunciadoVerdaderoFalso));
    strcpy(enunciadoVerdaderoFalso->enunciado, enunciado);
    enunciadoVerdaderoFalso->respuesta = correcta=='V'?1:0;


    return (void*) enunciadoVerdaderoFalso;
}

void* leer_enunciado_completar(FILE* CERTAMEN_TXT){
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



    return (void*) enunciadoCompletar;
}

void* leer_enunciado(FILE* archivo, char* tipo){
    if (strcmp(tipo, "AlternativaSimple") == 0)
        return leer_enunciado_alternativa_simple(archivo);

    if (strcmp(tipo, "AlternativaMultiple") == 0)
        return leer_enunciado_alternativa_multiple(archivo);

    if (strcmp(tipo, "VerdaderoFalso") == 0)
        return leer_enunciado_verdadero_falso(archivo);

    if (strcmp(tipo, "Completar") == 0)
        return leer_enunciado_completar(archivo);

    return NULL;
}


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

void liberar_certamen(tCertamen* certamen){
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
}