#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
// A struct é usada para agrupar dados relacionados em uma única entidade.
// Aqui, cada território terá um nome, uma cor de exército e a quantidade de tropas.
struct Territorio {
    char nome[30];   // Nome do território (até 29 caracteres + '\0')
    char cor[10];    // Cor do exército (até 9 caracteres + '\0')
    int tropas;      // Quantidade de tropas no território
};

int main() {
    // Declaração de um vetor de 5 elementos do tipo Territorio
    // Cada posição do vetor armazenará os dados de um território diferente.
    struct Territorio territorios[5];

    // Laço para cadastrar os 5 territórios
    for (int i = 0; i < 5; i++) {
        printf("Cadastro do território %d:\n", i + 1);

        // Entrada do nome do território
        printf("Digite o nome do território: ");
        scanf("%s", territorios[i].nome);

        // Entrada da cor do exército
        printf("Digite a cor do exército: ");
        scanf("%s", territorios[i].cor);

        // Entrada da quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n"); // Espaço para organizar a saída
    }

    // Exibição dos dados cadastrados
    printf("\n--- Lista de Territórios ---\n");
    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("---------------------------\n");
    }

    // Retorno 0 indica que o programa terminou com sucesso
    return 0;
}
