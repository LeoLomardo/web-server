# Projeto: Servidor Web Simples

Este projeto é parte do curso de Ferramentas do Unix da PUC-Rio, ministrado pelo Prof. Alexandre Meslin. O objetivo é desenvolver um servidor Web simples capaz de aceitar múltiplas requisições, cada uma sendo atendida por uma thread.

## Equipe

- **Aluno:** Leo Lomardo
- **Matrícula:** 2020201

## Documentação

Para mais detalhes sobre o projeto, consulte os documentos a seguir:

- [PDF do Trabalho](caminho/para/Trabalho_2 (4).pdf)

---

## Objetivo

Desenvolver um servidor Web simples, sem capacidade de atender a requisições de programação do lado do servidor.

## Instruções de Implementação

O servidor deve aceitar as seguintes opções na linha de comando:

- `-p --port <porta>`: Número da porta do serviço
- `-l --log <filename>`: Nome completo do arquivo de log
- `-s --statistics <filename>`: Nome completo do arquivo de estatísticas
- `-b --background`: O serviço deverá rodar em background (Desafio!)
- `-r --root <path>`: Caminho da raiz do site

O sinal SIGUSR1 deve terminar o serviço. Ao término, o servidor deverá, se solicitado através de opção na linha de comando, gerar estatística contendo a quantidade de cada tipo de arquivo atendido. O site conterá apenas arquivos HTML, imagens e texto. O programa deverá exibir na console o comando completo e exato que dever ser utilizado para terminar o serviço.

Um arquivo de log deve ser gerado se configurado na linha de comando de início. O arquivo de log deverá conter o nome completo do arquivo atendido (path virtual), assim como o horário local da requisição. Uma entrada por linha. A thread que atender a requisição deverá gerar a entrada do log e enviar para um buffer (produtor). Uma outra thread dedicada a escrita no arquivo de log deverá consumir esse buffer (leitor) e gravar os dados no arquivo (consumidor).

Mensagens de erro não fatais devem ser enviadas para o arquivo de log, se configurado. Mensagens de erro fatais devem ser enviadas para o canal de erro apropriado.

## Estrutura do Projeto

Cada função deve ser escrita em um arquivo C com o seu nome, resultando em um arquivo C contendo apenas uma função. Protótipos, tipos, constantes e correlatos devem ser declarados em arquivos de cabeçalho. 

## Makefile

Um makefile deve ser criado para construir a aplicação, incluindo opções de remoções. O makefile será avaliado também.


## Entrega

Todos os arquivos-fontes (arquivo C e cabeçalhos) e o makefile devem ser carregados no site de EaD da disciplina até o prazo de entrega.

---

### Como Começar

### Pré-requisitos

- Linguagem C
- Ambiente Unix/Linux

### Instalação

1. Clone o repositório:
    ```bash
    git clone https://github.com/LeoLomardo/web-server.git
    cd web-server
    ```
2. Compile o projeto:
    ```bash
    make
    ```

### Uso

Inicie o servidor:
```bash
./servidor -p 8080 -r /caminho/para/site
 
