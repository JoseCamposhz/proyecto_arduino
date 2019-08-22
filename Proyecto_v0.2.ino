#include <LiquidCrystal.h>
#include <SimpleDHT.h>

// iniciaiza el objeto de LCD  con los respectivos pines conectados
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int pinDHT11 = 2;                   // Este es el pin al que se conecta el sensor
SimpleDHT11 dht11;                  // Es el objeto que representa al sensor

const int pResistor = A0;       // El pin correspondiente al Fotoresistor
int value;                      // Variable que almacenará los valores del fotoresistor (0-1023)

#define BLUE 3
#define GREEN 5
#define RED 6

#define ENABLE 4

void setup() {
  lcd.begin(16, 2);             // se inicializa el numero de columnas y filas de la pantalla
  pinMode(pResistor, INPUT);     // Se inicializa el pin para el fotoresistor

  pinMode(RED, OUTPUT);         //Se definen los modos del pin
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(ENABLE,OUTPUT);
  digitalWrite(RED, HIGH);      //Se define el pin inicla 
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  Serial.begin(9600);
  lcd.print("Bienvenido!");   // Se emprime un mensaje en la pantalla.
}

//definir variables para los cambios del led
int redValue;       
int greenValue;
int blueValue;

void loop() {
    // start working...

  byte temperature = 0;                 // Elementos que almacenarán la indormación entragada por 
  byte humidity = 0;                    // el sensor, sin ser procesadas.
  byte data[40] = {0};                  // Arreglo que contiene los datos entregados por el sensor 

  if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
    Serial.println("DHT11 - error de lectura");
    return;
  }

  Serial.print("Muestra RAW Bits: ");
  for (int i = 0; i < 40; i++) {
    Serial.print((int)data[i]);
    if (i > 0 && ((i + 1) % 4) == 0) {
      Serial.print(' ');
    }
  }

  value = analogRead(pResistor);
  Serial.print("Brillo ");
  Serial.println(value);        // Se mostrara el valor almacenado del fotoresistor
  
  Serial.print("Sample OK: ");
  int temp = (int)temperature;
  int hum = (int)humidity;
  lcd.setCursor(0, 0);
  lcd.print(String("Brillo: ")+String(value));
  lcd.setCursor(0, 1); // Se inicia en el cursor en la columna 0 y fila 1
  lcd.print(String("T:")+String(temp)+String("C - H:")+String(humidity)+String("%"));
  #define delayTime 10  
  redValue = 0;
  greenValue = 255;
  blueValue = 0;

  digitalWrite(ENABLE, HIGH); // Giro para un lado  
  // digitalWrite(ENABLE,LOW);
  if (int(value) <= 350) {
        
    redValue = 255;
    greenValue = 0;
    analogWrite(RED, redValue);
    analogWrite(GREEN, greenValue);
  } else {
    digitalWrite(ENABLE,LOW);
    greenValue = 255;
    redValue = 0;
    analogWrite(RED, redValue);
    analogWrite(GREEN, greenValue);
  }
  delay(100); // Se pausa por un segundo, dado que la muestra del sensor se realiza a 1Hz
}
