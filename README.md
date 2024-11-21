# Sistema Inteligente de Monitoreo y Alertas para la Seguridad de Adultos Mayores

Este repositorio contiene el desarrollo del **Mini Proyecto 1** de la asignatura de Inteligencia artificial en dispositivos móviles y embebidos, titulado:  
**"Desarrollo de un Sistema Inteligente de Monitoreo y Alertas para la Seguridad de Adultos Mayores".**

---

## 📜 **Descripción General**
El objetivo de este proyecto fue diseñar e implementar un sistema inteligente capaz de monitorear en tiempo real los movimientos de adultos mayores para detectar eventos críticos como caídas, inmovilidad prolongada y convulsiones. El sistema combina sensores inerciales, aprendizaje automático y una aplicación móvil para ofrecer una solución robusta y accesible.

---

## 📋 **Componentes del Proyecto**

### 1. **Arduino Nano 33 BLE Sense**
- Microcontrolador con el que se realizó la captura de los datos de movimiento a través de sus sensores inerciales (acelerómetro y giroscopio).
- Permite la clasificación en tiempo real de eventos mediante un modelo de aprendizaje automático integrado.

### 2. **Edge Impulse**
- Plataforma utilizada para entrenar y optimizar el modelo de machine learning basado en datos de movimiento.
- El modelo clasifica patrones de movimiento en tres categorías: **Caída**, **Inmovilidad**, y **Convulsión**.

### 3. **Aplicación Móvil (App Inventor)**
- Interactúa con el Arduino a través de Bluetooth, recibiendo y procesando datos en tiempo real.
- Activa alarmas específicas para cada evento detectado:
  - **Alarma de inmovilidad:** Notificación visual.
  - **Alarma de convulsión:** Alarma sonora.
  - **Alarma de caída:** Envío de un correo electrónico a cuidadores o familiares.

---

## ⚙️ **Metodología**

### 1. **Captura de Datos**
- Se recolectaron datos de movimiento mediante los sensores del Arduino a una frecuencia de muestreo de 100Hz durante 8 segundos por muestra.
- Movimientos analizados: **Caída, inmovilidad y convulsión**.

### 2. **Entrenamiento del Modelo**
- Los datos capturados se procesaron y entrenaron en Edge Impulse.
- Modelo configurado con dos capas ocultas de 30 y 15 neuronas, respectivamente.
- Precisión obtenida:
  - **Inmovilidad y convulsión:** 100%.
  - **Caída:** 98.7%.

### 3. **Implementación del Modelo**
- Se desplegó el modelo entrenado en el microcontrolador Arduino, configurado para procesar y clasificar datos en tiempo real. Para realizar este despligue, la página de edge impulse cuenta con un apartado llamado despliegue en donde se debe seleccionar descargar el archivo como librería de arduino, lo que nos descargará un archivo .zip que debe ser agregado en las librerías del IDE de arduino, posterior a esto en un nuevo sketch de agrega el código del archivo .ino de este repositorio que se basa en el ejemplo de arduino con el nano 33 BLE sense que cuenta con un ejemplo del acelerómetro.

### 4. **Desarrollo de la Aplicación Móvil**
- Creación de una aplicación en **App Inventor** que interactúa con el Arduino para recibir datos y activar alarmas.
- Las alarmas responden automáticamente según el tipo de evento detectado.

### 5. **Pruebas y Validación**
- Se realizaron pruebas simuladas en diversos escenarios para validar la precisión y confiabilidad del sistema.
- El sistema demostró un desempeño altamente confiable en la detección de eventos críticos.

---

## 🛠 **Configuración del Proyecto**

### Requisitos
- **Hardware:** Arduino Nano 33 BLE Sense.
- **Software:**
  - Arduino IDE.
  - Plataforma Edge Impulse.
  - MIT App Inventor.
- **Librerías:** Incluir las librerías necesarias para comunicación Bluetooth y procesamiento de datos.

### Instrucciones de Uso
1. **Clonar el repositorio.**
2. **Configurar y cargar el código al Arduino Nano 33 BLE Sense.**
3. **Entrenar y desplegar el modelo en Edge Impulse (El proyecto de edge impulse se encuentra en el siguiente enlace (https://studio.edgeimpulse.com/public/507816/live)).**
4. **Instalar la aplicación móvil en un dispositivo Android.**
5. **Emparejar el dispositivo móvil con el Arduino mediante Bluetooth.**
6. **Realizar pruebas en escenarios simulados para validar el sistema.**

---

## 🚨 **Funciones de Alerta**
- **Inmovilidad:** Notificación emergente en la aplicación móvil.
- **Convulsión:** Alarma sonora hasta que se desactiva manualmente.
- **Caída:** Envío de correo automático al contacto registrado en la aplicación.

---

## 📊 **Resultados**
- Modelo de machine learning con alta precisión:
  - **Precisión global:** 99.6%.
  - **Errores mínimos en detección de caídas.**
- Sistema validado en escenarios simulados, demostrando alta confiabilidad y capacidad para activar alertas en tiempo real.

---

¡Gracias por visitar este proyecto! 🌟
