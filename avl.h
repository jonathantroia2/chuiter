#ifndef  AVL_H
#define  AVL_H
# include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct chuitter {
    int unix_timestamp;
    char autor[30];
    char mensagem[250];
    struct chuitter * prox

}chuitter;

typedef struct avl{
    int chave;
    chuitter* chuchu;
    struct avl * esq;
    struct avl * dir;
    int bal;

}avl;

avl * insereunix_timestamp(avl * raiz, int chave, chuitter * dados );
chuitter* criarchuitter(int unix_timestamp, char * autor, char * mensagem);
avl * carregarchuiters(char * nomearquuivo, avl * raiz);
avl * carregarchuiterscrip(char * nomearquuivo, avl * raiz);
int codificanome(char * nome);
int balanceamento(avl * t);
int altura(avl *raiz);
avl * rodadir(avl * raiz);
avl * rodaesq(avl * raiz);
int buscasemnome(avl * raiz, int unix_timestampcomeco, int unix_timestampfinal);
void unix_timestampdata(time_t unix_timestamp, char * buffer, size_t tamanhobuffer);
int converteunix_timestamp(char * datas, char * hora);
int buscanomeate(avl * raiznome, int unix_timestampfinal, int nomecrip);
int buscanomedepois(avl * raiznome, int unix_timestampfinal, int nomecrip);
int buscanome(avl * raiznome, int nomecrip);
int busca(avl * raiznome, int unix_timestampfinal, int unix_timestampinicial, int nomecrip);
int exibiravl(avl * raiz);
int buscaunix_timestampate(avl * raiz, int unix_timestampfinal);
int buscaunix_timestampdepois(avl * raiz, int unix_timestampfinal);
void adeus(avl * raiz);

#endif  /*AVL_H*/
