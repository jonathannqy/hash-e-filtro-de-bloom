# Hash e Filtro de Bloom
Este repositório serve como guia para executar o "Sistema de Consulta Eficiente com Tabela Hash e
Filtro de Bloom"

## Integrantes
- Breno Alves de Almeida
- Francisco Jonathan Aquino Souza
- Gustavo Patrício Batista
- Otávio Linhares Batista

### (Recomendo que use o VS Code para usar, compilar e depurar o sistema)

## Instruções de compilação

O repositório tem um arquio chamado "Makefile" que ajuda a compilar o sistema.  
(para saber mais sobre: [Make](https://www.gnu.org/software/make/))

O Makefile deve compilar em Ubuntu, Mint e Windows.

### Compilação

Após o git clone, deve entrar no diretório gerado e chamar o Make dessa fomra:

```bash
make
```

### Compilação (Debug)

Dentro do diretório, digite no terminal:

```bash
Linux:
        gdb exec

Windows:
        gdb exec.exe
```


### Formato de Entrada



### Exemplos de Execução

Quando entrar no sistema, aparecerá estas opções:
```bash
    --- Sistema de Verificação de Cadastro ---
    [1] Inserir novo usuário no hash e no bloom
    [2] Consultar usuário (com bloom)
    [3] Consultar usuário (sem bloom)
    [4] Exibir estatísticas
    [5] Inserir lote na tabela hash e no bloom
    [6] Gerar lote (Arquivo)
    [7] Quantidade de registrados na tabela hash
    [8] Teste de busca cronometrado (sem bloom)
    [9] Teste de busca cronometrado (com bloom)
    [0] Sair
```

#### Exemplos de execuções

##### 1) Inserção única de usuário
    * No terminal, digite: '1'.  
    * Após isso, coloque um nome qualquer, por exemplo "jonathan676"  
    * Pronto, o nome que foi digitado já está inserido na Hash e no Filtro de Bloom.

#### 2) Inserção em lote
    * É necessário gerar os lotes. Para isso, no terminal, digite: '6'.  
    * Escolha qual o tamanho do lote que você deseja gerar.
    * Após isso, escolha a opção '5' e selecione a opção que seja referente ao lote que foi gerado anteriormente.  
    (O arquivo será criado na pasta "data")

#### 3) Inserção em lote e testes de buscas cronometrados
    * Repita o processo do exemplo de execulção 2). 
    * Selecione a opção '8', o lote que deseja testar.
    * Selecione a opção '9', o lote que deseja testar.
    * Note a diferença dos resultados gerados sem e com o filtro de bloom.

#### 4) Inserção em lote e busca única de usuário
    * Repita o processo do exemplod e execução 2).  
    * Insira algum novo usuário na hash e na bloom pela opção '1'.  
    * Selecione a opção '2' e digite o usuário que deseja buscar, pode ser o que acabou de ser inserido   
    ou algum dos que foram gerados no lote. Para isso, será necessário entrar na pasta "data" e abrir o lote pelo  
    Explorador de Arquivos ou pelo próprio VS Code.
    * Tente consulta um usuário que não existe.  
    * Selecione '4' para exibir as estatísticas.