#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "trie.h"

#define TAM 26

void __inserePalavra(Trie *t,char *palavra,int n);
int __buscarPalavra(Trie *t,char *palavra,int n);
Trie* __buscarPrefixo(Trie *t,char *palavra,int n);
void __removerPalavra(Trie *t,char *palavra,int n);


Trie *criaTrie()
{
    Trie *t = criaNo(' ');
    t->termino = 1;
    return t;
}

void alphabetize2(Trie * t, char prefixo[])
{
    int i;

    if (t->termino == 1){
        printf("%s\n", prefixo); 
    }

    for (i = 0; i < TAM; ++i)
    {
        if (t->filhos[i] != NULL)
        {
            char ch = t->filhos[i]->letra;
            
            int l = strlen(prefixo);
            if(l > 0){
                char novo_prefixo[l];
                strcpy(novo_prefixo, prefixo);
                strncat(novo_prefixo, &ch, 1); 
                alphabetize2(t->filhos[i], novo_prefixo);
            }
            else{
                char novo_prefixo[] = {ch, '\0'};
                alphabetize2(t->filhos[i], novo_prefixo);
            }
        }
    }
}

void alphabetize(Trie * t){
    alphabetize2(t, "");
}

void liberar(Trie *t){
    
    int i;
    for (i = 0; i < TAM; ++i)
        if (t->filhos[i] != NULL)
            liberar(t->filhos[i]);
    
    free(t);
}

Trie *criaNo(char v)
{
    Trie *t = malloc(sizeof(Trie));
    t->letra = v;
    t->termino = 0;
    t->ocupacao = 0;
    return t;
}

void inserePalavra(Trie *t, char *palavra)
{
    __inserePalavra(t, palavra,0);
}

void __inserePalavra(Trie *t,char *palavra,int n){
    char letra = palavra[n];
    if(letra!='\0'){
        int i;
        if(n==0){
            i = letra - 'A';
        }else{
            i = letra - 'a';
        }
        if(t->filhos[i] == NULL){
            t->filhos[i] = criaNo(letra);
            t->ocupacao++;
        }
        __inserePalavra(t->filhos[i], palavra,n+1);
    }
    else{
        t->termino = 1;
    }
}


int buscarPalavra(Trie *t, char *palavra)
{
    return __buscarPalavra(t, palavra,0);
}

int __buscarPalavra(Trie *t,char *palavra,int n){
    char letra = palavra[n];
    if(letra!='\0'){
        int i;
        if(n==0){
            i = letra - 'A';
        }else{
            i = letra - 'a';
        }
        if(t->filhos[i] == NULL){
            return 0;
        }
        return __buscarPalavra(t->filhos[i], palavra,n+1);
    }
    else{
        return t->termino;
    }
}

Trie* buscarPrefixo(Trie *t, char *palavra)
{
    return __buscarPrefixo(t, palavra,0);
}

Trie* __buscarPrefixo(Trie *t, char *palavra,int n)
{
  /* implementar busca por prefixo */
    char letra = palavra[0];
    if(letra!='\0'){
        int i;
        if(n==0){
            i = letra - 'A';
        }else{
            i = letra - 'a';
        }
        if(t->filhos[i] == NULL){
            return NULL;
        }
        return __buscarPrefixo(t->filhos[i], palavra,n+1);
    }
    else{
        return t;
    }
}
void removerPalavra(Trie *t, char *palavra)
{
    __removerPalavra(t, palavra,0);
}
void __removerPalavra(Trie *t,char *palavra,int n){
    char letra = palavra[n];
    if(letra!='\0'){
        int i;
        if(n==0){
            i = letra - 'A';
        }else{
            i = letra - 'a';
        }
        if(t->filhos[i] == NULL){
            return;
        }
        __removerPalavra(t->filhos[i], palavra,n+1);
        if(t->filhos[i]->termino == 1 && t->filhos[i]->ocupacao == 0){
            free(t->filhos[i]);
            t->filhos[i] = NULL;
            t->ocupacao--;
        }
    }
    else{
        t->termino = 0;
    }
}

