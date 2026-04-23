#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 5        // Número máximo de territórios
#define TAM_NOME 50  // Tamanho máximo do nome de um território
#define TAM_COR 20   // Tamanho máximo da cor do exército

// Estrutura que representa um território no mapa
typedef struct {
    char nome[TAM_NOME]; // Nome do território
    char cor[TAM_COR];   // Cor do exército que ocupa o território
    int tropas;          // Número de tropas presentes
} Territorio;

// Enumeração que define os tipos de missões possíveis
typedef enum {
    MISSAO_DESTRUIR_VERDE,   // Missão: destruir o exército verde
    MISSAO_CONQUISTAR_TRES   // Missão: conquistar 3 territórios
} Missao;

// Função que inicializa o mapa com nomes, cores e tropas iniciais
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

// Função que mostra o estado atual do mapa
void mostrarMapa(const Territorio *mapa, const int n) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < n; i++) {
        printf("Territorio %d: Nome=%s | Cor=%s | Tropas=%d\n",
               i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função que simula uma batalha entre dois territórios
void batalha(Territorio *atacante, Territorio *defensor) {
    int dadoAtq = rand() % 6 + 1; // Sorteio de dado para atacante (1 a 6)
    int dadoDef = rand() % 6 + 1; // Sorteio de dado para defensor (1 a 6)

    printf("\nBatalha: %s (Atacante) vs %s (Defensor)\n", atacante->nome, defensor->nome);
    printf("Dado Atq=%d | Dado Def=%d\n", dadoAtq, dadoDef);

    // Se atacante tirar valor maior ou igual, defensor perde uma tropa
    if (dadoAtq >= dadoDef) {
        defensor->tropas--;
        printf("Atacante venceu! %s perde 1 tropa.\n", defensor->nome);

        // Se defensor ficar sem tropas, território é conquistado
        if (defensor->tropas <= 0) {
            defensor->tropas = atacante->tropas; // Transfere tropas
            strcpy(defensor->cor, atacante->cor); // Muda cor para a do atacante
            printf("%s foi conquistado pelo exercito %s!\n", defensor->nome, atacante->cor);
        }
    } else {
        printf("Defensor resistiu ao ataque!\n");
    }
}

// Função que sorteia e atribui uma missão ao jogador
Missao atribuirMissao() {
    int sorteio = rand() % 2; // Sorteio entre 0 e 1
    if (sorteio == 0) {
        printf("\nMissao atribuida: Destruir o exercito Verde!\n");
        return MISSAO_DESTRUIR_VERDE;
    } else {
        printf("\nMissao atribuida: Conquistar 3 territorios!\n");
        return MISSAO_CONQUISTAR_TRES;
    }
}

// Função que verifica se a missão foi cumprida
int verificarMissao(const Territorio *mapa, const int n, const Missao missao, const char *corJogador) {
    if (missao == MISSAO_DESTRUIR_VERDE) {
        // Verifica se ainda existe algum território com cor "Verde" e tropas > 0
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
        // Conta quantos territórios pertencem ao jogador
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

// Menu principal do jogo
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

            // Valida escolha e executa batalha
            if (atq >= 1 && atq <= n && def >= 1 && def <= n && atq != def) {
                batalha(&mapa[atq-1], &mapa[def-1]);
            } else {
                printf("Escolha invalida!\n");
            }
            mostrarMapa(mapa, n);
        } else if (opcao == 2) {
            // Verifica se a missão foi cumprida
            if (verificarMissao(mapa, n, missao, corJogador)) {
                printf("\n=== VITORIA! Missao concluida ===\n");
                break; // Encerra o jogo em caso de vitória
            }
        }
    } while (opcao != 0); // Continua até o jogador escolher sair
}

int main() {
    srand(time(NULL)); // Inicializa gerador de números aleatórios

    // Cria e inicializa o mapa
    Territorio *mapa = (Territorio *) calloc(MAX, sizeof(Territorio));
    inicializarMapa(mapa, MAX);
    mostrarMapa(mapa, MAX);

    // Atribui missão aleatória ao jogador
    Missao missao = atribuirMissao();
    const char corJogador[] = "Vermelho"; // Cor fixa do jogador

    // Executa menu principal
    menuPrincipal(mapa, MAX, missao, corJogador);

    // Libera memória alocada
    free(mapa);
    return 0;
}
