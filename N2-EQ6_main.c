/*--------------------------------------------------------*
* Disciplina: Programaçao Estruturada e Modular           *
*          Prof. Carlos Veríssimo                         *
*---------------------------------------------------------*
* Objetivo do Programa: Simular um sistema academico capaz*
*                       de armazenar disciplinas e alunos,*
*                        além da manipulação desses dados.*
* Data - 23/11/2025                                       * 
* Autor: Guilherme Rizzo Morais                           *
* Autor: Iginio Blasotti Frassei                          *
*---------------------------------------------------------*/


#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "N2-EQ6_func.c"




int main() {
    inicializarCursos();
    apresentarMenu();
    liberarEspacoDisciplina();
}
