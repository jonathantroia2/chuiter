#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// função que vai inserir e retornar uma avl ja balanceada;
avl * insereunix_timestamp(avl* raiz, int chave, chuitter * dados){
    if (raiz == NULL){
        avl* novo = malloc(sizeof(avl));
        novo->chave = chave;
        novo->chuchu = dados;       //vai criar uma nodo novo e anexar os dados a ele fazendo uma lista ligada
        novo->esq = NULL;
        novo->dir = NULL;
        novo->bal = 0;
        return novo;
    }

    if (chave < raiz->chave){
        raiz->esq = insereunix_timestamp(raiz->esq, chave, dados);
    } else if (chave > raiz->chave){
        raiz->dir = insereunix_timestamp(raiz->dir, chave, dados); // essa cadeia de if é para achar o lugar correto onde deve
    } else{                                                         // ficar o novo nodo
        chuitter * atual = raiz->chuchu;
        while (atual->prox != NULL){
            atual = atual->prox;
        }                                               // esse while vai verificar se por um acaso ja existe um usuario com essa chave ou
        atual->prox = dados;                            // um nodo para esse tempo unix e se ouver ele vai por os dados em forma de
    }                                                   // lista ligada

    raiz->bal = balanceamento(raiz);


    if (raiz->bal > 1 && chave < raiz->esq->chave)
        return rodadir(raiz);

    if (raiz->bal < -1 && chave > raiz->dir->chave)
        return rodaesq(raiz);

    if (raiz->bal> 1 && chave > raiz->esq->chave){
        raiz->esq = rodaesq(raiz->esq);
        return rodadir(raiz);
    }
    if (raiz->bal < -1 && chave < raiz->dir->chave){    // vai definir quais os passos necessarios pra balancear a avl
        raiz->dir = rodadir(raiz->dir);
        return rodaesq(raiz);
    }

    return raiz;
}
chuitter * criarchuitter(int unix_timestamp, char * autor, char * mensagem){
    chuitter* novo = malloc(sizeof(chuitter));
    novo->unix_timestamp = unix_timestamp;
    strcpy(novo->autor, autor);
    strcpy(novo->mensagem, mensagem);                   // cria um chuiter com os dados lidos da linha no fgets
    novo->prox = NULL;
    return novo;
}
avl * carregarchuiters(char * arquuivo, avl * raiz){
    FILE* arquivo = fopen(arquuivo, "r");
    char linha[1000];
    while (fgets(linha, sizeof(linha), arquivo)){
        int unix_timestamp;
        char autor[30];
        char mensagem[250];
        sscanf(linha, "%29s %d %249[^\n]", autor, &unix_timestamp, mensagem);   // lê e envia linha a linha pro criachuitter e inseri um nodo com o chuiter ou fazendo uma lista ligada
            chuitter * novo = criarchuitter(unix_timestamp, autor, mensagem);   // responsavel por colocar todas as informacoes na avl
            raiz = insereunix_timestamp(raiz, unix_timestamp, novo);
    }

    fclose(arquivo);
    return raiz;
}
avl * carregarchuiterscrip(char * arquuivo, avl * raiz){
    FILE* arquivo = fopen(arquuivo, "r");
    char linha[1000];
    while (fgets(linha, sizeof(linha), arquivo)){
        int unix_timestamp;
        char autor[30];
        char mensagem[250];
        sscanf(linha, "%29s %d %249[^\n]", autor, &unix_timestamp, mensagem);   // muito identica a anterior mas agora ela cria outra arvore com uma chave diferente, aqui vc utiliza o
            chuitter* novo = criarchuitter(unix_timestamp, autor, mensagem);    // nome do usario encriptado onde ele é unico impossivel existir colisoes
            int nomecrip = codificanome(autor);
            raiz = insereunix_timestamp(raiz, nomecrip, novo);
    }

    fclose(arquivo);
    return raiz;
}
int codificanome(char * nome){
    int soma = 0;
    int tamanho = strlen(nome);

    for (int i = 0; nome[i] != '\0'; i++){      // responsavel por criar a criptografia do nome e tranforma ele em um int pra servir de chave de uma avl.
        soma += (nome[i] * (i + 1) * 31);
    }

    return soma;
}
int balanceamento(avl * t){
    int b = altura(t->esq) - altura(t->dir);    // returna o balanceamneto de um nodo
    return b;
}
int altura(avl *raiz){
    if (raiz == NULL){
        return -1;
    }

    int alturaesquerda = altura(raiz->esq);
    int alturadireita = altura(raiz->dir);      // para nao criar mais uma variavel dentro do nodo criei um funcao pra puxar a altura do nodo.

    if (alturaesquerda > alturadireita){
        return alturaesquerda + 1;
    } else {
        return alturadireita + 1;
    }
}
avl * rodadir(avl * raiz){
    avl * auxesq = raiz->esq;
    raiz->esq = auxesq->dir;
    auxesq->dir = raiz;
    raiz->bal = balanceamento(raiz);            // essa aqui é a funcao que me fez coçar a cabeça roda a direita e depois que a fiz a roda a esquerda ficou facil de fazer
    auxesq->bal = balanceamento(auxesq);
    return auxesq;
}
avl * rodaesq(avl * raiz){
    avl * auxdir = raiz->dir;
    raiz->dir = auxdir->esq;
    auxdir->esq = raiz;
    raiz->bal = balanceamento(raiz);
    auxdir->bal = balanceamento(auxdir);
    return auxdir;
}
int buscasemnome(avl * raiz, int unix_timestampcomeco, int unix_timestampfinal){
    if(raiz == NULL)
        return 0;
    int conta = 0;
    conta = conta + buscasemnome(raiz->esq, unix_timestampcomeco, unix_timestampfinal);
    if(raiz->chave >= unix_timestampcomeco && raiz->chave <= unix_timestampfinal){
        chuitter * atual = raiz->chuchu;
        while (atual != NULL) {
            char dataf[20];
            unix_timestampdata(atual->unix_timestamp, dataf, sizeof(dataf));
            printf("%s (%s): %s\n", atual->autor, dataf, atual->mensagem);
            atual = atual->prox;
            conta++;
        }
    }
    conta = conta + buscasemnome(raiz->dir, unix_timestampcomeco, unix_timestampfinal); // percorre a arvore e verifica se esta dentro do range ela imprime e return quantos ela imprimiu
    return conta;
}
void unix_timestampdata(time_t unix_timestamp, char * buffer, size_t tamanhobuffer){
    struct tm * data_local = localtime(&unix_timestamp);
    strftime(buffer, tamanhobuffer, "%d/%m/%Y %H:%M:%S", data_local);                   // transforma um unix em uma saida formatada de hora, como pedido no enunciado
}
int converteunix_timestamp(char * datas, char * hora){
    struct tm data = {0};
    sscanf(datas, "%d/%d/%d", &data.tm_mday, &data.tm_mon, &data.tm_year);
    sscanf(hora, " %d:%d:%d", &data.tm_hour, &data.tm_min, &data.tm_sec);
    data.tm_year -= 1900;                                                               // literalmente o contrario da outra, ela pega uma entrada formatada de hora e data e tranforma em unix
    data.tm_mon -= 1;
    int unix_timestamp = mktime(&data);
    return unix_timestamp;
}
int buscanomeate(avl * raiznome, int unix_timestampfinal, int nomecrip){
    if(raiznome == NULL)
        return 0;                                                                       // as buscas sao praticamentes iguais, apenas muda as coisa que elas vao verificar antes de imprimir
    int conta = 0;
    if(raiznome->chave > nomecrip)
        conta = conta + buscanomeate(raiznome->esq, unix_timestampfinal, nomecrip);
    if(raiznome->chave == nomecrip){
        chuitter * atual = raiznome->chuchu;
         while (atual != NULL) {
            char dataf[20];
            unix_timestampdata(atual->unix_timestamp, dataf, sizeof(dataf));
            if(atual->unix_timestamp <= unix_timestampfinal){
                printf("%s (%s): %s\n", atual->autor, dataf, atual->mensagem);
                conta++;
            }
            atual = atual->prox;
        }
    }
    if(raiznome->chave < nomecrip)
        conta = conta + buscanomeate(raiznome->dir, unix_timestampfinal, nomecrip);

    return conta;
}
int buscanomedepois(avl * raiznome, int unix_timestampfinal, int nomecrip){
    if(raiznome == NULL)
        return 0;
    int conta = 0;
    if(raiznome->chave > nomecrip)
        conta = conta + buscanomedepois(raiznome->esq, unix_timestampfinal, nomecrip);
    if(raiznome->chave == nomecrip){
        chuitter * atual = raiznome->chuchu;
         while (atual != NULL) {
            char dataf[20];
            unix_timestampdata(atual->unix_timestamp, dataf, sizeof(dataf));
            if(atual->unix_timestamp >= unix_timestampfinal){
                printf("%s (%s): %s\n", atual->autor, dataf, atual->mensagem);
                conta++;}
            atual = atual->prox;
        }
    }
    if(raiznome->chave < nomecrip)
        conta = conta + buscanomedepois(raiznome->dir, unix_timestampfinal, nomecrip);

    return conta;
}
int buscanome(avl * raiznome, int nomecrip){
    if(raiznome == NULL)
        return 0;
    int conta = 0;
    if(raiznome->chave == nomecrip){
        chuitter * atual = raiznome->chuchu;
         while (atual != NULL) {
            char dataf[20];
            unix_timestampdata(atual->unix_timestamp, dataf, sizeof(dataf));
            printf("%s (%s): %s\n", atual->autor, dataf, atual->mensagem);
            conta++;
            atual = atual->prox;
        }
    }
    if(raiznome->chave > nomecrip)
        conta = conta + buscanome(raiznome->esq, nomecrip);
    if(raiznome->chave < nomecrip)
        conta = conta + buscanome(raiznome->dir, nomecrip);

    return conta;
}
int busca(avl * raiznome, int unix_timestampfinal, int unix_timestampinicial, int nomecrip){
    if(raiznome == NULL)
        return 0;
    int conta = 0;
    if(raiznome->chave == nomecrip){
        chuitter * atual = raiznome->chuchu;
         while (atual != NULL) {
            char dataf[20];
            unix_timestampdata(atual->unix_timestamp, dataf, sizeof(dataf));
            if(atual->unix_timestamp <= unix_timestampfinal && atual->unix_timestamp >= unix_timestampinicial){
            printf("%s (%s): %s\n", atual->autor, dataf, atual->mensagem);
            conta++;
            }
            atual = atual->prox;
        }
    }
    if(raiznome->chave > nomecrip)
        conta = conta + busca(raiznome->esq, unix_timestampfinal, unix_timestampinicial, nomecrip);
    if(raiznome->chave < nomecrip)
        conta = conta + busca(raiznome->dir, unix_timestampfinal, unix_timestampinicial, nomecrip);

    return conta;
}
int exibiravl(avl * raiz){
    if (raiz == NULL)
        return 0;
    int conta = 0;
        conta = conta + exibiravl(raiz->esq);
        chuitter * atual = raiz->chuchu;
        while (atual != NULL) {
            char dataf[20];
            unix_timestampdata(atual->unix_timestamp, dataf, sizeof(dataf));        // essa é barbaridade de simples! apenas imprime toda a arvore no modo Inorder
            printf("  %s (%s): %s\n", atual->autor, dataf, atual->mensagem);
            atual = atual->prox;
            conta++;
        }
        conta = conta + exibiravl(raiz->dir);

    return conta;
}
int buscaunix_timestampate(avl * raiz, int unix_timestampfinal){
    if(raiz == NULL)
        return 0;
    int conta = 0;
    conta = conta + buscaunix_timestampate(raiz->esq, unix_timestampfinal);
    if(raiz->chave <= unix_timestampfinal){
        chuitter * atual = raiz->chuchu;
        while (atual != NULL) {
            char dataf[20];
            unix_timestampdata(atual->unix_timestamp, dataf, sizeof(dataf));
            printf("%s (%s): %s\n", atual->autor, dataf, atual->mensagem);
            atual = atual->prox;
            conta++;
        }
    }
    conta = conta + buscaunix_timestampate(raiz->dir, unix_timestampfinal);
    return conta;
}
int buscaunix_timestampdepois(avl * raiz, int unix_timestampfinal){
    if(raiz == NULL)
        return 0;
    int conta = 0;
    conta = conta + buscaunix_timestampdepois(raiz->esq, unix_timestampfinal);
    if(raiz->chave >= unix_timestampfinal){
        chuitter * atual = raiz->chuchu;
        while (atual != NULL) {
            char dataf[20];
            unix_timestampdata(atual->unix_timestamp, dataf, sizeof(dataf));
            printf("%s (%s): %s\n", atual->autor, dataf, atual->mensagem);
            atual = atual->prox;
            conta++;
        }
    }
    conta = conta + buscaunix_timestampdepois(raiz->dir, unix_timestampfinal);
    return conta;
}
void adeus(avl * raiz){
    if(raiz == NULL)
        return;
    adeus(raiz->esq);
    adeus(raiz->dir);
    chuitter * atual = raiz->chuchu;                // desce ate as folhas e vem liberando a memoria de baixo pra cima, primeira a lista ligada dentro
    chuitter * aux;                                 // do nodo e depois libera o nodo
    while (atual != NULL) {
        aux = atual;
        atual = atual->prox;
        free(aux);
        }
    free(raiz);
}
