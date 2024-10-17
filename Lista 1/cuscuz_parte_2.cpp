#include <iostream>
#include <string>

using namespace std;

struct Carta{   //cada carta é um nó de uma lista encadeada que contém um dado e um ponteiro q aponta para a próxima carta
    int valor;
    char naipe;
    Carta* prox;
    Carta(): prox(nullptr){}
};

struct Fila{    //cada jogador tem uma fila de cartas
    Carta* inicio;
    Carta* fim;
};

void inicializaFila(Fila& fila){
    fila.inicio = nullptr;
    fila.fim = nullptr;
}

void adicionarCartas(Fila& fila, int valorCarta, char naipeCarta){   //adiciona novas cartas numa fila 
    Carta* novaCarta = new Carta();
    novaCarta->valor = valorCarta;
    novaCarta->naipe = naipeCarta;
    novaCarta->prox = nullptr;   //novo nó passa a ser o último
    if(fila.inicio != nullptr){  //verifica se a fila não está vazia
        fila.fim->prox = novaCarta;
    }
    else{
        fila.inicio = novaCarta;   //se a fila estava vazia, o novo elemento passa a ser o começo da fila
    }
    fila.fim = novaCarta;  // novo elemento sempre é o último da fila
}   

void retirarCartas(Fila& fila){   //deve retirar o primeiro elemento que foi inserido na fila
    if(fila.inicio != nullptr){
        Carta* temp = fila.inicio;
        fila.inicio = fila.inicio->prox;
        delete temp;
        if (fila.inicio == nullptr) {
            fila.fim = nullptr; // se a fila ficou vazia, fim deve ser nullptr também
        }
    }
}

struct NoPilha {
    Carta carta;
    NoPilha* prox;
    NoPilha(): prox(nullptr){}
};

struct Pilha {
    NoPilha* topo;
};

void inicializaPilha(Pilha& pilha) {
    pilha.topo = nullptr;
}

void empilharPrimeiraCarta(Pilha& pilha, Fila& fila) {
    if (fila.inicio != nullptr) {
        NoPilha* novoNo = new NoPilha();
        novoNo->carta = *(fila.inicio);
        novoNo->prox = pilha.topo;
        pilha.topo = novoNo;
    }
}

bool pilhaVazia(Pilha& pilha) {
    return pilha.topo == nullptr;
}

void imprimirPilha(Pilha& pilha) {
    NoPilha* atual = pilha.topo;
    while (atual != nullptr) {
        cout << atual->carta.valor << atual->carta.naipe;
        if(atual->prox != nullptr){
            cout << " ";
        }
        atual = atual->prox;
    }
    cout << endl;
}

void esvaziarPilha(NoPilha*& topo){
    while (topo != nullptr) {
        NoPilha* temp = topo;    // Armazena o nó atual em uma variável temporária
        topo = topo->prox;     // Avança para o próximo nó
        delete temp;           // Deleta o nó armazenado em temp
    }
}

void comandoDEA(string linha, Fila* filas, int numJogadores){
    int pos = 4;
    for(int i = 0; i<numJogadores; i++){
        while(linha[pos] == ' '){
            pos++;
        }
        if (pos > linha.size()){
            break;
        }
        int valorCarta = linha[pos] - '0';
        char naipeCarta = linha[pos+1];
        pos += 3;
        adicionarCartas(filas[i], valorCarta, naipeCarta);
    }
}

int compararCartas(Carta* a, Carta* b) {
    if (a->valor != b->valor) {
        return a->valor - b->valor;
    } else {
        return a->naipe - b->naipe;
    }
}

void vencedorDaRodada(Pilha& pilha) {
    if (pilha.topo == nullptr) {
        cout << -1;
        return;
    }
    Pilha pilhaTemp;
    inicializaPilha(pilhaTemp);
    NoPilha* atual = pilha.topo;

    while (atual != nullptr) {
        NoPilha* novoNo = new NoPilha();
        novoNo->carta = atual->carta;
        novoNo->prox = pilhaTemp.topo;
        pilhaTemp.topo = novoNo;
        atual = atual->prox;
    }

    atual = pilhaTemp.topo;
    Carta* cartaVencedora = &(atual->carta);
    int jogadorVencedor = 0;
    int pos = 0;
    bool empate = false;

    while (atual != nullptr) {
        int comparacao = compararCartas(&(atual->carta), cartaVencedora);
        if (comparacao > 0) {
            cartaVencedora = &(atual->carta);
            jogadorVencedor = pos;
            empate = false; 
        } else if (comparacao == 0 && &(atual->carta) != cartaVencedora) {
            empate = true; 
        } else if (comparacao == 0 && &(atual->carta) == cartaVencedora) {
            empate = false; 
        }
        atual = atual->prox;
        pos++;
    }

    if (empate) {
        cout << -1; 
    } else {
        cout << jogadorVencedor; 
    }
    esvaziarPilha(pilhaTemp.topo);
}

int main(){
    
    int numJog; 
    cin >> numJog;
    cin.ignore();
    Fila* filas = new Fila[numJog];
    for (int i = 0; i < numJog; i++) {
        inicializaFila(filas[i]);
    }
    Pilha pilha; 
    inicializaPilha(pilha);
    string linha;
    int numRodada = 0;
    while(true){
        getline(cin, linha);
        if (linha == "END") {
            break;
        } 
        else if (linha.substr(0, 3) == "DEA") {
            comandoDEA(linha, filas, numJog);
        } 
        else if (linha.substr(0, 3) == "RND") {
            esvaziarPilha(pilha.topo);
            cout << numRodada << " ";
            for (int i = 0; i < numJog; ++i) {
                empilharPrimeiraCarta(pilha, filas[i]);
            }
            vencedorDaRodada(pilha);
            cout << endl;
            for (int i = 0; i < numJog; ++i) {
                retirarCartas(filas[i]);
            }
            numRodada++;
        } 
        else if (linha.substr(0, 3) == "PRT") {
            imprimirPilha(pilha);
        }
    }
    delete[] filas;
    return 0;
}