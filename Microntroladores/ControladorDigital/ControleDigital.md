# Controle Digital

Biblioteca escrita em linguagem C, utilizando TDAs (Tipo da Dados Abstratos) para implementação de controladores clássicos em equações a diferenças.
Como é escrita em linguagem C deve rodar em qualquer microcontrolador com programação em C ou C++.
A biblioteca dá suporte à implementação de controladores digitais (no domínio Z), mas também realiza de forma automática a transformada do controlador do domínio S para o domínio Z.

Até o momento já foi implementado:

*Funções de Transferência de Primeira Ordem:
-- Permite a implementação direta de controladores como o PI e de filtros de primeira ordem.

*Funções de Transferência de Segunda Ordem;
-- Permite a implementação direta de controladores como o PID e de filtros de segunda ordem.

*Controlador PI:
-- Permite a implementação de um PI projetado em S. Sendo necessário apenas a constante de tempo, o ganho proporcional e estipular uma frequência de amostragem.

*Conversão para ponto flutuante do valor oriundo de um conversor analógico-digital:
-- Basta passar a resolução e o fundo de escala (máx. que pode ser lido, e.g. 3V3 ou 5V) da porta do microcontrolador.

*Conversão da saída do controlador para PWM.
-- Converte a saída do controlador em um inteiro para ser passado ao registrador/função que aciona a porta PWM do microcontrolador.
