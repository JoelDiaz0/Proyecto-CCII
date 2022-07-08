# <h1 align="center">Proyecto Final-CC</h1>
<h2 align="center"> Dimension Travelers</h2>
<h3 align="center">Proyecto de Videojuego
Para el curso de Ciencia de la Computacion II
</br> Universidad Nacional de San Agustin de Arequipa </h3>

## Detalles del juego
- 🕹 Videojuego en Plataforma 2D.
- 👥 Multiplayer.

## Concepto de juego
Juego plataformero desarrollado en C++, inspirado en las mecánicas del juego give up, donde el jugador pasará por una serie de niveles con obstáculos con dificultad escalable.

## Recursos
- C++ 
  - Modificación de acceso y asignación dinámica de memoria..
  - Punteros, smart pointers y referencias.
  - Encapsulamiento, herencia, polimorfismo y templates.
  - Sobrecarga de funciones, funtores y meta-programación.
  - Patrones de diseño.   
- SFML (Biblioteca cuyas funcionalidades permiten al usuario crear videojuegos y programas interactivos)
- Git (Gestion de versiones)

## Mecánicas del juego
- El juego permite a 2 jugadores que pueden moverse hacia la izquierda o derecha, saltar, mover algunos objetos con uso de colisiones y presionar botones que activan trampas.
- El objetivo del juego es cruzar un recorrido con obstáculos que incluye, enemigos, unos estáticos y otros móviles, y también trampas visibles u ocultas.
## Instalación del juego

Descargar la librería SMFL 2.5.1</br>
https://www.sfml-dev.org/download/sfml/2.5.1/ </br>
Después comprimir el archivo descargado</br>
IDE utilizado (Visual Studio 2022)</br>
Luego en su editor de código agregar la librería ingresando a Proyecto->Propiedades de Game

Seguir los siguientes pasos:

-	En propiedades de configuración ingresar</br>
-	C/C++ -> General ->Directorios de inclusión adicionales, ahí agregar la  ruta de la carpeta include que se encuentra en la carpeta de SFML.</br>
-	Luego en Vinculador -> General ->Directorios de bibliotecas adicionales, agregar la ruta de la carpeta lib que se también se encuentra en la carpeta de SFML.</br>
-	En la misma pestaña de Vinculador ->Entrada->Dependencias adicionales agregar lo siguiente.</br>
sfml-graphics-d.lib</br>
sfml-window-d.lib</br>
sfml-system-d.lib</br>
sfml-audio-d.lib</br>
sfml-main-d.lib</br>

-	Damos en aplicar y aceptar.</br>

-	Por último, ingresar a la carpeta descomprimida de SFML/bin y copiar los 11 archivos que aparecen, en la carpeta clonada del Proyecto-CCII/x64/Debug y pegar los archivos.</br>

Iniciar el juego desde archivo main.cpp







 
