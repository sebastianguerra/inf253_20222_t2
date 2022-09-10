#ifndef CERTAMEN_H
#define CERTAMEN_H

typedef struct {
  char enunciado[128];
  int n_alternativas;
  char** alternativas;
  int alternativa_correcta;
} tEnunciadoAlternativa;

typedef struct {
  char enunciado[128];
  int n_alternativas;
  char** alternativas;
  int n_correctas;
  int* alternativa_correcta;
} tEnunciadoAlternativaMultiple;

typedef struct {
  char enunciado[128];
  bool respuesta;
} tEnunciadoVerdaderoFalso;

typedef struct {
  int n_textos;
  char** textos;
  char** respuestas;
} tEnunciadoCompletar;

typedef struct {
  char tipo[64];
  void* enunciado;
  void* respuesta;
  bool (*revisar)(void*, void*);
} tPregunta;

typedef struct {
  int n_preguntas;
  tPregunta* preguntas;
} tCertamen;

// Crea un nuevo certamen vacio
tCertamen* crearCertamen(int n_preguntas);

// Crea una pregunta con el enunciado y funcion de revision dados
tPregunta* crearPregunta(
  tCertamen* certamen,
  char* tipo,
  void* enuncuado,
  bool revisar(void*, void*));

// Asigna la pregunta a la posicion n_pregunta del certamen
void asignarPregunta(
  tCertamen* certamen,
  int n_pregunta,
  tPregunta* pregunta);

// Retorna la pregunta en la posicion n_pregunta del certamen
tPregunta leerPregunta(tCertamen* certamen, int n_pregunta);

// Retorna el numero de respuestas correctas que tiene el certamen
int nCorrectasCertamen(tCeramen certamen);

// Retorna el numero de preguntas en un certamen
int largoCertamen(tCertamen certamen);

// Revisa si la respuesta a la pregunta es correcta
bool revisarAlternativaSimple(tPregunta pregunta);
bool revisarAlternativaMultiple(tPregunta pregunta);
bool revisarVerdaderoFalso(tPregunta pregunta);
bool revisarCompletar(tPregunta pregunta);

#endif
