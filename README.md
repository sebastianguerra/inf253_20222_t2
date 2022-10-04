Nombre: Sebastian Guerra Espinoza  
Rol: 202173563-1

# Instrucciones de uso

Ejecutar

`$ make run`

en la raiz del proyecto teniendo el archivo "certamen.txt" a la misma altura.

## Formato de respuesta

Por cada pregunta se indicara el numero de la pregunta y el tipo de la pregunta.

Existen 4 tipos de preguntas:

### AlternativaSimple

Para este tipo de pregunta se mostrara el enunciado y las alternativas disponibles.

La entrada debera ser una letra de las opciones.


### AlternativaMultiple

Para este tipo de pregunta se mostrara el enunciado y las alternativas disponibles.

La entrada deben ser las alternativas que el usuario considere correctas. Todas en una sola linea, ordenadas y separadas por un espacio.


### VerdaderoFalso

Para este tipo de pregunta solo se mostrara el enunciado de la pregunta.

La entrada debe ser una letra V o F (pueden ser en mayuscula o minuscula).

### Completar

Para este tipo de pregunta se mostrara el texto completo con los espacios en donde falta completar enumerados.

El usuario debe ingresar el texto correspondiente al indice indicado.

El texto se ira actualizando con la respuesta que vaya dando el usuario.



# Detalles de la implementacion


Para probar la memoria liberada tuve que usar un script de gdb porque no pude hacer funcionar Valgrind en Manjaro:(















