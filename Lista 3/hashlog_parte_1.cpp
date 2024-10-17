#include <iostream>
using namespace std;

struct Conexao {
    unsigned timestamp;
    unsigned Conexao;
};

void aumentarCapacidade(Conexao*& dado, int& capacidade) {
    int novaCap = capacidade == 0 ? 1 : capacidade * 2;

    Conexao* novoDado = new Conexao[novaCap];

    if (dado != nullptr) {
        copy(dado, dado + capacidade, novoDado);
        delete[] dado;
    }

    dado = novoDado;
    capacidade = novaCap;
}

void add(Conexao*& dado, int& tamanho, int& capacidade, unsigned timestamp, unsigned cliente) {
    if (tamanho == capacidade) {
        aumentarCapacidade(dado, capacidade);
    }

    dado[tamanho++] = {timestamp, cliente};  
}

void comandoNEW(Conexao*& dado, int& tamanho, int& capacidade, string linha){
    unsigned timestamp = 0, Conexao = 0;
    bool espaco = false;
    for (size_t i = 4; i < linha.length(); ++i) {
        if (linha[i] == ' ') {
            espaco = true;
        } else if (!espaco) {
            timestamp = timestamp * 10 + (linha[i] - '0');
        } else {
            Conexao = Conexao * 10 + (linha[i] - '0');
        }
    }
    add(dado, tamanho, capacidade, timestamp, Conexao);
}

int buscaTRecursiva(Conexao* dado, int esq, int dir, unsigned timestamp) {
    if (esq > dir) {
        return -1; // Caso base: não encontrado
    }

    int meio = esq + (dir - esq) / 2;

    if (dado[meio].timestamp == timestamp) {
        return meio; // Encontrado
    } else if (dado[meio].timestamp < timestamp) {
        return buscaTRecursiva(dado, meio + 1, dir, timestamp); // Busca na metade direita
    } else {
        return buscaTRecursiva(dado, esq, meio - 1, timestamp); // Busca na metade esquerda
    }
}

int buscaT(Conexao* dado, int tamanho, unsigned timestamp) {
    return buscaTRecursiva(dado, 0, tamanho - 1, timestamp);
}

unsigned extrairID(string linha, int pos){
    unsigned id = 0;
    for(int i = pos; i < linha.length(); ++i){
        if(linha[i] >= '0' && linha[i] <= '9'){
            id = id * 10 + (linha[i] - '0');
        } else {
            break;
        }
    }
    return id;
}

void comandoQRY(Conexao* dado, int& tamanho, string linha){
    unsigned timestamp = extrairID(linha, 4);
    int pos = buscaT(dado, tamanho, timestamp);
    if(pos != -1){
        cout << dado[pos].Conexao << " " << pos << endl;
    }
    else{
        cout << "-1 -1" << endl;
    }
}
int main(){

    Conexao* dado = nullptr;
    int tamanho = 0;
    int capacidade = 0;
    string linha;
    getline(cin, linha);
    while(true){
        if(linha == "END"){
            break;
        }
        if(linha.substr(0, 3) == "NEW"){
            comandoNEW(dado, tamanho, capacidade, linha);
        }
        else if(linha.substr(0, 3) == "QRY"){
            comandoQRY(dado, tamanho, linha);
        }
        getline(cin, linha);
    }

    delete[] dado;

    return 0;
}
