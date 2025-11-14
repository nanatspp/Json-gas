#include <BluetoothSerial.h>
#include <ArduinoJson.h> 
#include <ESP32Servo.h> 

BluetoothSerial SerialBT;
Servo myServo;

const int LED_PIN = 4; 
const int SERVO_PIN = 18;

const int minAngle = 10;
const int maxAngle = 170;

void setup() {
  Serial.begin(9600); 
  
  SerialBT.begin("ESP32_Slave"); 
  Serial.println("ESP2 (Slave) iniciado. Aguardando conexão do Master...");

  pinMode(LED_PIN, OUTPUT); 
  myServo.attach(SERVO_PIN);

  myServo.write(minAngle);    
  digitalWrite(LED_PIN, LOW); 
}

void loop() {
 
  if (SerialBT.available()) {
    String incomingJson = SerialBT.readStringUntil('\n');
    Serial.print("Recebido: ");
    Serial.println(incomingJson);

    JsonDocument jsonDoc;
    DeserializationError error = deserializeJson(jsonDoc, incomingJson);

    if (error) {
      Serial.print("Falha ao ler JSON: ");
      Serial.println(error.c_str());
      return; 
    }

    bool alert = jsonDoc["gas_alert"] | false; 

    if (alert) {
      Serial.println("ALERTA DE GÁS! Acionando atuadores.");
      myServo.write(maxAngle);       
      digitalWrite(LED_PIN, HIGH);
    } else {
      Serial.println("Nível de gás normal.");
      myServo.write(minAngle);  
      digitalWrite(LED_PIN, LOW); 
    }
  }
  
  delay(20); 
}


// #include <BluetoothSerial.h>
// #include <ArduinoJson.h> 
// #include <ESP32Servo.h> 

// BluetoothSerial SerialBT;
// Servo myServo;

// const int minAngle = 10;
// const int maxAngle = 170;
// const int stepDelay = 19; 

// const int LED_PIN = 4; 
// const int SERVO_PIN = 18;


// int currentPos = minAngle;
// int direction = 1; 

// unsigned long previousMillis = 0;
// const long interval = 1000;
// int servoState = 0;

// void setup() {
//   Serial.begin(9600); 
  
//   SerialBT.begin("ESP32_Slave"); 
//   Serial.println("ESP2 (Slave) iniciado. Aguardando conexão do Master...");

//   pinMode(LED_PIN, OUTPUT); 
//   myServo.attach(SERVO_PIN);

//   // Estado inicial
//   myServo.write(10);    
//   digitalWrite(LED_PIN, LOW); 
// }

// void loop() {
//   if (SerialBT.available()) {
//     String incomingJson = SerialBT.readStringUntil('\n');
//     Serial.print("Recebido: ");
//     Serial.println(incomingJson);

//     JsonDocument jsonDoc;
//     DeserializationError error = deserializeJson(jsonDoc, incomingJson);

//     if (error) {
//       Serial.print("Falha ao ler JSON: ");
//       Serial.println(error.c_str());
//       return; 
//     }

//     bool alert = jsonDoc["gas_alert"] | false; 

//     if (alert) {
     
//       Serial.println("ALERTA DE GÁS! Acionando atuadores.");
//       myServo.write(170);       
//       digitalWrite(LED_PIN, HIGH);
//     } else {
     
//       Serial.println("Nível de gás normal.");
//       myServo.write(10);  
//       digitalWrite(LED_PIN, LOW); 
//     }
//   }
  
//   delay(20); 
//}
// #include <BluetoothSerial.h>
// #include <ArduinoJson.h> 
// #include <ESP32Servo.h> 

// BluetoothSerial SerialBT;
// Servo myServo;

// const int LED_PIN = 4; 
// const int SERVO_PIN = 18;

// void setup() {
//   Serial.begin(9600); 
  
//   SerialBT.begin("ESP32_Slave"); 
//   Serial.println("ESP2 (Slave) iniciado. Aguardando conexão do Master...");

//   pinMode(LED_PIN, OUTPUT);
  
//   myServo.attach(SERVO_PIN);

//   // Estado inicial
//   myServo.write(10);    
//   digitalWrite(LED_PIN, LOW);
// }

// void loop() {
 
//   if (SerialBT.available()) {
//     String incomingJson = SerialBT.readStringUntil('\n');
//     Serial.print("Recebido: ");
//     Serial.println(incomingJson);

//     StaticJsonDocument<100> jsonDoc;
//     DeserializationError error = deserializeJson(jsonDoc, incomingJson);

//     if (error) {
//       Serial.print("Falha ao ler JSON: ");
//       Serial.println(error.c_str());
//       return; 
//     }

//     bool alert = jsonDoc["gas_alert"] | false; 

//     if (alert) {
//       Serial.println("ALERTA DE GÁS! Acionando atuadores.");
//       myServo.write(170);       
//       digitalWrite(LED_PIN, HIGH); 
//     } else {
//       Serial.println("Nível de gás normal.");
//       myServo.write(10);  
//       digitalWrite(LED_PIN, LOW);
//     }
//   }
  
//   delay(20000);
// }