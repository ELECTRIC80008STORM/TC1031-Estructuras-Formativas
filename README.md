# TC1031_Estructuras_Formativas

Estas actividades son para que practiques la implementación de algoritmos y estructuras de datos. Se basan en las actividades y programas desarrollados en clase, pero tienen pequeñas diferencias para garantizar que no copies y pegues el código ciegamente sin entenderlo.

Cuando tengas que entregar la actividad en canvas por favor solo entrega el archivo.h que lleva el nombre del algoritmo o estructura como se viene en el encabezado del main.

Los cambios que puedes esperar son: 
el manejo de excepciones, 
los casos de prueba, 
los formatos de entrada y salida de algunas funciones.

# Correcciones

## 8 Grafos y Búsquedas.

Se subió el archivo _“graph.h”_ faltante con las funciones solicitadas y adaptadas para el nuevo _“main.cpp”_.

### loadGraphList
- Línea 46 (**loadGraphList**): Se añadió la definición de la función para poder leer el contenido de las líneas que incluyen la relación entre nodos / vértices.
- Línea 91 (**addEdgeAdjList**): Se añadió una función auxiliar para añadir las conexiones entre nodos.
- Línea 227 (**sortAdjList**): Se añadió una función auxiliar para ordenar las conexiones entre nodos para cada uno de los nodos.

### DFS
- Línea 126 (**DFS**): Se añadió la definición de la función para poder realizar el “Depth First Search” con ayuda de una función auxiliar.
- Línea 137 (**depthHelper**): Se añadió una función auxiliar la cual se encarga del proceso para realizar la búsqueda.

### BFS
- Línea 156 (**BFS**): Se añadió la definición de la función para poder realizar el “Breadth First Search” con ayuda de una función auxiliar.
- Línea 168 (**breadthHelper**): Se añadió una función auxiliar la cual se encarga del proceso para realizar la búsqueda.
