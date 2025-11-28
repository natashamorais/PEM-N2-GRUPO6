/*--------------------------------------------------------*
* Disciplina: Programaçao Estruturada e Modular           *
*          Prof. Carlos Veríssimo                         *
*---------------------------------------------------------*
* Objetivo do Programa: Simular um sistema academico capaz*
*                       de armazenar disciplinas e alunos,*
*                        além da manipulação desses dados.*
* Data - 23/11/2025                                       * 
* Autor: Guilherme Rizzo Morais                           *
*---------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define TAM_MAX_NOME 50
#define NUM_CURSOS 3
#define TAM_MAX_TURMA 50

typedef struct {
    char nome[TAM_MAX_NOME];
    int codigoCurso;
    int codMatricula;
    float mediaFinal;
    bool notasInformadas;
    bool statusAprovado;
} Aluno;

typedef struct {
    char nome[TAM_MAX_NOME];
    int codigo;
    float cargaHoraria;
    Aluno *turma;
    int contadorAlunos;
} Disciplina;

typedef struct {
    char nome[TAM_MAX_NOME];
    Disciplina *gradeCurricular;
    int contadorDisciplinas;
} Curso;

Curso cursos[NUM_CURSOS];

int resposta = 1;
bool resultadoInput;
char nomeBuffer[50];
float numeroBuffer;
float numeroBuffer2;
float horarioBuffer;
int indexAluno[3];
int indexDisciplina[2];

void alocarEspacoDisciplina(int indexCurso);
void alocarEspacoAluno(int indexCurso);
void liberarEspacoDisciplina();

void exibirMensagem(char *mensagem);
bool saoApenasEspacosVazios(char *string, int tamanho);
bool verificarOverflow(char *string, int tamanhoMax);
bool verificarOverflowNumero(float numero, int tamanhoMin, int tamanhoMax);
void inicializarCursos();
void suspenderExecucao();

void cadastrarDisciplinas();
bool receberNome(char *mensagemInicial);
bool receberCodigo();
bool verificarAlunosCadastrados(int indexCurso);
bool receberCargaHrDisciplina();
bool certificarCodigoDuplicado();
void setDisciplina(int indexCurso);
bool encontrarDisciplinas(int indexCurso);

void cadastarAluno();
bool receberCodigoMatricula();
void setAluno(int IndexCurso);
bool certificarMatriculaDuplicada();


bool receberCodigoMatriculaConsulta();
bool encontrarAluno();
void inserirNotas();

void gerarBoletim();

void listarAlunosAproRepro();
void listarDisciplinas();
bool receberCodigoConsulta();
void consultarAprovadosDisciplina();

bool receberResposta(int numeroMaxOpcoes);
void apresentarMenu();


int main() {
    inicializarCursos();
    apresentarMenu();
    liberarEspacoDisciplina();
}

/*--------------------> CONTAINER DE ALOCAÇÃO DE MEMORIA*/
void alocarEspacoDisciplina(int indexCurso) {
    if(cursos[indexCurso].contadorDisciplinas == 0) {
        cursos[indexCurso].gradeCurricular = malloc(sizeof(Disciplina));
        cursos[indexCurso].contadorDisciplinas++;
    }
    else {
        cursos[indexCurso].contadorDisciplinas++;
        cursos[indexCurso].gradeCurricular = realloc(
            cursos[indexCurso].gradeCurricular,
            (cursos[indexCurso].contadorDisciplinas) * sizeof(Disciplina)
        );
    }
}

void alocarEspacoAluno(int indexCurso) {
    if(cursos[indexCurso].contadorDisciplinas == 0) {
        return;
    }
    else {
        for(int i = 0; i < cursos[indexCurso].contadorDisciplinas; i++) {
            if(cursos[indexCurso].gradeCurricular[i].contadorAlunos == 0) {
                cursos[indexCurso].gradeCurricular[i].turma = malloc(sizeof(Aluno));
                cursos[indexCurso].gradeCurricular[i].contadorAlunos++;
            }
            else {
                cursos[indexCurso].gradeCurricular[i].contadorAlunos++;
                cursos[indexCurso].gradeCurricular[i].turma = realloc(
                    cursos[indexCurso].gradeCurricular[i].turma,
                    (cursos[indexCurso].gradeCurricular[i].contadorAlunos) * sizeof(Aluno)
                );
            }
        }
    }
}

void liberarEspacoDisciplina() {
    for(int i = 0; i < NUM_CURSOS; i++) {
        for(int j = 0; j < cursos[i].contadorDisciplinas; j++) {
            free(cursos[i].gradeCurricular[j].turma);
        }
        free(cursos[i].gradeCurricular);
    }
}

/*--------------------> CONTAINER DE VALIDAÇÃO DE INPUT - GERAL*/
void exibirMensagem(char *mensagem) {
    printf("\n\n \033[1;31m===> Erro. %s.\033[0m\n\n", mensagem);
}

bool saoApenasEspacosVazios(char *string, int tamanho) {
    int somador = 0;
    for(int i = 0; string[i] != '\0'; i++) {
        if(*(string + i) == ' ') {
            somador++;
        }
    }

    if(somador == tamanho - 1) {
        exibirMensagem("Este nome nao faz sentido"); 
        return true;
    }
    else return false;
}

bool verificarOverflow(char *string, int tamanhoMax) {
    int somador = 0;
    for(int i = 0; *(string + i) != '\0'; i++) {
        somador++;
    }

    if(somador >= tamanhoMax - 1) {
        exibirMensagem("Voce ultrapassou o limite de caracteres"); 
        while(getchar() != '\n');
        return true;
    }
    else return false;
}

bool verificarOverflowNumero(float numero, int tamanhoMin, int tamanhoMax) {
    if((numero < tamanhoMin) || (numero > tamanhoMax)) {
        exibirMensagem("Esse numero nao pode ser usado");
        return true;
    }
    else return false;
}

void suspenderExecucao() {
    printf("\n| Pressione qualquer tecla para continuar\n");
    getchar();
}

/*--------------------> CONTAINER DE FUNÇOES PARA INPUT - GERAL */

bool receberNome(char *mensagemInicial) {
    printf("%s\n", mensagemInicial);
    fgets(&nomeBuffer[0], sizeof(nomeBuffer), stdin);
    nomeBuffer[strcspn(nomeBuffer, "\n")] = '\0';
    if((saoApenasEspacosVazios(nomeBuffer, strlen(nomeBuffer))) || verificarOverflow(nomeBuffer, TAM_MAX_NOME)) {
        return false;
    }
    else return true;
}

bool receberCodigo() {
    printf("\nDigite o codigo da disciplina(o codigo varia de 0 a 100): \n");
    scanf("%f", &numeroBuffer);
    while(getchar() != '\n');
    if((verificarOverflowNumero(numeroBuffer, 0, 100)) || (certificarCodigoDuplicado())) {
        return false;
    }
    else {
        if((int)numeroBuffer == 0) {
            exibirMensagem("Esse numero nao pode ser usado");
            return false;
        }
        else return true;
    }
}

/*--------------------> CONTAINER DE DISCIPLINAS */

void inicializarCursos() {
    for(int i = 0; i < NUM_CURSOS; i++) {
        cursos[i].gradeCurricular = NULL;
        cursos[i].contadorDisciplinas = 0;
    }
    strcpy(cursos[0].nome, "Analise e Desenvolvimento de Sistemas");
    strcpy(cursos[1].nome, "Ciencias Economicas");
    strcpy(cursos[2].nome, "Arquitetura e Urbanismo");
}

void cadastrarDisciplinas() {
    int cursoIndex;
    printf("\n\n===>> CADASTRO DE DISCIPLINAS\nSelecione um curso para adicionar a disciplina ou selecione 0 para retornar ao menu principal:\n\n");
    for(int i = 0; i < NUM_CURSOS; i++) {
        printf("|--> %s: Selecione %d\n", cursos[i].nome, i + 1);
    }
    resultadoInput = false;
    while(!resultadoInput) {
        if(receberResposta(3)) {
            if(resposta == 0) {
                return;
            }
            else {
                cursoIndex = resposta - 1;
                resultadoInput = !verificarAlunosCadastrados(cursoIndex);
            }
        }

    }

    resultadoInput = false;
    while(!resultadoInput) {
        resultadoInput = receberNome("Digite o nome da disciplina: ");
    }
    resultadoInput = false;
    while(!resultadoInput) {
        resultadoInput = receberCodigo();
    }
    resultadoInput = false;
    while(!resultadoInput) {
        resultadoInput = receberCargaHrDisciplina();
    }

    setDisciplina(cursoIndex);
}

bool receberCargaHrDisciplina() {
    printf("\nDigite a carga horaria da disciplina:\n(Em horas. Nao e necessario adicionar sufixos para indicar horas e minutos) \n");
    scanf("%f", &horarioBuffer);
    while(getchar() != '\n');
    if(verificarOverflowNumero(horarioBuffer, 0, 1000)) {
        return false;
    }
    else return true;

}

void setDisciplina(int indexCurso) {
    alocarEspacoDisciplina(indexCurso);
    int indexGradeCurricular = (cursos[indexCurso].contadorDisciplinas) - 1;
    //obs: A variavel apenas foi criada para abreviar a menção dos dados das disciplinas
    strcpy(cursos[indexCurso].gradeCurricular[indexGradeCurricular].nome, nomeBuffer);
    cursos[indexCurso].gradeCurricular[indexGradeCurricular].codigo = (int)numeroBuffer;
    cursos[indexCurso].gradeCurricular[indexGradeCurricular].cargaHoraria = horarioBuffer;
    cursos[indexCurso].gradeCurricular[indexGradeCurricular].contadorAlunos = 0;
    cursos[indexCurso].gradeCurricular[indexGradeCurricular].turma = NULL;
    printf("\n===> A Disciplina: %s foi adicionada com sucesso.\n", nomeBuffer);
}

bool certificarCodigoDuplicado() {
    int i = 0;
    int j = 0;
    bool sentinela = false;

    while((i < NUM_CURSOS) && (!sentinela)) {
        if(cursos[i].contadorDisciplinas > 0) {
            while((j < cursos[i].contadorDisciplinas) && (!sentinela)) {
                if((cursos[i].gradeCurricular[j].codigo) == (int)numeroBuffer) {
                    sentinela = true;
                }
                j++;
            }
        }
        i++;
    }
    if(sentinela) {
        exibirMensagem("Esse codigo esta sendo utilizado por outra disciplina");
        return true;
    }
    else return false;
}

bool encontrarDisciplinas(int indexCurso) {
    if(cursos[indexCurso].contadorDisciplinas > 0) {
        return true;
    }
    else {
        exibirMensagem("Nao e possivel adicionar alunos se esse curso ainda nao possui disciplinas");
        return false;
    }
}

/*--------------------> CONTAINER DO ALUNO*/

void cadastarAluno() {
    int cursoIndex;
    printf("\n\n===>> CADASTRO DE ALUNO\nSelecione o curso em que esta cadastrado ou selecione 0 para retornar ao menu principal:\n\n");
    for(int i = 0; i < NUM_CURSOS; i++) {
        printf("|--> %s: Selecione %d\n", cursos[i].nome, i + 1);
    }

    resultadoInput = false;
    while(!resultadoInput) {
        if(receberResposta(3)) {
            if(resposta == 0) {
                return;
            }
            else {
                cursoIndex = resposta - 1;
                resultadoInput = encontrarDisciplinas(cursoIndex);
            }
        }

    }

    resultadoInput = false;
    while(!resultadoInput) {
        resultadoInput = receberNome("Digite o nome do aluno: ");
    }
    resultadoInput = false;
    while(!resultadoInput) {
        resultadoInput = receberCodigoMatricula();
    } 

    setAluno(cursoIndex);
}

bool receberCodigoMatricula() {
    printf("\nDigite o numero de matricula do aluno(o numero varia de 1 a 1000):\n");
    scanf("%f", &numeroBuffer);
    while(getchar() != '\n');
    if((verificarOverflowNumero(numeroBuffer, 0, 1000)) || (certificarMatriculaDuplicada())) {
        return false;
    }
    else {
        if((int)numeroBuffer == 0) {
            exibirMensagem("Esse numero nao pode ser usado");
            return false;
        }
        else return true;
    }
}

void setAluno(int IndexCurso) {
    alocarEspacoAluno(IndexCurso);
    for(int i = 0; i < cursos[IndexCurso].contadorDisciplinas; i++) {
        int indexTurma = (cursos[IndexCurso].gradeCurricular[i].contadorAlunos) - 1;
        strcpy(cursos[IndexCurso].gradeCurricular[i].turma[indexTurma].nome, nomeBuffer);
        cursos[IndexCurso].gradeCurricular[i].turma[indexTurma].codMatricula = (int)numeroBuffer;
        cursos[IndexCurso].gradeCurricular[i].turma[indexTurma].codigoCurso = IndexCurso;
    }
    printf("\n===> O(A) aluno(a): %s foi cadastrado(a) com sucesso em %s.", nomeBuffer, cursos[IndexCurso].nome);
}

bool certificarMatriculaDuplicada() {
    int i = 0;
    int j = 0;
    int k = 0;
    bool sentinela = false;
    while((i < NUM_CURSOS) && (!sentinela)) {
        while((j < cursos[i].contadorDisciplinas) && (!sentinela)) {
            while((k < cursos[i].gradeCurricular[j].contadorAlunos) && (!sentinela)) {
                if(cursos[i].gradeCurricular[j].turma[k].codMatricula == (int)numeroBuffer) {
                    sentinela = true;
                }
                k++;
            }
            j++;
        }
        i++;
    }
    if(sentinela) {
        exibirMensagem("Esse codigo de matricula ja existe");
        return true;
    }
    else return false;
}

bool verificarAlunosCadastrados(int indexCurso) {
    int j = 0;
    bool sentinela = false;

    while((j < cursos[indexCurso].contadorDisciplinas) && (!sentinela)) {
        if(cursos[indexCurso].gradeCurricular[j].contadorAlunos > 0) {
            sentinela = true;
        }
        j++;
    }
    if(sentinela) {
        exibirMensagem("Esse curso ja possue alunos cadastrados (leia as regras de uso para mais detalhes)");
        return true;
    }
    else return false;
    
}

/*--------------------> CONTAINER DE NOTAS */

void inserirNotas() {
    printf("\n\n===>> INSERCAO DE NOTAS");
    resultadoInput = false;
    while(!resultadoInput) {
        resultadoInput = receberCodigoMatriculaConsulta();
        resultadoInput = encontrarAluno();
        if((int)numeroBuffer == 0) {
            return; 
        }
    }

    Aluno *aluno = &cursos[indexAluno[0]].gradeCurricular[indexAluno[1]].turma[indexAluno[2]];

    printf("===>> Aluno(a) encontrado(a): %s, matriculado(a) em: %s\n", 
        aluno->nome,
        cursos[aluno->codigoCurso].nome
    );

    int cursoIndex = indexAluno[0];
    int matricula = cursos[cursoIndex].gradeCurricular[indexAluno[1]].turma[indexAluno[2]].codMatricula;

    for(int j = 0; j < cursos[cursoIndex].contadorDisciplinas; j++) {
        for(int k = 0; k < cursos[cursoIndex].gradeCurricular[j].contadorAlunos; k++) {
            Aluno *aluno = &cursos[cursoIndex].gradeCurricular[j].turma[k];
            if(aluno->codMatricula == matricula) {
                printf("\nDisciplina: %s\n", cursos[cursoIndex].gradeCurricular[j].nome);
                printf("Digite a nota do primeiro e segundo semestre (separe por espaco): \n");
                scanf("%f%f", &numeroBuffer, &numeroBuffer2);
                while(getchar() != '\n');

                while((verificarOverflowNumero(numeroBuffer, 0, 10)) || (verificarOverflowNumero(numeroBuffer2, 0, 10))) {
                    printf("Digite a nota do primeiro e segundo semestre (separe por espaco): \n");
                    scanf("%f%f", &numeroBuffer, &numeroBuffer2);
                }

                aluno->mediaFinal = (numeroBuffer + numeroBuffer2) / 2.0f;
                aluno->notasInformadas = true;
                aluno->statusAprovado = (aluno->mediaFinal >= 6.0f);
            }
        }
    }

    printf("\n===>> As notas foram registradas com sucesso. Status de aprovacao do(a) aluno(a) disponivel.\n");
}

bool receberCodigoMatriculaConsulta() {
    printf("\nDigite o numero de matricula do aluno ou selecione 0 para retornar ao menu principal:\n");
    scanf("%f", &numeroBuffer);
    while(getchar() != '\n');
    if(verificarOverflowNumero(numeroBuffer, -1, 1000)) {
        return false;
    }
    else {
        return true;
    }
}

bool encontrarAluno() {
    int i = 0;
    int j = 0;
    int k = 0;
    bool sentinela = false;
    while((i < NUM_CURSOS) && (!sentinela)) {
        while((j < cursos[i].contadorDisciplinas) && (!sentinela)) {
            while((k < cursos[i].gradeCurricular[j].contadorAlunos) && (!sentinela)) {
                if(cursos[i].gradeCurricular[j].turma[k].codMatricula == (int)numeroBuffer) {
                    indexAluno[0] = i;
                    indexAluno[1] = j;
                    indexAluno[2] = k;
                    sentinela = true;
                }
                k++;
            }
            j++;
        }
        i++;
    }

    if(!sentinela) {
        if((int)numeroBuffer == 0) {
            return false;
        }
        else {
            exibirMensagem("O aluno nao foi encontrado");
        return false;
        }
    }
    else {
        return true;
    }
}

/*--------------------> CONTAINER DE GERAÇÃO DE BOLETIM */

void gerarBoletim() {
    printf("\n\n===>> GERAR BOLETIM");
    resultadoInput = false;
    while(!resultadoInput) {
        resultadoInput = receberCodigoMatriculaConsulta();
        resultadoInput = encontrarAluno();
        if((int)numeroBuffer == 0) {
            return;
        }
    }

    Aluno *aluno = &cursos[indexAluno[0]].gradeCurricular[indexAluno[1]].turma[indexAluno[2]];

    printf("\n=========================================================================================================================\n");
    printf("---> NOME: %s\nMATRICULA: %d\nCURSO: %s",
        aluno->nome,
        aluno->codMatricula,
        cursos[aluno->codigoCurso].nome
    );
    printf("\n=========================================================================================================================\n");

    int cursoIndex = indexAluno[0];
    int matricula = cursos[cursoIndex].gradeCurricular[indexAluno[1]].turma[indexAluno[2]].codMatricula;

    for(int j = 0; j < cursos[cursoIndex].contadorDisciplinas; j++) {
        for(int k = 0; k < cursos[cursoIndex].gradeCurricular[j].contadorAlunos; k++) {
            Aluno *aluno = &cursos[cursoIndex].gradeCurricular[j].turma[k];
            if(aluno->codMatricula == matricula) {

                if(aluno->notasInformadas) {
                    char statusAprovado[13];
                    if(aluno->statusAprovado) {
                        strcpy(statusAprovado, "Aprovado(a)");
                    }
                    else {
                        strcpy(statusAprovado, "Reprovado(a)");
                    }

                    printf("\n===> Disciplina: %s\n", cursos[cursoIndex].gradeCurricular[j].nome);
                    printf("MEDIA FINAL: %.2f\nSTATUS: %s", 
                    aluno->mediaFinal,
                    statusAprovado
                    );
                }
                else {
                    printf("\n===> Disciplina: %s\n", cursos[cursoIndex].gradeCurricular[j].nome);
                    printf("MEDIA FINAL: nao foi informada a nota\nSTATUS: pendente");
                }
                
            }
        }
    }
    printf("\n=========================================================================================================================\n");
    
   suspenderExecucao();
    return;
}

/*--------------------> CONTAINER DE LISTAGEM */

void listarAlunosAproRepro() {
    printf("\n\n===>> LISTAGEM DE APROVADOS E REPROVADOS");
    resultadoInput = false;
    while(!resultadoInput) {
        resultadoInput = receberCodigoConsulta();
        if((int)numeroBuffer == 0) return;
    }
    consultarAprovadosDisciplina();
    suspenderExecucao();
}

bool receberCodigoConsulta() {
    printf("\nDigite o codigo da disciplina ou selecione 0 para retornar ao menu principal:");
    scanf("%f", &numeroBuffer);
    while(getchar() != '\n');
    if(verificarOverflowNumero(numeroBuffer, -1, 100)) {
        return false;
    }
    else return true;
}

void consultarAprovadosDisciplina() {
    int i = 0;
    int j = 0;
    
    bool sentinela = false;
    while((i < NUM_CURSOS) && (!sentinela)) {
        j = 0;
        while((j < cursos[i].contadorDisciplinas) && (!sentinela)) {
            if(cursos[i].gradeCurricular[j].codigo == (int)numeroBuffer) {
                indexDisciplina[0] = i;
                indexDisciplina[1] = j;
                sentinela = true;
            }
            j++;
        }
        i++;
    }

    if(!sentinela) {
        exibirMensagem("A disciplina nao foi encontrada");
        return;
    }
    else {
       Disciplina *disciplina = &cursos[indexDisciplina[0]].gradeCurricular[indexDisciplina[1]];
       printf("===> Disciplina: %s\n\n", disciplina->nome);
       for(int i = 0; i < disciplina->contadorAlunos; i++) {
            if(disciplina->turma[i].notasInformadas) {
                char statusAprovado[13];
                if(disciplina->turma[i].statusAprovado) {
                    strcpy(statusAprovado, "Aprovado(a)");
                }
                else {
                    strcpy(statusAprovado, "Reprovado(a)");
                }

                printf("- %s: %s\n", disciplina->turma[i].nome, statusAprovado);
            }
            else {
                printf("- %s: nota nao foi informada\n", disciplina->turma[i].nome);
            }
            
       }
       return;
    }
}



/*--------------------> CONTAINER DO FLUXO PRINCIPAL */

bool receberResposta(int numeroMaxOpcoes) {
    if((scanf("%d", &resposta) != 1)) {
        while(getchar() != '\n');
        exibirMensagem("Essa opcao nao existe");
        return false;
    }
    else if(!verificarOverflowNumero(resposta, -1, numeroMaxOpcoes)) {
        while(getchar() != '\n');
        return true;
    }
}

void apresentarRegras() {
    printf("\n\n===>> REGRAS DE USO\n");
    printf("- Disciplinas nao podem ter codigos iguais.\n");
    printf("- Alunos nao podem ter numeros de matricula iguais.\n");
    printf("- Alunos podem ser adicionados a um curso apenas se o curso tiver ao menos uma disciplina.\n");
    printf("- A adicao de novas disciplinas a um curso pode apenas ocorrer quando ainda nao houverem alunos cadastrados no curso.\n");
    printf("Dessa forma, busque sempre cadastrar alunos depois de adicionado todas as disciplinas ao curso\n\n");
    suspenderExecucao();
}

void apresentarMenu() {
    while(resposta != -1) {
        resultadoInput = false;
        while(!resultadoInput) {
            printf("\n//--------BEM VINDO AO SISTEMA ACADEMICO--------//");
            printf("\n\n|---> Selecione 1 para cadastrar disciplinas\n");
            printf("|---> Selecione 2 para cadastrar alunos\n");
            printf("|---> Selecione 3 para listar aprovados e reprovados\n");
            printf("|---> Selecione 4 para acessar as regras de uso do sistema\n");
            printf("|---> Selecione 5 para inserir notas\n");
            printf("|---> Selecione 6 para gerar um boletim\n");
            printf("|---> Selecione 0 para encerrar o sistema\n");
            resultadoInput = receberResposta(6);
        }

        switch(resposta) {
            case 1:
                cadastrarDisciplinas();
                break;
            case 2:
                cadastarAluno();
                break;
            case 3:
                listarAlunosAproRepro();
                break;
            case 4:
                apresentarRegras();
                break;
            case 5:
                inserirNotas();
                break;
            case 6:
                gerarBoletim();
                break;
            case 0:
                printf("===> Encerrando sistema...");
                resposta = -1;
                break;
        }
    }
}


