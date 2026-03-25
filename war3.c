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

typedef enum {
    MISSAO_DESTRUIR_VERDE,
    MISSAO_CONQUISTAR_TRES
} Missao;

void inicializarMapa(Territorio *mapa, const int n) {
    const char *nomes[MAX] = {"Norte", "Sul", "Leste", "Oeste", "Centro"};
    const char *cores[MAX] = {"Vermelho", "Azul", "Verde", "Amarelo", "Preto"};
    const int tropasIniciais[MAX] = {5, 5, 5, 5, 5};

    for (int i = 0; i < n; i++) {
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].cor, cores[i]);
        mapa[i].tropas = tropasIniciais[i];
    }
}

void mostrarMapa(const Territorio *mapa, const int n) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < n; i++) {
        printf("Territorio %d: Nome=%s | Cor=%s | Tropas=%d\n",
               i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void batalha(Territorio *atacante, Territorio *defensor) {
    int dadoAtq = rand() % 6 + 1;
    int dadoDef = rand() % 6 + 1;

    printf("\nBatalha: %s (Atacante) vs %s (Defensor)\n", atacante->nome, defensor->nome);
    printf("Dado Atq=%d | Dado Def=%d\n", dadoAtq, dadoDef);

    if (dadoAtq >= dadoDef) {
        defensor->tropas--;
        printf("Atacante venceu! %s perde 1 tropa.\n", defensor->nome);
        if (defensor->tropas <= 0) {
            defensor->tropas = atacante->tropas;
            strcpy(defensor->cor, atacante->cor);
            printf("%s foi conquistado pelo exercito %s!\n", defensor->nome, atacante->cor);
        }
    } else {
        printf("Defensor resistiu ao ataque!\n");
    }
}

Missao atribuirMissao() {
    int sorteio = rand() % 2;
    if (sorteio == 0) {
        printf("\nMissao atribuida: Destruir o exercito Verde!\n");
        return MISSAO_DESTRUIR_VERDE;
    } else {
        printf("\nMissao atribuida: Conquistar 3 territorios!\n");
        return MISSAO_CONQUISTAR_TRES;
    }
}

int verificarMissao(const Territorio *mapa, const int n, const Missao missao, const char *corJogador) {
    if (missao == MISSAO_DESTRUIR_VERDE) {
        for (int i = 0; i < n; i++) {
            if (strcmp(mapa[i].cor, "Verde") == 0 && mapa[i].tropas > 0) {
                printf("Missao ainda nao cumprida: exercito Verde resiste.\n");
                return 0;
            }
        }
        printf("Missao cumprida: exercito Verde destruido!\n");
        return 1;
    } else if (missao == MISSAO_CONQUISTAR_TRES) {
        int conquistados = 0;
        for (int i = 0; i < n; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                conquistados++;
            }
        }
        if (conquistados >= 3) {
            printf("Missao cumprida: voce conquistou 3 territorios!\n");
            return 1;
        } else {
            printf("Missao ainda nao cumprida: voce possui %d territorios.\n", conquistados);
            return 0;
        }
    }
    return 0;
}

void menuPrincipal(Territorio *mapa, const int n, const Missao missao, const char *corJogador) {
    int opcao;
    do {
        printf("\n=== Menu Principal ===\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missao\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            int atq, def;
            printf("Escolha o atacante (1-%d): ", n);
            scanf("%d", &atq);
            printf("Escolha o defensor (1-%d): ", n);
            scanf("%d", &def);
            getchar();

            if (atq >= 1 && atq <= n && def >= 1 && def <= n && atq != def) {
                batalha(&mapa[atq-1], &mapa[def-1]);
            } else {
                printf("Escolha invalida!\n");
            }
            mostrarMapa(mapa, n);
        } else if (opcao == 2) {
            if (verificarMissao(mapa, n, missao, corJogador)) {
                printf("\n=== VITORIA! Missao concluida ===\n");
                break;
            }
        }
    } while (opcao != 0);
}

int main() {
    srand(time(NULL));

    Territorio *mapa = (Territorio *) calloc(MAX, sizeof(Territorio));
    inicializarMapa(mapa, MAX);
    mostrarMapa(mapa, MAX);

    Missao missao = atribuirMissao();
    const char corJogador[] = "Vermelho"; // jogador fixo

    menuPrincipal(mapa, MAX, missao, corJogador);

    free(mapa);
    return 0;
}
