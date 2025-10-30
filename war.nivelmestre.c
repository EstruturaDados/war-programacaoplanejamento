#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura que representa um território no jogo War
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar os territórios
void cadastrarTerritorios(Territorio* mapa, int total) {
    for (int i = 0; i < total; i++) {
        printf("\n🛡️ Cadastro do território %d:\n", i + 1);
        printf("Nome: ");
        scanf("%s", mapa[i].nome);
        printf("Cor do exército: ");
        scanf("%s", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para exibir os territórios
void exibirTerritorios(Territorio* mapa, int total) {
    printf("\n🌍 Territórios cadastrados:\n");
    for (int i = 0; i < total; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

// Função que simula um ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("⚠️ Não é permitido atacar um território da mesma cor!\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n🎲 Dados rolados:\n");
    printf("Atacante (%s): %d\n", atacante->nome, dadoAtacante);
    printf("Defensor (%s): %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("✅ Ataque bem-sucedido! O território %s foi conquistado.\n", defensor->nome);
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf("❌ Ataque falhou! O atacante perde uma tropa.\n");
        if (atacante->tropas > 0) {
            atacante->tropas--;
        }
    }
}

// Função para exibir a missão do jogador
void exibirMissao(char* missao) {
    printf("\n🎯 Sua missão estratégica: %s\n", missao);
}

// Função para atribuir uma missão aleatória ao jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// Função para verificar se a missão foi cumprida (lógica simplificada)
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    if (strstr(missao, "vermelha") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0) {
                return 0;
            }
        }
        return 1;
    }

    if (strstr(missao, "3 territórios") != NULL) {
        int sequencia = 0;
        for (int i = 1; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, mapa[i - 1].cor) == 0) {
                sequencia++;
                if (sequencia >= 2) return 1;
            } else {
                sequencia = 0;
            }
        }
        return 0;
    }

    return 0;
}

// Função para liberar memória das missões
void liberarMissoes(char** missoes, int totalJogadores) {
    for (int i = 0; i < totalJogadores; i++) {
        free(missoes[i]);
    }
    free(missoes);
}

// Função para liberar a memória alocada dos territórios
void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("\n --- Memória liberada com sucesso. ---\n");
}

int main() {
    srand(time(NULL)); // Inicializa a aleatoriedade

    int total;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &total);

    Territorio* mapa = (Territorio*) calloc(total, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, total);
    exibirTerritorios(mapa, total);

    // Vetor de missões disponíveis
    char* missoesDisponiveis[] = {
        "Conquistar 3 territórios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Controlar pelo menos 5 territórios",
        "Ter mais de 50 tropas no total",
        "Conquistar territórios alternados"
    };
    int totalMissoes = 5;

    // Número de jogadores
    int jogadores = 2;
    char** missoesJogadores = (char**) malloc(jogadores * sizeof(char*));
    for (int i = 0; i < jogadores; i++) {
        missoesJogadores[i] = (char*) malloc(100 * sizeof(char));
        atribuirMissao(missoesJogadores[i], missoesDisponiveis, totalMissoes);
        printf("\n🧑 Jogador %d", i + 1);
        exibirMissao(missoesJogadores[i]);
    }

    // Simulação de ataque
    int atacante, defensor;
    printf("\n⚔️ Escolha os territórios para o ataque:\n");
    printf("Número do território atacante (1 a %d): ", total);
    scanf("%d", &atacante);
    printf("Número do território defensor (1 a %d): ", total);
    scanf("%d", &defensor);

    if (atacante < 1 || atacante > total || defensor < 1 || defensor > total) {
        printf("❌ Índices inválidos.\n");
    } else {
        atacar(&mapa[atacante - 1], &mapa[defensor - 1]);
        exibirTerritorios(mapa, total);
    }

    // Verificação de missão após o turno
    for (int i = 0; i < jogadores; i++) {
        if (verificarMissao(missoesJogadores[i], mapa, total)) {
            printf("\n🏆 Jogador %d venceu ao cumprir a missão: %s\n", i + 1, missoesJogadores[i]);
            break;
        }
    }

    liberarMissoes(missoesJogadores, jogadores);
    liberarMemoria(mapa);
    return 0;
}