#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

    strcpy(pregunta->tipo, tipo);
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
}

// Retorna la pregunta en la posicion n_pregunta del certamen
tPregunta leerPregunta(tCertamen* certamen, int n_pregunta){
    return certamen->preguntas[n_pregunta];
}

// Retorna el numero de respuestas correctas que tiene el certamen
int nCorrectasCertamen(tCertamen certamen){
    int i;
    int n_correctas = 0;
    for (i = 0; i < certamen.n_preguntas; i++){
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
    return false;
}
bool revisarAlternativaMultiple(tPregunta pregunta){
    return false;
}
bool revisarVerdaderoFalso(tPregunta pregunta){
    return false;
}
bool revisarCompletar(tPregunta pregunta){
    return false;
}
