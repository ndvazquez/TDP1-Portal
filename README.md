# Trabajo Práctico 4: Portal

### Alumnos:
- Camila Bojman
- Cecilia Hortas
- Nicolas Vázquez

### Estado del trabajo hasta el momento:
Al ejecutar el main del cliente se pueden probar los movimientos de Chell con las teclas:
- **w** para saltar
- **d** para moverse a la derecha
- **a** para moverse a la izquierda

Hay una roca en el escenario para levantarla con la tecla **g** y descargarla con la tecla **f**. Debajo de los dos bloques de metal dibujados hay dos portales horizontales colocados justo debajo de ellos donde se pueden teletransportar ambos objetos presentes en el escenario.

Estamos trabajando para enviar la información entre cliente y servidor a través de elementos de formato JSON y poder terminar de testear la lógica del juego y unirla a sus vistas.

### Dependencias a instalar:
- Para la interfaz gráfica:
`sudo apt-get install libsdl2-dev`
`sudo apt-get install libsdl2-image-dev`

- Para trabajar con archivos formato YAML:
`sudo apt-get install libyaml-cpp-dev`

- Para la libreria de sonidos:
`sudo apt-get install libsdl2-mixer-dev`