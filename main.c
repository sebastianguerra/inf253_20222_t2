#include <stdio.h>
#include <string.h>

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
    char* tipos[n];
    for (int i = 0; i < n; i++) {
        printf("\n");
        char tipo[64];
        fscanf(CERTAMEN_TXT, "%s\n", tipo);
        printf("intento: %d, tipo: %s\n", i, tipo);

        if (strcmp(tipo, "AlternativaSimple") == 0){
            printf("Es AlternativaSimple en la posicion %d\n", i);
            char enunciado[128];
            fscanf(CERTAMEN_TXT, "%[^\n]\n", enunciado);
            printf("Enunciado: %s\n", enunciado);

            int n_alternativas;
            fscanf(CERTAMEN_TXT, "%d\n", &n_alternativas);
            printf("n_alternativas: %d\n", n_alternativas);

            char **alternativas = (char**) malloc(sizeof(char*) * n_alternativas);
            for (int j = 0; j < n_alternativas; j++){
                char alternativa[128];
                fscanf(CERTAMEN_TXT, "%[^\n]\n", &alternativa);
                alternativas[j] = (char*) malloc(sizeof(char) * (strlen(alternativa)+1));
                strcpy(alternativas[j], alternativa);
            }
            for(int j = 0; j < n_alternativas; j++){
                printf("alternativa %d: %s\n", j, alternativas[j]);
            }

            int correcta;
            fscanf(CERTAMEN_TXT, "%d", &correcta);
            printf("correcta: %d\n", correcta);

            tEnunciadoAlternativa *enunciadoAlternativa = (tEnunciadoAlternativa*) malloc(sizeof(tEnunciadoAlternativa));
            strcpy(enunciadoAlternativa->enunciado, enunciado);
            enunciadoAlternativa->n_alternativas = n_alternativas;
            enunciadoAlternativa->alternativas = alternativas;
            enunciadoAlternativa->alternativa_correcta = correcta;

            printf("Probando estructura:\n");
            printf("enunciado: %s\n", enunciadoAlternativa->enunciado);
            printf("n_alternativas: %d\n", enunciadoAlternativa->n_alternativas);
            for(int j = 0; j < n_alternativas; j++){
                printf("alternativa %d: %s\n", j, enunciadoAlternativa->alternativas[j]);
            }
            printf("correcta: %d\n", enunciadoAlternativa->alternativa_correcta);

            enunciados[i] = (void*) enunciadoAlternativa;
            continue;
        }
        if (strcmp(tipo, "AlternativaMultiple") == 0){
            printf("Es AlternativaMultiple en la posicion %d\n", i);

            char enunciado[128];
            fscanf(CERTAMEN_TXT, "%[^\n]\n", enunciado);
            printf("Enunciado: %s\n", enunciado);

            int n_alternativas;
            fscanf(CERTAMEN_TXT, "%d\n", &n_alternativas);
            printf("n_alternativas: %d\n", n_alternativas);

            char **alternativas = (char**) malloc(sizeof(char*) * n_alternativas);
            for (int j = 0; j < n_alternativas; j++){
                char alternativa[128];
                fscanf(CERTAMEN_TXT, "%[^\n]\n", &alternativa);
                alternativas[j] = (char*) malloc(sizeof(char) * (strlen(alternativa)+1));
                strcpy(alternativas[j], alternativa);
            }
            for(int j = 0; j < n_alternativas; j++){
                printf("alternativa %d: %s\n", j, alternativas[j]);
            }

            int n_correctas;
            fscanf(CERTAMEN_TXT, "%d\n", &n_correctas);
            printf("n_correctas: %d\n", n_correctas);

            int *correctas = (int*) malloc(sizeof(int) * n_correctas);
            for (int j = 0; j < n_correctas; j++){
                int correcta;
                fscanf(CERTAMEN_TXT, "%d\n", &correcta);
                correctas[j] = correcta;
            }
            for(int j = 0; j < n_correctas; j++){
                printf("correcta %d: %d\n", j, correctas[j]);
            }

            tEnunciadoAlternativaMultiple *enunciadoAlternativaMultiple = (tEnunciadoAlternativaMultiple*) malloc(sizeof(tEnunciadoAlternativaMultiple));
            strcpy(enunciadoAlternativaMultiple->enunciado, enunciado);
            enunciadoAlternativaMultiple->n_alternativas = n_alternativas;
            enunciadoAlternativaMultiple->alternativas = alternativas;
            enunciadoAlternativaMultiple->n_correctas = n_correctas;
            enunciadoAlternativaMultiple->alternativa_correcta = correctas;

            printf("Probando estructura:\n");
            printf("enunciado: %s\n", enunciadoAlternativaMultiple->enunciado);
            printf("n_alternativas: %d\n", enunciadoAlternativaMultiple->n_alternativas);
            for(int j = 0; j < n_alternativas; j++){
                printf("alternativa %d: %s\n", j, enunciadoAlternativaMultiple->alternativas[j]);
            }
            printf("n_correctas: %d\n", enunciadoAlternativaMultiple->n_correctas);
            for(int j = 0; j < n_correctas; j++){
                printf("correcta %d: %d\n", j, enunciadoAlternativaMultiple->alternativa_correcta[j]);
            }

            enunciados[i] = (void*) enunciadoAlternativaMultiple;
            continue;
        }
        if (strcmp(tipo, "VerdaderoFalso") == 0){
            printf("Es VerdaderoFalso en la posicion %d\n", i);

            char enunciado[128];
            fscanf(CERTAMEN_TXT, "%[^\n]\n", enunciado);
            printf("Enunciado: %s\n", enunciado);

            char correcta;
            fscanf(CERTAMEN_TXT, "%c\n", &correcta);
            printf("correcta: %c\n", correcta);

            tEnunciadoVerdaderoFalso *enunciadoVerdaderoFalso = (tEnunciadoVerdaderoFalso*) malloc(sizeof(tEnunciadoVerdaderoFalso));
            strcpy(enunciadoVerdaderoFalso->enunciado, enunciado);
            enunciadoVerdaderoFalso->respuesta = correcta=='V'?1:0;

            printf("Probando estructura:\n");
            printf("enunciado: %s\n", enunciadoVerdaderoFalso->enunciado);
            printf("correcta: %d\n", enunciadoVerdaderoFalso->respuesta);

            enunciados[i] = (void*) enunciadoVerdaderoFalso;
            continue;
        }
        if (strcmp(tipo, "Completar") == 0){
            printf("Es Completar en la posicion %d\n", i);

            int n_textos;
            fscanf(CERTAMEN_TXT, "%d\n", &n_textos);
            printf("n_textos: %d\n", n_textos);

            char **textos = (char**) malloc(sizeof(char*) * n_textos);
            for (int j = 0; j < n_textos; j++){
                char texto[128];
                fscanf(CERTAMEN_TXT, "%[^\n]\n", &texto);
                textos[j] = (char*) malloc(sizeof(char) * (strlen(texto)+1));
                strcpy(textos[j], texto);
            }
            for(int j = 0; j < n_textos; j++){
                printf("texto %d: %s\n", j, textos[j]);
            }

            char **respuestas = (char**) malloc(sizeof(char*) * n_textos);
            for (int j = 0; j < n_textos-1; j++){
                char respuesta[128];
                fscanf(CERTAMEN_TXT, "%[^\n]\n", &respuesta);
                respuestas[j] = (char*) malloc(sizeof(char) * (strlen(respuesta)+1));
                strcpy(respuestas[j], respuesta);
            }
            for(int j = 0; j < n_textos-1; j++){
                printf("respuesta %d: %s\n", j, respuestas[j]);
            }

            tEnunciadoCompletar *enunciadoCompletar = (tEnunciadoCompletar*) malloc(sizeof(tEnunciadoCompletar));
            enunciadoCompletar->n_textos = n_textos;
            enunciadoCompletar->textos = textos;
            enunciadoCompletar->respuestas = respuestas;

            printf("Probando estructura:\n");
            printf("n_textos: %d\n", enunciadoCompletar->n_textos);
            for(int j = 0; j < n_textos; j++){
                printf("texto %d: %s\n", j, enunciadoCompletar->textos[j]);
            }
            for(int j = 0; j < n_textos-1; j++){
                printf("respuesta %d: %s\n", j, enunciadoCompletar->respuestas[j]);
            }

            enunciados[i] = (void*) enunciadoCompletar;
            continue;
        }
    }
    fclose(CERTAMEN_TXT);



    // muestra los enunciados por pantalla
    for (int i = 0; i < n; i++) {
        void* enunciado = enunciados[i];
        char tipo[64];
        strcpy(tipo, ((char*) enunciado));
        printf("%s\n", tipo);
    }

    return 0;
}
