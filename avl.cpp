#include <bits/stdc++.h>

#include "avl.h"

using namespace std;

struct no {
    int info;
    struct no *sae;    // sub-árvore a esquerda
    struct no *sad;    // sub-árvore a direita
    int altura;
};

int altura(no *n) {
    if(n == NULL)
        return 0;

    return n->altura;
}

int buscar(no* n, int valor) {
    if(n == NULL)
        return false;
    
    if(valor == n->info)
        return true;
    else if(valor < n->info)
        return buscar(n->sae, valor);
    else
        return buscar(n->sad, valor);
}

no* criar(int valor) {
    no* n = (no*) calloc(1, sizeof(no));
    if(n != NULL) {
        n->info = valor;
        n->altura = 1;
    }

    return n;
}

void em_ordem(no *n) {
    if(n == NULL)
        return;

    em_ordem(n->sae);
    cout << n->info << " ";
    em_ordem(n->sad);
}

int fb(no* n){
    if(n == NULL)
        return 0;

    return altura(n->sae) - altura(n->sad);
}

no* inserir(no* n, int valor){
    if (n == NULL)
        return criar(valor);
 
    if (valor < n->info)
        n->sae = inserir(n->sae, valor);
    else
        n->sad = inserir(n->sad, valor);
 
    n->altura = 1 + max(altura(n->sae), altura(n->sad));
 
    int bf = fb(n);
    // LL-imbalance
    if(bf > 1 && valor < n->sae->info)
        return rot_direita(n);

    // RR-imbalance
    if(bf < -1 && valor > n->sad->info)
        return rot_esquerda(n);

    // LR-imbalance
    if(bf > 1 && valor > n->sae->info){
        n->sae = rot_esquerda(n->sae);
        return rot_direita(n);
    }

    // RL-imbalance
    if(bf < -1 && valor < n->sad->info){
        n->sad = rot_direita(n->sad);
        return rot_esquerda(n);
    }

    return n;
}

void largura(no* n) {
    queue<no*> f;
    f.push(n);
    while(!f.empty()) {
        no* atual = f.front();
        cout << atual->info << " ";
        f.pop();
        if(atual->sae)
            f.push(atual->sae);
        if(atual->sad)
            f.push(atual->sad);
    }
}

void liberar(no** n) {
    if(n == NULL)
        return;
    
    no* temp = *n;
    liberar(&((*n)->sae));
    liberar(&((*n)->sad));
    free(temp);
}

no* remover(no *n, int valor) {
    if (n == NULL)
        return NULL;

    no *temp = NULL;
    if(valor > n->info) {
        n->sad = remover(n->sad, valor);
        if(fb(n) == 2) {
            if(fb(n->sae) >= 0)
                n = rot_direita(n);
            else {
                n->sae = rot_esquerda(n->sae);
                n = rot_direita(n);
            }
        }
    } else if(valor < n->info) {
        n->sae = remover(n->sae, valor);
        if(fb(n) == -2)  {
            if(fb(n->sad) <= 0)
                n = rot_esquerda(n);
            else {
                n->sad = rot_direita(n->sad);
                n = rot_esquerda(n);
            }
        }
    } else {
        if(n->sad != NULL) { 
            temp = n->sad;
            while(temp->sae != NULL)
                temp = temp->sae;
 
            n->info = temp->info;
            n->sad = remover(n->sad, temp->info);
            if(fb(n) == 2) {
                if(fb(n->sae) >= 0)
                    n = rot_direita(n);
                else {
                    n->sae = rot_esquerda(n->sae);
                    n = rot_direita(n);
                }
            }
        } else {
            return n->sae;
        }
    }
    n->altura = altura(n);
    return n;
}

// LL-rotation
no* rot_direita(no* n){
    no* E = n->sae;
 
    n->sae = E->sad;
    E->sad = n;
 
    n->altura = 1 + max(altura(n->sad), altura(n->sae));
    E->altura = 1 + max(altura(E->sad), altura(E->sae));
 
    return E;
}
 
// RR-rotation
no* rot_esquerda(no* n) {
    no* D = n->sad;
 
    n->sad = D->sae;
    D->sae = n;
 
    n->altura = max(altura(n->sad), altura(n->sae)) + 1;
    D->altura = max(altura(D->sad), altura(D->sae)) + 1;
 
    return D;
}