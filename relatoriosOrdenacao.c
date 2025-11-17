#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cadastroDisciplinas.h"

int comparaAlunoRA(const void *a, const void *b) {
    const tds_aluno *aluno1 = (const tds_aluno *)a;
    const tds_aluno *aluno2 = (const tds_aluno *)b;
    return aluno1->ra - aluno2->ra;
}

int comparaCompromissoDataHora(const void *a, const void *b) {
    const tds_compromisso *comp1 = (const tds_compromisso *)a;
    const tds_compromisso *comp2 = (const tds_compromisso *)b;
    
    // Comparação por ano
    if (comp1->data.ano != comp2->data.ano)
        return comp1->data.ano - comp2->data.ano;
    
    // Comparação por mês
    if (comp1->data.mes != comp2->data.mes)
        return comp1->data.mes - comp2->data.mes;
    
    // Comparação por dia
    if (comp1->data.dia != comp2->data.dia)
        return comp1->data.dia - comp2->data.dia;
    
    // Comparação por hora
    if (comp1->horario.hora != comp2->horario.hora)
        return comp1->horario.hora - comp2->horario.hora;
    
    // Comparação por minuto
    return comp1->horario.min - comp2->horario.min;
}

// Comparação para compromissos por RA, data e hora
int comparaCompromissoRADataHora(const void *a, const void *b) {
    const tds_compromisso *comp1 = (const tds_compromisso *)a;
    const tds_compromisso *comp2 = (const tds_compromisso *)b;
    
    // Primeiro por RA
    if (comp1->aluno.ra != comp2->aluno.ra)
        return comp1->aluno.ra - comp2->aluno.ra;
    
    // Depois por data e hora
    return comparaCompromissoDataHora(a, b);
}

// Comparação para compromissos por hora e RA
int comparaCompromissoHoraRA(const void *a, const void *b) {
    const tds_compromisso *comp1 = (const tds_compromisso *)a;
    const tds_compromisso *comp2 = (const tds_compromisso *)b;
    
    // Primeiro por hora
    if (comp1->horario.hora != comp2->horario.hora)
        return comp1->horario.hora - comp2->horario.hora;
    
    // Depois por minuto
    if (comp1->horario.min != comp2->horario.min)
        return comp1->horario.min - comp2->horario.min;
    
    // Por último por RA
    return comp1->aluno.ra - comp2->aluno.ra;
}

// Comparação para compromissos por data, hora e RA
int comparaCompromissoDataHoraRA(const void *a, const void *b) {
    const tds_compromisso *comp1 = (const tds_compromisso *)a;
    const tds_compromisso *comp2 = (const tds_compromisso *)b;
    
    // Primeiro por data e hora
    int cmpDataHora = comparaCompromissoDataHora(a, b);
    if (cmpDataHora != 0)
        return cmpDataHora;
    
    // Se mesma data e hora, ordena por RA
    return comp1->aluno.ra - comp2->aluno.ra;
}

// FUNÇÕES DE RELATÓRIOS

// 5a - Compromissos de um aluno (ordenado por data e hora)
void imprimirCompromissosAluno(tds_compromisso *compromissos, int n, int ra_aluno) {
    // Filtrar compromissos do aluno
    tds_compromisso *filtrados = malloc(n * sizeof(tds_compromisso));
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        if (compromissos[i].aluno.ra == ra_aluno) {
            filtrados[count++] = compromissos[i];
        }
    }
    
    if (count == 0) {
        printf("Nenhum compromisso encontrado para o aluno RA: %d\n", ra_aluno);
        free(filtrados);
        return;
    }
    
    // Ordenar por data e hora
    qsort(filtrados, count, sizeof(tds_compromisso), comparaCompromissoDataHora);
    
    printf("\n=== COMPROMISSOS DO ALUNO RA: %d ===\n", ra_aluno);
    for (int i = 0; i < count; i++) {
        printf("Data: %02d/%02d/%04d - Hora: %02d:%02d - Descricao: %s\n",
               filtrados[i].data.dia, filtrados[i].data.mes, filtrados[i].data.ano,
               filtrados[i].horario.hora, filtrados[i].horario.min,
               filtrados[i].descricao);
    }
    
    free(filtrados);
}

// Compromissos de todos os alunos (ordenado por RA, data e hora)
void imprimirCompromissosTodos(tds_compromisso *compromissos, int n) {
    if (n == 0) {
        printf("Nenhum compromisso cadastrado.\n");
        return;
    }
    
    // Ordenar o vetor completo
    qsort(compromissos, n, sizeof(tds_compromisso), comparaCompromissoRADataHora);
    
    printf("\n=== COMPROMISSOS DE TODOS OS ALUNOS ===\n");
    for (int i = 0; i < n; i++) {
        printf("RA: %d - Data: %02d/%02d/%04d - Hora: %02d:%02d - Descricao: %s\n",
               compromissos[i].aluno.ra,
               compromissos[i].data.dia, compromissos[i].data.mes, compromissos[i].data.ano,
               compromissos[i].horario.hora, compromissos[i].horario.min,
               compromissos[i].descricao);
    }
}

// Compromissos de uma data (ordenado por hora e RA)
void imprimirCompromissosData(tds_compromisso *compromissos, int n, tds_data data) {
    tds_compromisso *filtrados = malloc(n * sizeof(tds_compromisso));
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        if (compromissos[i].data.dia == data.dia &&
            compromissos[i].data.mes == data.mes &&
            compromissos[i].data.ano == data.ano) {
            filtrados[count++] = compromissos[i];
        }
    }
    
    if (count == 0) {
        printf("Nenhum compromisso encontrado para a data: %02d/%02d/%04d\n", 
               data.dia, data.mes, data.ano);
        free(filtrados);
        return;
    }
    
    // Ordenar por hora e RA
    qsort(filtrados, count, sizeof(tds_compromisso), comparaCompromissoHoraRA);
    
    printf("\n=== COMPROMISSOS NA DATA %02d/%02d/%04d ===\n", data.dia, data.mes, data.ano);
    for (int i = 0; i < count; i++) {
        printf("RA: %d - Hora: %02d:%02d - Descricao: %s\n",
               filtrados[i].aluno.ra,
               filtrados[i].horario.hora, filtrados[i].horario.min,
               filtrados[i].descricao);
    }
    
    free(filtrados);
}

// Compromissos de todas as datas (ordenado por data, hora e RA)
void imprimirCompromissosTodasDatas(tds_compromisso *compromissos, int n) {
    if (n == 0) {
        printf("Nenhum compromisso cadastrado.\n");
        return;
    }
    
    // Ordenar o vetor completo
    qsort(compromissos, n, sizeof(tds_compromisso), comparaCompromissoDataHoraRA);
    
    printf("\n=== COMPROMISSOS DE TODAS AS DATAS ===\n");
    for (int i = 0; i < n; i++) {
        printf("Data: %02d/%02d/%04d - Hora: %02d:%02d - RA: %d - Descricao: %s\n",
               compromissos[i].data.dia, compromissos[i].data.mes, compromissos[i].data.ano,
               compromissos[i].horario.hora, compromissos[i].horario.min,
               compromissos[i].aluno.ra,
               compromissos[i].descricao);
    }
}

// Imprimir dados de um aluno
void imprimirDadosAluno(tds_aluno *alunos, int n, int ra) {
    int pos = encontrarAluno(alunos, n, ra);
    if (pos == -1) {
        printf("Aluno com RA %d nao encontrado.\n", ra);
        return;
    }
    
    printf("\n=== DADOS DO ALUNO ===\n");
    printf("RA: %d\n", alunos[pos].ra);
    printf("Nome: %s\n", alunos[pos].nome);
    printf("Email: %s\n", alunos[pos].email);
}

// Imprimir dados de todos os alunos (ordenado por RA)
void imprimirTodosAlunos(tds_aluno *alunos, int n) {
    if (n == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }
    
    // Ordenar por RA
    qsort(alunos, n, sizeof(tds_aluno), comparaAlunoRA);
    
    printf("\n=== TODOS OS ALUNOS (ordenado por RA) ===\n");
    for (int i = 0; i < n; i++) {
        printf("RA: %d - Nome: %s - Email: %s\n",
               alunos[i].ra, alunos[i].nome, alunos[i].email);
    }
}