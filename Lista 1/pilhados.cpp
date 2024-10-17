#include <iostream>

struct caixa{
    int valor;   //dado armazenado no nó
    caixa* prox; //ponteiro que aponta para o proximo nó 
};

void empilhar(caixa*& topo, int novoValor, int& tamanho){
    caixa* novoNo = new caixa(); //cria um novo nó
    novoNo->valor = novoValor;
    novoNo->prox = topo; //aponta o ponteiro prox do novo nó para o antigo topo da pilha
    topo = novoNo;
    tamanho++;
}

bool ehPar(int numero) {
    return (numero % 2 == 0);
}

void processarPilha(caixa*& topo, int& tamanho) {
    while (topo != nullptr && topo->prox != nullptr) {
        // Verifica se ambos os nós têm a mesma paridade
        if (ehPar(topo->valor) == ehPar(topo->prox->valor)) {
            int resultado = abs(topo->valor - topo->prox->valor);

            caixa* temp1 = topo;
            caixa* temp2 = topo->prox;
            topo = topo->prox->prox; // Avança o topo para pular dois nós
            delete temp1;
            delete temp2;

            tamanho -= 2;
            if (topo == nullptr) {
                caixa* novoNo = new caixa();
                novoNo->valor = resultado;
                novoNo->prox = nullptr;
                topo = novoNo;
                tamanho++;
                return;
            }

            caixa* novoNo = new caixa();
            novoNo->valor = resultado;
            novoNo->prox = topo;
            topo = novoNo;
            tamanho++;
        } else {
            break;
        }
    }
}


void esvaziarPilha(caixa*& topo, int &tamanho){
    while (topo != nullptr) {
        caixa* temp = topo;    // Armazena o nó atual em uma variável temporária
        topo = topo->prox;     // Avança para o próximo nó
        delete temp;           // Deleta o nó armazenado em temp
    }
    
    tamanho = 0;  // Atualiza o tamanho da pilha para zero
}

using namespace std;

int main()
{
    int numCasos; 
    cin >> numCasos;
    caixa* topo = nullptr; //inicializa a pilha vazia
    int tamanho = 0;
    
    for(int i=0; i<numCasos; i++){
        int elemento;
        cin >> elemento; 
        while (elemento != 0){
            empilhar(topo, elemento, tamanho);
            processarPilha(topo, tamanho);
            cin >> elemento;
        }
        if(tamanho == 0){
            topo->valor = -1;
        }
        cout << "Pilha " << i+1 << ": " << tamanho << " " << topo->valor << endl;
        esvaziarPilha(topo, tamanho);
    }
    return 0;
}
