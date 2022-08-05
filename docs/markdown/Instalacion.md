## 1. Descargar la librería SMFL 2.5.1</br>
https://www.sfml-dev.org/download/sfml/2.5.1/ </br>
Después comprimir el archivo descargado</br>
IDE utilizado (Visual Studio 2022)</br>
## 2. Agregar la libreria SFML en VS2022
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

## 3. Cargar los archivos .bin a la carpeta del Proyecto
-	Por último, ingresar a la carpeta descomprimida de SFML/bin y copiar los 11 archivos que aparecen, en la carpeta clonada del Proyecto-CCII/x64/Debug y pegar los archivos.</br>

Iniciar el juego desde archivo main.cpp