/*
 * Universidade Federal Rural de Pernambuco
 * Bacharelado em Sistemas de Informação
 * Docente: Sônia 
 * Nome: José Carlos da Silva Cavalcanti
 * Polo - Surubim
 * Compilador: online, disponível em https://www.online-cpp.com/online_c_compiler
 */

#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int    codigo;
    char   nome[20];       
    int    sexo;           
    int    tratamento;     
    int    conveniado;    
    double valor;          
} Paciente;

Paciente pacientes[MAX];
int total = 0;

int    menuPrincipal(void);
void   cadastrarPaciente(void);
void   listarPacientes(void);
void   relatorioEstatistico(void);
double calcularValor(int tratamento, int conveniado, int sexo);

// MAIN
int main(void) {
    int opc;
    do {
        opc = menuPrincipal();
        switch (opc) {
            case 1: cadastrarPaciente();      break;
            case 2: listarPacientes();        break;
            case 3: relatorioEstatistico();   break;
            case 0: printf("\nSaindo...\n");   break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opc != 0);
    return 0;
}

//Menu principal
int menuPrincipal(void) {
    int op;
    printf("\nClinica Odontologica Sorriso\n\n");
    printf("1 - Cadastrar Paciente\n");
    printf("2 - Listagem Geral\n");
    printf("3 - Relatorio Estatistico\n");
    printf("0 - Sair\n");
    printf("\nOpcao desejada: ");
    scanf("%d", &op);
    return op;
}

double calcularValor(int tratamento, int conveniado, int sexo) {
    double tabelaNao[5] = {0.0, 110.0, 135.0, 460.0, 290.0};
    double tabelaSim[5] = {0.0,  65.0, 107.0, 280.0, 210.0};
    double base = conveniado
                  ? tabelaSim[tratamento]
                  : tabelaNao[tratamento];
    if (sexo == 1)   // desconto 15% para feminino 
        base *= 0.85;
    return base;
}





void cadastrarPaciente(void) {
    int continua;
    do {
        Paciente p;
        printf("\n--- Cadastro de Paciente ---\n");
        printf("Codigo: ");
        scanf("%d", &p.codigo);
        printf("Nome: ");
        scanf(" %15[^\n]", p.nome);
        printf("Sexo (1-fem/2-mas): ");
        scanf("%d", &p.sexo);
        printf("Tratamento (1-ext/2-res/3-canal/4-limpeza): ");
        scanf("%d", &p.tratamento);
        printf("Conveniado (1-sim/0-nao): ");
        scanf("%d", &p.conveniado);

        p.valor = calcularValor(p.tratamento, p.conveniado, p.sexo);
        pacientes[total++] = p;

        printf("Cadastrar outro (1-sim/0-nao)? ");
        scanf("%d", &continua);
    } while (continua == 1 && total < MAX);
}




void listarPacientes(void) {
    printf("\n--- Listagem Geral ---\n");
    printf("%-5s %-15s %-4s %-10s %-10s %-12s\n",
           "Cod", "Nome", "Sexo", "Trat.", "Conv.", "Valor");
    for (int i = 0; i < total; i++) {
        Paciente *p = &pacientes[i];
        printf("%-5d %-15s %-4d %-10d %-10d R$ %8.2f\n",
               p->codigo, p->nome,
               p->sexo, p->tratamento, p->conveniado,
               p->valor);
    }
    printf("\nTecle ENTER para voltar...");
    getchar(); getchar();
}




void relatorioEstatistico(void) {
    int contMulherCanal = 0, totMulher = 0;
    int contHomemConv = 0, contHomem = 0;
    double somaValHomem = 0.0;
    double arrecadExtracao = 0.0;

    for (int i = 0; i < total; i++) {
        Paciente *p = &pacientes[i];
        //percentual mulheres que fizeram canal 
        if (p->sexo == 1) {
            totMulher++;
            if (p->tratamento == 3) contMulherCanal++;
        }
        //homens e conveniados 
        if (p->sexo == 2) {
            contHomem++;
            somaValHomem += p->valor;
            if (p->conveniado == 1) contHomemConv++;
        }
        // arrecadado com extracao 
        if (p->tratamento == 1) {
            arrecadExtracao += p->valor;
        }
    }

    double pctMulherCanal = (totMulher > 0)
                            ? (100.0 * contMulherCanal / totMulher)
                            : 0.0;
    double mediaHomens = (contHomem > 0)
                         ? (somaValHomem / contHomem)
                         : 0.0;

    printf("\n--- Relatorio Estatistico ---\n");
    printf("Percentual de mulheres que fizeram canal: %.2f%%\n",
           pctMulherCanal);
           
    printf("Quantidade de homens em empresas conveniadas: %d\n",
           contHomemConv);
           
    printf("Media do valor dos tratamentos dos homens: R$ %.2f\n",
           mediaHomens);
           
    printf("Valor arrecadado com extracao: R$ %.2f\n",
           arrecadExtracao);
           

    printf("\nTecle ENTER para voltar...");
    getchar(); getchar();
}
