#include <stdio.h>
#include <stdlib.h>
#include "ListaHotel.h"

int main()
{
    int opcao;
    Quartos *lstQuartos;
    lstQuartos = iniciarLista();
    menuHospedagem(lstQuartos);
}
