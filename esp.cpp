#include <WiFi.h>
const char* ssid = "iphone (83)";
const char* password = "Password";
const int motorAPin1 = 26;
const int motorAPin2 = 27;
const int motorBPin1 = 14;
const int motorBPin2 = 12;
WiFiServer server(80);
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi.");
  pinMode(motorAPin1, OUTPUT);
  pinMode(motorAPin2, OUTPUT);
  pinMode(motorBPin1, OUTPUT);a
  pinMode(motorBPin2, OUTPUT);
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    while (!client.available()) {
      delay(1);
    }
    String request = client.readStringUntil('\r');
    client.flush();
    if (request.indexOf("/forward") != -1) {
      moveForward();
    } else if (request.indexOf("/backward") != -1) {
      moveBackward();
    } else if (request.indexOf("/left") != -1) {
      turnLeft();
    } else if (request.indexOf("/right") != -1) {
      turnRight();
    } else if (request.indexOf("/stop") != -1) {
      stopMotors();
    }
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<body>");
    client.println("<h1>ESP32 Motor Controller</h1>");
    client.println("<p>Use the buttons below to control the motors:</p>");
    client.println("<a href=\"/forward\"><button>Forward</button></a><br>");
    client.println("<a href=\"/backward\"><button>Backward</button></a><br>");
    client.println("<a href=\"/left\"><button>Left</button></a><br>");
    client.println("<a href=\"/right\"><button>Right</button></a><br>");
    client.println("<a href=\"/stop\"><button>Stop</button></a><br>");
    client.println("</body>");
    client.println("</html>");
    delay(1);
    client.stop();
  }
}
void moveForward() {
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorAPin2, LOW);
  digitalWrite(motorBPin1, HIGH);
  digitalWrite(motorBPin2, LOW);
}
void moveBackward() {
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, HIGH);
  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, HIGH);
}
void turnLeft() {
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, HIGH);
  digitalWrite(motorBPin1, HIGH);
  digitalWrite(motorBPin2, LOW);
}
void turnRight() {
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorAPin2, LOW);
  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, HIGH);
}
void stopMotors() {
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, LOW);
  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, LOW);
}
