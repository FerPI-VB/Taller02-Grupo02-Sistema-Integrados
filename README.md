# Sistema Integrado de Riego Automatizado 🌱
## Descripción del Proyecto
Este proyecto simula un sistema embebido diseñado para optimizar el uso del agua en la agricultura de precisión. Utiliza una arquitectura basada en eventos (EDA) para tomar decisiones en tiempo real sin intervención manual, evaluando constantemente las condiciones de humedad del suelo y la temperatura ambiente.

## Hardware Simulado (Tinkercad)
* **Microcontrolador:** Arduino Uno R3
* **Sensores (Entrada):**  
  * Sensor de Temperatura (TMP36)  
  * Potenciómetro (Simulador de humedad del suelo)
* **Actuadores (Salida):**
  * Microservomotor (Simulador de válvula de agua)
* **Interfaz (Feedback):** Pantalla LCD 16x2 (I2C)

## Lógica de Decisión Combinada
El sistema opera bajo las siguientes reglas lógicas:
1. **Riego Eficiente (AND):** Se activa si la humedad es menor al 40% Y la temperatura es mayor a 28°C.
2. **Riego de Emergencia (OR):** Se activa si la humedad cae a un nivel crítico menor al 15% sin importar la temperatura, priorizando la supervivencia de la planta.

## Estructura del Repositorio
* `sistema_riego_eda.ino`: Código fuente principal documentado y modularizado.

## Enlace a la Simulación
[Diseño en Tinkercad](https://www.tinkercad.com/things/3loM5z10V30/editel?sharecode=WzNssVyD3rWS8nFSvjZqu36kJ-pSlVuPMxSUSzbc_M0)
