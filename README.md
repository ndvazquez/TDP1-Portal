# Trabajo Práctico 4: Portal

### Alumnos:
- Camila Bojman
- Cecilia Hortas
- Nicolas Vázquez

### Estado del trabajo hasta el momento:

Para compilar el proyecto ejecutar en el root del repo:
```
cmake CMakeLists.txt &&
make Client &&
make Server &&
make Editor
```

Separamos cliente y servidor y está implementado el soporte multijugador. De momento está _hardcodeada_ la cantidad de clientes que atiende una partida, con un límite de dos. Al ejecutar un cliente hay que pasarle el ID correspondiente que utilizará en la partida (Debe ser Chell1 o Chell2 por ahora, esto es temporal, sólo para probar).

Para ejecutarlo hay que hacer lo siguiente:

1. `./Server`
2. `./Client Chell1`
3. `./Client Chell2`

Después vamos a sacar esta versión harcodeada y usar los comandos vistos en los TPS individuales.

Se pueden probar los movimientos de Chell con las teclas:
- **w** para saltar
- **d** para moverse a la derecha
- **a** para moverse a la izquierda
- **r** para quitar portales
- **click izquierdo** para poner un portal azul.
- **click derecho** para poner un portal naranja.

El resto de las funcionalidades (mover rocas, botones, compuertas) están implementadas y testeadas, nos queda tener un mapa diseñado para integrar todo en un nivel, deberíamos tenerlo listo para el día martes 18/06.

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
