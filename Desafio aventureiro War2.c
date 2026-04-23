#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 5        // Número máximo de territórios
#define TAM_NOME 50  // Tamanho máximo do nome do território
#define TAM_COR 20   // Tamanho máximo da cor do exército

// Estrutura que representa um território
typedef struct {
    char nome[TAM_NOME]; // Nome do território
    char cor[TAM_COR];   // Cor do exército que ocupa o território
    int tropas;          // Número de tropas presentes
} Territorio;

// Função para mostrar o estado atual do mapa
void mostrarMapa(Territorio *mapa, int n) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < n; i++) {
        printf("Territorio %d: Nome=%s | Cor=%s | Tropas=%d\n",
               i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função que simula uma batalha entre dois territórios
void batalha(Territorio *atacante, Territorio *defensor) {
    int dadoAtq = rand() % 6 + 1; // Sorteia valor de 1 a 6 para atacante
    int dadoDef = rand() % 6 + 1; // Sorteia valor de 1 a 6 para defensor

    printf("\nBatalha: %s (Atacante) vs %s (Defensor)\n", atacante->nome, defensor->nome);
    printf("Dado Atq=%d | Dado Def=%d\n", dadoAtq, dadoDef);

    // Se o atacante tirar valor maior ou igual, defensor perde uma tropa
    if (dadoAtq >= dadoDef) {
        defensor->tropas--;
        printf("Atacante venceu! %s perde 1 tropa.\n", defensor->nome);

        // Se o defensor ficar sem tropas, território é conquistado
        if (defensor->tropas <= 0) {
            defensor->tropas = atacante->tropas; // Transfere tropas do atacante
            strcpy(defensor->cor, atacante->cor); // Muda cor para a do atacante
            printf("%s foi conquistado pelo exercito %s!\n", defensor->nome, atacante->cor);
        }
    } else {
        printf("Defensor resistiu ao ataque!\n");
    }
}

int main() {
    srand(time(NULL)); // Inicializa gerador de números aleatórios

    // Aloca dinamicamente memória para os territórios
    Territorio *mapa = (Territorio *) calloc(MAX, sizeof(Territorio));

    printf("=== Cadastro dos Territorios ===\n");
    for (int i = 0; i < MAX; i++) {
        printf("\nTerritorio %d:\n", i+1);

        // Cadastro do nome do território
        printf("Nome: ");
        fgets(mapa[i].nome, TAM_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // Remove quebra de linha

        // Cadastro da cor do exército
        printf("Cor do Exercito: ");
        fgets(mapa[i].cor, TAM_COR, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0'; // Remove quebra de linha

        // Cadastro do número de tropas
        printf("Numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // Consome o ENTER deixado pelo scanf
    }

    // Mostra o mapa inicial
    mostrarMapa(mapa, MAX);

    int atq, def;
    char continuar;
    do {
        // Escolha dos territórios para batalha
        printf("\nEscolha o atacante (1-5): ");
        scanf("%d", &atq);
        printf("Escolha o defensor (1-5): ");
        scanf("%d", &def);
        getchar();

        // Valida escolha e executa batalha
        if (atq >= 1 && atq <= MAX && def >= 1 && def <= MAX && atq != def) {
            batalha(&mapa[atq-1], &mapa[def-1]);
        } else {
            printf("Escolha invalida!\n");
        }

        // Mostra mapa atualizado
        mostrarMapa(mapa, MAX);

        // Pergunta se o usuário deseja continuar batalhando
        printf("\nDeseja continuar batalhando? (s/n): ");
        scanf("%c", &continuar);
        getchar();
    } while (continuar == 's' || continuar == 'S');

    // Libera memória alocada
    free(mapa);
    return 0;
}
