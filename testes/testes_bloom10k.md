# Resultados dos Testes de Performance: Filtro de Bloom vs Sem Filtro (10k Buscas)

Este arquivo .md contém os resultados dos testes realizados com **10k buscas falsas (fake)**, avaliando o impacto do **Filtro de Bloom** no tempo de execução em microssegundos sob diferentes Fatores de Carga (FC = 25%, 50% e 75%).

## Tabela Comparativa Resumida (Médias)

A tabela abaixo consolida as médias obtidas em cada cenário, evidenciando a eficiência do Filtro de Bloom.


| Filtro de Bloom | Fator de Carga (FC) | Tempo Total Médio (µs) | Taxa de Falsos Positivos | Ganho de Velocidade (Speedup) |
| :--- | :---: | :---: | :---: | :---: |
| **Sem Filtro** | 25% | 543.040,0 | N/A | Ref. |
| **Com Filtro** | 25% | 2.530,6 | 0,00% | **~214,6x mais rápido** |
| **Sem Filtro** | 50% | 420.314,0 | N/A | Ref. |
| **Com Filtro** | 50% | 2.546,0 | 0,00% | **~165,1x mais rápido** |
| **Sem Filtro** | 75% | 444.523,0 | N/A | Ref. |
| **Com Filtro** | 75% | 2.424,0 | 0,00% | **~183,4x mais rápido** |

---

## Detalhamento das Execuções

Abaixo estão as tabelas com os dados brutos de cada uma das 3 execuções por teste, divididos por cenário. Os tempos apresentados estão na unidade de microssegundos (µs).

### Cenário: Sem Filtro de BLOOM

#### 1. Fator de Carga (FC) = 25% (Hash: 40009)
| Execução | Tempo Total Gasto (µs) |
| :---: | :---: |
| Run 1 | 547.513 |
| Run 2 | 538.130 |
| Run 3 | 543.477 |
| **MÉDIA** | **543.040,0** |

#### 2. Fator de Carga (FC) = 50% (Hash: 20011)
| Execução | Tempo Total Gasto (µs) |
| :---: | :---: |
| Run 1 | 413.860 |
| Run 2 | 424.012 |
| Run 3 | 423.070 |
| **MÉDIA** | **420.314,0** |

#### 3. Fator de Carga (FC) = 75% (Hash: 13337)
| Execução | Tempo Total Gasto (µs) |
| :---: | :---: |
| Run 1 | 444.204 |
| Run 2 | 441.835 |
| Run 3 | 447.530 |
| **MÉDIA** | **444.523,0** |

---

### Cenário: COM Filtro de BLOOM

#### 1. Fator de Carga (FC) = 25% (Hash: 40009)
| Execução | Tempo Total Gasto (µs) | Taxa de Falsos Positivos |
| :---: | :---: | :---: |
| Run 1 | 2.336 | 0,00% |
| Run 2 | 2.503 | 0,00% |
| Run 3 | 2.753 | 0,00% |
| **MÉDIA** | **2.530,6** | **0,00%** |

#### 2. Fator de Carga (FC) = 50% (Hash: 20011)
| Execução | Tempo Total Gasto (µs) | Taxa de Falsos Positivos |
| :---: | :---: | :---: |
| Run 1 | 2.562 | 0,00% |
| Run 2 | 2.486 | 0,00% |
| Run 3 | 2.590 | 0,00% |
| **MÉDIA** | **2.546,0** | **0,00%** |

#### 3. Fator de Carga (FC) = 75% (Hash: 13337)
| Execução | Tempo Total Gasto (µs) | Taxa de Falsos Positivos |
| :---: | :---: | :---: |
| Run 1 | 2.379 | 0,00% |
| Run 2 | 2.385 | 0,00% |
| Run 3 | 2.508 | 0,00% |
| **MÉDIA** | **2.424,0** | **0,00%** |

---

## Conclusão dos Testes (10k)
O aumento do volume de dados para 10.000 buscas evidencia ainda mais o poder do Filtro de Bloom em evitar consultas desnecessárias a elementos inexistentes. Enquanto as abordagens sem filtro consumiram em média entre 420 mil e 543 mil microssegundos, o Filtro de Bloom derrubou esse tempo para cerca de 2.400 a 2.500 microssegundos. 

O algoritmo provou ser entre **~165x e ~214x mais rápido**, mantendo uma precisão perfeita com `0,00%` de falsos positivos em todas as execuções e fatores de carga testados.