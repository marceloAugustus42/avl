#ifndef AVL_H
#define AVL_H

typedef struct no no;
 
int altura(no *n);
int buscar(no* n, int valor);
no* criar(int valor);
void em_ordem(no *n);
int fb(no* n);
no* inserir(no* n, int valor);
void largura(no* n);
void liberar(no** n);
no* remover(no* n, int valor);
no* rot_direita(no* n); 
no* rot_esquerda(no* n); 

#endif // AVL_H