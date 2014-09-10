#ifndef LISTAHOTEL_H
#define LISTAHOTEL_H
struct hospedes
{
    char nome[100];
    double cpf;
};//usando o typedef
typedef struct hospedes Hospedes;

struct produtos
{
    int cod;
    char nome[50];
    float preco;
};

typedef struct produtos Produtos;

struct quartos
{
    Hospedes hospede ; //Aqui armazena o hospede responsável pela hospedagem...


    int cont;//contador para controle da quantidade de quartos

    int numero;
    int andar;
    int qtdePessoas;

    int statusQuarto; //Ex.: [0]Livre, [1]reservado, [2]ocupado

    float valorQuarto;

    char tipoQuarto[20];    //Ex.: Suite, simples
    char detalhes[150];   //Ex.: Possui 3 camas, TV a Cabo etc..
    char dataEntrada[10];
    char dataSaida[10];

    struct quartos* prox;
}; //usando o typedef, muda-se o nome da estrutura Ex.: struct quartos == Quartos.
typedef struct quartos Quartos;

//--------------------AQUI COMEÇA OS MÉTODOS BÁSICOS --------------------

void limpar();
Quartos *iniciarLista();
Quartos *iniciarQuartos();
void arquivos(char nomeArquivo[40], char conteudo[100]);
Quartos *realizarHospedagem(char tipoQuarto[20]); //Esta função realiza a hospedagem do quarto
Quartos *exibirQuartoHospede(Quartos *lstQuartos);
Quartos *buscarQuartoHospede(Quartos *lstQuartos);
void buscarQuartoTipo(Quartos *lstQuartos, char tipo[20]);
Quartos *realizarVenda(Quartos *lstQuartos);
Quartos *realizarSaida(Quartos *lstQuartos);

//-------------- MENUS PRINCIPAIS --------------

void menuHospedagem(Quartos *lstQuartos);
void menuReservas();

//------------------MENUS: Hospedagem ---------------------------

void menuEntradaHospedes(Quartos *lstQuartos);
void consultarHospedagens(Quartos *lstQuartos);
void menuConsumoHospedes(Quartos *lstQuartos);
void menuSaidaHospedes(Quartos *lstQuartos);

//------------------MENUS: RESERVAS ---------------------------

void menuRealizarReserva();
void menuConsultarReservas();

//------------------MENUS: STATUS HOTEL ---------------------------

int exibirTotalHospedou();
int exibirTotalReservados();
int exibirTotalLivres();
int exibirTotalOcupados();

//------------------ROTINAS AUXILIARES ------------------------

void listarTiposQuartos();

    /***
        Esta função busca os quartos pelo tipo.
        Ex.: Simples, Suite etc.
        Lista os quartos e seus respectivos status.
    ***/
char *converterStatus(int status); //Esta função, verifica o número do status e converte em um char;
int listaVazia(Quartos *lstQuartos); //Aqui verifica se a lista esta vazia. [0]NAO, [1]SIM.
int qtdeOcupadoPeloTipo(Quartos *lstQuartos, char tipo[20]); //Aqui mostra os quartos ocupados, ordenados pelo tipo
int qtdeRegistrosLista(Quartos *lstQuartos); //Aqui retorna o total que a lista possui

//Funções para a manipulação dos produtos e do caixa do hotel
void preencherTabelaProdutos();
void exibirTabelaProdutos();
float efetuarCalculoVenda(float preco);
#endif // LISTAHOTEL_H
