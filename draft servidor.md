## Draft diseño servidor

Ideas pensadas:
- Servidor tiene una instancia de ``Escenario`` con la que regula los distintos requests del cliente para realizar acciones.
- El cliente le envia al servidor las distintas acciones a realizar: moverse lateralmente, verticalmente, crear un portal, colocar un pin, saltar.
- El servidor analiza el request, chequea si es válido y le envía al cliente la respuesta (OK o rechazado). Para eso tiene guardada una instancia a alguna clase que regule la organización interna del juego. No sería válido colocar un portal en un lugar inválido (un bloque de roca) o en un lugar donde otro jugador colocó un portal.
- Cualquier modificación al escenario es bloqueante. No pueden colocar dos jugadores al mismo tiempo un portal en el mismo lugar.
- Hay ciertos objetos del enunciado cuya presencia no es bloqueante. Por ejemplo el acido.
- Duda respecto de la comunicación: el cliente le envía el request (acción) al servidor, el servidor analiza si puede realizarse, le envía la respuesta, actualiza organización interna y envía a todos los clientes la nueva organización para que cada uno renderice? Esto resultaría en una actualización constante por parte del cliente de su visualización.
- El cliente se encarga de la parte gráfica y del envío de requests y el servidor regula la lógica del juego, enviando constantemente mensajes a todos los clientes.

## Dudas
- Comunicación correcta?
- Como funciona el manejo de los escenarios? Cuando el cliente se une a la partida abre un archivo donde esta predeterminado los distintos valores? (Ya sabemos que hay ciertos parámetros configurables por archivo, nos referimos al escenario en sí).
- Tema de actualización de la interfaz gráfica responsabilidad entera del cliente? 