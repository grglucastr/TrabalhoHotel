struct Hospedes
{
    char nome[70];
    long int cpf;
};

struct Quartos
{
    struct Hospedes hospede; //Aqui armazena o hospede responsável pela hospedagem...

    int numero;
    int andar;
    int qtde_pessoas;

    float valorQuarto;

    char tipoQuarto[20];    //Ex.: Suite, simples
    char statusQuarto[40]; //Ex.: Livre, ocupado
    char detalhes[140];   //Ex.: Possui 3 camas, TV a Cabo etc..
    char data_entrada[10];
    char data_saida[10];
};

struct ListaHotel
{
    //Deyvid, aqui é com você...

    struct Quartos quarto; //Aqui as informações de cada quarto.
    struct Hotel *prox;   //Ponteiro responsável por aponta o próximo elemento da lista.
};
