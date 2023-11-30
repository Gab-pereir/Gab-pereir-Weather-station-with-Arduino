# Mini Estação Meteorológica com Arduino

Bem-vindo ao repositório da Mini Estação Meteorológica utilizando Arduino. Este projeto oferece uma solução prática e acessível para o monitoramento em tempo real de condições climáticas locais. A integração do Arduino Uno com sensores específicos e um LCD 16x2 com I2C proporciona dados precisos de temperatura, umidade, pressão atmosférica e qualidade do ar, apresentados de forma clara no visor.

## Componentes Utilizados e Justificativas

1. **Arduino Uno:**
   - **Justificativa:** Escolhido pela versatilidade, acessibilidade e comunidade ativa, o Arduino Uno serve como plataforma central para a integração dos componentes.

2. **DHT22 (Sensor de Umidade e Temperatura):**
   - **Justificativa:** Essencial para medir umidade e temperatura, contribuindo para uma compreensão abrangente das condições ambientais.

3. **BMP280 (Sensor de Pressão Atmosférica):**
   - **Justificativa:** Fornecendo dados precisos de pressão atmosférica, o BMP280 é fundamental para análises meteorológicas e previsões.

4. **DSM501A (Sensor de Partículas):**
   - **Justificativa:** Contribui para a análise da qualidade do ar, contando partículas suspensas e permitindo monitoramento eficaz da poluição ambiental.

5. **LCD 16x2 com I2C:**
   - **Justificativa:** Facilita a apresentação clara e legível dos dados coletados, enriquecendo a experiência de usuário.

## Configuração do Hardware

1. **Conexão dos Sensores e LCD:**
   - Siga o esquema de conexão fornecido no arquivo de código (`main.ino`) para garantir a correta integração dos sensores e do LCD.

2. **Carregando o Código:**
   - Abra o arquivo `main.ino` na Arduino IDE e faça o upload para o Arduino Uno.

## Uso e Personalização

- Acesse os dados coletados através da interface serial da Arduino IDE ou visualize as informações diretamente no LCD. Personalize o código conforme necessário para atender a requisitos específicos.

## Contribuição

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues, propor melhorias ou adicionar novos recursos.

