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

Após o git clone, deve entrar no diretório gerado e chamar o Make dessa forma:

```bash
make
```

Para rodar o código:
```bash
make run
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


* É esperado a digitação de números inteiros correspondentes às opções exibidas na tela.  

* Quando o sistema solicitar a inserção ou busca manual de um usuário (Opções 1, 2 e 3), deve-se digitar uma única  
string (texto) sem espaços.

* Os lotes serão gerados na pasta "data" do projeto e o script cria strings de 11 caracteres contendo exatamente  
8 letras minúsculas aleatórias (de 'a' a 'z') seguidas por 3 números aleatórios (de '0' a '9'). Por exemplo 'jonathan676'.  

* O sistema está programado para buscar automaticamente nomes de arquivo padronizados ao utilizar as opções de lote:  
usuarios1k.txt, usuarios10k.txt e usuarios100k.txt.  

* Caso queira voltar uma opção por ter se confundido, é necessário fechar o programa e realizar os processos novamente.

* O tamanho da tabela hash desse sistema só pode ser alterado no arquivo "hash.c" em "TAMANHO_TABELA". Nele, há também os Fatores  
de Carga ideais referentes a quantidade de "usuários" que serão inseridos. 

* O tamanho do filtro de bloom desse sistema só pode ser alterado no arquivo "main.c" em "criar_filtro(100000)". 

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

#### 1) Inserção única de usuário

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