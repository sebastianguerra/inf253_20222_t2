#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "certamen.h"


/*
Crea un nuevo certamen vacio

    Parametros:
        n_preguntas ( int ): Cantidad de preguntas del certamen

    Retorno:
        certamen ( tCertamen* ): Estructura creada

*/
tCertamen* crearCertamen(int n_preguntas){
    tCertamen* certamen = (tCertamen*) malloc(sizeof(tCertamen));

    certamen->n_preguntas = n_preguntas;
    certamen->preguntas = (tPregunta*) malloc(sizeof(tPregunta) * n_preguntas);

    return certamen;
}

/*
Crea una pregunta con el enunciado y funcion de revision dados

    Parametros:
        certamen ( tCertamen* ): Certamen.
        tipo ( char* ): tipo de pregunta.
        enunciado ( void* ): Estructura con la informacion del enunciado de la pregunta.
        revisar ( bool (*revisar)(void*, void*) ): Funcion que revisa la respuesta.

    Retorno:
        pregunta ( tPregunta* ): Pregunta creada
*/
*/
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

/*
Asigna la pregunta a la posicion n_pregunta del certamen

    Parametros:
        certamen ( tCertamen* ): Puntero al certamen al que se le asignara la pregunta.
        n_pregunta ( int ): Indice al que se asignara la pregunta.
        pregunta ( tPregunta* ): Pregunta a asignar.

    Retorno:
        void
*/
*/
void asignarPregunta (  tCertamen* certamen,
                        int n_pregunta,
                        tPregunta* pregunta){
    certamen->preguntas[n_pregunta] = *pregunta;
    free(pregunta);
}

/*
Retorna la pregunta en la posicion n_pregunta del certamen

    Parametros:
        certamen ( tCertamen* ): Puntero al certamen del que se obtendra la pregunta.
        n_pregunta ( int ): Indice de la pregunta a obtener.

    Retorno:
        pregunta ( tPregunta* ): Puntero a la pregunta en la posicion n_pregunta del certamen.
*/
tPregunta* leerPregunta(tCertamen* certamen, int n_pregunta){
    return &certamen->preguntas[n_pregunta];
}

/*
Retorna el numero de respuestas correctas que tiene el certamen

    Parametros:
        certamen ( tCertamen* ): Puntero al certamen del que se obtendra la cantidad de respuestas correctas.

    Retorno:
        n_correctas ( int ): Cantidad de respuestas correctas del certamen.
*/
int nCorrectasCertamen(tCertamen certamen){
    int n_correctas = 0;
    for (int i = 0; i < certamen.n_preguntas; i++){
        if (certamen.preguntas[i].revisar(certamen.preguntas[i].enunciado, certamen.preguntas[i].respuesta)){
            n_correctas++;
        }
    }
    return n_correctas;
}

/*
Retorna el numero de preguntas en un certamen
    
    Parametros:
        certamen ( tCertamen* ): Puntero al certamen del que se obtendra la cantidad de preguntas.

    Retorno:
        n_preguntas ( int ): Cantidad de preguntas del certamen.
*/
int largoCertamen(tCertamen certamen){
    return certamen.n_preguntas;
}

/*
Revisa si la respuesta a la pregunta es correcta
    
    Parametros:
        pregunta ( tPregunta ): Pregunta a revisar.

    Retorno:
        ( bool ): True si la respuesta es correcta, False en caso contrario.
*/
bool revisarAlternativaSimple(tPregunta pregunta){
    return pregunta.revisar(pregunta.enunciado, pregunta.respuesta);
}
/*
Revisa si la respuesta a la pregunta es correcta
    
    Parametros:
        pregunta ( tPregunta ): Pregunta a revisar.

    Retorno:
        ( bool ): True si la respuesta es correcta, False en caso contrario.
*/
bool revisarAlternativaMultiple(tPregunta pregunta){
    return pregunta.revisar(pregunta.enunciado, pregunta.respuesta);
}
/*
Revisa si la respuesta a la pregunta es correcta
    
    Parametros:
        pregunta ( tPregunta ): Pregunta a revisar.

    Retorno:
        ( bool ): True si la respuesta es correcta, False en caso contrario.
*/
bool revisarVerdaderoFalso(tPregunta pregunta){
    return pregunta.revisar(pregunta.enunciado, pregunta.respuesta);
}
/*
Revisa si la respuesta a la pregunta es correcta
    
    Parametros:
        pregunta ( tPregunta ): Pregunta a revisar.

    Retorno:
        ( bool ): True si la respuesta es correcta, False en caso contrario.
*/
bool revisarCompletar(tPregunta pregunta){
    return pregunta.revisar(pregunta.enunciado, pregunta.respuesta);
}
