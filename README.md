# PEM-N2-GRUPO6

📘 README — Sistema de Controle Acadêmico em Linguagem C

1. Descrição Geral do Projeto

Este projeto consiste no desenvolvimento de um Sistema de Controle Acadêmico implementado em linguagem C, com o objetivo de consolidar o uso de estruturas fundamentais da linguagem, tais como structs, ponteiros, alocação dinâmica de memória, vetores/matrizes e modularização de funções.

O sistema modela o relacionamento entre Cursos, suas respectivas Disciplinas e os Alunos matriculados, utilizando estruturas encadeadas e alocação dinâmica para permitir que o número de elementos seja definido em tempo de execução.

Este trabalho foi desenvolvido com fins acadêmicos, visando aplicar conceitos teóricos em um contexto prático de gerenciamento de dados.


2. Objetivos do Sistema

O programa tem como principais finalidades:

Permitir o cadastro dinâmico de disciplinas associadas a um curso.

Gerenciar alunos matriculados em cada disciplina.

Validar entradas de usuário, evitando erros comuns como overflow, valores inválidos e strings inconsistentes.

Demonstrar a correta utilização de alocação e liberação de memória dinâmica.

Representar estruturas hierárquicas de dados utilizando structs compostas.


3.Compilação e Execução 

Compilar:

```
gcc N2-EQ6_main.c -o SistemaAcademico
```

Executar:

```
./SistemaAcademico
```


4.Testes Unitários 

Compilar:

```
 gcc N2-EQ6_test.c unity/unity.c -o tests
```

Executar:

```
./tests
```
