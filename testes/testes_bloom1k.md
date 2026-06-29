# Resultados dos Testes de Performance: Filtro de Bloom vs Sem Filtro (1k Buscas)

Este arquivo .md contém os resultados dos testes realizados com **1k buscas falsas (fake)**, avaliando o impacto do **Filtro de Bloom** no tempo de execução em microssegundos sob diferentes Fatores de Carga (FC = 25%, 50% e 75%).

## Tabela Comparativa Resumida (Médias)

A tabela abaixo consolida as médias obtidas em cada cenário, evidenciando a eficiência do Filtro de Bloom.

| Filtro de Bloom | Fator de Carga (FC) | Tempo Total Médio (µs) | Taxa de Falsos Positivos | Ganho de Velocidade (Speedup) |
| :--- | :---: | :---: | :---: | :---: |
| **Sem Filtro** | 25% | 13.151,3 | N/A | Ref. |
| **Com Filtro** | 25% | 362,3 | 0,00% | **~36,3x mais rápido** |
| **Sem Filtro** | 50% | 7.155,0 | N/A | Ref. |
| **Com Filtro** | 50% | 365,3 | 0,00% | **~19,6x mais rápido** |
| **Sem Filtro** | 75% | 10.764,3 | N/A | Ref. |
| **Com Filtro** | 75% | 324,6 | 0,00% | **~33,2x mais rápido** |

---

## Detalhamento das Execuções

Abaixo estão as tabelas com os dados brutos de cada uma das 3 execuções por teste, divididos por cenário. Os tempos apresentados estão na unidade de microssegundos.

### Cenário: Sem Filtro de BLOOM

#### 1. Fator de Carga (FC) = 25% (Hash: 4001)
| Execução | Tempo Total Gasto (µs) |
| :---: | :---: |
| Run 1 | 14.141 |
| Run 2 | 12.119 |
| Run 3 | 13.194 |
| **MÉDIA** | **13.151,3** |

#### 2. Fator de Carga (FC) = 50% (Hash: 1999)
| Execução | Tempo Total Gasto (µs) |
| :---: | :---: |
| Run 1 | 7.135 |
| Run 2 | 6.811 |
| Run 3 | 7.519 |
| **MÉDIA** | **7.155,0** |

#### 3. Fator de Carga (FC) = 75% (Hash: 1361)
| Execução | Tempo Total Gasto (µs) |
| :---: | :---: |
| Run 1 | 11.609 |
| Run 2 | 12.605 |
| Run 3 | 8.079 |
| **MÉDIA** | **10.764,3** |

---

### Cenário: COM Filtro de BLOOM

#### 1. Fator de Carga (FC) = 25% (Hash: 4001)
| Execução | Tempo Total Gasto (µs) | Taxa de Falsos Positivos |
| :---: | :---: | :---: |
| Run 1 | 343 | 0,00% |
| Run 2 | 361 | 0,00% |
| Run 3 | 383 | 0,00% |
| **MÉDIA** | **362,3** | **0,00%** |

#### 2. Fator de Carga (FC) = 50% (Hash: 1999)
| Execução | Tempo Total Gasto (µs) | Taxa de Falsos Positivos |
| :---: | :---: | :---: |
| Run 1 | 418 | 0,00% |
| Run 2 | 316 | 0,00% |
| Run 3 | 362 | 0,00% |
| **MÉDIA** | **365,3** | **0,00%** |

#### 3. Fator de Carga (FC) = 75% (Hash: 1361)
| Execução | Tempo Total Gasto (µs) | Taxa de Falsos Positivos |
| :---: | :---: | :---: |
| Run 1 | 322 | 0,00% |
| Run 2 | 503 | 0,00% |
| Run 3 | 149 | 0,00% |
| **MÉDIA** | **324,6** | **0,00%** |

---

## Conclusão dos Testes (1k)
Para o conjunto de 1k usuários, a utilização do Filtro de Bloom continuou mostrando forte impacto na otimização da consulta de chaves inexistentes. Os dados apontam que o algoritmo atingiu picos de performance, sendo de **~19x a ~36x mais rápido** dependendo do fator de carga, tudo isso garantindo uma taxa de falsos positivos de exatos `0,00%`.