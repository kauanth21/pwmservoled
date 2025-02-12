# Projeto: Controle de Servomotor e LED via PWM no RP2040

##  Descrição Geral

Este projeto implementa o controle de um **servomotor** e de um **LED** utilizando **Modulação por Largura de Pulso (PWM)** no microcontrolador **RP2040** da placa **Raspberry Pi Pico W**. O programa permite alternar entre o controle do **servo motor** e do **LED**, dependendo da configuração do código.

Por padrão, o programa está configurado para controlar o **servo motor** (GPIO 22), mas, ao modificar a definição do pino (`SERVO_GPIO` para `LED_GPIO`), pode-se visualizar o comportamento do **PWM no LED**. A movimentação ocorre em três estágios fixos e depois alterna continuamente entre **0° e 180°** por **30 segundos**.

## Objetivos

- Controlar um **servo motor** utilizando **PWM**.
- Alternativamente, controlar a **intensidade de um LED** via **PWM**.
- Simular e testar o funcionamento no **Wokwi** ou em hardware real.
- Criar uma movimentação fixa e contínua entre os ângulos do servo ou intensidades do LED.
- Implementar uma movimentação **suave** para evitar deslocamentos bruscos.

##  Componentes Utilizados

- **Microcontrolador**: RP2040 (Raspberry Pi Pico W)
- **LED**: Conectado ao GPIO **12** *(opcional)*
- **Servomotor**: Conectado ao GPIO **22**

## Funcionalidades Implementadas

### 1️ **Controle via PWM**
- O código está configurado para controlar um **servo motor**, mas pode ser modificado para um **LED**.
- O usuário pode alternar entre **servo e LED** comentando/definindo as macros `SERVO_GPIO` e `LED_GPIO` no código.

### 2️ **Controle do Servomotor via PWM**
- O servo motor é posicionado em:
  - **0°** (**500µs** de duty cycle)
  - **90°** (**1470µs** de duty cycle)
  - **180°** (**2400µs** de duty cycle)
- Movimentação **suave** entre as posições com incrementos de **5µs** e pausas de **10ms**.
- Após atingir **180°**, entra em um **loop alternando continuamente entre 0° e 180° por 30 segundos**.

### 3️ **Controle de Intensidade do LED via PWM**
- Caso o LED seja selecionado, os duty cycles equivalem a:
  - **Baixa intensidade** (equivalente a 0° do servo)
  - **Média intensidade** (equivalente a 90° do servo)
  - **Alta intensidade** (equivalente a 180° do servo)
- A intensidade do LED varia **suavemente**, utilizando os mesmos princípios aplicados ao servo motor.

### 4️ **Estrutura do Loop Principal**
- O programa começa posicionando o **servo motor ou o LED** em **três estágios fixos**.
- Após alcançar **180° ou intensidade máxima**, entra em um **loop contínuo alternando entre 0° e 180° (ou mínima e máxima intensidade) por 30 segundos**.
- Após **30 segundos de alternância**, o programa reinicia o ciclo.

## Como Executar o Projeto

### 1️ **Configuração do Ambiente**
- Instale o **VS Code** e configure o **Pico SDK**.
- Caso deseje simular o código, utilize o **Wokwi**.

### 2️ **Compilação e Execução**
- Compile o código e gere um arquivo `.uf2`.
- Transfira o arquivo para a placa **Raspberry Pi Pico W**.
- Utilize o **Serial Monitor** do VS Code para acompanhar as mensagens do programa.

### 3️ **Testes e Depuração**
- **Por padrão**, o código controla o **servo motor**.
- Para testar o **LED**, altere a definição do pino (`SERVO_GPIO` para `LED_GPIO`).
- Observe as mensagens e o comportamento do servo ou do LED.
- Após **30 segundos de alternância**, o programa reinicia automaticamente.

##  Estrutura do Projeto

- `controle_pwm.c`: Código principal do projeto.
- `diagram.json`: Arquivo de simulação para o **Wokwi**.
- `README.md`: Documentação do projeto.

## 🎥 Espaço para Vídeo de Demonstração

*(https://www.youtube.com/watch?v=fhXcu7IIgHg)*

## 👨‍💻 Autor
**Kauan Teixeira da Hora**