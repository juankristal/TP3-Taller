# Taller de Programacion [75.42] - TP3

**Nombre: Juan Ignacio Kristal**

**Padron: 99779**

**Repositorio: https://github.com/juankristal/TP2-Taller**

**Cuatrimestre: 2C 2020**


1. **[Sockets](#Sockets)**

2. **[Cliente](#BPFP)**

3. **[Servidor](#BPFV)**

## Sockets <a name="Sockets"></a>

Para la resolucion del trabajo se utilizaron sockets de manera similar al TP1. Dadas las ventajas de C++ en comparacion a C se pudieron realizar ciertas mejoras con respecto al Socket anterior. Entre ellas fueron definidos 3 constructores y un destructor asi como la definicion de la construccion por movimiento.

Los tres constructores definidos corresponden a:

1. Socket(ip, puerto), el cual es el constructor utilizado por el cliente. Se realiza un connect a dicha IP/Puerto en el constructor.
2. Socket(puerto), el cual es utilizado por el cliente y realiza un bind&listen en el constructor.
3. Socket(fd), el cual es utilizado en el accept() del socket, ya que este mismo devuelve un Socket en base al fd que nos da la syscall del accept. Este constructor es privado ya que solo se utiliza para dicha funcion (construccion de Workers/Peers).

Ademas, fue implementada la excepcion NetworkError la cual maneja los errores del Socket. Si ocurre un error en el constructor el Socket no fue inicializado, en caso de haber un error en el recv o el send y se levante dicha excepcion, el destructor del Socket se encarga de cerrar y hacer shutdown con RAII.

Para utilizar el protocolo propuesto, se implemento una funcion de interfaz extra en el Socket llamada kill_channel(str channel) la cual le hace shutdown al canal recibido por parametro (w o r).

## Cliente <a name="Cliente"></a>

El cliente tiene un comportamiento sencillo y casi ninguna logica. Solo maneja las excepciones del Socket en caso de que tenga algun fallo. 

Sencillamente lo unico que hace es leer un mensaje de stdin, enviar el mensaje mediante un Socket y luego esperar a recibir la respuesta del Servidor.

## Servidor <a name="Servidor"></a>

El servidor tiene una logica mas compleja que la del cliente. Como debe aceptar multiples clientes de manera concurrente, se utilizaron Threads para las clases Server y Worker que escencialmente representan al Socket aceptador y a los Peers respectivamente.

Para el funcionamiento de dichas clases se implemento el operador() para ambas (un wrapper de la funcion start de thread). Particularmente el servidor tiene el ownership de los recursos (clase Resources) el cual es luego el objeto compartido de los Workers donde escribiran los mensajes recibidos por los clientes.

El Server dentro de su run crea Workers segun lo necesite cuando llegan clientes y cada vez que llega uno se eliminan a los Workers que ya hayan terminado.

Cada Worker instancia un HTTPParser en su funcion run y lo utiliza para parsear la entrada del Cliente. Dicho parser tiene una interfaz para conseguir la primera linea (la cual luego el Worker imprime) y las diferentes partes del mensaje que utilizaran luego los Handlers para generar la respuesta al cliente.

Los Handlers utilizados por el Worker son GETHandler, POSTHandler y ERRORHandler los cuales generan la respuesta al Cliente de forma polimorfica como fue indicado en la consigna.

![Imagen 1](img/server.png?raw=true)

_Imagen 1. Clases del servidor_
