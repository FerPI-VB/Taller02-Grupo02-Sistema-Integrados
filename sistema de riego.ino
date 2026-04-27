#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>

// ==========================================
// 1. DEFINICIÓN DE PINES Y CONSTANTES
// ==========================================
const int PIN_TEMP = A0;       
const int PIN_HUMEDAD = A1;    
const int PIN_SERVO = 9;       

const int UMBRAL_HUM_MINIMA = 40;     
const int UMBRAL_HUM_CRITICA = 15;    
const int UMBRAL_TEMP_ALTA = 28;      

Servo valvulaServo;
LiquidCrystal_I2C lcd(32, 16, 2); 

// ==========================================
// 2. CONFIGURACIÓN INICIAL
// ==========================================
void setup() {
  Serial.begin(9600); 
  
  valvulaServo.attach(PIN_SERVO);
  valvulaServo.write(0); 
  
  // Inicialización para el LCD I2C
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("SISTEMA DE RIEGO");
  delay(1500);
  lcd.clear();
}

// ==========================================
// 3. PIPELINE DE PROCESAMIENTO
// ==========================================
void loop() {
  int humedad = obtenerHumedad();
  int temperatura = obtenerTemperatura();
  
  //Enviar datos al Monitor Serie
  Serial.print("Temperatura: "); 
  Serial.print(temperatura); 
  Serial.print("C | Humedad: "); 
  Serial.print(humedad); 
  Serial.println("%");
  
  bool activarRiego = evaluarLogica(humedad, temperatura);
  
  ejecutarAccion(activarRiego);
  mostrarEstado(humedad, temperatura, activarRiego);
  
  delay(250); 
}

// ==========================================
// 4. MÉTODOS
// ==========================================
int obtenerHumedad() {
  int lectura = analogRead(PIN_HUMEDAD);
  return map(lectura, 0, 1023, 0, 100);
}

int obtenerTemperatura() {
  int lectura = analogRead(PIN_TEMP);
  float voltaje = lectura * (5.0 / 1024.0);
  float celsius = (voltaje - 0.5) * 100;
  return (int)celsius;
}

bool evaluarLogica(int hum, int temp) {
  bool reglaNormal = (hum < UMBRAL_HUM_MINIMA) && (temp > UMBRAL_TEMP_ALTA);
  bool reglaEmergencia = (hum < UMBRAL_HUM_CRITICA);
  return (reglaNormal || reglaEmergencia);
}

void ejecutarAccion(bool regar) {
  if (regar) {
    valvulaServo.write(90); 
  } else {
    valvulaServo.write(0);  
  }
}

void mostrarEstado(int h, int t, bool r) {
  lcd.setCursor(0, 0);
  lcd.print("H:"); lcd.print(h); lcd.print("%  ");
  lcd.print("T:"); lcd.print(t); lcd.print("C  ");
  
  lcd.setCursor(0, 1);
  if (r) {
    if (h < UMBRAL_HUM_CRITICA) {
      lcd.print("MODO: EMERGENCIA");
    } else {
      lcd.print("MODO: RIEGO     ");
    }
  } else {
    lcd.print("ESTADO: ESPERA  ");
  }
}