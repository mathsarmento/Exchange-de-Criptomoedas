#include <stdio.h>
#include <string.h>
#include <windows.h>

void loading() {
    printf("\n");
    for (int i = 0; i <= 100; i++) {
        Sleep(15);
        printf(".");
    }
    printf("\n\n");
}

void resgatarSaldo(char* cpf, float* saldo, float* bitcoin, float* ethereum, float* ripple) {
    char arq[50]; 
    float saldoAux;
    float bitcoinAux;
    float ethereumAux;
    float rippleAux;
    
    sprintf(arq, "saldo/%s.txt", cpf);
    FILE *file = fopen(arq, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo saldo.txt");
        return;
    }

    fscanf(file, "%f", &saldoAux);
    fscanf(file, "%f", &bitcoinAux);
    fscanf(file, "%f", &ethereumAux);
    fscanf(file, "%f", &rippleAux);
    fclose(file);

    *saldo = saldoAux;
    *bitcoin = bitcoinAux;
    *ethereum = ethereumAux;
    *ripple = rippleAux;
}

void salvarSaldo(char* cpf, float saldo, float bitcoin, float ethereum, float ripple) {
    char arq[50]; 
    sprintf(arq, "saldo/%s.txt", cpf);
    
    FILE *file = fopen(arq, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo saldo.txt");
        return;
    }

    fprintf(file, "%f\n", saldo);
    fprintf(file, "%f\n", bitcoin);
    fprintf(file, "%f\n", ethereum);
    fprintf(file, "%f\n", ripple);

    fclose(file);
}

void criarSaldo(char* cpf) {
    char arq[50];
    sprintf(arq, "saldo/%s.txt", cpf);
    
    FILE *file = fopen(arq, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo saldo.txt");
        return;
    }

    fprintf(file, "0.0\n");
    fprintf(file, "0.0\n");
    fprintf(file, "0.0\n");
    fprintf(file, "0.0\n");

    fclose(file);
}

void criarRegistro(char* cpf) {
    char arq[50];
    sprintf(arq, "registros/%s.txt", cpf);
    
    FILE *file = fopen(arq, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo registro.txt");
        return;
    }

    fclose(file);
}

int lenRegistros(char* cpf) {
    char arq[50];
    sprintf(arq, "registros/%s.txt", cpf);
    
    FILE *file = fopen(arq, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo registro.txt");
        return 0;
    }

    int i = 0;
    char c;

    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            i++;
        }
    }

    fclose(file);
    return i;
}

void salvarRegistro(char* cpf, char* registro) {
    char arq[50];
    sprintf(arq, "registros/%s.txt", cpf);
    
    FILE *file = fopen(arq, "a");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo registro.txt");
        return;
    }

    fprintf(file, "%s\n", registro);

    fclose(file);
}

void resgatarRegistros(char* cpf) {
    char arq[50];
    sprintf(arq, "registros/%s.txt", cpf);
    
    FILE *file = fopen(arq, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo registro.txt");
        return;
    }

    while (1) {
        char registro[100];

        if (fscanf(file, "%[^\n]", registro) == 1) {
            printf("%s\n", registro);
           fgetc(file);
        } else {
            break;
        }
    }

    fclose(file);
}

int checkIsNumber(char* str){
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
    }
    return 1;
}

int checkCpfExist(char* cpf){
    char cpfCheck[20];
    FILE *file = fopen("cpfs.txt", "r");
    
    if (file == NULL) {
        perror("Erro ao abrir o arquivo cpfs.txt");
        return 0;
    }

    int i = 0;
    while (1) {
        if (feof(file)) {
            break;
        }

        fscanf(file, "%[^\n]", cpfCheck);
        fgetc(file);

        if (strcmp(cpf, cpfCheck) == 0) {
            fclose(file);
            return 1;
        }
        i++;
    }
    fclose(file);
    return 0;
}

int totalCpf() {
    FILE *file = fopen("cpfs.txt", "r");
    
    if (file == NULL) {
        perror("Erro ao abrir o arquivo cpfs.txt");
        return 0;
    }

    int i = 0;
    char c;

    // Loop para contar o número de linhas no arquivo
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            i++;
        }
    }

    fclose(file);
    return i;
}

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

    printf("Digite a senha do investidor (4 digitos): ");
    scanf("%[^\n]", senha);
    getchar();

    if (strlen(nome) == 0 || strlen(cpf) == 0 || strlen(senha) == 0) {
        printf("Nome, CPF ou senha invalidos!\n\n");
        Sleep(2000);
        registrarInvestidor();
        return;
    }
    if (strlen(cpf) != 11 || !checkIsNumber(cpf)) {
        printf("CPF invalido!\n\n");
        Sleep(2000);
        registrarInvestidor();
        return;
    }
    if (strlen(senha) < 4) 
    {
        printf("Senha invalida!\n\n");
        Sleep(2000);
        registrarInvestidor();
        return;
    }
    if (checkCpfExist(cpf)) {
        printf("CPF ja cadastrado!\n\n");
        Sleep(2000);
        registrarInvestidor();
        return;
    }
    if (totalCpf() >= 10) {
        printf("Numero maximo de investidores atingido!\n\n");
        return;
    }

    FILE *file = fopen("investidores.txt", "a");
    
    if (file == NULL) {
        perror("Erro ao abrir o arquivo investidores.txt");
        return;
    }

    fprintf(file, "%s\n%s\n%s\n", nome, cpf, senha);
    fclose(file);

    FILE *fileCpfs = fopen("cpfs.txt", "a");
    
    if (fileCpfs == NULL) {
        perror("Erro ao abrir o arquivo cpfs.txt");
        return;
    }

    fprintf(fileCpfs, "%s\n", cpf);
    fclose(fileCpfs);

    criarSaldo(cpf);
    criarRegistro(cpf);
    printf("Investidor registrado com sucesso!\n\n");
    
    printf("Deseja registrar outro investidor? (s para sim | enter para nao): ");
    scanf("%[^\n]", opcao);
    getchar();

    opcao[1] = '\0';

    if (strcmp(opcao, "s") == 0) {
        registrarInvestidor();
    }
    
    return;
}

int autenticarInvestidor(char* nome, char* cpf, char* senha, float* saldo, float* bitcoin, float* ethereum, float* ripple) {
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
        perror("Erro ao abrir o arquivo investidores.txt");
        return 0;
    }

    int autenticado = 0;

    printf("Autenticando...\n");
    loading();
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
            fclose(file);
            
            resgatarSaldo(cpf, saldo, bitcoin, ethereum, ripple);
            autenticado = 1;
            break;
        }
    }

    if (autenticado) {
        printf("Login bem-sucedido!\n");
        loading();

        return 1;
    } else {
        fclose(file);

        char opcao[100];
        
        printf("CPF ou senha incorreto!\n\n");
        printf("Deseja tentar novamente? (s para sim | enter para nao): ");
        
        scanf("%[^\n]", opcao);
        getchar();

        if (strcmp(opcao, "s") == 0) {
            return autenticarInvestidor(nome, cpf, senha, saldo, bitcoin, ethereum, ripple);
        } 
        return 0;
    }

}

void consultarsaldo(char* nome, char* cpf, float saldo, float bitcoin, float ethereum, float ripple, float bitcoinCotacao, float ethereumCotacao, float rippleCotacao) {
    printf("\nNome: %s\nCPF: %s\n", nome, cpf);
    printf("\nSeu saldo atual em reais: R$ %.2f\n", saldo);

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

void depositar(float* saldo, char* cpf) {
    float valor;
    char registro[100];
    
    printf("\nInforme o valor para deposito: R$ ");
    scanf("%f", &valor);
    if (valor > 0) {
        *saldo += valor;
        sprintf(registro, "+ R$%.2f depositado | Saldo: R$%.2f", valor, *saldo);
        salvarRegistro(cpf, registro);
        printf("Deposito realizado com sucesso!\n");
        printf("Seu novo saldo: R$ %.2f\n\n", *saldo);
    } else {
        printf("Valor invalido para deposito!\n\n");
    }
}

void sacar(float* saldo, char* senha, char* cpf) {
    float valor;
    char senhadigitada[100];
    char registro[100];

    printf("\nInforme o valor para saque: R$ ");
    scanf("%f", &valor);

    printf("Digite a senha: ");
    scanf("%s", senhadigitada);
    getchar();

    if (strcmp(senha, senhadigitada) == 0) { 
        if (valor > 0 && valor <= *saldo) {
            *saldo -= valor;
            sprintf(registro, "- R$%.2f sacado | Saldo: R$%.2f", valor, *saldo);
            salvarRegistro(cpf, registro);
            printf("Saque realizado com sucesso!\n");
            printf("Seu novo saldo: R$ %.2f\n\n", *saldo);
        } else if (valor > *saldo) {
            printf("Saldo insuficiente para saque!\n\n");
        } else {
            printf("Valor invalido para saque!\n\n");
        }
    } else {
        printf("Senha incorreta!\n\n");
    }
}

void exibirCotacao(float bitcoinCotacao, float ethereumCotacao, float rippleCotacao) {
    printf("Cotacao Atual:\n");
    printf("1 Bitcoin: R$ %.2f\n", bitcoinCotacao);
    printf("1 Ethereum: R$ %.2f\n", ethereumCotacao);
    printf("1 Ripple: R$ %.2f\n\n", rippleCotacao);
}

void comprarcriptomoedas(float* saldo, float* bitcoin, float* ripple, float* ethereum, char* senha, float bitcoinCotacao, float ethereumCotacao, float rippleCotacao, char* cpf) {
    int opcao;
    float valorcompra;
    float taxa;
    char senhadigitada[100];
    char registro[100];

    exibirCotacao(bitcoinCotacao, ethereumCotacao, rippleCotacao);

    printf("Selecione a criptomoeda que deseja comprar:\n");
    printf("1. Bitcoin (Taxa: 2%%)\n");
    printf("2. Ethereum (Taxa: 1%%)\n");
    printf("3. Ripple (Taxa: 1%%)\n");
    printf("4. Sair\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    if (opcao == 4) {
        printf("Saindo da compra...\n");
        return;
    }

    printf("Digite o valor em reais que deseja comprar: ");
    scanf("%f", &valorcompra);

    printf("Digite a senha para confirmar a compra: ");
    scanf("%s", senhadigitada);
    
    if (strcmp(senha, senhadigitada) != 0) {
        printf("Senha incorreta! A compra foi cancelada.\n\n");
        return;
    }

    if (valorcompra > *saldo)
    {
        printf("Saldo insuficiente para compra!\n\n");
        return;
    }
    

    if (valorcompra > 0) {
        switch (opcao) {
            case 1: // Bitcoin
                taxa = valorcompra * 0.02;
                *bitcoin += (valorcompra - taxa) / bitcoinCotacao;
                printf("Voce comprou R$ %.2f em Bitcoin (%.8f BTC).\n", valorcompra - taxa, (valorcompra - taxa) / bitcoinCotacao);
                printf("Taxa cobrada: R$ %.2f\n", taxa);
                sprintf(registro, "- R$%.2f | + %.8f BTC | taxa: %.2f | Saldo: R$%.2f", valorcompra - taxa, (valorcompra - taxa) / bitcoinCotacao, bitcoinCotacao, *saldo);
                salvarRegistro(cpf, registro);
                break;
            case 2: // Ethereum
                taxa = valorcompra * 0.01;
                *ethereum += (valorcompra - taxa) / ethereumCotacao;
                printf("Voce comprou R$ %.2f em Ethereum (%.8f ETH).\n", valorcompra - taxa, (valorcompra - taxa) / ethereumCotacao);
                printf("Taxa cobrada: R$ %.2f\n", taxa);
                sprintf(registro, "- R$%.2f | + %.8f ETH | taxa: %.2f | Saldo: R$%.2f", valorcompra - taxa, (valorcompra - taxa) / ethereumCotacao, ethereumCotacao, *saldo);
                salvarRegistro(cpf, registro);
                break;
            case 3: // Ripple
                taxa = valorcompra * 0.01; // 1% de taxa
                *ripple += (valorcompra - taxa) / rippleCotacao;
                printf("Voce comprou R$ %.2f em Ripple (%.8f XRP).\n", valorcompra - taxa, (valorcompra - taxa) / rippleCotacao);
                printf("Taxa cobrada: R$ %.2f\n", taxa);
                sprintf(registro, "- R$%.2f | + %.8f XRP | taxa: %.2f | Saldo: R$%.2f", valorcompra - taxa, (valorcompra - taxa) / rippleCotacao, rippleCotacao, *saldo);
                salvarRegistro(cpf, registro);
                break;
            default:
                printf("Opcao invalida! Selecione 1, 2, 3 ou 4.\n");
                break;
        }
    } else {
        printf("Valor invalido para compra!\n");
    }
}

void vendercriptomoedas(float* saldo, float* bitcoin, float* ripple, float* ethereum, char* senha, float bitcoinCotacao, float ethereumCotacao, float rippleCotacao, char* cpf) {
    int opcao;
    float valorVenda;
    float taxa;
    float valorVendaReal;
    char senhadigitada[100];
    char registro[100];

    printf("Selecione a criptomoeda que deseja vender:\n");
    printf("1. Bitcoin (Taxa: 3%%)\n");
    printf("2. Ethereum (Taxa: 2%%)\n");
    printf("3. Ripple (Taxa: 1%%)\n");
    printf("4. Sair\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    if (opcao == 4) {
        printf("Saindo da venda...\n");
        return;
    }

    printf("Digite a quantidade que deseja vender: ");
    scanf("%f", &valorVenda);

    printf("Digite a senha para confirmar a compra: ");
    scanf("%s", senhadigitada);
    
    if (strcmp(senha, senhadigitada) != 0) {
        printf("Senha incorreta! A compra foi cancelada.\n\n");
        return;
    }

    if (valorVenda > 0) {
        switch (opcao) {
            case 1: // Bitcoin
                if (*bitcoin >= valorVenda) {
                    valorVendaReal = valorVenda * bitcoinCotacao;
                    taxa = valorVendaReal * 0.03;
                    valorVendaReal -= taxa;
                    *bitcoin -= valorVenda;
                    printf("Você vendeu %.8f BTC.\n", valorVenda);
                    printf("Taxa cobrada: R$ %.2f\n", taxa);
                    printf("Você recebera R$ %.2f após a taxa.\n", valorVendaReal);
                    *saldo += valorVendaReal;
                    sprintf(registro, "+ R$%.2f | - %.8f BTC | Cot: R$%.2f | Saldo: R$%.2f",valorVendaReal, valorVenda, bitcoinCotacao, *saldo);
                    salvarRegistro(cpf, registro);
                } else {
                    printf("Saldo insuficiente para venda!\n");
                }
                break;
            case 2: // Ethereum
                if (*ethereum >= valorVenda) {
                    valorVendaReal = valorVenda * ethereumCotacao;
                    taxa = valorVendaReal * 0.02; 
                    valorVendaReal -= taxa;
                    *ethereum -= valorVenda;
                    printf("Você vendeu %.5f ETH.\n", valorVenda);
                    printf("Taxa cobrada: R$ %.2f\n", taxa);
                    printf("Você recebera R$ %.2f após a taxa.\n", valorVendaReal);
                    *saldo += valorVendaReal;
                    sprintf(registro, "+ R$%.2f | - %.5f ETH | Cot: R$%.2f | Saldo: R$%.2f",valorVendaReal, valorVenda, ethereumCotacao, *saldo);
                    salvarRegistro(cpf, registro);
                } else {
                    printf("Saldo insuficiente para venda!\n");
                }
                break;
            case 3: // Ripple
                if (*ripple >= valorVenda) {
                    valorVendaReal = valorVenda * rippleCotacao;
                    taxa = valorVendaReal * 0.01;
                    valorVendaReal -= taxa;
                    *ripple -= valorVenda;
                    printf("Você vendeu R$ %.2f XRP.\n", valorVenda);
                    printf("Taxa cobrada: R$ %.2f\n", taxa);
                    printf("Você recebera R$ %.2f após a taxa.\n", valorVendaReal);
                    *saldo += valorVendaReal;
                    sprintf(registro, "+ R$%.2f | - %.2f XRP | Cot: R$%.2f | Saldo: R$%.2f",valorVendaReal, valorVenda, rippleCotacao, *saldo);
                    salvarRegistro(cpf, registro);
                } else {
                    printf("Saldo insuficiente para venda!\n");
                }
                break;
            default:
                printf("Opção invalida! Selecione 1, 2, 3 ou 4.\n");
                break;
        }
    } else {
        printf("Valor invalido para venda!\n");
    }
}

void atualizarCotacao(float* bitcoinCotacao, float* ethereumCotacao, float* rippleCotacao) {
    float variacao;

    variacao = ((rand() % 100) / 100.0) * 0.1 - 0.05;
    *bitcoinCotacao *= (1 + variacao);
    
    variacao = ((rand() % 100) / 100.0) * 0.1 - 0.05;
    *ethereumCotacao *= (1 + variacao);
    
    variacao = ((rand() % 100) / 100.0) * 0.1 - 0.05;
    *rippleCotacao *= (1 + variacao);

    printf("Cotações atualizadas com sucesso!\n\n");
    
    exibirCotacao(*bitcoinCotacao, *ethereumCotacao, *rippleCotacao);
}
    
int menuInvestidor(char* nome, char* cpf, char* senha, float *saldo, float *bitcoin, float *ethereum, float *ripple) {
    int opcao = 0;
    float bitcoinCotacao = 200000.0;
    float ethereumCotacao = 12000.0;
    float rippleCotacao = 5.50;
    int numeroRegistros;

    while (opcao != 8) {
        numeroRegistros = lenRegistros(cpf);
        if (numeroRegistros >= 100) {
            printf("Numero maximo de registros atingido!\n\n");
            loading();
            return 0;
        }
        
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
                consultarsaldo(nome, cpf, *saldo, *bitcoin, *ethereum, *ripple, bitcoinCotacao, ethereumCotacao, rippleCotacao);
                break;
            
            case 2:
                resgatarRegistros(cpf);
                break;

            case 3:
                depositar(saldo, cpf);
                salvarSaldo(cpf, *saldo, *bitcoin, *ethereum, *ripple);
                break;

            case 4:
                sacar(saldo, senha, cpf);
                salvarSaldo(cpf, *saldo, *bitcoin, *ethereum, *ripple);
                break;

            case 5:
                comprarcriptomoedas(saldo, bitcoin, ripple, ethereum, senha, bitcoinCotacao, ethereumCotacao, rippleCotacao, cpf);
                salvarSaldo(cpf, *saldo, *bitcoin, *ethereum, *ripple);
                break;

            case 6:
                exibirCotacao(bitcoinCotacao, ethereumCotacao, rippleCotacao);
                loading();
                vendercriptomoedas(saldo, bitcoin, ripple, ethereum, senha, bitcoinCotacao, ethereumCotacao, rippleCotacao, cpf);
                salvarSaldo(cpf, *saldo, *bitcoin, *ethereum, *ripple);
                break;

            case 7:
                atualizarCotacao(&bitcoinCotacao, &ethereumCotacao, &rippleCotacao);
                break;

            case 8:
                printf("Obrigado por utilizar o sistema, %s! Ate logo.\n\n", nome);
                loading();
                return 0;

            default:
                printf("Opcao invalida! Por favor, selecione uma opcao valida.\n\n");
        }
        loading();
    }

    return 0;
}

int main() {
    int autenticado = 0;
    char cpfAuth[100];
    char senhaAuth[100];
    char nomeAuth[100];

    float saldo = 0.0;
    float bitcoin = 0.0;
    float ethereum = 0.0;
    float ripple = 0.0;

    printf("\n\nBem-vindo ao sistema de investimentos!\n\n");
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
            autenticado = autenticarInvestidor(nomeAuth, cpfAuth, senhaAuth, &saldo, &bitcoin, &ethereum, &ripple);

            while (autenticado) {
               autenticado = menuInvestidor(nomeAuth, cpfAuth, senhaAuth, &saldo, &bitcoin, &ethereum, &ripple);
            }
        } else if (opcao == 3) {
            printf("Saindo...\n");
            break;
        } else {
            printf("Opcao invalida! Tente novamente.\n");
        }
    }
    
}
