# Sistemas Operacionais - Alocador

Implementação de um alocador de memória personalizado, inspirado no malloc do linux. Foi feita a utilização de uma lista encadeada simulando os bits de cada blocos, os quais foram manipulados via operações de bit-wise e bit-vector

* Construtor*, que recebe o tamanho da memória a ser alocada e uma constante que diz qual a política de alocação (ver código)
* Aloca, que recebe um tamanho e retorna um ponteiro para a posição de memória deste tamanho que passe a ser utilizada.
* Verifica, que recebe um ponteiro e um offset, e verifica se a posição ponteiro+offset já foi previamente alocada, retornando o tamanho desta região alocada se sim, 0 se não
* Libera, similar à free, libera a memória “alocada” em um ponteiro. Repare que ela não recebe o tamanho da região alocada.
* Destrutor*, que libera as memórias alocadas.

## Objetivos

* Gerenciar o espaço livre no bloco.
* Atender a pedidos de novos segmentos (usando ou o algoritmo first fit ou o best fit, de acordo com um parâmetro).
* Receber segmentos liberados e atualizar a lista de espaços livres.
* Garantir que só segmentos válidos possam ser liberados e verificar se acessos a determinadas posições são válidos.
