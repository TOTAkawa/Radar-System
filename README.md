
# Radar ESP32 com Motor de Passo e Sensor Ultrassônico

## 📌 Descrição
Projeto de radar utilizando **ESP32**, **motor de passo 28BYJ-48 com driver ULN2003** (na montagem real), **sensor ultrassônico HC-SR04** e **display LCD 16x2 com I2C**.  
Para simulação no Wokwi, foram usados componentes genéricos (**A4988 + motor bipolar**) porque o Wokwi não possui o 28BYJ-48 nem o ULN2003.

## 🔧 Componentes (Montagem Real)
- ESP32 DevKit V1
- Motor de passo **28BYJ-48**
- Driver **ULN2003**
- Sensor ultrassônico **HC-SR04**
- Display LCD 16x2 com módulo I2C
- Fonte 9–12V para o motor (hardware real)

## 🖥️ Componentes (Simulação Wokwi)
- ESP32 DevKit V1
- Driver A4988
- Motor de passo bipolar genérico
- Sensor HC-SR04
- LCD 16x2 I2C

## ▶️ Como rodar no Wokwi
1. Abra o link da simulação: **[https://wokwi.com/projects/452428536460495873]**
2. Carregue o código `RadarESP32.ino`.
3. Confira o arquivo `diagram.json` para conexões.

## 🛠 Como rodar na vida real
- Ajuste alimentação do motor (VMOT = 9–12V).
- Use divisor de tensão no ECHO do HC-SR04 (para 3,3V).
- Ajuste corrente do ULN2003 (não precisa regulagem como A4988).
- Ligue as bobinas do 28BYJ-48 conforme a sequência do ULN2003.

