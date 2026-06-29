# Resultados dos Testes de Performance: Filtro de Bloom vs Sem Filtro (100k Buscas)

Este arquivo .md contém os resultados dos testes realizados com **100k buscas falsas (fake)**, avaliando o impacto do **Filtro de Bloom** no tempo de execução em microssegundos sob diferentes Fatores de Carga (FC = 25%, 50% e 75%).

## Tabela Comparativa Resumida (Médias)

A tabela abaixo consolida as médias obtidas em cada cenário, evidenciando a eficiência do Filtro de Bloom.

| Filtro de Bloom | Fator de Carga (FC) | Tempo Total Médio | Tempo Médio por Busca | Taxa de Falsos Positivos | Ganho de Velocidade (Speedup) |
| :--- | :---: | :---: | :---: | :---: | :---: |
| **Sem Filtro** | 25% | 52.628.147 | 526,9481 | N/A | Ref. |
| **Com Filtro** | 25% | 510.795 | 5,1080 | 0,99% | **~103,0x mais rápido** |
| **Sem Filtro** | 50% | 49.025.231 | 490,2523 | N/A | Ref. |
| **Com Filtro** | 50% | 535.912 | 5,3591 | 0,99% | **~91,5x mais rápido** |
| **Sem Filtro** | 75% | 47.517019 | 475,1702 | N/A | Ref. |
| **Com Filtro** | 75% | 508.165 | 5,0816 | 0,99% | **~93,5x mais rápido** |

---

## Detalhamento das Execuções

Abaixo estão as tabelas com os dados brutos de cada uma das 3 execuções por teste, divididos por cenário. Os tempos apresentados estão na unidade de microssegundos (µs).

### Cenário: Sem Filtro de BLOOM

#### 1. Fator de Carga (FC) = 25%
| Execução | Tempo Total Gasto | Tempo Médio por Busca |
| :---: | :---: | :---: |
| Run 1 | 52.368.080 | 523,6808 |
| Run 2 | 52.743.100 | 527,4310 |
| Run 3 | 52.773.262 | 527,7326 |
| **MÉDIA** | **52.628.147** | **526,9481** |

#### 2. Fator de Carga (FC) = 50%
| Execução | Tempo Total Gasto | Tempo Médio por Busca |
| :---: | :---: | :---: |
| Run 1 | 48.909.691 | 489,0969 |
| Run 2 | 48.730.357 | 487,3036 |
| Run 3 | 49.435.646 | 494,3565 |
| **MÉDIA** | **49.025.231** | **490,2523** |

#### 3. Fator de Carga (FC) = 75%
| Execução | Tempo Total Gasto | Tempo Médio por Busca |
| :---: | :---: | :---: |
| Run 1 | 47.236.987 | 472,3699 |
| Run 2 | 47.531.076 | 475,3108 |
| Run 3 | 47.782.995 | 477,8299 |
| **MÉDIA** | **47.517.019** | **475,1702** |

---

### Cenário: COM Filtro de BLOOM

#### 1. Fator de Carga (FC) = 25%
| Execução | Tempo Total Gasto | Tempo Médio por Busca | Taxa de Falsos Positivos |
| :---: | :---: | :---: | :---: |
| Run 1 | 527.537 | 5,2754 | 0,99% |
| Run 2 | 508.037 | 5,0804 | 0,99% |
| Run 3 | 496.811 | 4,9681 | 0,99% |
| **MÉDIA** | **510.795** | **5,1080** | **0,99%** |

#### 2. Fator de Carga (FC) = 50%
| Execução | Tempo Total Gasto | Tempo Médio por Busca | Taxa de Falsos Positivos |
| :---: | :---: | :---: | :---: |
| Run 1 | 535.166 | 5,3512 | 0,99% |
| Run 2 | 534.583 | 5,3458 | 0,99% |
| Run 3 | 537.986 | 5,3799 | 0,99% |
| **MÉDIA** | **535.912** | **5,3591** | **0,99%** |

#### 3. Fator de Carga (FC) = 75%
| Execução | Tempo Total Gasto | Tempo Médio por Busca | Taxa de Falsos Positivos |
| :---: | :---: | :---: | :---: |
| Run 1 | 514.908 | 5,1491 | 0,99% |
| Run 2 | 500.724 | 5,0072 | 0,99% |
| Run 3 | 508.863 | 5,0886 | 0,99% |
| **MÉDIA** | **508.165** | **5,0816** | **0,99%** |

---

## Conclusão dos Testes (100k)
A utilização do Filtro de Bloom reduziu drasticamente o tempo de busca para elementos inexistentes (fake). O tempo médio por busca caiu de patamares na casa de **~470 a 520 unidades de tempo** para meros **~5 unidades de tempo**, o que representa uma otimização média superior a **90x (ou 9000%)** em todos os fatores de carga testados, mantendo uma taxa controlada e estável de falsos positivos de apenas `0,99%`.
