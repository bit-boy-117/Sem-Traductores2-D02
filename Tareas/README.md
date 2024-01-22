# ¿Qué es un analizador léxico?

Un analizador léxico es la primera fase de un compilador o intérprete en el proceso de traducción de un programa fuente escrito en un lenguaje de programación a un código ejecutable. Su función principal es analizar el flujo de caracteres del programa fuente y dividirlo en unidades más pequeñas llamadas **"lexemas"** o **"tokens"**.

## Caracteristicas:

El objetivo del analizador léxico es reconocer y clasificar estos lexemas, que son las unidades más básicas del lenguaje de programación, como:

* palabras clave 
* identificadores 
* operadores 
* constantes  
* símbolos especiales

Cada lexema se representa como un par **"token-valor"**, donde el token es una etiqueta que indica la categoría del lexema y el valor es la cadena de caracteres correspondiente.
 

## Funcion en sistemas más complejos:

El analizador léxico elimina comentarios y espacios en blanco innecesarios, generando una secuencia de tokens que se pasa a la siguiente fase del compilador.

Esta información estructurada facilita el trabajo del analizador sintáctico, que se encarga de verificar la gramática del programa. 

Juntos, el **analizador léxico** y el **analizador sintáctico** contribuyen al análisis y procesamiento del código fuente para crear la representación interna que permitirá generar el código ejecutable.
