#include <iostream>
#include <string>

using namespace std;

struct AVLno {
    string nome; 
    int pontos;
    AVLno* direita;
    AVLno* esquerda;
    int h; //altura

    AVLno(string n, int k) : nome(n), pontos(k), esquerda(nullptr), direita(nullptr), h(1) {}
};

int altura(struct AVLno* n){
    if (n == NULL)
        return 0;
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

AVLno* rotDireita(AVLno* n){
    AVLno* x = n->esquerda;
    AVLno* y = x->direita;
    x->direita = n;
    n->esquerda = y;
    
    n->h = max(altura(n->esquerda), altura(n->direita)) + 1;
    x->h = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

AVLno* rotEsquerda(AVLno* n){
    AVLno* z = n->direita;
    AVLno* y = z->esquerda;
    z->esquerda = n;
    n->direita = y;
    
    n->h = max(altura(n->esquerda), altura(n->direita)) + 1;
    z->h = max(altura(z->esquerda), altura(z->direita)) + 1;
    
    return z;
}

AVLno* inserir(AVLno* noAtual, string nome, int pontos) {
    //realizar a inserção padrão da ABB
    if (noAtual == nullptr){
        return new AVLno(nome, pontos);
    }

    if(pontos < noAtual->pontos){
        noAtual->esquerda = inserir(noAtual->esquerda, nome, pontos);
    }
    else if(pontos > noAtual->pontos){
        noAtual->direita = inserir(noAtual->direita, nome, pontos);
    }
    else{
        return noAtual;
    }
    noAtual->h = 1 + max(altura(noAtual->esquerda), altura(noAtual->direita));
    int balance = FatorDeBalanceamento(noAtual);
    
    //4 casos para um nó desbalanceado:
    if(balance > 1 && pontos > noAtual->direita->pontos){
        return rotEsquerda(noAtual);
    }
    if(balance < -1 && pontos < noAtual->esquerda->pontos){
        return rotDireita(noAtual);
    }
    if(balance > 1 && pontos < noAtual->direita->pontos){
        noAtual->direita = rotDireita(noAtual->direita);
        return rotEsquerda(noAtual);
    }
    if(balance < -1 && pontos > noAtual->esquerda->pontos){
        noAtual->esquerda = rotEsquerda(noAtual->esquerda);
        return rotDireita(noAtual);
    }
    
    return noAtual;
}

AVLno* buscarNo(AVLno* noAtual, int k) {
    if (noAtual == nullptr)
        return nullptr;

    if (k < noAtual->pontos) {
        return buscarNo(noAtual->esquerda, k);
    } else if (k == noAtual->pontos) {
        return noAtual;
    } else {
        return buscarNo(noAtual->direita, k);
    }
}

AVLno* buscar(AVLno* no, int k){
    return buscarNo(no, k);
}

AVLno* minimo(AVLno* noAtual){
    while(noAtual->esquerda != nullptr){
        noAtual = noAtual->esquerda;
    }
    return noAtual;
}

AVLno* maximo(AVLno* noAtual){
    while(noAtual->direita != nullptr){
        noAtual = noAtual->direita;
    }
    return noAtual;
}

AVLno* sucessor(AVLno* noAtual, AVLno* n){
    if(n->direita != nullptr){
        return minimo(n->direita);
    }
    AVLno* proximo = nullptr;
    AVLno* atual = noAtual;
    while(atual != nullptr){
        if(n->pontos < atual->pontos){
            proximo = atual;
            atual = atual->esquerda;
        }
        else if(n->pontos > atual->pontos){
            atual = atual->direita;
        }
        else{
            break;
        }
    } 
    return proximo;
}

AVLno* antecessor(AVLno* noAtual, AVLno* n) {
    // Caso 1: Se o nó tem um filho à esquerda, o antecessor é o maior nó na subárvore à esquerda
    if (n->esquerda != nullptr)
        return maximo(n->esquerda);

    // Caso 2: Se o nó não tem um filho à esquerda, subimos a árvore a partir da raiz para encontrar o antecessor
    AVLno* anterior = nullptr;
    AVLno* atual = noAtual;
    while (atual != nullptr) {
        if (n->pontos > atual->pontos) {
            anterior = atual;
            atual = atual->direita;
        } else if (n->pontos < atual->pontos) {
            atual = atual->esquerda;
        }
        else{
            break;
        }
    }
    return anterior;
}

int extrairPontos(string linha, int pos){
    int pontos = 0;
    for(int i = pos; i < linha.length(); ++i){
        if(linha[i] >= '0' && linha[i] <= '9'){
            pontos = pontos * 10 + (linha[i] - '0');
        } else {
            break;
        }
    }
    return pontos;
}

void comandoADD(AVLno* &noAtual, string linha){
    int pos = 4;
    while(linha[pos] != ' '){
        pos++;
    } 
    string nome = linha.substr(4, pos-4);
    int pontos = extrairPontos(linha, pos+1);

    AVLno* atual = buscar(noAtual, pontos);
    if(atual != nullptr && nome == atual->nome){
        cout << nome << " ja esta no sistema." << endl;
    }
    else{
        noAtual = inserir(noAtual, nome, pontos);
        cout << nome << " inserido com sucesso!" << endl;
    }

}

void comandoPROX(AVLno* noAtual, string linha){
    int p = extrairPontos(linha, 5);

    AVLno* atual = buscar(noAtual, p);
    if (atual == nullptr) {
        return;
    }
    
    AVLno* noSucessor = sucessor(noAtual, atual);
    AVLno* noAntecessor = antecessor(noAtual, atual);

    if (noAntecessor != nullptr && noSucessor != nullptr) {
        cout << atual->nome << " vem apos " << noAntecessor->nome << " e antes de " << noSucessor->nome << endl;
    } else if (noSucessor != nullptr) {
        cout << atual->nome << " e o menor! e logo apos vem " << noSucessor->nome << endl;
    } else if (noAntecessor != nullptr) {
        cout << atual->nome << " e o maior! e logo atras vem " << noAntecessor->nome << endl;
    } else {
        cout << "Apenas " << atual->nome << " existe no sistema..." << endl;
    }
}

int main()
{
    int k;
    cin >> k;
    cin.ignore();
    string linha;
    AVLno* raiz = nullptr;
    for(int i=0; i<k; i++){
        getline(cin, linha);
        
        if(linha.substr(0, 3) == "ADD"){
            comandoADD(raiz, linha);
        }
        else if(linha.substr(0, 4) == "PROX"){
            comandoPROX(raiz, linha);
        }
    }

    return 0;
}
