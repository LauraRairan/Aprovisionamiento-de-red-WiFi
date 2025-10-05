# Documentación de Endpoints

## 1. GET /
- **Descripción**: Muestra el formulario HTML para ingresar el SSID y la contraseña de la red WiFi.
- **URL**: `http://192.168.4.1/`
- **Método**: GET
- **Headers**: Ninguno requerido.
- **Query Parameters**: Ninguno.
- **Payload**: Ninguno.
- **Respuesta**:
  - Código: 200
  - Contenido: HTML con un formulario que incluye campos para SSID y contraseña, y un enlace a "/reset".

## 2. POST /config
- **Descripción**: Recibe el SSID y la contraseña enviados desde el formulario y los guarda en la memoria no volátil del ESP32. Luego reinicia el dispositivo.
- **URL**: `http://192.168.4.1/config`
- **Método**: POST
- **Headers**: `Content-Type: application/x-www-form-urlencoded`
- **Query Parameters**: Ninguno.
- **Payload**: 
  - `ssid`: Nombre de la red WiFi (texto).
  - `pass`: Contraseña de la red WiFi (texto).
- **Respuesta**:
  - Código: 200
  - Contenido: `<h1>Configuración guardada. Reiniciando...</h1>` si los datos son válidos.
  - Código: 400
  - Contenido: `<h1>Error: Datos incompletos</h1>` si faltan `ssid` o `pass`.

## 3. GET /reset
- **Descripción**: Borra las credenciales guardadas en la memoria no volátil y reinicia el ESP32 en modo AP.
- **URL**: `http://192.168.4.1/reset`
- **Método**: GET
- **Headers**: Ninguno requerido.
- **Query Parameters**: Ninguno.
- **Payload**: Ninguno.
- **Respuesta**:
  - Código: 200
  - Contenido: `<h1>Configuración reseteada. Reiniciando...</h1>`.
