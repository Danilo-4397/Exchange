#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USUARIOS 10
#define MAX_TRANSACOES 100

typedef struct {
    char cpf[12];
    char senha[7];
    double saldo_reais;
    double saldo_bitcoin;
    double saldo_ethereum;
    double saldo_ripple;
} Usuario;

typedef struct {
    char descricao[100];
    char data[20];
} Transacao;

typedef struct {
    Usuario usuario;
    Transacao transacoes[MAX_TRANSACOES];
    int num_transacoes;
} Carteira;

void salvar_usuarios(Carteira usuarios[], int num_usuarios) {
    FILE *arquivo = fopen("carteiras.dat", "wb");
    if (arquivo != NULL) {
        fwrite(usuarios, sizeof(Carteira), num_usuarios, arquivo);
        fclose(arquivo);
    } else {
        printf("Erro ao salvar os dados dos usuários.\n");
    }
}

void carregar_usuarios(Carteira usuarios[], int *num_usuarios) {
    FILE *arquivo = fopen("carteiras.dat", "rb");
    if (arquivo != NULL) {
        *num_usuarios = fread(usuarios, sizeof(Carteira), MAX_USUARIOS, arquivo);
        fclose(arquivo);
    } else {
        printf("Erro ao carregar os dados dos usuários.\n");
    }
}

int usuario_existe(Carteira usuarios[], int num_usuarios, const char *cpf) {
    for (int i = 0; i < num_usuarios; i++) {
        if (strcmp(usuarios[i].usuario.cpf, cpf) == 0) {
            return 1; // Usuário já existe
        }
    }
    return 0; // Usuário não existe
}

void cadastrar_usuario(Carteira usuarios[], int *num_usuarios) {
    if (*num_usuarios >= MAX_USUARIOS) {
        printf("Limite de usuários atingido. Não é possível cadastrar mais.\n");
        return;
    }

    printf("Cadastro de novo usuário:\n");
    char cpf[12], senha[7];

    printf("CPF (apenas números): ");
    scanf("%s", cpf);
    if (usuario_existe(usuarios, *num_usuarios, cpf)) {
        printf("Usuário com este CPF já cadastrado!\n");
        return;
    }

    printf("Senha (6 caracteres): ");
    scanf("%s", senha);

    // Adiciona novo usuário
    strcpy(usuarios[*num_usuarios].usuario.cpf, cpf);
    strcpy(usuarios[*num_usuarios].usuario.senha, senha);
    usuarios[*num_usuarios].usuario.saldo_reais = 0;
    usuarios[*num_usuarios].usuario.saldo_bitcoin = 0;
    usuarios[*num_usuarios].usuario.saldo_ethereum = 0;
    usuarios[*num_usuarios].usuario.saldo_ripple = 0;
    usuarios[*num_usuarios].num_transacoes = 0;

    (*num_usuarios)++;
    printf("Usuário cadastrado com sucesso!\n");
}

int login(Carteira usuarios[], int num_usuarios) {
    char cpf[12], senha[7];
    printf("CPF: ");
    scanf("%s", cpf);
    printf("Senha: ");
    scanf("%s", senha);

    for (int i = 0; i < num_usuarios; i++) {
        if (strcmp(usuarios[i].usuario.cpf, cpf) == 0 && strcmp(usuarios[i].usuario.senha, senha) == 0) {
            printf("Login bem-sucedido!\n");
            return i;  // Retorna o índice do usuário
        }
    }
    printf("CPF ou senha incorretos!\n");
    return -1;  // Login falhou
}

void consultar_saldo(Carteira *usuario) {
    printf("Saldo em reais: R$ %.2f\n", usuario->usuario.saldo_reais);
    printf("Saldo em Bitcoin: %.6f BTC\n", usuario->usuario.saldo_bitcoin);
    printf("Saldo em Ethereum: %.6f ETH\n", usuario->usuario.saldo_ethereum);
    printf("Saldo em Ripple: %.6f XRP\n", usuario->usuario.saldo_ripple);
}

void deposito(Carteira *usuario) {
    double valor;
    printf("Valor a depositar: R$ ");
    scanf("%lf", &valor);
    usuario->usuario.saldo_reais += valor;
    printf("Depósito realizado com sucesso! Novo saldo: R$ %.2f\n", usuario->usuario.saldo_reais);
}

int saque(Carteira *usuario) {
    char senha[7];
    double valor;
    printf("Senha: ");
    scanf("%s", senha);
    if (strcmp(usuario->usuario.senha, senha) != 0) {
        printf("Senha incorreta!\n");
        return 0;
    }

    printf("Valor a sacar: R$ ");
    scanf("%lf", &valor);

    if (valor > usuario->usuario.saldo_reais) {
        printf("Saldo insuficiente!\n");
        return 0;
    }

    usuario->usuario.saldo_reais -= valor;
    printf("Saque realizado com sucesso! Novo saldo: R$ %.2f\n", usuario->usuario.saldo_reais);
    return 1;
}

void comprar_criptomoeda(Carteira *usuario, double cotacao, const char *nome_cripto, double *saldo_cripto, double taxa) {
    double valor_reais, quantidade_cripto, custo_total;
    char senha[7];

    printf("Senha: ");
    scanf("%s", senha);
    if (strcmp(usuario->usuario.senha, senha) != 0) {
        printf("Senha incorreta!\n");
        return;
    }

    printf("Valor a investir em %s: R$ ", nome_cripto);
    scanf("%lf", &valor_reais);

    custo_total = valor_reais * (1 + taxa);
    if (custo_total > usuario->usuario.saldo_reais) {
        printf("Saldo insuficiente!\n");
        return;
    }

    quantidade_cripto = valor_reais / cotacao;
    usuario->usuario.saldo_reais -= custo_total;
    *saldo_cripto += quantidade_cripto;
    printf("Compra de %.6f %s realizada com sucesso! Taxa: %.2f%%\n", quantidade_cripto, nome_cripto, taxa * 100);
}

void vender_criptomoeda(Carteira *usuario, double cotacao, const char *nome_cripto, double *saldo_cripto, double taxa) {
    double valor_reais, quantidade_cripto, valor_venda;
    char senha[7];

    printf("Senha: ");
    scanf("%s", senha);
    if (strcmp(usuario->usuario.senha, senha) != 0) {
        printf("Senha incorreta!\n");
        return;
    }

    printf("Quantidade de %s a vender: ", nome_cripto);
    scanf("%lf", &quantidade_cripto);

    if (quantidade_cripto > *saldo_cripto) {
        printf("Saldo insuficiente de %s!\n", nome_cripto);
        return;
    }

    valor_venda = quantidade_cripto * cotacao * (1 - taxa);
    *saldo_cripto -= quantidade_cripto;
    usuario->usuario.saldo_reais += valor_venda;
    printf("Venda de %.6f %s realizada com sucesso! Taxa: %.2f%%\n", quantidade_cripto, nome_cripto, taxa * 100);
}

void atualizar_cotacoes(double *bitcoin, double *ethereum, double *ripple) {
    srand(time(NULL));
    *bitcoin += *bitcoin * ((rand() % 1001 - 500) / 10000.0);
    *ethereum += *ethereum * ((rand() % 1001 - 500) / 10000.0);
    *ripple += *ripple * ((rand() % 1001 - 500) / 10000.0);
    printf("Cotações atualizadas!\n");
}

void salvar_transacao(Carteira *usuario, const char *descricao) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char data[20];
    strftime(data, 20, "%Y-%m-%d %H:%M:%S", tm_info);

    if (usuario->num_transacoes < MAX_TRANSACOES) {
        strcpy(usuario->transacoes[usuario->num_transacoes].descricao, descricao);
        strcpy(usuario->transacoes[usuario->num_transacoes].data, data);
        usuario->num_transacoes++;
    } else {
        printf("Histórico de transações cheio!\n");
    }

    // Salvar no arquivo de texto
    FILE *arquivo = fopen("extrato.txt", "a");
    if (arquivo != NULL) {
        fprintf(arquivo, "%s - %s\n", data, descricao);
        fclose(arquivo);
    } else {
        printf("Erro ao salvar o extrato de transações.\n");
    }
}

void menu(Carteira *usuario) {
    int opcao;
    double cotacao_bitcoin = 50000.0;
    double cotacao_ethereum = 4000.0;
    double cotacao_ripple = 1.0;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Consultar Saldo\n");
        printf("2. Consultar Extrato\n");
        printf("3. Depositar Reais\n");
        printf("4. Sacar Reais\n");
        printf("5. Comprar Criptomoedas\n");
        printf("6. Vender Criptomoedas\n");
        printf("7. Atualizar Cotações\n");
        printf("8. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                consultar_saldo(usuario);
                break;
            case 2:
                for (int i = 0; i < usuario->num_transacoes; i++) {
                    printf("%s - %s\n", usuario->transacoes[i].data, usuario->transacoes[i].descricao);
                }
                break;
            case 3:
                deposito(usuario);
                break;
            case 4:
                saque(usuario);
                break;
            case 5:
                printf("Escolha uma criptomoeda para comprar:\n1. Bitcoin\n2. Ethereum\n3. Ripple\n");
                scanf("%d", &opcao);
                if (opcao == 1) {
                    comprar_criptomoeda(usuario, cotacao_bitcoin, "Bitcoin", &usuario->usuario.saldo_bitcoin, 0.02);
                    salvar_transacao(usuario, "Compra de Bitcoin.");
                } else if (opcao == 2) {
                    comprar_criptomoeda(usuario, cotacao_ethereum, "Ethereum", &usuario->usuario.saldo_ethereum, 0.01);
                    salvar_transacao(usuario, "Compra de Ethereum.");
                } else if (opcao == 3) {
                    comprar_criptomoeda(usuario, cotacao_ripple, "Ripple", &usuario->usuario.saldo_ripple, 0.01);
                    salvar_transacao(usuario, "Compra de Ripple.");
                }
                break;
            case 6:
                printf("Escolha uma criptomoeda para vender:\n1. Bitcoin\n2. Ethereum\n3. Ripple\n");
                scanf("%d", &opcao);
                if (opcao == 1) {
                    vender_criptomoeda(usuario, cotacao_bitcoin, "Bitcoin", &usuario->usuario.saldo_bitcoin, 0.03);
                    salvar_transacao(usuario, "Venda de Bitcoin.");
                } else if (opcao == 2) {
                    vender_criptomoeda(usuario, cotacao_ethereum, "Ethereum", &usuario->usuario.saldo_ethereum, 0.02);
                    salvar_transacao(usuario, "Venda de Ethereum.");
                } else if (opcao == 3) {
                    vender_criptomoeda(usuario, cotacao_ripple, "Ripple", &usuario->usuario.saldo_ripple, 0.01);
                    salvar_transacao(usuario, "Venda de Ripple.");
                }
                break;
            case 7:
                atualizar_cotacoes(&cotacao_bitcoin, &cotacao_ethereum, &cotacao_ripple);
                break;
            case 8:
                return;
            default:
                printf("Opção inválida!\n");
        }
    }
}

int main() {
    Carteira usuarios[MAX_USUARIOS];
    int num_usuarios = 0, indice_usuario;

    carregar_usuarios(usuarios, &num_usuarios);

    int opcao;
    printf("1. Login\n2. Cadastrar\nEscolha uma opção: ");
    scanf("%d", &opcao);
    if (opcao == 1) {
        indice_usuario = login(usuarios, num_usuarios);
        if (indice_usuario >= 0) {
            menu(&usuarios[indice_usuario]);
            salvar_usuarios(usuarios, num_usuarios);
        }
    } else if (opcao == 2) {
        cadastrar_usuario(usuarios, &num_usuarios);
        salvar_usuarios(usuarios, num_usuarios);
    } else {
        printf("Opção inválida!\n");
    }

    return 0;
}
