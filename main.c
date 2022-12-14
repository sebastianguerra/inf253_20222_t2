#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "certamen.h"


void* leer_enunciado_alternativa_simple(FILE* archivo);
void* leer_enunciado_alternativa_multiple(FILE* archivo);
void* leer_enunciado_verdadero_falso(FILE* archivo);
void* leer_enunciado_completar(FILE* archivo);

void* leer_enunciado(FILE* archivo, char* tipo);


void ejecutar_alternativa_simple(tPregunta* pregunta);
void ejecutar_alternativa_multiple(tPregunta* pregunta);
void ejecutar_verdadero_falso(tPregunta* pregunta);
void ejecutar_completar(tPregunta* pregunta);

void ejecutar_certamen(tCertamen* certamen);


bool revisar_alternativa_simple(void* _enunciado, void* _respuesta);
bool revisar_alternativa_multiple(void* _enunciado, void* _respuesta);
bool revisar_verdadero_falso(void* _enunciado, void* _respuesta);
bool revisar_completar(void* _enunciado, void* _respuesta);


void liberar_certamen(tCertamen* certamen);



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








/*
Lee un enunciado de tipo AlternativaSimple de acuerdo al formato indicado por el pdf

    Parametros:
        CERTAMEN_TXT ( FILE* ): archivo del que se leera el enunciado.
    
    Retorno:
        enunciadoAlternativa ( void* ): estructura que almacena el enunciado.
*/
void* leer_enunciado_alternativa_simple(FILE* CERTAMEN_TXT){
    // linea con string **enunciado**
    char enunciado[128];
    fscanf(CERTAMEN_TXT, "%[^\n]\n", enunciado);

    // linea con el entero **n_alternativas**
    int n_alternativas;
    fscanf(CERTAMEN_TXT, "%d\n", &n_alternativas);

    // **n_alternativas** lineas con un string que corresponde a cada alternativa
    char **alternativas = (char**) malloc(sizeof(char*) * n_alternativas);
    for (int j = 0; j < n_alternativas; j++){
        char alternativa[128]; // longitud de alternativa: 128 dicho en aula
        fscanf(CERTAMEN_TXT, "%[^\n]\n", alternativa);
        alternativas[j] = (char*) malloc(sizeof(char) * (strlen(alternativa)+1));
        strcpy(alternativas[j], alternativa);
    }

    // linea con un entero correspondiente a la alternativa correcta
    int correcta;
    fscanf(CERTAMEN_TXT, "%d", &correcta);


    // Crear estructura del enunciado
    tEnunciadoAlternativa *enunciadoAlternativa;
    enunciadoAlternativa = (tEnunciadoAlternativa*) malloc(sizeof(tEnunciadoAlternativa));

    strcpy(enunciadoAlternativa->enunciado, enunciado);
    enunciadoAlternativa->n_alternativas = n_alternativas;
    enunciadoAlternativa->alternativas = alternativas;
    enunciadoAlternativa->alternativa_correcta = correcta;

    return (void*) enunciadoAlternativa;
}
/*
Lee un enunciado de tipo AlternativaMultiple de acuerdo al formato indicado por el pdf

    Parametros:
        CERTAMEN_TXT ( FILE* ): archivo del que se leera el enunciado.
    
    Retorno:
        enunciadoAlternativaMultiple ( void* ): estructura que almacena el enunciado.
*/
void* leer_enunciado_alternativa_multiple(FILE* CERTAMEN_TXT){
    // linea con string **enunciado**
    char enunciado[128];
    fscanf(CERTAMEN_TXT, "%[^\n]\n", enunciado);

    // linea con el entero **n_alternativas**
    int n_alternativas;
    fscanf(CERTAMEN_TXT, "%d\n", &n_alternativas);

    // **n_alternativas** lineas con un string que corresponde a cada alternativa
    char **alternativas = (char**) malloc(sizeof(char*) * n_alternativas);
    for (int j = 0; j < n_alternativas; j++){
        char alternativa[128];
        fscanf(CERTAMEN_TXT, "%[^\n]\n", alternativa);
        alternativas[j] = (char*) malloc(sizeof(char) * (strlen(alternativa)+1));
        strcpy(alternativas[j], alternativa);
    }

    // linea con entero **n_correctas**
    int n_correctas;
    fscanf(CERTAMEN_TXT, "%d\n", &n_correctas);

    // **n_correctas** lineas con un entero correspondiente a cada alternativa correcta
    int *correctas = (int*) malloc(sizeof(int) * n_correctas);
    for (int j = 0; j < n_correctas; j++){
        int correcta;
        fscanf(CERTAMEN_TXT, "%d\n", &correcta);
        correctas[j] = correcta;
    }


    // Crear estructura del enunciado
    tEnunciadoAlternativaMultiple *enunciadoAlternativaMultiple = (tEnunciadoAlternativaMultiple*) malloc(sizeof(tEnunciadoAlternativaMultiple));
    strcpy(enunciadoAlternativaMultiple->enunciado, enunciado);
    enunciadoAlternativaMultiple->n_alternativas = n_alternativas;
    enunciadoAlternativaMultiple->alternativas = alternativas;
    enunciadoAlternativaMultiple->n_correctas = n_correctas;
    enunciadoAlternativaMultiple->alternativa_correcta = correctas;

    return (void*) enunciadoAlternativaMultiple;
}
/*
Lee un enunciado de tipo VerdaderoFalso de acuerdo al formato indicado por el pdf

    Parametros:
        CERTAMEN_TXT ( FILE* ): archivo del que se leera el enunciado.
    
    Retorno:
        enunciadoVerdaderoFalso ( void* ): estructura que almacena el enunciado.
*/
void* leer_enunciado_verdadero_falso(FILE* CERTAMEN_TXT){
    // linea con string **enunciado**
    char enunciado[128];
    fscanf(CERTAMEN_TXT, "%[^\n]\n", enunciado);

    // linea con 'V' o 'F'
    char correcta;
    fscanf(CERTAMEN_TXT, "%c\n", &correcta);


    // Crear estructura del enunciado
    tEnunciadoVerdaderoFalso *enunciadoVerdaderoFalso = (tEnunciadoVerdaderoFalso*) malloc(sizeof(tEnunciadoVerdaderoFalso));
    strcpy(enunciadoVerdaderoFalso->enunciado, enunciado);
    enunciadoVerdaderoFalso->respuesta = correcta=='V'?1:0;

    return (void*) enunciadoVerdaderoFalso;
}
/*
Lee un enunciado de tipo Completar de acuerdo al formato indicado por el pdf

    Parametros:
        CERTAMEN_TXT ( FILE* ): archivo del que se leera el enunciado.
    
    Retorno:
        enunciadoCompletar ( void* ): estructura que almacena el enunciado.
*/
void* leer_enunciado_completar(FILE* CERTAMEN_TXT){
    // linea con entero **n_textos**
    int n_textos;
    fscanf(CERTAMEN_TXT, "%d\n", &n_textos);

    // **n_textos** lineas con un string que corresponde a una parte del texto que debe ser completado
    char **textos = (char**) malloc(sizeof(char*) * n_textos);
    for (int j = 0; j < n_textos; j++){
        char texto[128];
        fscanf(CERTAMEN_TXT, "%[^\n]\n", texto);
        textos[j] = (char*) malloc(sizeof(char) * (strlen(texto)+1));
        strcpy(textos[j], texto);
    }

    // **n_textos**-1 lineas con un string que corresponde a la respuesta correcta
    char **respuestas = (char**) malloc(sizeof(char*) * n_textos);
    for (int j = 0; j < n_textos-1; j++){
        char respuesta[128];
        fscanf(CERTAMEN_TXT, "%[^\n]\n", respuesta);
        respuestas[j] = (char*) malloc(sizeof(char) * (strlen(respuesta)+1));
        strcpy(respuestas[j], respuesta);
    }


    // Crear estructura del enunciado
    tEnunciadoCompletar *enunciadoCompletar = (tEnunciadoCompletar*) malloc(sizeof(tEnunciadoCompletar));
    enunciadoCompletar->n_textos = n_textos;
    enunciadoCompletar->textos = textos;
    enunciadoCompletar->respuestas = respuestas;

    return (void*) enunciadoCompletar;
}
/*
Delega la tarea de leer un enunciado a su funcion correspondiente de acuerdo al tipo indicado

    Parametros:
        archivo ( FILE* ): archivo del que se leera el enunciado.
        tipo ( char* ): tipo de acuerdo al cual se intentara leer el enunciado
    
    Retorno:
        ( void* ): puntero a la estructura que almacena el enunciado.
*/
void* leer_enunciado(FILE* archivo, char* tipo){
    if (strcmp(tipo, "AlternativaSimple") == 0)
        return (void*) leer_enunciado_alternativa_simple(archivo);

    if (strcmp(tipo, "AlternativaMultiple") == 0)
        return (void*) leer_enunciado_alternativa_multiple(archivo);

    if (strcmp(tipo, "VerdaderoFalso") == 0)
        return (void*) leer_enunciado_verdadero_falso(archivo);

    if (strcmp(tipo, "Completar") == 0)
        return (void*) leer_enunciado_completar(archivo);

    return NULL;
}

/*
Muestra por pantalla el enunciado, las posibles respuestas y guarda la respuesta del usuario

    Parametros:
        pregunta ( tPregunta* ): pregunta de la que sacara los datos y donde almacenara la respuesta.
    
    Retorno:
        ( void )
*/
void ejecutar_alternativa_simple(tPregunta* pregunta){
    tEnunciadoAlternativa* enunciado;
    enunciado = (typeof(enunciado)) pregunta->enunciado;

    printf("%s\n", enunciado->enunciado);
    printf("Alternativas: \n");
    for(int j = 0; j < enunciado->n_alternativas; j++){
        printf("\t%c) %s\n", j+97, enunciado->alternativas[j]);
    }
    printf("[a-%c]: ", enunciado->n_alternativas+97 - 1);

    int* respuesta = (int*) malloc(sizeof(int));
    char r;
    scanf("%c", &r);
    *respuesta = r - 97 + 1;
    pregunta->respuesta = respuesta;
}
/*
Muestra por pantalla el enunciado, las posibles respuestas y guarda la respuesta del usuario

    Parametros:
        pregunta ( tPregunta* ): pregunta de la que sacara los datos y donde almacenara la respuesta.
    
    Retorno:
        ( void )
*/
void ejecutar_alternativa_multiple(tPregunta* pregunta){
    tEnunciadoAlternativaMultiple* enunciado = (tEnunciadoAlternativaMultiple*) pregunta->enunciado;

    printf("Enunciado: %s\n", enunciado->enunciado);
    printf("Alternativas: \n");
    for(int j = 0; j < enunciado->n_alternativas; j++){
        printf("\t%c) %s\n", j+97, enunciado->alternativas[j]);
    }
    printf("Ingresa las alternativas que consideres correctas (en una linea, ordenadas y separadas por un espacio):\n");

    getc(stdin); // limpia un salto de linea
    int* respuesta = (int*) malloc(sizeof(int) * enunciado->n_alternativas);
    bool leyendo = true;
    for(int j = 0; j < enunciado->n_alternativas; j++){
        if (leyendo){
            char r;
            scanf("%c", &r);
            if (r == ' '){
                j--;
                continue;
            }
            if (r == '\n'){
                leyendo = false;
                j--;
                continue;
            }
            respuesta[j] = r - 97 + 1;
        } else {
            respuesta[j] = -1;
        }
    }
    pregunta->respuesta = respuesta;
}
/*
Muestra por pantalla el enunciado, las posibles respuestas y guarda la respuesta del usuario

    Parametros:
        pregunta ( tPregunta* ): pregunta de la que sacara los datos y donde almacenara la respuesta.
    
    Retorno:
        ( void )
*/
void ejecutar_verdadero_falso(tPregunta* pregunta){
    tEnunciadoVerdaderoFalso* enunciado = (tEnunciadoVerdaderoFalso*) pregunta->enunciado;

    printf("%s\n", enunciado->enunciado);
    printf("[V/F]: ");

    bool* respuesta = (bool*) malloc(sizeof(bool));
    char c;
    scanf(" %c", &c);
    *respuesta = c == 'V' || c == 'v';
    pregunta->respuesta = respuesta;
}
/*
Muestra por pantalla el enunciado, las posibles respuestas y guarda la respuesta del usuario

    Parametros:
        pregunta ( tPregunta* ): pregunta de la que sacara los datos y donde almacenara la respuesta.
    
    Retorno:
        ( void )
*/
void ejecutar_completar(tPregunta* pregunta){
    tEnunciadoCompletar* enunciado = (tEnunciadoCompletar*) pregunta->enunciado;

    printf("%s", enunciado->textos[0]);
    for(int j = 1; j < enunciado->n_textos; j++){
        printf(" __%d__ %s", j, enunciado->textos[j]);
    }
    printf("\n");

    char** respuesta = (char**) malloc(sizeof(char*) * (enunciado->n_textos-1));
    for(int j = 0; j < enunciado->n_textos-1; j++){
        printf("\t%d: ", j+1);

        respuesta[j] = (char*) malloc(sizeof(char) * 100);
        scanf("%[^\n]", respuesta[j]);
        getc(stdin);

        printf("%s", enunciado->textos[0]);
        for(int k = 1; k < enunciado->n_textos; k++){
            if (k-1 <= j)
                printf(" %s %s", respuesta[k-1], enunciado->textos[k]);
            else
                printf(" __%d__ %s", k, enunciado->textos[k]);
        }
        printf("\n");
    }
    pregunta->respuesta = respuesta;
}

/*
Muestra por pantalla el enunciado, las posibles respuestas y guarda la respuesta del usuario por cada pregunta.

    Parametros:
        certamen ( tCertamen* ): certamen de donde sacara las preguntas a mostrar.
    
    Retorno:
        ( void )
*/
void ejecutar_certamen(tCertamen* certamen){
    for(int i = 0; i < largoCertamen(*certamen); i++){
        tPregunta* pregunta = leerPregunta(certamen, i);

        printf("\n");
        printf("%d\n", i+1);
        printf("%s\n", pregunta->tipo);

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

        bool correcta = pregunta->revisar(pregunta->enunciado, pregunta->respuesta);
        if (correcta){
            printf("\nCorrecto!\n");
        } else {
            printf("\nIncorrecto!\n");
        }

        printf("\n\n");
    }
}



/*
Revisa la respuesta de una pregunta de alternativa simple

    Parametros:
        _enunciado ( void* ): puntero al enunciado de donde se sacara la respuesta correcta
        _respuesta ( void* ): puntero a la respuesta del usuario
    
    Retorno:
        ( bool ): respuestas coindiden
*/
bool revisar_alternativa_simple(void* _enunciado, void* _respuesta){
    tEnunciadoAlternativa* enunciado = (tEnunciadoAlternativa*) _enunciado;
    int* respuesta = (int*) _respuesta;

    return enunciado->alternativa_correcta == *respuesta;
}
/*
Revisa la respuesta de una pregunta de alternativa multiple

    Parametros:
        _enunciado ( void* ): puntero al enunciado de donde se sacara la respuesta correcta
        _respuesta ( void* ): puntero a la respuesta del usuario
    
    Retorno:
        ( bool ): respuestas coindiden
*/
bool revisar_alternativa_multiple(void* _enunciado, void* _respuesta){
    tEnunciadoAlternativaMultiple* enunciado = (tEnunciadoAlternativaMultiple*) _enunciado;
    int* respuesta = (int*) _respuesta;

    for(int i = 0; i < enunciado->n_alternativas; i++){
        if (i < enunciado->n_correctas){
            if (respuesta[i] != enunciado->alternativa_correcta[i])
                return false;
        } else {
            if (respuesta[i] != -1)
                return false;
        }
    }
    return true;
}
/*
Revisa la respuesta de una pregunta verdadero y falso

    Parametros:
        _enunciado ( void* ): puntero al enunciado de donde se sacara la respuesta correcta
        _respuesta ( void* ): puntero a la respuesta del usuario
    
    Retorno:
        ( bool ): respuestas coindiden
*/
bool revisar_verdadero_falso(void* _enunciado, void* _respuesta){
    tEnunciadoVerdaderoFalso* enunciado = (tEnunciadoVerdaderoFalso*) _enunciado;
    bool* respuesta = (bool*) _respuesta;

    return enunciado->respuesta == *respuesta;
}
/*
Revisa la respuesta de una pregunta tipo completar

    Parametros:
        _enunciado ( void* ): puntero al enunciado de donde se sacara la respuesta correcta
        _respuesta ( void* ): puntero a la respuesta del usuario
    
    Retorno:
        ( bool ): respuestas coindiden
*/
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



/*
Libera toda la memoria solicitada durante la ejecucion de un certamen

    Parametros:
        certamen ( tCertamen* ): puntero al certamen a eliminar
    
    Retorno:
        ( void )
*/
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