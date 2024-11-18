

/* Includes ------------------------------------------------------------- */
#include <Proyecto1_inferencing.h>
#include <Arduino_LSM9DS1.h> // Biblioteca para el IMU

/* Constantes ------------------------------------------------------------ */
#define CONVERT_G_TO_MS2    9.80665f
#define MAX_ACCEPTED_RANGE  2.0f        

/* Variables privadas ---------------------------------------------------- */
static bool debug_nn = false;

/* Funciones ------------------------------------------------------------- */
void setup() {
    // Iniciar comunicación serial con el PC (si está disponible)
    Serial.begin(115200);
    
    // Iniciar comunicación serial con el módulo HC-06 (usualmente a 9600 bps)
    Serial1.begin(9600);  // HC-06 se conecta a Serial1 (en el Nano BLE Sense, es la UART secundaria)
    
    // Esperar 5 segundos para ver si hay una conexión serial (PC)
    unsigned long startMillis = millis();
    while (!Serial && millis() - startMillis < 5000) {
        // Esperar por conexión serial durante 5 segundos
    }

    if (!Serial) {
        // Si no está conectado a una PC, imprimir un mensaje en caso de estar conectado más tarde
        Serial.println("Iniciando sin conexión a PC...");
    }

    // Inicializar IMU
    if (!IMU.begin()) {
        Serial.println("Fallo al inicializar IMU!");
    } else {
        Serial.println("IMU inicializada");
    }

    if (EI_CLASSIFIER_RAW_SAMPLES_PER_FRAME != 3) {
        Serial.println("ERR: EI_CLASSIFIER_RAW_SAMPLES_PER_FRAME debe ser igual a 3 (los 3 ejes del sensor)");
        return;
    }

    Serial.println("Sistema listo para clasificar y enviar resultados por HC-06.");
}

void loop() {
    // Realiza la inferencia y obtiene el resultado
    String result = realizarInferencia();

    // Enviar el resultado por el módulo HC-06 (Serial1)
    Serial1.println(result);  // Enviar la cadena clasificada al dispositivo Bluetooth conectado al HC-06
    Serial.println("Resultado enviado por HC-06: " + result);  // Mostrar en el monitor serial del PC (si está disponible)

    delay(2000);  // Controlar la frecuencia de envío
}

/**
 * @brief Realiza la inferencia y devuelve el resultado con la mayor probabilidad
 */
String realizarInferencia() {
    float buffer[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE] = {0};

    // Capturar datos del acelerómetro
    for (size_t ix = 0; ix < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE; ix += 3) {
        IMU.readAcceleration(buffer[ix], buffer[ix + 1], buffer[ix + 2]);

        // Limitar los valores del buffer a un rango aceptable
        for (int i = 0; i < 3; i++) {
            if (fabs(buffer[ix + i]) > MAX_ACCEPTED_RANGE) {
                buffer[ix + i] = (buffer[ix + i] > 0) ? MAX_ACCEPTED_RANGE : -MAX_ACCEPTED_RANGE;
            }
        }

        // Convertir g a m/s^2
        buffer[ix + 0] *= CONVERT_G_TO_MS2;
        buffer[ix + 1] *= CONVERT_G_TO_MS2;
        buffer[ix + 2] *= CONVERT_G_TO_MS2;
    }

    // Crear una señal a partir del buffer
    signal_t signal;
    int err = numpy::signal_from_buffer(buffer, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &signal);
    if (err != 0) {
        Serial.println("Error al crear la señal desde el buffer");
        return "Error";
    }

    // Ejecutar la clasificación
    ei_impulse_result_t result = { 0 };
    err = run_classifier(&signal, &result, debug_nn);
    if (err != EI_IMPULSE_OK) {
        Serial.println("Error al ejecutar el clasificador");
        return "Error";
    }

    // Encontrar la clase con mayor probabilidad
    float max_probabilidad = 0.0;
    String mejor_clase = "";

    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
        if (result.classification[ix].value > max_probabilidad) {
            max_probabilidad = result.classification[ix].value;
            mejor_clase = String(result.classification[ix].label);
        }
    }

#if EI_CLASSIFIER_HAS_ANOMALY == 1
    if (result.anomaly > max_probabilidad) {
        mejor_clase = "Anomalia";
    }
#endif

    Serial.println("Clasificación más probable: " + mejor_clase);
    return mejor_clase;
}
