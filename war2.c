#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 5
#define TAM_NOME 50
#define TAM_COR 20

typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

void mostrarMapa(Territorio *mapa, int n) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < n; i++) {
        printf("Territorio %d: Nome=%s | Cor=%s | Tropas=%d\n",
               i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void batalha(Territorio *atacante, Territorio *defensor) {
    int dadoAtq = rand() % 6 + 1; // 1 a 6
    int dadoDef = rand() % 6 + 1;

    printf("\nBatalha: %s (Atacante) vs %s (Defensor)\n", atacante->nome, defensor->nome);
    printf("Dado Atq=%d | Dado Def=%d\n", dadoAtq, dadoDef);

    if (dadoAtq >= dadoDef) {
        defensor->tropas--;
        printf("Atacante venceu! %s perde 1 tropa.\n", defensor->nome);
        if (defensor->tropas <= 0) {
            defensor->tropas = atacante->tropas; // transfere tropas
            strcpy(defensor->cor, atacante->cor);
            printf("%s foi conquistado pelo exercito %s!\n", defensor->nome, atacante->cor);
        }
    } else {
        printf("Defensor resistiu ao ataque!\n");
    }
}

int main() {
    srand(time(NULL));

    Territorio *mapa = (Territorio *) calloc(MAX, sizeof(Territorio));

    printf("=== Cadastro dos Territorios ===\n");
    for (int i = 0; i < MAX; i++) {
        printf("\nTerritorio %d:\n", i+1);

        printf("Nome: ");
        fgets(mapa[i].nome, TAM_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do Exercito: ");
        fgets(mapa[i].cor, TAM_COR, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();
    }

    mostrarMapa(mapa, MAX);

    int atq, def;
    char continuar;
    do {
        printf("\nEscolha o atacante (1-5): ");
        scanf("%d", &atq);
        printf("Escolha o defensor (1-5): ");
        scanf("%d", &def);
        getchar();

        if (atq >= 1 && atq <= MAX && def >= 1 && def <= MAX && atq != def) {
            batalha(&mapa[atq-1], &mapa[def-1]);
        } else {
            printf("Escolha invalida!\n");
        }

        mostrarMapa(mapa, MAX);

        printf("\nDeseja continuar batalhando? (s/n): ");
        scanf("%c", &continuar);
        getchar();
    } while (continuar == 's' || continuar == 'S');

    free(mapa);
    return 0;
}
