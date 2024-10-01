#include <stdio.h>
#include <string.h>
#include <windows.h>

void registrarInvestidor(){
    char cpf[100];
    char nome[100];
    char senha[100];
    char opcao[100];

    printf("Digite o nome do investidor: ");
    scanf("%[^\n]", nome);
    getchar();

    printf("Digite o CPF do investidor: ");
    scanf("%[^\n]", cpf);
    getchar();

    printf("Digite a senha para entrar: ");
    scanf("%[^\n]", senha);
    getchar();

    // TODO adicionar para verificar no arquivo se o investidor já existe ou não colocou nada em nome ou senha ou cpf

    FILE *file = fopen("investidores.txt", "a");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    fprintf(file, "%s\n%s\n%s\n", nome, cpf, senha);
    fclose(file);
    printf("Investidor registrado com sucesso!\n");
    
    printf("Deseja registrar outro investidor? (s para sim | enter para nao): ");
    scanf("%[^\n]", opcao);
    getchar();

    opcao[1] = '\0';

    if (strcmp(opcao, "s") == 0) {
        registrarInvestidor();
    }
    
    return;
}

int autenticarInvestidor(char* nome, char* cpf, char* senha) {
    char cpfAuth[100];
    char nomeAuth[100];
    char senhaAuth[100];

    printf("Digite o CPF do investidor: ");
    scanf("%s", cpf);
    getchar();

    printf("Digite a senha: ");
    scanf("%s", senha);
    getchar();

    printf("\n");
    FILE *file = fopen("investidores.txt", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 0;
    }

    int autenticado = 0;

    printf("Autenticando...\n\n");
    // Sleep(2000);
    while (1) {
        if (feof(file)) {
            break;
        }

        fscanf(file, "%[^\n]", nomeAuth);
        fgetc(file);
        fscanf(file, "%[^\n]", cpfAuth);
        fgetc(file);
        fscanf(file, "%[^\n]", senhaAuth);
        fgetc(file);

        if (strcmp(cpf, cpfAuth) == 0 && strcmp(senha, senhaAuth) == 0) {
            strcpy(nome, nomeAuth);
            strcpy(cpf, cpfAuth);
            strcpy(senha, senhaAuth);

            autenticado = 1;
            break;
        }
    }
    fclose(file);
    // Sleep(2000);

    if (autenticado) {
        printf("Login bem-sucedido!\n\n\n");
        // Sleep(2000);
        return 1;
    } else {
        char opcao[100];
        
        printf("CPF ou senha incorreto!\n\n");
        printf("Deseja tentar novamente? (s para sim | enter para nao): ");
        
        scanf("%[^\n]", opcao);
        getchar();

        if (strcmp(opcao, "s") == 0) {
            return autenticarInvestidor(nome, cpf, senha);
        } 
        return 0;
    }

}

void consultarsaldo(char* nome, char* cpf, float saldo, float bitcoin, float ethereum, float ripple, float bitcoinCotacao, float ethereumCotacao, float rippleCotacao) {
    printf("\nNome: %s\nCPF: %s\n", nome, cpf);
    printf("\nSeu saldo atual em reais: R$ %.2f\n", saldo);

     // Verifica se o saldo de cada criptomoeda é maior que zero antes de realizar a conversão
    if (bitcoin > 0) {
        printf("Seu saldo atual em Bitcoin: %.8f BTC (R$ %.2f)\n", bitcoin, bitcoin * bitcoinCotacao);
    } else {
        printf("Seu saldo atual em Bitcoin: 0 BTC (R$ 0.00)\n");
    }

    if (ethereum > 0) {
        printf("Seu saldo atual em Ethereum: %.8f ETH (R$ %.2f)\n", ethereum, ethereum * ethereumCotacao);
    } else {
        printf("Seu saldo atual em Ethereum: 0 ETH (R$ 0.00)\n");
    }

    if (ripple > 0) {
        printf("Seu saldo atual em Ripple: %.8f XRP (R$ %.2f)\n", ripple, ripple * rippleCotacao);
    } else {
        printf("Seu saldo atual em Ripple: 0 XRP (R$ 0.00)\n\n");
    }
}

void depositar(float* saldo) {
    float valor;
    printf("\nInforme o valor para deposito: R$ ");
    scanf("%f", &valor);
    if (valor > 0) {
        *saldo += valor;
        printf("Deposito realizado com sucesso!\n");
        printf("Seu novo saldo: R$ %.2f\n\n", *saldo);
    } else {
        printf("Valor invalido para deposito!\n\n");
    }
}

void sacar(float* saldo, char* senha) {
    float valor;
    char senhadigitada[100];

    printf("\nInforme o valor para saque: R$ ");
    scanf("%f", &valor);

    printf("Digite a senha: ");
    scanf("%s", senhadigitada);
    getchar(); // Clear the input buffer

    if (strcmp(senha, senhadigitada) == 0) { 
        if (valor > 0 && valor <= *saldo) {
            *saldo -= valor;
            printf("Saque realizado com sucesso!\n");
            printf("Seu novo saldo é: R$ %.2f\n\n", *saldo);
        } else if (valor > *saldo) {
            printf("Saldo insuficiente para saque!\n\n");
        } else {
            printf("Valor inválido para saque!\n\n");
        }
    } else {
        printf("Senha incorreta!\n\n");
    }
}

int menuInvestidor(char* nome, char* cpf, char* senha, float* bitcoinCotacao, float* ethereumCotacao, float* rippleCotacao ) {
    int opcao = 0;
    float saldo = 0.0;
    float bitcoin = 0.0;
    float ethereum = 0.0;
    float ripple = 0.0;

    while (opcao != 8) {
        printf("Selecione a opcao desejada:\n");
        printf("1. Ver saldo\n");
        printf("2. Consultar extrato\n");
        printf("3. Depositar\n");
        printf("4. Sacar\n");
        printf("5. Comprar criptomoedas\n");
        printf("6. Vender criptomoedas\n");
        printf("7. Atualizar cotacao\n");
        printf("8. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                consultarsaldo(nome, cpf, saldo, bitcoin, ethereum, ripple, *bitcoinCotacao, *ethereumCotacao, *rippleCotacao);
                break;
            
            case 2:
                //consultarextrato();
                break;

            case 3:
                depositar(&saldo);
                break;

            case 4:
                sacar(&saldo, senha);
                break;

            case 5:
                // comprarcriptomoedas(&bitcoin, &ripple, &ethereum, senha, *bitcoinCotacao, *ethereumCotacao, *rippleCotacao);
                break;

            case 6:
                // vendercriptomoedas(bitcoinCotacao, ethereumCotacao, rippleCotacao, senha);
                break;

            case 7:
                // atualizarCotacao(bitcoinCotacao, ethereumCotacao, rippleCotacao);
                break;

            case 8:
                printf("Obrigado por utilizar o sistema, %s! Ate logo.\n\n", nome);
                return 0;

            default:
                printf("Opcao invalida! Por favor, selecione uma opcao valida.\n\n");
        }
    }

    return 0;
}

int main() {
    int autenticado = 0;
    char cpfAuth[100];
    char senhaAuth[100];
    char nomeAuth[100];
    float bitcoinCotacao = 0;
    float ethereumCotacao = 0;
    float rippleCotacao = 0;

    while (1)
    {
        int opcao;

        printf("Selecione a opcao desejada:\n\n");
        printf("1. Registrar investidor\n");
        printf("2. Logar investidor\n");
        printf("3. Sair\n\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();
        printf("\n\n");

        if (opcao == 1) {
            registrarInvestidor();
        } else if (opcao == 2) {
            autenticado = autenticarInvestidor(nomeAuth, cpfAuth, senhaAuth);

            while (autenticado) {
               autenticado = menuInvestidor(nomeAuth, cpfAuth, senhaAuth, &bitcoinCotacao, &ethereumCotacao, &rippleCotacao);
            }
        } else if (opcao == 3) {
            printf("Saindo...\n");
            break;
        } else {
            printf("Opcao invalida! Tente novamente.\n");
        }
    }
    
}
