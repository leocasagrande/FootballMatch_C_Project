// Alunos:
// Leonardo Casagrande UC21106140
// Vithor Felix        UC21200066

#include <stdio.h>  //Bibliotecas usadas no programa
#include <string.h>
#include <stdlib.h>

#define MAX_JOGOS 450 //Define para o maximo de jogos
#define TAM_CIDADE 120  //Define para o maximo de caracteres do nome da cidade
#define MAX_PRE 120 //Define o max de caracteres para o nome do presidente

int le_valida_id(int *jogos);//funcao para retornar o id de cada jogo
float le_valida_arrecadacao();//funcao para retornar o valor arrecadado de cada jogo
char *le_valida_cidade();//funcao para retornar o nome da cidade sede

//funcao int
int main(){
    int i = 0, j = 0, k = 0, opcao_menu = 0, num_jogos = 0, i_cidades = 0, tam_presidente = 0, contador = 0;//variaveis do tipo inteiro
    int id_jogos[MAX_JOGOS];//variavel do tipo inteiro
    float arrecadacao[MAX_JOGOS];//variavel do tipo float
    char cidade[MAX_JOGOS][TAM_CIDADE], *ponteiro;//variaveis do tipo char
    char consulta_cidade[TAM_CIDADE];//variaveis do tipo char
    char n_presidente[MAX_PRE];//variaveis do tipo char

    FILE *p_arquivo;//criando o arquivo
    p_arquivo = fopen("nome_presidente.txt", "w");//abertura do arquivo

    //do while para arquivar o nome do presidente
    do {
        printf("Nome do presidente: ");
        fflush(stdin);
        scanf("%[^\n]s", &n_presidente);
        tam_presidente = strlen(n_presidente);
        for (j=0; j<tam_presidente; j++){
            n_presidente[j] = tolower(n_presidente[j]);//botar o nome todo do presidente em minusculo
        }

        n_presidente[0] = toupper(n_presidente[0]);//botar a primeira letra do nome do presidente em maiusculo

        for (j=0; j<tam_presidente; j++){
            if (n_presidente[j] == ' '){
                n_presidente[j+1] = toupper(n_presidente[j+1]);//cada letra depois de um espaco no nome vai ser retornada maiuscula
            }
        }
        
        fprintf(p_arquivo, "%s", n_presidente);//salvando o nome do presidente no arquivo
        fclose(p_arquivo);//fechando o arquivo

        system("cls");

    } while (tam_presidente < 3 || tam_presidente > MAX_PRE);//do while para nome menor que 3 e maior que o max de caracteres disponiveis

//do while do MENU 
    do {
        printf("-------------------------");
    	printf("\n1 - Cadastrar jogo");
    	printf("\n2 - Mostrar tabela dos jogos cadastrados");
    	printf("\n3 - Consultar jogo");
    	printf("\n4 - Encerrar programa\n");
    	printf("-------------------------\n");
    	printf("\nINFORME O QUE DESEJA FAZER: ");
    	scanf("%d", &opcao_menu);//salvando na variavel o numero que o usuario digitou

        system("cls");

//switch case para as 4 opcoes possiveis do usuario
        switch (opcao_menu) {
        case 1:
            id_jogos[i] = le_valida_id(id_jogos);//id jogos[i] recebe o valor retornado da funcao de id
            arrecadacao[i] = le_valida_arrecadacao();//arrecadacao[i] recebe o valor retornado da funcao de arrecadacao 
            ponteiro = le_valida_cidade();//ponteiro recebe o nome validado na funcao valida_cidade
            strcpy(cidade[i], ponteiro);//o nome que ponteiro recebeu sera passado para cidade[i]
            i++;//adicao do i a cada loop
            num_jogos++;//adicao e num_jogos a cada loop
            break;//fim do case
        case 2:
            if (num_jogos<1){//se nao existir jogo cadastrado ele vai avisar
                printf("NENHUM JOGO CADASTRADO\n");
                break;
            } else {//se ja existir algum jogo, o programa vai printar todas as informacoes necessarias
                printf("PRESIDENTE: %s\n\n", n_presidente);
                for(j=0; j<num_jogos; j++){//for para printar as informacoes dos jogos
                    fflush(stdin);
                    printf("CIDADE:%s\t\tID DO JOGO:%d\t\tVALOR ARRECADADO:%.2f\n", cidade[j], id_jogos[j], arrecadacao[j]);
                }
            }
            break;//fim do case 2
        case 3:
            if (num_jogos == 0){//if para informar que nao tem nenhuma cidade cadastrada 
                printf("Nenhuma cidade cadastrada.\n\n");
            } else {//se ja existir alguma cidade cadastrada, o programa vai informar as informacoes dos jogos feitos na cidade
                printf("Digite a cidade que deseja consultar: ");
                fflush(stdin);
                scanf("%[^\n]s", &consulta_cidade);
                system("cls");
                printf("Informacao do(s) jogo(s) em %s:\n\n", consulta_cidade);
                for (j=0; j<MAX_JOGOS; j++){
                    if (strcmp(consulta_cidade, cidade[j]) == 0){//comparacao para saber se cidade[j] e a cidade que o usuario deseja consultar sao iguais. Caso sejam, o programa vai informar os ids e arrecadacoes dos jogos da cidade
                        printf("ID DO JOGO:%d\t\tARRECADACAO:R$%.2f\n\n", id_jogos[j], arrecadacao[j]);
                    }
                }
            }
            break;//fim do case 3
        case 4:
            printf("Obrigado!");
            return 0;//fechar o programa
            break;//fim do case 4
        }

        opcao_menu = 0;//opcao_menu recebe 0 para sempre continuar no looping do MENU
    } while (opcao_menu < 1 || opcao_menu > 3);//fim do do while para o MENU
}

int le_valida_id (int *jogos){//funcao para validar a id do jogo
    int i = 0;
    int id_jogo = 0;
    do {
        printf("Informe o ID: ");
        scanf("%d", &id_jogo);
        system("cls");
        if (id_jogo < 300 || id_jogo > 10000){
            system("cls");
            printf("ERRO - ID INVALIDO\n");
        }
        for (i=0; i<MAX_JOGOS; i++){
            if(id_jogo == jogos[i]){//if para o id nao se repitir
                system("cls");
                printf("ERRO - ID JA CADASTRADO\n");
                id_jogo = 0;
            }
            break;
        }
    } while (id_jogo < 300 || id_jogo > 10000);
    
    return id_jogo;//retorna o valor de id
}

float le_valida_arrecadacao(){//funcao para receber o valor arrecadado
    float valor_arrecadado;

    do{
        printf("Informe o valor arrecadado: R$");
        scanf("%f", &valor_arrecadado);
        system("cls");
        if(valor_arrecadado < 1000 || valor_arrecadado > 1000000){
            system("cls");
            printf("- ERRO - VALOR NAO ACEITO\n");
        }

    }while(valor_arrecadado<1000 || valor_arrecadado>1000000);

    return valor_arrecadado;//retorna o valor arrecadado
}

char *le_valida_cidade(){//funcao para validar a cidade

    int i = 0, tam = 0;
    char cidade[TAM_CIDADE], *ponteiro;
    do {
        printf("Informe a cidade que o jogo foi realizado: ");
        fflush(stdin);
        scanf("%[^\n]s", &cidade);
        system("cls");
        tam = strlen(cidade);
        if(tam < 3 || tam > TAM_CIDADE){
            system("cls");
            printf("ERRO - NOME INVALIDO.\n");
        }
    } while (tam < 3 || tam > TAM_CIDADE);
    for (i=0; i<tam; i++){
        cidade[i] = tolower(cidade[i]);//colocar o nome da cidade toda em minusculo
    }
    ponteiro = malloc(tam * sizeof(char));
    for (i=0; i<tam; i++){
        fflush(stdin);
        ponteiro[i] = cidade[i];//passar o nome da cidade para o ponteiro
    }
    
    ponteiro[i] = '\0';
    return ponteiro;//retorna o nome da cidade
}