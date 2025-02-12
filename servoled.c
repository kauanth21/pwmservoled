#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// ============================= DEFINIÇÃO DE PINOS =============================
// Define a GPIO onde o servo motor está conectado
//#define SERVO_GPIO 22  
// Caso queira testar com um LED, comente a linha acima e defina a GPIO do LED aqui:
 #define LED_GPIO 12  

// ============================= CONFIGURAÇÃO DO PWM =============================
// Define o valor máximo do contador PWM para gerar um sinal de 50Hz
const uint16_t PWM_MAX = 25000;
// Define o divisor de clock para garantir precisão no sinal PWM
const float PWM_CLOCK_DIV = 100.0f;

// ============================= DEFINIÇÃO DOS ÂNGULOS =============================
// Define os ciclos de trabalho do PWM para cada posição do servo
const uint16_t ANGLE_0 = 625;    // Ângulo de 0° (500µs)
const uint16_t ANGLE_90 = 1837;  // Ângulo de 90° (1470µs)
const uint16_t ANGLE_180 = 3000; // Ângulo de 180° (2400µs)

// Define o incremento do duty cycle para movimentação suave (5µs)
const uint16_t ANGLE_STEP = (5 * PWM_MAX / 20000); 

// ============================= FUNÇÃO DE CONFIGURAÇÃO DO PWM =============================
// Inicializa o PWM na GPIO especificada
void pwm_setup(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM); // Configura o pino como saída PWM
    uint slice = pwm_gpio_to_slice_num(pin); // Obtém o número do slice PWM associado ao pino
    
    // Configura o divisor de clock para manter a frequência correta
    pwm_set_clkdiv(slice, PWM_CLOCK_DIV);
    // Define o valor máximo do contador PWM
    pwm_set_wrap(slice, PWM_MAX);
    // Ativa o PWM no slice correspondente
    pwm_set_enabled(slice, true);
}

// ============================= FUNÇÃO DE MOVIMENTAÇÃO SUAVE DO SERVO =============================
// Move o servo de um ângulo para outro com incrementos suaves
void movimentar_servo(uint16_t start, uint16_t end) {
    if (start < end) {
        // Aumenta gradualmente o duty cycle para mover o servo no sentido crescente
        for (uint16_t duty = start; duty <= end; duty += ANGLE_STEP) {
            pwm_set_gpio_level(LED_GPIO, duty); // Aplica o duty cycle no pino do servo
            sleep_ms(10); // Pequena pausa para suavizar o movimento
        }
    } else {
        // Diminui gradualmente o duty cycle para mover o servo no sentido decrescente
        for (uint16_t duty = start; duty >= end; duty -= ANGLE_STEP) {
            pwm_set_gpio_level(LED_GPIO, duty);
            sleep_ms(10);
        }
    }
}

// ============================= FUNÇÃO PRINCIPAL =============================
int main() {
    //Não se esqueça caso queira utilizar o led troque o SERVO_GPIO pelo SERVO_GPIO
    stdio_init_all(); // Inicializa a comunicação serial

    while (true) {
        pwm_setup(LED_GPIO); // Configura o PWM na GPIO do servo motor

        uint slice_num = pwm_gpio_to_slice_num(LED_GPIO); // Obtém o slice do PWM

        // ============================= POSICIONAMENTO INICIAL SERVO =============================
        // Move o servo para a posição 0° e mantém por 5 segundos
        printf("\nIntensidade media...\n");
        pwm_set_gpio_level(ANGLE_0, ANGLE_0);
        sleep_ms(5000);

        // Move suavemente o servo de 0° para 90° e mantém por 5 segundos
        printf("\nIntensidade minima...\n");
        movimentar_servo(ANGLE_0, ANGLE_90);
        sleep_ms(5000);

        // Move suavemente o servo de 90° para 180° e mantém por 5 segundos
        printf("\nIntensidade maxima...\n");
        movimentar_servo(ANGLE_90, ANGLE_180);
        sleep_ms(5000);

        

        // ============================= MOVIMENTAÇÃO CONTÍNUA =============================
        // Alterna continuamente entre 0° e 180° por 30 segundos
        printf("\nIniciando intensidade entre minima e maxima por 30s...\n");
        uint32_t start_time = to_ms_since_boot(get_absolute_time());

        while (to_ms_since_boot(get_absolute_time()) - start_time < 30000) {
            movimentar_servo(ANGLE_180, ANGLE_0); // Volta de 180° para 0°
            movimentar_servo(ANGLE_0, ANGLE_180); // Vai de 0° para 180°
        }
    }
}
