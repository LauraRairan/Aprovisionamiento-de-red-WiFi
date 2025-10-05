# ESP32-WiFi-Config

Solución IoT basada en el microcontrolador ESP32 que permite la configuración dinámica de una red WiFi sin necesidad de reprogramar el dispositivo. El sistema ofrece una interfaz web local para que el usuario final ingrese el SSID y la contraseña, guardando las credenciales en memoria no volátil. Incluye reconexión automática y un mecanismo para reestablecer la configuración.

## Descripción
- **Plataforma**: ESP32
- **Lenguaje**: Arduino (C/C++)
- **Funcionalidades**:
  - Inicia en modo Punto de Acceso (AP) si no hay credenciales guardadas.
  - Proporciona una interfaz web para configurar SSID y contraseña.
  - Almacena credenciales en memoria no volátil usando Preferences.
  - Se reconecta automáticamente a la red configurada.
  - Permite resetear la configuración mediante un botón o vía web.
- **Estado**: Proyecto funcional y documentado.

## Requisitos
- Hardware: ESP32 (compatible con Arduino), botón con resistencia pull-up (opcional para GPIO 0).
- Software: Arduino IDE, Git, GitHub, Postman (para probar endpoints).

## Instrucciones de Uso
1. **Cargar el código**:
   - Conecta el ESP32 al computador vía USB.
   - Abre Arduino IDE, selecciona la placa ESP32 y el puerto correcto.
   - Copia el archivo `ESP32_WiFi_Config.ino` y súbelo al ESP32.
2. **Configurar el WiFi**:
   - El ESP32 creará una red WiFi llamada "ESP32-Config".
   - Conéctate a esta red desde tu dispositivo (sin contraseña por defecto).
   - Abre un navegador y ve a `http://192.168.4.1`.
   - Ingresa el SSID y la contraseña de tu red WiFi, luego haz clic en "Guardar".
   - Espera 10-30 segundos; el ESP32 se reiniciará y intentará conectarse.
3. **Verificar la conexión**:
   - Abre el Monitor Serial en Arduino IDE (115200 baudios).
   - Busca el mensaje "Conectado! IP: [tu IP]" (por ejemplo, "10.246.87.77").
   - El LED integrado (GPIO 2) debería encenderse fijo si está conectado.
4. **Resetear (opcional)**:
   - Presiona el botón en GPIO 0 o visita `http://192.168.4.1/reset` desde la red "ESP32-Config" para borrar las credenciales.

## Documentación
- **Endpoints**: Detallados en [`/endpoints.md`](./endpoints.md).
- **Colección Postman**: Disponible en [`/postman_collection.json`](./postman_collection.json).
- **Conversaciones con IA**: Registradas en [`/docs/conversaciones_IA.md`](./docs/conversaciones_IA.md).
- **Diagramas**: Incluyen UML de secuencia y esquemático en [`/docs/diagrams`](./docs/diagrams).

## Requisitos Cumplidos
- Inicia en modo AP si no hay credenciales.
- Interfaz web para configuración.
- Almacenamiento en memoria no volátil.
- Reconexión automática.
- Mecanismo de reset.
- Documentación técnica (diagramas, endpoints, código comentado).
- Repositorio en GitHub con Wiki/README.

## Colaboradores
- Profesor: [@fabianpaeri](https://github.com/fabianpaeri) (agregado como colaborador).

## Licencia
[Agregar licencia si aplica, por ejemplo, MIT o GPL.]

## Capturas
- Monitor Serial con conexión exitosa:
