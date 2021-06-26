#ifndef __ADDRESS__H
#define __ADDRESS__H

#include "ponto.h"
#include "quadra.h"

typedef void* Address;

Address criaAddress(Quadra q, char cpf[], char face[], double num, char complemento[]);

char* getAddressCep(Address address);

char* getAddressCpf(Address address);

char* getAddressFace(Address address);

char* getAddressComplemento(Address address);

Ponto getAddressPonto(Address address);

double getAddressNum(Address address);

int getAddressSize();

void setAddressCep(Address address, char cep[]);

void setAddressCpf(Address address, char cpf[]);

void setAddressFace(Address address, char face[]);

void setAddressComplemento(Address address, char complemento[]);

void setAddressPonto(Address address, double x, double y);

void setAddressNum(Address address, double num);

void swapAddress(Address a1, Address a2);

void desalocaAddress(Address address);

#endif