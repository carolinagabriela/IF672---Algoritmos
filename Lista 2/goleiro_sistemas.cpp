#include <iostream>

using namespace std;

struct AVLno {
    int id;
    AVLno* esquerda;
    AVLno* direita;
    int bytes;
    int soma;
    int tamanho;  //armazena o tamanho da subárvore cuja raiz é o nó atual
    int h;

    AVLno(int val, int bytes) : id(val), esquerda(nullptr), direita(nullptr), bytes(bytes), soma(bytes), h(1) {}
};

AVLno* raiz = nullptr;

int altura(AVLno* n){
    if(n == nullptr){
        return 0;
    }
    return n->h;
}

int max(int a, int b) {
    if(a > b){
        return a;
    }
    else {
        return b;
    }
}

int FatorDeBalanceamento(AVLno* n) {
    if (n == nullptr)
        return 0;
    return altura(n->direita) - altura(n->esquerda);
}

int getSoma(AVLno* n){
    if(n == nullptr){
        return 0;
    }
    return n->soma;
}

int getTam(AVLno* n){
    if(n == nullptr){
        return 0;
    }
    return n->tamanho;
}

void tam(AVLno* n){
    if(n == nullptr){
        return;
    }
    n->tamanho = 1 + getTam(n->esquerda) + getTam(n->direita);
}

void soma(AVLno* n){
    if (n == nullptr)
        return;        
    if(n->esquerda != nullptr && n->direita != nullptr){
        n->soma = n->bytes + n->esquerda->soma + n->direita->soma;
    }
    else if(n->esquerda != nullptr && n->direita == nullptr){
         n->soma = n->bytes + n->esquerda->soma;
    }
    else if(n->esquerda == nullptr && n->direita != nullptr){
         n->soma = n->bytes + n->direita->soma;
    }
    else{
         n->soma = n->bytes;
    }
}

AVLno* rotDireita(AVLno* n){
    AVLno* x = n->esquerda;
    AVLno* y = x->direita;
    x->direita = n;
    n->esquerda = y;
    
    n->h = max(altura(n->esquerda), altura(n->direita)) + 1;
    x->h = max(altura(x->esquerda), altura(x->direita)) + 1;

    tam(n);
    tam(x);
    
    soma(n);
    soma(x);

    return x;
}

AVLno* rotEsquerda(AVLno* n){
    AVLno* z = n->direita;
    AVLno* y = z->esquerda;
    z->esquerda = n;
    n->direita = y;
    
    n->h = max(altura(n->esquerda), altura(n->direita)) + 1;
    z->h = max(altura(z->esquerda), altura(z->direita)) + 1;

    tam(n);
    tam(z);

    soma(n);
    soma(z);
    
    return z;
}

AVLno* inserir(AVLno* noAtual, int id, int bytes) {
    //realizar a inserção padrão da ABB
    if (noAtual == nullptr){
        return new AVLno(id, bytes);
    }

    if(id < noAtual->id){
        noAtual->esquerda = inserir(noAtual->esquerda, id, bytes);
    }
    else if(id > noAtual->id){
        noAtual->direita = inserir(noAtual->direita, id, bytes);
    }
    else{
        noAtual->bytes += bytes;
        soma(noAtual);
        return noAtual;
    }
    noAtual->h = 1 + max(altura(noAtual->esquerda), altura(noAtual->direita));
    tam(noAtual);
    soma(noAtual);
    int balance = FatorDeBalanceamento(noAtual);
    
    //4 casos para um nó desbalanceado:
    if(balance > 1 && id > noAtual->direita->id){
        return rotEsquerda(noAtual);
    }
    if(balance < -1 && id < noAtual->esquerda->id){
        return rotDireita(noAtual);
    }
    if(balance > 1 && id < noAtual->direita->id){
        noAtual->direita = rotDireita(noAtual->direita);
        return rotEsquerda(noAtual);
    }
    if(balance < -1 && id > noAtual->esquerda->id){
        noAtual->esquerda = rotEsquerda(noAtual->esquerda);
        return rotDireita(noAtual);
    }
    
    return noAtual;
}

AVLno* buscarNo(AVLno* noAtual, int k, int *cont) {
    if (noAtual == nullptr)
        return nullptr;

    if (k < noAtual->id) {
        *cont = *cont + 1;
        return buscarNo(noAtual->esquerda, k, cont);
    } else if (k == noAtual->id) {
        return noAtual;
    } else {
        *cont = *cont + 1;
        return buscarNo(noAtual->direita, k, cont);
    }
}

AVLno* buscar(AVLno* no, int k, int* cont){
    return buscarNo(no, k, cont);
}

int rankear(AVLno* noAtual, int id, int& rank){
    if(noAtual == nullptr){
        return 0;
    }

    if(id < noAtual->id){
        return rankear(noAtual->esquerda, id, rank);
    }
    else if(id == noAtual->id){
        rank += getSoma(noAtual->esquerda);
        return getTam(noAtual->esquerda);
    }
    else{
        rank += noAtual->bytes + getSoma(noAtual->esquerda);
        return 1 + getTam(noAtual->esquerda) + rankear(noAtual->direita, id, rank);
    }
}

int extrairID(string linha, int pos){
    int id = 0;
    for(int i = pos; i < linha.length(); ++i){
        if(linha[i] >= '0' && linha[i] <= '9'){
            id = id * 10 + (linha[i] - '0');
        } else {
            break;
        }
    }
    return id;
}

void ADD(AVLno* noAtual, string linha, int* cont){
    int id = 0, bytes = 0;
    bool espaco = false;
    for (size_t i = 4; i < linha.length(); ++i) {
        if (linha[i] == ' ') {
            espaco = true;
        } else if (!espaco) {
            id = id * 10 + (linha[i] - '0');
        } else {
            bytes = bytes * 10 + (linha[i] - '0');
        }
    }
    raiz = inserir(raiz, id, bytes);
    *cont = *cont + bytes;
    cout << *cont << endl;
}

void WEI(AVLno* noAtual, string linha){
    int id = extrairID(linha, 4);
    int contp = 0;
    AVLno* temp = buscar(raiz, id, &contp);
    if(temp == nullptr){
        cout << "0 -1" << endl;
    }
    else{
        cout << temp->bytes << " " << contp << endl;
    }
}

void RNK(AVLno* noAtual, string linha){
    int id = extrairID(linha, 4);
    int ranking = 0;
    rankear(raiz, id, ranking);
    cout << ranking << endl;
}

int main(){
    AVLno* raiz = nullptr;
    string linha;
    int contador = 0;
        while(linha != "END"){
            getline(cin, linha);

            if(linha.substr(0, 3) == "ADD"){
                ADD(raiz, linha, &contador);
            }
            else if(linha.substr(0, 3) == "WEI"){
                WEI(raiz, linha);
            }
            else if(linha.substr(0, 3) == "RNK"){
                RNK(raiz, linha);
            }
        }
    
    return 0;
}