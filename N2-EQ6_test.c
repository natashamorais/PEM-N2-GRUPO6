/*--------------------------------------------------------*
* Disciplina: Programaçao Estruturada e Modular           *
*          Prof. Carlos Veríssimo                         *
*---------------------------------------------------------*
* Objetivo do Programa: Testar um sistema academico capaz *
*                       de armazenar disciplinas e alunos,*
*                        além da manipulação desses dados.*
* Data - 26/11/2025                                       * 
* Autor: Natasha Morais Silva                             *
*---------------------------------------------------------*/
#include "unity/unity.h"
#include "N2-EQ6_func.c"


#define NUM_CURSOS 3
#define TAM_MAX_NOME 50


/* Unity setup/teardown - inicializa e limpa memória entre testes */
void setUp(void) {
    inicializarCursos();
}

void tearDown(void) {
    liberarEspacoDisciplina();
}

/* ---------- TESTS ---------- */

void test_inicializarCursos_deve_zerar_contadores_e_setar_nomes(void) {
    TEST_ASSERT_EQUAL_INT(0, cursos[0].contadorDisciplinas);
    TEST_ASSERT_EQUAL_INT(0, cursos[1].contadorDisciplinas);
    TEST_ASSERT_EQUAL_INT(0, cursos[2].contadorDisciplinas);

    TEST_ASSERT_TRUE(strstr(cursos[0].nome, "Analise") != NULL);
    TEST_ASSERT_TRUE(strstr(cursos[1].nome, "Ciencias") != NULL);
    TEST_ASSERT_TRUE(strstr(cursos[2].nome, "Arquitetura") != NULL);
}

void test_setDisciplina_deve_adicionar_disciplina_com_campos_corretos(void) {
    /* preenche buffers globais usados por setDisciplina */
    strcpy(nomeBuffer, "Matematica I");
    numeroBuffer = 10.0f;
    horarioBuffer = 60.0f;

    setDisciplina(0); /* adiciona ao curso 0 */

    TEST_ASSERT_EQUAL_INT(1, cursos[0].contadorDisciplinas);
    TEST_ASSERT_NOT_NULL(cursos[0].gradeCurricular);
    TEST_ASSERT_EQUAL_INT(10, cursos[0].gradeCurricular[0].codigo);
    TEST_ASSERT_EQUAL_STRING("Matematica I", cursos[0].gradeCurricular[0].nome);
    TEST_ASSERT_EQUAL_FLOAT(60.0f, cursos[0].gradeCurricular[0].cargaHoraria);
    TEST_ASSERT_EQUAL_INT(0, cursos[0].gradeCurricular[0].contadorAlunos);
}

void test_certificarCodigoDuplicado_deve_detectar_codigo_ja_existente(void) {
    /* Adiciona uma disciplina com codigo 20 */
    strcpy(nomeBuffer, "Fisica I");
    numeroBuffer = 20.0f;
    horarioBuffer = 40.0f;
    setDisciplina(1); /* curso 1 */

    /* tenta certificar duplicata com numeroBuffer = 20 */
    numeroBuffer = 20.0f;
    int dup = certificarCodigoDuplicado();
    TEST_ASSERT_TRUE(dup != 0); /* função retorna booleano (true) quando duplicado */
}

void test_setAluno_adiciona_aluno_em_turma_e_certifica_duplicata_matricula(void) {
    /* cria disciplina no curso 0 se nao existir */
    if (cursos[0].contadorDisciplinas == 0) {
        strcpy(nomeBuffer, "Prog I");
        numeroBuffer = 30.0f;
        horarioBuffer = 80.0f;
        setDisciplina(0);
    }

    /* cadastra aluno: setAluno usa nomeBuffer e numeroBuffer como matricula */
    strcpy(nomeBuffer, "Alice Silva");
    numeroBuffer = 123.0f; /* matricula */
    setAluno(0);

    /* verificacoes */
    TEST_ASSERT_EQUAL_INT(1, cursos[0].gradeCurricular[0].contadorAlunos);
    TEST_ASSERT_EQUAL_STRING("Alice Silva", cursos[0].gradeCurricular[0].turma[0].nome);
    TEST_ASSERT_EQUAL_INT(123, cursos[0].gradeCurricular[0].turma[0].codMatricula);

    /* agora certificar duplicata com a mesma matricula */
    numeroBuffer = 123.0f;
    int dupMat = certificarMatriculaDuplicada();
    TEST_ASSERT_TRUE(dupMat != 0);
}

void test_encontrarAluno_deve_localizar_aluno_pelo_numero_de_matricula(void) {
    /* garante que existe aluno 777 no curso 2 */
    if (cursos[2].contadorDisciplinas == 0) {
        strcpy(nomeBuffer, "Historia");
        numeroBuffer = 40.0f;
        horarioBuffer = 30.0f;
        setDisciplina(2);
    }

    strcpy(nomeBuffer, "Joao");
    numeroBuffer = 777.0f;
    setAluno(2);

    numeroBuffer = 777.0f;
    int found = encontrarAluno();
    TEST_ASSERT_TRUE(found != 0);
    TEST_ASSERT_EQUAL_INT(2, indexAluno[0]);
    TEST_ASSERT_EQUAL_INT(0, indexAluno[1]);
    TEST_ASSERT_EQUAL_INT(0, indexAluno[2]);
}

void test_verificarOverflowNumero_valida_intervalos(void) {
    TEST_ASSERT_FALSE(verificarOverflowNumero(5.0f, 0, 10)); /* dentro do intervalo -> false (sem overflow) */
    TEST_ASSERT_TRUE(verificarOverflowNumero(-1.0f, 0, 10)); /* abaixo -> true */
    TEST_ASSERT_TRUE(verificarOverflowNumero(11.0f, 0, 10)); /* acima -> true */
}

void test_verificarOverflow_detecta_string_muito_grande(void) {
    /* cria string com TAM_MAX_NOME caracteres (preenchendo com 'x') */
    char buf[TAM_MAX_NOME + 5];
    for (int i = 0; i < TAM_MAX_NOME; i++) buf[i] = 'x';
    buf[TAM_MAX_NOME] = '\0';

    int overflow = verificarOverflow(buf, TAM_MAX_NOME);
    TEST_ASSERT_TRUE(overflow != 0);
}

/* ---------- RUNNER ---------- */

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_inicializarCursos_deve_zerar_contadores_e_setar_nomes);
    RUN_TEST(test_setDisciplina_deve_adicionar_disciplina_com_campos_corretos);
    RUN_TEST(test_certificarCodigoDuplicado_deve_detectar_codigo_ja_existente);
    RUN_TEST(test_setAluno_adiciona_aluno_em_turma_e_certifica_duplicata_matricula);
    RUN_TEST(test_encontrarAluno_deve_localizar_aluno_pelo_numero_de_matricula);
    RUN_TEST(test_verificarOverflowNumero_valida_intervalos);
    RUN_TEST(test_verificarOverflow_detecta_string_muito_grande);

    return UNITY_END();
}
