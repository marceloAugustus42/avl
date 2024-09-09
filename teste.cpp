#include <bits/stdc++.h>
#include "avl.h"

using namespace std;

int main() {
    int valores[] = {10, 15, 20, 9, 5, 16, 17, 8, 6}, 
        tam = sizeof(valores)/sizeof(int);
    
    no * root = NULL;
    for(int i = 0; i < tam; i++) {
        root = inserir(root, valores[i]);
        cout << "largura: ";
        largura(root);
        cout << endl;
    }

    cout << "\nem ordem: ";
    em_ordem(root);
    cout << endl;

    cout << "\nremocao de 8 e 10 \n";
    root = remover(root, 8);
    root = remover(root, 10);

    cout << "em ordem: ";
    em_ordem(root);
    cout << endl;
    cout << "largura: ";
    largura(root);
    cout << endl;

    cout << "\nremocao de 15 \n";
    root = remover(root, 15);

    cout << "em ordem: ";
    em_ordem(root);
    cout << endl;
    cout << "largura: ";
    largura(root);

    return 0;
}