#include <iostream>

using namespace std;

struct elemento {
    int dado;
    elemento* prox;
    elemento(): prox(nullptr){}
};

struct Pilha {
    elemento* topo;
};

void inicializaPilha(Pilha& pilha) {
    pilha.topo = nullptr;
}

struct noDaLista {
    Pilha pilha;
    noDaLista* prox;
    noDaLista(): prox(nullptr){}
};

noDaLista* inicio = nullptr;

void desempilhar(Pilha& pilha) {
    if (pilha.topo != nullptr) {
        elemento* temp = pilha.topo;
        pilha.topo = pilha.topo->prox;
        delete temp;
    }
}

void empilhar(Pilha& pilha, int novoDado) {
    if (pilha.topo != nullptr && pilha.topo->dado == novoDado) {
        desempilhar(pilha);
    } else {
        elemento* novoNo = new elemento();
        novoNo->dado = novoDado;
        novoNo->prox = pilha.topo;
        pilha.topo = novoNo;
    }
}

bool pilhaVazia(const Pilha& pilha) {
    return pilha.topo == nullptr;
}

int topo(const Pilha& pilha) {
    if (pilha.topo != nullptr) {
        return pilha.topo->dado;
    }
    return -1;
}

void inserirAntes(int novoDado) {
    noDaLista* novoNo = new noDaLista();
    inicializaPilha(novoNo->pilha);
    empilhar(novoNo->pilha, novoDado);
    novoNo->prox = inicio;
    inicio = novoNo;
}

void inserirNoFinal(int novoDado) {
    noDaLista* novoNo = new noDaLista();
    inicializaPilha(novoNo->pilha);
    empilhar(novoNo->pilha, novoDado);
    novoNo->prox = nullptr;
    if (inicio == nullptr) {
        inicio = novoNo;
    } else {
        noDaLista* atual = inicio;
        while (atual->prox != nullptr) {
            atual = atual->prox;
        }
        atual->prox = novoNo;
    }
}

void inserirNoMeio(int coluna, int novoDado, int& tamlist) {
    noDaLista* atual = inicio;
    int posAtual = 1;
    while (posAtual < coluna && atual->prox != nullptr) {
        atual = atual->prox;
        posAtual++;
    }

    if (atual != nullptr) {
        empilhar(atual->pilha, novoDado);
        if (pilhaVazia(atual->pilha)) {
            if (atual == inicio) {
                inicio = atual->prox;
            } else {
                noDaLista* anterior = inicio;
                while (anterior->prox != atual) {
                    anterior = anterior->prox;
                }
                anterior->prox = atual->prox;
            }
            delete atual;
            tamlist--;
        }
    }
}

void esvaziarLista() {
    while (inicio != nullptr) {
        noDaLista* atual = inicio;
        while (!pilhaVazia(atual->pilha)) {
            desempilhar(atual->pilha);
        }
        inicio = inicio->prox;
        delete atual;
    }
}

int main() {
    int numCasos;
    int tamlist = 0;
    cin >> numCasos;
    cin.ignore();
    for (int caso = 1; caso <= numCasos; caso++) {
       string linha;
        while (true) {
            getline(cin, linha);
            if (linha == "END") {
                cin.ignore();
                break;
            }

            int coluna = 0, num = 0;
            bool espaco = false;
            for (size_t i = 0; i < linha.length(); ++i) {
                if (linha[i] == ' ') {
                    espaco = true;
                } else if (!espaco) {
                    coluna = coluna * 10 + (linha[i] - '0');
                } else {
                    num = num * 10 + (linha[i] - '0');
                }
            }
            if (coluna == 0) {
                inserirAntes(num);
                tamlist++;
            }
            else if (coluna == tamlist + 1) {
                inserirNoFinal(num);
                tamlist++;
            }
            else {
                inserirNoMeio(coluna, num, tamlist);
            }
        }
        
        cout << "caso " << caso-1 << ":";
        noDaLista *atual = inicio;
        while (atual != nullptr) {
            cout << " " << atual->pilha.topo->dado;
            atual = atual->prox;
        }
        cout << endl;

        esvaziarLista();
        tamlist = 0;
    }

    return 0;
}
