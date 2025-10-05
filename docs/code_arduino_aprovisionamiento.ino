#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>

// Definiciones
const char* apSSID = "ESP32-Config";  // SSID del AP
const char* apPass = "";              // Sin contraseña para simplicidad (puedes agregar)
IPAddress apIP(192, 168, 4, 1);       // IP fija para AP

WebServer server(80);                 // Servidor web en puerto 80
Preferences preferences;              // Para almacenamiento no volátil

String wifiSSID = "";
String wifiPass = "";

const int resetPin = 0;               // GPIO 0 para reset (botón pull-up externo)

// Página HTML para configuración (simple form)
const char* htmlForm = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Configurar WiFi</title>
  <style>body { font-family: Arial; text-align: center; } form { margin: 20px; }</style>
</head>
<body>
  <h1>Configurar Red WiFi</h1>
  <form action="/config" method="POST">
    <label>SSID:</label><br><input type="text" name="ssid"><br>
    <label>Contraseña:</label><br><input type="password" name="pass"><br><br>
    <input type="submit" value="Guardar">
  </form>
  <br><a href="/reset">Resetear Configuración</a>
</body>
</html>
)rawliteral";

// Función para manejar root (/)
void handleRoot() {
  server.send(200, "text/html", htmlForm);
}

// Función para manejar config (POST)
void handleConfig() {
  if (server.hasArg("ssid") && server.hasArg("pass")) {
    wifiSSID = server.arg("ssid");
    wifiPass = server.arg("pass");
    
    // Guardar en Preferences
    preferences.begin("wifi", false);
    preferences.putString("ssid", wifiSSID);
    preferences.putString("pass", wifiPass);
    preferences.end();
    
    server.send(200, "text/html", "<h1>Configuración guardada. Reiniciando...</h1>");
    delay(2000);
    ESP.restart();
  } else {
    server.send(400, "text/html", "<h1>Error: Datos incompletos</h1>");
  }
}

// Función para reset
void handleReset() {
  preferences.begin("wifi", false);
  preferences.clear();
  preferences.end();
  
  server.send(200, "text/html", "<h1>Configuración reseteada. Reiniciando...</h1>");
  delay(2000);
  ESP.restart();
}

// Setup
void setup() {
  Serial.begin(115200);
  pinMode(resetPin, INPUT_PULLUP);  // Botón para reset
  
  // Leer credenciales
  preferences.begin("wifi", true);
  wifiSSID = preferences.getString("ssid", "");
  wifiPass = preferences.getString("pass", "");
  preferences.end();
  
  if (wifiSSID == "") {
    // Modo AP si no hay creds
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(apSSID, apPass);
    Serial.println("Modo AP iniciado. Conéctate a " + String(apSSID));
    
    // Configurar servidor
    server.on("/", HTTP_GET, handleRoot);
    server.on("/config", HTTP_POST, handleConfig);
    server.on("/reset", HTTP_GET, handleReset);
    server.begin();
  } else {
    // Modo STA
    WiFi.mode(WIFI_STA);
    WiFi.begin(wifiSSID.c_str(), wifiPass.c_str());
    Serial.print("Conectando a " + wifiSSID + "...");
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
      delay(500);
      Serial.print(".");
      attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\nConectado! IP: " + WiFi.localIP().toString());
      // Aquí puedes agregar lógica IoT adicional (e.g., MQTT)
    } else {
      Serial.println("\nFallo conexión. Reiniciando en AP...");
      preferences.begin("wifi", false);
      preferences.clear();
      preferences.end();
      ESP.restart();
    }
  }
}

// Loop
void loop() {
  // Manejar servidor si en AP
  if (wifiSSID == "") {
    server.handleClient();
  }
  
  // Verificar botón de reset (en cualquier modo)
  if (digitalRead(resetPin) == LOW) {
    delay(50);  // Debounce
    if (digitalRead(resetPin) == LOW) {
      handleReset();
    }
  }
  
  // Reconexión automática si desconectado en STA
  if (wifiSSID != "" && WiFi.status() != WL_CONNECTED) {
    Serial.println("Reconectando...");
    WiFi.reconnect();
    delay(5000);
  }
}
