# soshell
Implementação de um Interpretador de Comandos em C.

## Enunciados utilizados para realizar o soshell
Lista de enunciados utilizados (podem ser encontrados na pasta `.enunciados`):
- [x] Ficha P4-shell
- [x] Ficha P5-builtins
- [x] Ficha P6-pipes
- [x] Ficha P7-cp-thread
- [x] Ficha P8-ls

## Compilar o soshell
Para compilar o soshell, basta executar o comando `make` na pasta raiz do projeto.

## Executar o soshell
Para executar o soshell, basta executar o comando `./soshell` na pasta raiz do projeto.

## Limpar os *object files* gerados pela compilação
Para limpar os *object files* gerados pela compilação, basta executar o comando `make clean` na pasta raiz do projeto.

## Como utilizar
Para usar o soshell, basta digitar os comandos desejados e pressionar a tecla `Enter`.

## Comandos implementados
- [x] `sair` - Sai do interpretador de comandos (soshell).
- [x] `42` - Mostra a resposta para a vida, o universo e tudo mais.
- [x] `obterinfo` - Obtém a versão atual do interpretador de comandos (soshell).
- [x] `quemsoueu` - Obtém informações sobre o utilizador atual.
- [x] `cd` - Muda o diretório atual para o diretório especificado.
- [x] `socp` - Copia um ficheiro para outro local.
- [x] `calc` - Calculadora simples.
- [x] `bits` - Calculadora de bits.
- [x] `isjpg` - Verifica se um ficheiro é uma imagem do tipo JPG.
- [x] `aviso` - Mostra um aviso utilizando *threads*.
- [x] `socpth` - Copia um ficheiro utilizando *threads*.
- [x] `maior` - Devolve qual o ficheiro com maior tamanho.
- [x] `setx` - **Adiciona permissões de execução** a um ficheiro (*user*).
- [x] `removerl` - **Remove permissões de leitura** a um ficheiro (*group* e *others*).
- [x] `sols` - Lista os ficheiros de um diretório.

**Nota importante:** O soshell também suporta comandos que estão presentes no `PATH` do sistema.

## TODO:
- [ ] Revisão de todos os comentários.
