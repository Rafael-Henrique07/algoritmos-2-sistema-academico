#ifndef cadastroDisciplinas_h
#define cadastroDisciplinas_h

typedef struct {
    int dia;
    int mes;
    int ano;
} tds_data;

typedef struct {
    int hora;
    int min;
} tds_hora;

typedef struct {
    int codigoDis;
    char disciplina[100];
} tds_disciplina;

typedef struct {
    int ra;
    char nome[100];
    char email[100];
} tds_aluno;

typedef struct {
    int ra;
    int codigoDis;
    tds_data dataMatricula;
    float notas[4];
} tds_matricula;

typedef struct {
    tds_aluno aluno;
    tds_hora horario;
    tds_data data;
    char descricao[300];
} tds_compromisso;

/*Funções para cadastro*/
void cadastrarAluno(tds_aluno[], int);
void cadastrarDisciplina(tds_disciplina[], int);
void cadastrarMatricula(tds_matricula[], int, tds_aluno[], int, tds_disciplina[], int);
void cadastrarCompromisso(tds_compromisso*, int*, tds_aluno*, int);

/*Funções para validação de dados*/
int verificaData(tds_data*);
int verificaHorario(tds_hora*);
int verificarEmail(char email[]);


/*Funções para impressão*/
void imprimeVetorDeALunos(tds_aluno[], int);


/*Funções de busca*/
int encontrarAluno(tds_aluno*, int, int);
int encontrarDisciplina(tds_disciplina*, int,int);
int procurarData(tds_compromisso*, int, tds_data*, int);
int procurarHorario(tds_compromisso*, int, tds_hora*, tds_data*, int);

/*Funções opcionais*/
void lerHorario(tds_hora*);
void lerData(tds_data*);

/*Funções para Menu*/
int menuCompromissos();
int menu();

/*Funções para Alocação Dinâmica*/
tds_aluno* alocaVetorAluno(int tamanhoInicial);
tds_disciplina* alocaVetorDisciplina(int tamanhoInicial);
tds_matricula* alocaVetorMatricula(int tamanhoInicial);
tds_compromisso* alocaVetorCompromisso(int tamanhoInicial);

/*Funções para Realocação Dinâmica*/
tds_aluno* realocaVetorAluno(tds_aluno* vetor, int novoTamanho);
tds_disciplina* realocaVetorDisciplina(tds_disciplina* vetor, int novoTamanho);
tds_matricula* realocaVetorMatricula(tds_matricula* vetor, int novoTamanho);
tds_compromisso* realocaVetorCompromisso(tds_compromisso* vetor, int novoTamanho);

#endif // cadastroDisciplinas_h