# Trabajo Práctico 4: Portal

### Alumnos:
- Camila Bojman
- Cecilia Hortas
- Nicolas Vázquez

### Instalación:

Para instalar el juego en su totalidad:

1. Clonar el repositorio o descargar el código fuente del último release
2. Ejecutar `chmod +x install.sh`
3. Ejecutar `install.sh <path>` siendo `<path>` una ruta válida (de ser necesario, ejecutar con `sudo`)
4. ????
5. Profit.

### Cómo jugar:

1. Levantar un servidor con `./Server <port>`
2. Conectarse con el cliente con `./Client <host> <port>` 
siendo `<host>` una dirección IP y `<port>` el mismo puerto del servidor.

Para crear y editar mapas, ejecutar `./Editor`.

Los controles del juego son:
- **w** para saltar
- **d** para moverse a la derecha
- **a** para moverse a la izquierda
- **r** para quitar portales
- **g** para agarrar la roca más cercana al personaje
- **f** para soltar la roca agarrada
- **t** para lanzar una roca agarrada hacia arriba
- **m** para cambiar entre Fullscreen y Windowed mode
- **p** para poner un pin (marca en la pantalla)
- **click izquierdo** para poner un portal azul
- **click derecho** para poner un portal naranja

### Dependencias a instalar:

Es necesario contar con Cmake en la versión `3.14.5` o superior.

- Para la interfaz gráfica:
```
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
sudo apt-get install libsdl2-mixer-dev
sudo apt-get install libsdl2-ttf-dev 
sudo apt-get install libyaml-cpp-dev
```

### Ffmpeg
Este feature fue desarrollado en un repositorio externo. 
Aún no está integrado al proyecto por lo tanto no hay necesidad de compilarlo ni mucho menos descargar sus dependecias.

En el [repositorio](https://github.com/camiboj/tutorial-ffmpeg) se pueden encontrar (a modo de ejemplo/prueba) un programa simple.
Su README explica que dependencias se deben installar y cómo ejecutar el programa.
