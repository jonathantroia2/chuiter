#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include <time.h>

int main(){
avl * raizunix_timestamp = NULL;
avl * raiznome = NULL;
raizunix_timestamp = carregarchuiters("chuiter.txt", raizunix_timestamp);
raiznome = carregarchuiterscrip("chuiter.txt", raiznome);
char entradanome[26];
char entradadata1[20];
char entradahora1[20];
char entradadata2[20];
char entradahora2[20];
char linha[110];
do{
    if (fgets(linha, sizeof(linha), stdin) == NULL) break;
    sscanf(linha, "%25s %19s %19s %19s %19s",entradanome, entradadata1, entradahora1, entradadata2, entradahora2);
    if(strcmp(entradanome, "*") == 0 && strcmp(entradadata1, "*") != 0 && strcmp(entradahora1, "*") != 0
       && strcmp(entradadata2, "*") != 0 && strcmp(entradahora2, "*") != 0){  // para * no nome
        int unix_timestampcomeco = converteunix_timestamp(entradadata1, entradahora1);
        int unix_timestampfinal = converteunix_timestamp(entradadata2, entradahora2);
        int a = buscasemnome(raizunix_timestamp, unix_timestampcomeco, unix_timestampfinal);
        printf("%d chuites encontrado(s). \n", a);
    }
    else if(strcmp(entradanome, "*") != 0 && strcmp(entradadata1, "*") == 0 && strcmp(entradahora1, "*") == 0
            && strcmp(entradadata2, "*") != 0 && strcmp(entradahora2, "*") != 0){
        int unix_timestampfinal = converteunix_timestamp(entradadata2, entradahora2);
        int nomecrip = codificanome(entradanome);
        int a = buscanomeate(raiznome, unix_timestampfinal, nomecrip);
        printf("%d chuites encontrado(s). \n", a);

    }
    else if(strcmp(entradanome, "*") != 0 && strcmp(entradadata2, "*") == 0 && strcmp(entradahora2, "*") == 0
            && strcmp(entradadata1, "*") != 0 && strcmp(entradahora1, "*") != 0){
        int unix_timestampfinal = converteunix_timestamp(entradadata1, entradahora1);
        int nomecrip = codificanome(entradanome);
        int a = buscanomedepois(raiznome, unix_timestampfinal, nomecrip);
        printf("%d chuites encontrado(s). \n", a);
    }
    else if(strcmp(entradanome, "*") != 0 && strcmp(entradadata1, "*") == 0 && strcmp(entradahora1, "*") == 0 && strcmp(entradadata2, "*") == 0 && strcmp(entradahora2, "*") == 0){
        int nomecrip = codificanome(entradanome);
        int a = buscanome(raiznome, nomecrip);
        printf("%d chuites encontrado(s). \n", a);
    }
    else if(strcmp(entradanome, "*") == 0 && strcmp(entradadata1, "*") == 0 && strcmp(entradahora1, "*") == 0
       && strcmp(entradadata2, "*") == 0 && strcmp(entradahora2, "*") == 0){
           printf("%d chuites encontrado(s). \n", exibiravl(raiznome));
       }
    else if(strcmp(entradanome, "*") == 0 && strcmp(entradadata1, "*") == 0 && strcmp(entradahora1, "*") == 0
       && strcmp(entradadata2, "*") != 0 && strcmp(entradahora2, "*") != 0){
           int unix_timestampfinal = converteunix_timestamp(entradadata2, entradahora2);
           printf("%d chuites encontrado(s). \n", buscaunix_timestampate(raizunix_timestamp, unix_timestampfinal));
       }
    else if(strcmp(entradanome, "*") == 0 && strcmp(entradadata1, "*") != 0 && strcmp(entradahora1, "*") != 0
       && strcmp(entradadata2, "*") == 0 && strcmp(entradahora2, "*") == 0){
            int unix_timestampinical = converteunix_timestamp(entradadata1, entradahora1);
            printf("%d chuites encontrado(s). \n", buscaunix_timestampdepois(raizunix_timestamp, unix_timestampinical));
       }
    else{
        int unix_timestampinicial = converteunix_timestamp(entradadata1, entradahora1);
        int unix_timestampfinal = converteunix_timestamp(entradadata2, entradahora2);
        int nomecrip = codificanome(entradanome);
        int a = busca(raiznome, unix_timestampfinal, unix_timestampinicial, nomecrip);
        printf("%d chuites encontrado(s). \n", a);
    }
        // como existe 3 campos a serem preenchidos ou nao, existe 2*2*2 possibilidades entao criei 8 if
}while(1);
adeus(raiznome);
adeus(raizunix_timestamp);
return 0;
}
