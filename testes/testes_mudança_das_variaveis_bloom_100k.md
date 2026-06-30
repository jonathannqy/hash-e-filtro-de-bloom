# Resultados dos Testes de Performance: Impacto dos Parâmetros do Filtro de Bloom (100k Usuários)

Este arquivo .md contém os resultados dos testes realizados com um volume de **100k usuários**, avaliando o impacto da variação do tamanho do vetor de bits ($m$) e da quantidade de funções hash ($k$) na eficiência do **Filtro de Bloom**. Todos os cenários foram avaliados sob um **Fator de Carga (FC) de 50%** na estrutura principal.

## Tabela Comparativa Resumida

A tabela abaixo consolida as métricas obtidas em cada configuração, evidenciando como a parametrização do Filtro de Bloom dita o tempo médio de busca e a taxa de falsos positivos.

| Cenário de Teste | Tamanho do Vetor ($m$) | Funções Hash ($k$) | Tempo Médio por Busca (µs) | Taxa de Falsos Positivos | Impacto / Observação |
| :--- | :---: | :---: | :---: | :---: | :--- |
| **1. Referência / Padrão** | $n \times 10$ | 7 | 5,0608 | 0,99% | Equilíbrio ideal entre consumo de tempo e precisão. |
| **2. Vetor Muito Pequeno** | $n \times 2$ | 7 | 370,4312 | 80,49% | Saturação do vetor degrada severamente a performance. |
| **3. Vetor Muito Grande** | $n \times 20$ | 7 | 1,2524 | 0,09% | Máxima velocidade e quase exclusão de falsos positivos. |
| **4. Poucas Funções Hash** | $n \times 10$ | 2 | 17,5883 | 3,38% | Subotimização matemática eleva falsos positivos. |
| **5. Muitas Funções Hash** | $n \times 10$ | 15 | 13,5522 | 2,62% | Sobrecarga computacional no cálculo de múltiplos hashes. |

---

## Detalhamento dos Parâmetros e Execuções

Os testes foram estruturados para isolar as duas principais variáveis do Filtro de Bloom: o espaço alocado em memória ($m$) e a quantidade de verificações independentes ($k$). O número de elementos inseridos é fixo em $n = 100.000$.

### Análise 1: Variação do Tamanho do Vetor ($m$)
Neste bloco, o número de funções hash foi mantido constante em **$k = 7$**.

#### Cenário: Vetor Reduzido ($m = n \times 2$)
* **Configuração:** Vetor excessivamente pequeno para 100k elementos.
* **Métricas Obtidas:**
  | Métrica | Valor Encontrado |
  | :--- | :---: |
  | Tempo Médio por Busca | **370,4312 µs** |
  | Taxa de Falsos Positivos | **80,49%** |
* **Análise:** Com apenas 2 bits por elemento, o Filtro de Bloom fica praticamente saturado (quase todos os bits viram `1`). Isso gera uma taxa abusiva de falsos positivos (80,49%), forçando o algoritmo a buscar quase sempre na estrutura de dados principal, anulando o propósito do filtro.

#### Cenário: Vetor Padrão ($m = n \times 10$) - Referência
* **Configuração:** Dimensionamento ideal recomendado pela literatura técnica.
* **Métricas Obtidas:**
  | Métrica | Valor Encontrado |
  | :--- | :---: |
  | Tempo Médio por Busca | **5,0608 µs** |
  | Taxa de Falsos Positivos | **0,99%** |
* **Análise:** Apresenta um ótimo balanço. A taxa de falsos positivos cai para menos de 1%, permitindo que o filtro barre 99% das buscas por chaves inexistentes instantaneamente.

#### Cenário: Vetor Expandido ($m = n \times 20$)
* **Configuração:** Superdimensionamento do vetor de bits para alta dispersão.
* **Métricas Obtidas:**
  | Métrica | Valor Encontrado |
  | :--- | :---: |
  | Tempo Médio por Busca | **1,2524 µs** |
  | Taxa de Falsos Positivos | **0,09%** |
* **Análise:** O aumento do espaço reduz as colisões a quase zero (0,09%). Como resultado, o tempo médio de busca cai para apenas 1,25 microssegundos, tornando-se a configuração mais rápida.

---

### Análise 2: Variação da Quantidade de Funções Hash ($k$)
Neste bloco, o tamanho do vetor foi mantido fixo em **$m = n \times 10$**.

#### Cenário: Poucas Funções Hash ($k = 2$)
* **Configuração:** Redução do número de hashes para diminuir o custo de processamento inicial.
* **Métricas Obtidas:**
  | Métrica | Valor Encontrado |
  | :--- | :---: |
  | Tempo Médio por Busca | **17,5883 µs** |
  | Taxa de Falsos Positivos | **3,38%** |
* **Análise:** Embora calcular apenas 2 hashes seja rápido, a falta de checagens adicionais aumenta a taxa de falsos positivos para 3,38%. O custo de pesquisar esses falsos positivos na estrutura principal supera a economia feita no cálculo dos hashes.

#### Cenário: Muitas Funções Hash ($k = 15$)
* **Configuração:** Aumento expressivo do número de hashes buscando maior rigor.
* **Métricas Obtidas:**
  | Métrica | Valor Encontrado |
  | :--- | :---: |
  | Tempo Médio por Busca | **13,5522 µs** |
  | Taxa de Falsos Positivos | **2,62%** |
* **Análise:** O uso de 15 funções hash prejudica o filtro por dois motivos: primeiro, gasta-se mais tempo computacional calculando os 15 hashes por busca; segundo, muitas funções hash preenchem o vetor de bits muito rápido, aumentando os falsos positivos em comparação com o ponto ótimo ($k=7$).

---

## Conclusão dos Testes (100k)
Os novos testes com 100k usuários expõem de forma prática a precisão das fórmulas matemáticas por trás do Filtro de Bloom:
1. **O impacto do espaço ($m$) é drástico:** Reduzir o vetor de $10n$ para $2n$ causou um aumento de **~73x no tempo médio de busca** devido à inundação de falsos positivos.
2. **Existe um ponto de equilíbrio para $k$:** O ponto ótimo teórico para um vetor de tamanho $10n$ é $k \approx 7$. Os dados provam isso, já que tanto reduzir as funções ($k=2$) quanto aumentá-las demais ($k=15$) resultou em tempos piores e maior incidência de falsos positivos.
