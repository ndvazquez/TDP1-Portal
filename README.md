# Trabajo Práctico 4: Portal

### Alumnos:
- Camila Bojman
- Cecilia Hortas
- Nicolas Vázquez

### Estado del trabajo hasta el momento:
Separamos cliente y servidor y está implementado el soporte multijugador. Para ejecutarlo hay que hacer lo siguiente:
1. Compilar Server y ejecutarlo: `./Server`
2. Compilar Cliente y ejecutar:
`./Client Chell1`
`./Client Chell2`

Después vamos a sacar esta versión harcodeada y usar los comandos vistos en los TPS individuales.

Se pueden probar los movimientos de Chell con las teclas:
- **w** para saltar
- **d** para moverse a la derecha
- **a** para moverse a la izquierda

El juego completo está implementado pero la versión en master no tiene un nivel con todas las funcionalidades a testear. Arriba de todo hay una cake que si se llega a ella se gana. Estamos trabajando en el parseo del YAML del editor al comienzo del juego y en el soporte multipartida. Así mismo hay algunas vistas a fixear y algunos bugs detectados en los que vamos a trabajar esta semana.

### Dependencias a instalar:
- Para la interfaz gráfica:
`sudo apt-get install libsdl2-dev`
`sudo apt-get install libsdl2-image-dev`

- Para trabajar con archivos formato YAML:
`sudo apt-get install libyaml-cpp-dev`

- Para la libreria de sonidos:
`sudo apt-get install libsdl2-mixer-dev`

### Ffmpeg
Este feature fue desarrollado en un repositorio externo. 
Aún no está integrado al proyecto por lo tanto no hay necesidad de compilarlo ni mucho menos descargar sus dependecias.

En el [repositorio](https://github.com/camiboj/tutorial-ffmpeg) se pueden encontrar (a modo de ejemplo/prueba) un programa simple. Su README explica que dependencias se deben installar y cómo ejecutar el programa.
