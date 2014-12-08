Sistemas Operacionais
======================

Introdução
-----------

Neste repositório temos vários exemplos de programas que utilizam primitivas de comunicação interprocesso para realizar uma tarefa.
A utilização de threads também é abordada.

Compilação
----------
Os programas podem ser compilados facilmente utilizando o gcc
```
  gcc <fonte.c> -o <nome do executável>
```

Os programas que utilizam a API Pthreads, necessitam de uma flag especial de ligação:

```
  gcc <fonte.c> -o <nome do executável> -lpthread
```
