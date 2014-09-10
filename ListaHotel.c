#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SUITES 3
#define MAX_SIMPLES 17
#define MAX_PRESIDENCIAL 1

#include "ListaHotel.h"

//Esta função limpa a tela apenas
void limpar()
{
    system("cls");
}

//Esta função inicia a lista com NULL
Quartos *iniciarLista()
{
    return NULL;
}

//Esta função verifica se a lista esta vazia
int listaVazia(Quartos *lstQuartos)
{
    return (lstQuartos == NULL);
}

/*Esta funcao escreve dados em arquivos e caso eles ainda nao existam ela o cria.
Recebe como parametro o nome do arquivo e sua extensão, 
e o conteudo que será salvo no arquivo.
*/
void arquivos(char nomeArquivo[40], char conteudo[100])
{
        FILE* arq;//Inicia o arquivo
        arq = fopen(nomeArquivo, "ab");//Tenta abrir o arquivo
        if(arq == NULL)//verifica se o arquivo foi aberto caso contrario ele é criado 
            arq = fopen(nomeArquivo, "wb");
        fprintf(arq,"%s\n", conteudo);//salva os dados no arquivo
        fclose(arq);//Fecha o arquivo
}

//Aqui apenas mostra um menu com as opções de hospedagens
void menuHospedagem(Quartos *lstQuartos)
{
    int opcao;

    printf("------------------- MENU HOSPEDAGEM -------------------\n\n");
    printf("1 - Entrada de hospedes\n");
    printf("2 - Consultar hospedagens\n");
    printf("3 - Consumo hospedes\n");
    printf("4 - Saida de hospedes\n");
    printf("0 - Sair do sistema\n\n");
    //printf("0 - Menu principal\n\n");
    scanf("%i", &opcao);

    switch(opcao)
    {
        case 0:
            limpar();
            //main();
            system("exit");
            break;

        case 1:
            limpar();
            menuEntradaHospedes(lstQuartos);
            break;

        case 2:
            limpar();
            consultarHospedagens(lstQuartos);
            break;

        case 3:
            limpar();
            menuConsumoHospedes(lstQuartos);
            break;

        case 4:
            limpar();
            menuSaidaHospedes(lstQuartos);
            break;
        default:
            main();
            break;
    }
}

//Aqui é um SUBMENU para registrar as hospedagens
void menuEntradaHospedes(Quartos *lstQuartos)
{
    int opcao, opcao2, qtdeOcupado = 0;
    char tipoQuarto[20];
    Quartos *atual = lstQuartos; //Aqui recebe o inicio da lista
    Quartos *anterior = NULL; //Aqui vai sempre manter o registro anterior
    Quartos *novoQuarto; //Aqui registra o novo quarto

    limpar();
    printf("--------------------- ENTRADA DE HOSPEDES ---------------------\n\n");

    //Esta função (VOID) vai listar os tipos de quartos. Ex.: Simples, suite etc...
    //Fiz isso para o código ficar mais compreensível
    listarTiposQuartos();

    //Aqui o usuário vai escolher que tipo de quarto ele vai querer...
    scanf("%i", &opcao);

    limpar();
    switch(opcao)
    {
        case 1:
            strcpy(tipoQuarto, "Simples");

            //Aqui calcula a quantidade de quartos do tipo SIMPLES que está ocupada.
            qtdeOcupado = qtdeOcupadoPeloTipo(lstQuartos, tipoQuarto);

            printf("Total de quartos %s livres: %i quarto(s)", tipoQuarto, (MAX_SIMPLES - qtdeOcupado));
            break;

        case 2:
            strcpy(tipoQuarto, "Suite");

            //Aqui calcula a quantidade de quartos do tipo SUITE que está ocupada.
            qtdeOcupado = qtdeOcupadoPeloTipo(lstQuartos, tipoQuarto);

            printf("Total de quartos %s livres: %i quarto(s)", tipoQuarto, (MAX_SUITES - qtdeOcupado));
            break;

        case 3:
            strcpy(tipoQuarto, "Presidencial");

            //Aqui calcula a quantidade de quartos do tipo PRESIDENCIAL que está ocupada.
            qtdeOcupado = qtdeOcupadoPeloTipo(lstQuartos, tipoQuarto);

            printf("Total de quartos %s livres: %i quarto(s)", tipoQuarto, (MAX_PRESIDENCIAL - qtdeOcupado));
            break;

        default:
            printf("Opcao Invalida!\n\n");
            system("pause");
            menuEntradaHospedes(lstQuartos);
    }

    fflush(stdin);

    if(listaVazia(lstQuartos) == 1)
    {
        printf("\n\nO que deseja fazer a seguir?\n\n");
        printf("\t1 - Realizar hospedagem\n");
        printf("\t0 - Voltar para menu principal\n");
        scanf("%i", &opcao2);
    }
    else
    {
        /***
            AS ESTRUTURAS CONDICIONAIS A SEGUIR, SERVEM PARA VERIFICAR SE HÁ VAGAS NO
            HOTEL PARA DETERMINADOS QUARTOS.

            DENTRO DELAS, TEM UM PEQUENO MENU COM OPÇÕES...
        */

        if( (strcmp(tipoQuarto, "Simples")== 0) && (qtdeOcupado >= MAX_SIMPLES))
        {
            printf("\n\nInfelizmente, nao temos quartos simples disponiveis...");
            printf("\n\nO que deseja fazer a seguir?\n\n");
            printf("\t0 - Voltar para menu principal\n");
            scanf("%i", &opcao2);
        }
        else if( (strcmp(tipoQuarto, "Suite") == 0) && (qtdeOcupado >= MAX_SUITES))
        {
            printf("\n\nInfelizmente, nao temos suites disponiveis...");
            printf("\n\nO que deseja fazer a seguir?\n\n");
            printf("\t0 - Voltar para menu principal\n");
            scanf("%i", &opcao2);
        }
        else if( (strcmp(tipoQuarto, "Presidencial") == 0) && (qtdeOcupado >= MAX_PRESIDENCIAL))
        {
            printf("\n\nInfelizmente, nao temos quartos presidenciais disponiveis...");
            printf("\n\nO que deseja fazer a seguir?\n\n");
            printf("\t0 - Voltar para menu principal\n");
            scanf("%i", &opcao2);
        }
        else
        {
            printf("\n\nO que deseja fazer a seguir?\n\n");
            printf("\t1 - Realizar hospedagem\n");
            printf("\t0 - Voltar para menu principal\n");
            scanf("%i", &opcao2);
        }
    }

    printf("\n\n");

    switch(opcao2)
    {
        case 0:
            limpar();
            menuHospedagem(lstQuartos);
            break;

        case 1:
            //Aqui chama o método realizar HOSPEDAGEM e atribui para uma variável do tipo QUARTO
            novoQuarto = realizarHospedagem(tipoQuarto); //Aqui registra o novo quarto

            //Este laço de repetição tenta encontrar o registro anterior
            //As variáveis aqui utilizadas, foram declaradas no inicio desta função
            while(atual != NULL)
            {
                anterior = atual;
                atual = atual->prox;
            }

            if(anterior == NULL)
            {
                //Insere no inicio da lista
                novoQuarto->prox = lstQuartos;
                lstQuartos = novoQuarto;
            }
            else
            {
                //Insere no meio ou no fim da lista
                novoQuarto->prox = anterior->prox;
                anterior->prox = novoQuarto;
            }
            system("pause");
            limpar();
            menuHospedagem(lstQuartos);
            break;

        default:
            printf("Opcao Invalida!\n\n");
            system("pause");
            limpar();
            menuEntradaHospedes(lstQuartos);
            break;
    }
}

//Função responsável por REALIZAR A HOSPEDAGEM PROPRIAMENTE DITA
Quartos *realizarHospedagem(char tipoQuarto[20])
{
    Quartos *quarto = (Quartos*) malloc(sizeof(Quartos)); //Aqui vai guardar os dados do quarto que vai ser ocupado

    limpar();
    printf("------------ OCUPAR UM QUARTO ---------------\n\n");
    //Aqui na hora de hospedar, exibe o tipo do quarto para o usuario.
    printf("Tipo: %s\n\n", tipoQuarto);

    //Aqui passa o tipo do quarto para o REGISTRO para ser salvo na lista
    strcpy(quarto->tipoQuarto, tipoQuarto);
    
    
    //Aqui limpa o BUFFER
    fflush(stdin);

    /**
        A ESTRUTURA CONDICIONAL ABAIXO SERVE APENAS PARA
        ATRIBUIR O VALOR DO QUARTO NO REGISTRO. ELA COMPARA O TIPO DO QUARTO
        E DEFINE O VALOR DO QUARTO.
    */
    if( strcmp(tipoQuarto, "Simples") == 0 )
        quarto->valorQuarto = 50.00;
    else if( strcmp(tipoQuarto, "Suite") == 0 )
        quarto->valorQuarto = 150.00;
    else
        quarto->valorQuarto = 250.00;


    //Aqui exibe o valor do quarto para o usuário
    printf("Valor do quarto: %.2f\n\n", quarto->valorQuarto);

    //Aqui pede as informações do HOSPEDE para salvar no REGISTRO
    printf("\t------------- DADOS DO HOSPEDE -------------\n\n");

    printf("\tNome do hospede: "); //Pede o nome do HOSPEDE
    scanf("%[^\n]", &quarto->hospede.nome); //lÊ O NOME DO HPSPEDE
    fflush(stdin); //LIMPA BUFFER

    printf("\tHospede CPF: ");
    scanf("%i", &quarto->hospede.cpf);
    fflush(stdin);
  
    printf("\tQuantidade de pessoas: ");
    scanf("%i", &quarto->qtdePessoas);
    
    //Aqui altera o status do quarto para OCUPADO
    quarto->statusQuarto = 2;

    //MENSAGEM DE SALVO COM SUCCESSO
    printf("\n\nDados salvos com sucesso!\n");
    printf("Ocupacao do quarto realizada com sucesso!\n\n");
    printf("Favor liberar a chave!\n\n\n");

    //RETORNA O QUARTO
    return quarto;
}

//Aqui é o SUBMENU para CONSULTA DE HOSPEDES e QUARTOS
void consultarHospedagens(Quartos *lstQuartos)
{
    int opcao;
    int opTipo; //Esta variavel serve para armazenar o tipo do quarto escolhido no menu
    char tipo[20]; //Esta variavel vai armazenar o tipo do quarto em caracteres.

    printf("-------------------- CONSULTA DE HOSPEDAGENS --------------------\n\n");
    printf("1 - Buscar por hospede\n");
    printf("2 - Buscar por tipo do quarto\n\n");
    scanf("%i", &opcao);

    switch(opcao)
    {
        case 1:
            limpar();

            //Esta função vai BUSCAR o HOSPEDE na LISTA pelo CPF
            exibirQuartoHospede(lstQuartos);

            //Mostra uma mensagem ao usuário e aguarda ele apertar uma tecla
            printf("\n\nPressione qualquer tecla para voltar ao menu de hospedagens\n\n");
            getchar();

            //Limpa a tela e VOLTA para o MENU inicial passando a listar por parâmetro.
            limpar();
            menuHospedagem(lstQuartos);
            break;

        case 2:
            limpar();
            printf("------------- BUSCAR QUARTOS POR TIPO -------------\n\n");
            printf("1 - Simples\n");
            printf("2 - Suite\n");
            printf("3 - Presidencial\n\n");
            scanf("%i", &opTipo);

            //Aqui converte o NUMERO escolhido no MENU para uma string
            switch(opTipo)
            {
                case 1:
                    strcpy(tipo, "Simples");
                    break;

                case 2:
                    strcpy(tipo, "Suite");
                    break;

                case 3:
                    strcpy(tipo, "Presidencial");
                    break;
            }
            //Aqui BUSCA TODOS OS HOSPEDES que estão em UM TIPO DE QUARTO
            buscarQuartoTipo(lstQuartos, tipo);
            printf("\n\n");
            system("pause");
            limpar();
            menuHospedagem(lstQuartos);
            break;
    }

}

//Esta função busca quanto um certo hospede consumiiu
//E adiciona algo mais caso ele queira consumir algo a mais...
void menuConsumoHospedes(Quartos *lstQuartos)
{
    //Eu faço isso para evitar DANOS na lista PRINCIPAL,
    //Essa que é passada por parâmetro...
    Quartos *quartos = lstQuartos;

    int opcao;

    printf("------------------ LOJA DO HOTEL ------------------\n\n");
    printf("1 - Realizar venda\n");
    printf("0 - Voltar para o menu principal\n\n");
    scanf("%i", &opcao);

    switch(opcao)
    {
        case 0:
        default:
            limpar();
            menuHospedagem(lstQuartos);
            break;

        case 1:
            limpar();

            //Esta função abre o menu de comes e bebes do hotel
            //E vende algo para o cliente caso ele queira comprar
            //Como isso vai alterar o registro, entao ela deve retornar toda a lista
            lstQuartos = realizarVenda(lstQuartos);

            printf("\n\n");
            system("pause");
            limpar();
            menuHospedagem(lstQuartos);
            break;
    }
}

Quartos *realizarVenda(Quartos *lstQuartos)
{
    Quartos *quarto; //Aqui vamos obter os dados do hospede que vai efetuar a compra

    int opcao; //aqui vai armazenar a opcao escolhida no menu
    int qtde; //Aqui armazena a quantidade do produto que a pessoa vai comprar
    int isHospede; //Aqui verifica se a pessoa eh hospede ou nao
    float vlrCompra; //Aqui vai ocorrer a multiplicacao entre a qtde e o valor do produto.

    printf("------------------ REALIZAR VENDA ------------------\n\n");

    //Esta funcao apenas imprime na tela o que o hotel tem para vender
    exibirTabelaProdutos();
    scanf("%i", &opcao);

    switch(opcao)
    {
        case 0:
        default:
            menuHospedagem(lstQuartos);
            break;

        case 1:
            limpar();
            printf("Voce escolheu: Refrigerante (Lata)\n");
            printf("Valor: R$ 2.50\n");
            vlrCompra = efetuarCalculoVenda(2.50);
            quarto = buscarQuartoHospede(lstQuartos);
            quarto->valorQuarto += vlrCompra;
            printf("\n\nCompra contabilizada!\n\n");
            break;

        case 2:
            limpar();
            printf("Voce escolheu: Refrigerante (2L)\n");
            printf("Valor: R$ 5.00\n");
            vlrCompra = efetuarCalculoVenda(5.00);
            quarto = buscarQuartoHospede(lstQuartos);
            quarto->valorQuarto += vlrCompra;
            printf("\n\nCompra contabilizada!\n\n");
            break;

        case 3:
            limpar();
            printf("Voce escolheu: Cafe da manha\n");
            printf("Valor: R$ 8.00\n");

            vlrCompra = efetuarCalculoVenda(8.00);
            quarto = buscarQuartoHospede(lstQuartos);
            quarto->valorQuarto += vlrCompra;

            printf("\n\nCompra contabilizada!\n\n");
            break;

        case 4:
            limpar();
            printf("Voce escolheu: Almoco\n");
            printf("Valor: R$ 10.00\n");

            vlrCompra = efetuarCalculoVenda(10.00);
            quarto = buscarQuartoHospede(lstQuartos);
            quarto->valorQuarto += vlrCompra;

            printf("\n\nCompra contabilizada!\n\n");
            break;

        case 5:
            limpar();
            printf("Voce escolheu: Janta\n");
            printf("Valor: R$ 20.00\n");

            vlrCompra = efetuarCalculoVenda(20.00);
            quarto = buscarQuartoHospede(lstQuartos);
            quarto->valorQuarto += vlrCompra;

            printf("\n\nCompra contabilizada!\n\n");
            break;

        case 6:
            limpar();
            printf("Voce escolheu: Pizza\n");
            printf("Valor: R$ 15.00\n");

            vlrCompra = efetuarCalculoVenda(15.00);
            quarto = buscarQuartoHospede(lstQuartos);
            quarto->valorQuarto += vlrCompra;

            printf("\n\nCompra contabilizada!\n\n");
            break;

        case 7:
            limpar();
            printf("Voce escolheu: Sushi\n");
            printf("Valor: R$ 30.00\n");

            vlrCompra = efetuarCalculoVenda(30.00);
            quarto = buscarQuartoHospede(lstQuartos);
            quarto->valorQuarto += vlrCompra;

            printf("\n\nCompra contabilizada!\n\n");
            break;

        case 8:
            limpar();
            printf("Voce escolheu: Halls\n");
            printf("Valor: R$ 1.00\n");

            vlrCompra = efetuarCalculoVenda(1.00);
            quarto = buscarQuartoHospede(lstQuartos);
            quarto->valorQuarto += vlrCompra;

            printf("\n\nCompra contabilizada!\n\n");
            break;

        case 9:
            limpar();
            printf("Voce escolheu: Sorvete\n");
            printf("Valor: R$ 2.00\n");

            vlrCompra = efetuarCalculoVenda(2.00);
            quarto = buscarQuartoHospede(lstQuartos);
            quarto->valorQuarto += vlrCompra;

            printf("\n\nCompra contabilizada!\n\n");
            break;
    }

    return lstQuartos;
}

void menuSaidaHospedes(Quartos *lstQuartos)
{
    int opcao;
    printf("------------------ REALIZAR CHECKOUT ------------------\n\n");
    printf("1 - Realizar checkout hospede\n");
    printf("0 - Voltar para menu\n\n");
    scanf("%i", &opcao);

    switch(opcao)
    {
        case 0:
        default:
            limpar();
            menuHospedagem(lstQuartos);
            break;

        case 1:
            limpar();
            printf("------------------ REALIZAR CHECKOUT ------------------\n\n");
            lstQuartos = realizarSaida(lstQuartos);
            printf("\n\n");
            system("pause");
            limpar();
            menuHospedagem(lstQuartos);
            break;
    }
}

Quartos *realizarSaida(Quartos *lstQuartos)
{
    Quartos *quarto; //Aqui vamos colocar o quarto que vai ser excluído.
    Quartos *anterior = NULL;
    Quartos *auxLocalizar = lstQuartos; //Aqui vai ajudar a localizar o quarto anterior
    int opcao;

    quarto = exibirQuartoHospede(lstQuartos);

    //Aqui vamos encontrar o registro anterior a este
    while(auxLocalizar->hospede.cpf != quarto->hospede.cpf)
    {
        anterior = auxLocalizar;
        auxLocalizar = auxLocalizar->prox;
    }

    printf("\n\nConfirma checkout deste hospede?\n\n");
    printf("\t1 - Sim\n");
    printf("\t2 - Nao\n");
    printf("\t0 - Voltar para menu principal\n");
    scanf("%i", &opcao);

    switch(opcao)
    {
        case 1:
            if(anterior == NULL)
                lstQuartos = quarto->prox;
            else
                anterior->prox = quarto->prox;

            free(quarto);
            printf("\n\nHospede retirado com sucesso!\n\n");
            break;

        case 2:
        default:
            limpar();
            menuHospedagem(lstQuartos);
            break;
    }

    return lstQuartos;
}

/***----------------- PROCEDIMENTOS AUXILIARES -----------------**/
//Esta função apenas imprime na tela os tipos de quartos. Ex.: 1-Simples, 2-Suite etc...
void listarTiposQuartos()
{
    printf("Escolha o tipo de quarto: \n\n");
    printf("\t1 - Simples\n");
    printf("\t2 - Suite\n");
    printf("\t3 - Presidencial\n");
}

//Esta função localiza o HOSPEDE e o QUARTO DELE pelo CPF e IMPRIME NA TELA
Quartos *exibirQuartoHospede(Quartos *lstQuartos)
{
    Quartos *quartoHospede = lstQuartos; //Esta variavel vai armazenar os dados do quarto do hospede que foi buscado.
    int cpf;
    int encontrou = 0;
    printf("---------------- BUSCAR HOSPEDE ----------------\n\n");
    printf("Hospede CPF: ");
    scanf("%i", &cpf); //Aqui lê o CPF
    fflush(stdin); //Limpa buffer

    //Aqui começa a busca pelo hospede
    while((quartoHospede != NULL)  && (encontrou == 0))
    {
        if(quartoHospede->hospede.cpf == cpf)
        {
            encontrou = 1;
            printf("\n\nTipo de quarto: %s\n", quartoHospede->tipoQuarto);
            printf("Valor quarto: %.2f\n", quartoHospede->valorQuarto);
            printf("Hospede: %s\n", quartoHospede->hospede.nome);
            printf("Hospede CPF: %i\n", quartoHospede->hospede.cpf);
            printf("QTDE Pessoas: %i\n", quartoHospede->qtdePessoas);
            printf("Colocar data de entrada\n");
            printf("Colocar data de saida\n");
            printf("\n\n-----------------------------------------");
        }
        else
        {
            //Continua no laço até encontrar,
            //digamos que isso aqui seja um "INCREMENTO"
            quartoHospede = quartoHospede->prox;
        }
    }

    if(quartoHospede == NULL)
    {
        printf("Nenhum registro encontrado com o CPF: %i\n\n", cpf);
    }

    return quartoHospede;
}

//Esta função localiza o HOSPEDE e o QUARTO DELE pelo CPF, MAS NÃO IMPRIME NA TELA
Quartos *buscarQuartoHospede(Quartos *lstQuartos)
{
    Quartos *quartoHospede = lstQuartos; //Esta variavel vai armazenar os dados do quarto do hospede que foi buscado.
    int cpf;
    int encontrou = 0;
    printf("---------------- BUSCAR HOSPEDE ----------------\n\n");
    printf("Hospede CPF: ");
    scanf("%i", &cpf); //Aqui lê o CPF
    fflush(stdin); //Limpa buffer

    //Aqui começa a busca pelo hospede
    while((quartoHospede != NULL)  && (encontrou == 0))
    {
        if(quartoHospede->hospede.cpf == cpf)
        {
            encontrou = 1;
        }
        else
        {
            //Continua no laço até encontrar,
            //digamos que isso aqui seja um "INCREMENTO"
            quartoHospede = quartoHospede->prox;
        }
    }

    if(quartoHospede == NULL)
    {
        printf("Nenhum registro encontrado com o CPF: %i\n\n", cpf);
    }

    return quartoHospede;
}

//Aqui lista TODOS OS HOSPEDES HOSPEDADOS EM um certo tipo de QUARTO.
//Ex.: Mostrar todos os hospedes que estao hospedados em suites...
//O tipo de quarto varia de acordo com o que é passado via parâmetro.
void buscarQuartoTipo(Quartos *lstQuartos, char tipo[20])
{
    Quartos *quartos = lstQuartos;

    while(quartos != NULL)
    {
        if( strcmp(quartos->tipoQuarto, tipo) == 0)
        {
            printf("\nQuarto: %s\n", quartos->tipoQuarto);
            printf("Hospede: %s\n", quartos->hospede.nome);
            printf("Hospede CPF: %i\n", quartos->hospede.cpf);
            printf("QTDE Pessoas: %i\n", quartos->qtdePessoas);
            printf("Valor consumido: %.2f\n", quartos->valorQuarto);
            printf("Data de entrada: colocar ainda....");
            printf("\n\n-------------------------------------\n\n");
        }
        //DIGAMOS QUE ISSO AQUI FOSSE UM "INCREMENTO"
        //Ele vai "incrementando" até chegar em NULL para poder sair do laço
        quartos = quartos->prox;
    }
}

//Esta função retorna a QUANTIDADE DE QUARTOS de um CERTO TIPO que estão OCUPADOS
//O tipo varia de acordo com o que é passado via parâmetro
int qtdeOcupadoPeloTipo(Quartos *lstQuartos, char tipo[20])
{
    int qtde = 0;

    while(lstQuartos != NULL)
    {
        if( (strcmp(lstQuartos->tipoQuarto, tipo) == 0) && (lstQuartos->statusQuarto == 2))
            qtde++;

        lstQuartos = lstQuartos->prox;
    }

    return qtde;
}

//Esta função recebe por parâmetro um inteiro e retorna uma sequência de CHARS
//Ex.: parametro(0) então vai retornar LIVRE
char *converterStatus(int status)
{
    if(status == 0)
        return "Livre";
    else if(status == 1)
        return "Reservado";
    else
        return "Ocupado";

}

//Esta função mostra a quantidade de registros que tem em toda a lista.
int qtdeRegistrosLista(Quartos *lstQuartos)
{
    int qtde = 0;
    Quartos *lista = lstQuartos;
    while(lista != NULL)
    {
        qtde++;
        lista = lista->prox;
    }
}

//Esta função recebe o valor do produto e multiplica pela quantidade
//E retorna o valor dessa compra.
float efetuarCalculoVenda(float preco)
{
    float vlr;
    int qtde;

    printf("Quantidade: ");
    scanf("%i", &qtde);

    return vlr = (qtde * preco);
}

//Esta função mostra a tabela de produtos do HOTEL
void exibirTabelaProdutos()
{
    printf("\t\tMenu: 0 - VOLTAR\n\n");
    printf("|COD.|\t\tPRODUTO \t| PRECO \t|\n");
    printf("|    |\t\t        \t|       \t|\n");
    printf("|  1 |\tRefrigerante(Lata) \t| R$ 2.50 \t|\n");
    printf("|  2 |\tRefrigerante(2L) \t| R$ 5.00 \t|\n");
    printf("|  3 |\tCafe da manha \t\t| R$ 8.00 \t|\n");
    printf("|  4 |\tAlmoco \t\t\t| R$ 10.00 \t|\n");
    printf("|  5 |\tJanta \t\t\t| R$ 20.00 \t|\n");
    printf("|  6 |\tPizza \t\t\t| R$ 15.00 \t|\n");
    printf("|  7 |\tSushi \t\t\t| R$ 30.00 \t|\n");
    printf("|  8 |\tHalls \t\t\t| R$ 1.00 \t|\n");
    printf("|  9 |\tSorvete \t\t| R$ 2.00 \t|\n");
    printf("\n");
    printf("Escolha: ");
}
