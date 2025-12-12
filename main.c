#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "cadastroDisciplinas.h"

int main() {
    setlocale(LC_ALL, "Portuguese");
    
    tds_aluno *alunos = NULL;
    tds_disciplina *disciplinas = NULL;
    tds_matricula *matriculas = NULL;
    tds_compromisso *compromissos = NULL;
    
    int tamAlunos = 0, capAlunos = 10;
    int tamDisciplinas = 0, capDisciplinas = 10;
    int tamMatriculas = 0, capMatriculas = 20;
    int tamCompromissos = 0, capCompromissos = 15;
    
    alunos = alocaVetorAluno(capAlunos);
    disciplinas = malloc(capDisciplinas * sizeof(tds_disciplina));
    matriculas = alocaVetorMatricula(capMatriculas);
    compromissos = alocaVetorCompromisso(capCompromissos);
    
    if (!disciplinas) {
        printf("Erro ao alocar memória para disciplinas!\n");
        return 1;
    }
    
    int opcao;
    
    do {
        opcao = menu();
        
        switch(opcao) {
            case 1: 
                if (tamAlunos >= capAlunos) {
                    capAlunos += 10;
                    alunos = realocaVetorAluno(alunos, capAlunos);
                    printf("Vetor de alunos realocado para %d posições.\n", capAlunos);
                }
                cadastrarAluno(alunos, tamAlunos);
                tamAlunos++;
                break;
                
            case 2:
                if (tamDisciplinas >= capDisciplinas) {
                    capDisciplinas += 5;
                    tds_disciplina *temp = realloc(disciplinas, capDisciplinas * sizeof(tds_disciplina));
                    if (temp) {
                        disciplinas = temp;
                        printf("Vetor de disciplinas realocado para %d posições.\n", capDisciplinas);
                    } else {
                        printf("Erro ao realocar memória!\n");
                    }
                }
                cadastrarDisciplina(disciplinas, tamDisciplinas);
                tamDisciplinas++;
                break;
                
            case 3:
                if (tamMatriculas >= capMatriculas) {
                    capMatriculas += 10;
                    matriculas = realocaVetorMatricula(matriculas, capMatriculas);
                    printf("Vetor de matrículas realocado para %d posições.\n", capMatriculas);
                }
                if (tamAlunos == 0) {
                    printf("É necessário cadastrar alunos primeiro!\n");
                } else if (tamDisciplinas == 0) {
                    printf("É necessário cadastrar disciplinas primeiro!\n");
                } else {
                    cadastrarMatricula(matriculas, tamMatriculas, alunos, tamAlunos, disciplinas, tamDisciplinas);
                    tamMatriculas++;
                }
                break;
                
            case 4:
                if (tamCompromissos >= capCompromissos) {
                    capCompromissos += 5;
                    compromissos = realocaVetorCompromisso(compromissos, capCompromissos);
                    printf("Vetor de compromissos realocado para %d posições.\n", capCompromissos);
                }
                if (tamAlunos == 0) {
                    printf("É necessário cadastrar alunos primeiro!\n");
                } else {
                    cadastrarCompromisso(compromissos, &tamCompromissos, alunos, tamAlunos);
                }
                break;
                
            case 5:
                {
                    int subOpcao;
                    do {
                        subOpcao = menuCompromissos();
                        
                        switch(subOpcao) {
                            case 1: 
                                {
                                    int ra;
                                    printf("Digite o RA do aluno: ");
                                    scanf("%d", &ra);
                                    getchar();
                                    imprimirCompromissosAluno(compromissos, tamCompromissos, ra);
                                }
                                break;
                            case 2: 
                                imprimirCompromissosTodos(compromissos, tamCompromissos);
                                break;
                            case 3: 
                                {
                                    tds_data data;
                                    printf("Digite a data (dd mm aaaa): ");
                                    scanf("%d %d %d", &data.dia, &data.mes, &data.ano);
                                    getchar();
                                    imprimirCompromissosData(compromissos, tamCompromissos, data);
                                }
                                break;
                            case 4: 
                                imprimirCompromissosTodasDatas(compromissos, tamCompromissos);
                                break;
                        }
                    } while (subOpcao != 0);
                }
                break;
                
            case 6: 
                {
                    int ra;
                    printf("Digite o RA do aluno: ");
                    scanf("%d", &ra);
                    getchar();
                    imprimirDadosAluno(alunos, tamAlunos, ra);
                }
                break;
                
            case 7: 
                imprimirTodosAlunos(alunos, tamAlunos);
                break;
                
            case 8: 
                printf("Encerrando o programa...\n");
                break;
                
            default:
                printf("Opção inválida!\n");
        }
        
    } while (opcao != 8);
    
    
    free(alunos);
    free(disciplinas);
    free(matriculas);
    free(compromissos);
    
    printf("Programa finalizado com sucesso!\n");
    return 0;
}