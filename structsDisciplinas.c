#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cadastroDisciplinas.h"

// DESENVOLVER TODAS AS FUNÇÕES DECLARADAS NO ARQUIVO DE CABEÇALHO cadastroDisciplinas.h

/*Fun��es para cadastro*/
void cadastrarAluno(tds_aluno vetorAlunos[], int posicao) {
    // Implementação da função para cadastrar aluno
    printf("\n=== CADASTRO DE ALUNO ===\n");

    printf("RA: ");
    scanf("%d", &vetorAlunos[posicao].ra);
    getchar(); // Limpar o buffer do teclado

    printf("Nome: ");
    fgets(vetorAlunos[posicao].nome, 100, stdin);
    vetorAlunos[posicao].nome[strcspn(vetorAlunos[posicao].nome, "\n")] = 0;

    do {
        printf("Email: ");
        fgets(vetorAlunos[posicao].email, 100, stdin);
        vetorAlunos[posicao].email[strcspn(vetorAlunos[posicao].email, "\n")] = 0;

        if(!verificarEmail(vetorAlunos[posicao].email)) {
            printf("Email inválido. Tente novamente.\n");
        }
    }while(!verificarEmail(vetorAlunos[posicao].email));
    
    printf("Aluno cadastrado com sucesso!\n");
}

/*Função para cadastrar disciplina*/
void cadastrarDisciplina(tds_disciplina vetorDisciplinas[], int posicao) {
    printf("\n=== CADASTRO DE DISCIPLINA ===\n");

    printf("Codigo da disciplina: ");
    scanf("%d", &vetorDisciplinas[posicao].codigoDis);
    getchar();

    printf("Nome da disciplina: ");
    fgets(vetorDisciplinas[posicao].disciplina, 100, stdin);
    vetorDisciplinas[posicao].disciplina[strcspn(vetorDisciplinas[posicao].disciplina, "\n")] = 0;

    printf("Disciplina cadastrada com sucesso!\n");
}

void cadastrarMatricula(tds_matricula[], int, tds_aluno[], int, tds_disciplina[], int);
void cadastrarCompromisso(tds_compromisso*, int*, tds_aluno*, int);

/*Fun��es para valida��o de dados*/
int verificaData(tds_data*);
int verificaHorario(tds_hora*);

/*FUnção para validar email*/
int verificarEmail(char email[]) {
    int possuiArroba = 0;
    int possuiPonto = 0;
    int i;

    for (i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            if (possuiArroba) return 0; // Mais de um @
            possuiArroba = 1;
        } else if (email[i] == '.') {
            possuiPonto = 1;
        } else if(!((email[i] >= 'a' && email[i] <= 'z') || (email[i] >= 'A' && email[i] <= 'Z') || (email[i] >= '0' && email[i] <= '9') || email[i] == '-' || email[i] == '_' || email[i] == '.')) {
            return 0;
        }
    }

    return (possuiArroba && possuiPonto); 
}


/*Fun��es para impress�o*/
void imprimeVetorDeALunos(tds_aluno[], int);


/*Fun��es de busca*/
int encontrarAluno(tds_aluno*, int, int);
int encontrarDisciplina(tds_disciplina*, int,int);
int procurarData(tds_compromisso*, int, tds_data*, int);
int procurarHorario(tds_compromisso*, int, tds_hora*, tds_data*, int);

/*Fun��es opcionais*/
void lerHorario(tds_hora*);
void lerData(tds_data*);

/*Funções para menu*/
int menuCompromissos() {

    printf("\n=== MENU DE COMPROMISSOS ===\n");
    printf("a - Compromissos de um aluno (ordenado por data e hora)\n");
    printf("b - Compromissos de todos os alunos (ordenado por RA, data e hora)\n");
    printf("c - Compromissos de uma data (ordenado por hora e RA)\n");
    printf("d - Compromissos de todas as datas (ordenado por data, hora e RA)\n");
    printf("e - Voltar ao menu principal\n");
    printf("Escolha uma opcao: ");

    char letra;
    scanf(" %c", &letra);
    getchar();

    switch(letra) {
        case 'a':
        case 'A':
            printf("Opção selecionada: Compromissos de um aluno\n");
            // Chamar a função correspondente
            return 1;
        
        case 'b':
        case 'B':
            printf("Opção selecionada: Compromissos de todos os alunos\n");
            // Chamar a função correspondente
            return 2;
            
        case 'c':
        case 'C':
            printf("Opção selecionada: Compromissos de uma data\n");
            // Chamar a função correspondente
            return 3;

        case 'd':
        case 'D':
            printf("Opção selecionada: Compromissos de todas as datas\n");
            // Chamar a função correspondente
            return 4;
        
        case 'e':
        case 'E':
            printf("Voltando ao menu principal...\n");
            return 0;

        default:
            printf("Opção inválida!\n");
            return -1;
    }
}

int menu() {
    int opcao;

    printf("\n=== MENU PRINCIPAL ===\n");
    printf("1 - Cadastrar Aluno\n");
    printf("2 - Cadastrar Disciplina\n");
    printf("3 - Cadastrar Matrícula\n");
    printf("4 - Cadastrar Compromisso\n");
    printf("5 - Imprimir Compromisso\n");
    printf("6 - Imprimir Dados de um Aluno\n");
    printf("7 - Imprimir Dados de Todos os Alunos (ordenado por RA)\n");
    printf("8 - Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    getchar();

    if(opcao == 5) {
        int opc;

        do {
            opc = menuCompromissos();
        }while(opc != 0);
    }
    return opcao;
}

/*FUnção para alocação dinâmica*/
tds_aluno* alocaVetorAluno(int tamanhoInicial) {
    tds_aluno *vetor = malloc(tamanhoInicial * sizeof(tds_aluno));
    if (vetor == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }
    return vetor;
}

tds_matricula* alocaVetorMatricula(int tamanhoInicial) {
    tds_matricula *vetor = malloc(tamanhoInicial * sizeof(tds_matricula));
    if (vetor == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }
    return vetor;
}

tds_compromisso* alocaVetorCompromisso(int tamanhoInicial) {
    tds_compromisso *vetor = malloc(tamanhoInicial * sizeof(tds_compromisso));
    if (vetor == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }
    return vetor;
}

/*Funções para realocação dinâmica*/
tds_aluno* realocaVetorAluno(tds_aluno* vetor, int novoTamanho) {
    tds_aluno* novoVetor = realloc(vetor, novoTamanho * sizeof(tds_aluno));
    if (novoVetor == NULL) {
        printf("Erro de realocacao de memoria!\n");
        free(vetor); // Libera o vetor original em caso de erro
        exit(1);
    }
    return novoVetor;
}

tds_disciplina* realocaVetorDisciplina(tds_disciplina* vetor, int novoTamanho) {
    tds_disciplina* novoVetor = realloc(vetor, novoTamanho * sizeof(tds_disciplina));
    if (novoVetor == NULL) {
        printf("Erro de realocacao de memoria!\n");
        free(vetor); // Libera o vetor original em caso de erro
        exit(1);
    }
    return novoVetor;
}

tds_matricula* realocaVetorMatricula(tds_matricula* vetor, int novoTamanho) {
    tds_matricula* novoVetor = realloc(vetor, novoTamanho * sizeof(tds_matricula));
    if (novoVetor == NULL) {
        printf("Erro de realocacao de memoria!\n");
        free(vetor); // Libera o vetor original em caso de erro
        exit(1);
    }
    return novoVetor;
}

tds_compromisso* realocaVetorCompromisso(tds_compromisso* vetor, int novoTamanho) {
    tds_compromisso* novoVetor = realloc(vetor, novoTamanho * sizeof(tds_compromisso));
    if (novoVetor == NULL) {
        printf("Erro de realocacao de memoria!\n");
        free(vetor); // Libera o vetor original em caso de erro
        exit(1);
    }
    return novoVetor;
}