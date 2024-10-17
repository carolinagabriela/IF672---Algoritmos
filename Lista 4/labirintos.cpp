#include <iostream>

using namespace std;

struct Posicao{
    int linha;
    int coluna;
};

bool posicaoValida(int** grafo, bool** visitado, int L, int C, int linha, int coluna) {
    return (linha >= 0) && (linha < L) && (coluna >= 0) && (coluna < C) && (grafo[linha][coluna] != 1) && (!visitado[linha][coluna]);
}

int bfs(int** matriz, int L, int C, Posicao origem) {
    // Direções possíveis de movimento: cima, baixo, esquerda, direita
    int linhaMov[] = {-1, 1, 0, 0};
    int colunaMov[] = {0, 0, -1, 1};

    // Fila para armazenar as posições 
    Posicao* fila = new Posicao[L * C];
    int inicio = 0, fim = 0;

    // Matriz para armazenar as posições visitadas
    bool** visitado = new bool*[L];
    for (int i = 0; i < L; i++) {
        visitado[i] = new bool[C]();  //todo o vetor de visitados é inicialmente false
    }

    // Adicionar a posição inicial à fila e marcar como visitada
    fila[fim] = origem;
    fim++;
    visitado[origem.linha][origem.coluna] = true;
    int passos = 0;

    while (inicio < fim) {
        int tamanho = fim - inicio;
        for (int i = 0; i < tamanho; i++) {
            Posicao atual = fila[inicio];
            inicio++;

            // Se a posição atual é o destino, retorna o número de passos
            if (matriz[atual.linha][atual.coluna] == 3) {
                for (int i = 0; i < L; i++) {
                    delete[] visitado[i];
                }
                delete[] visitado;
                delete[] fila;
                return passos;
            }

            // Explora todas as direções
            for (int d = 0; d < 4; d++) {
                int novaLinha = atual.linha + linhaMov[d];
                int novaColuna = atual.coluna + colunaMov[d];

                // Se a nova posição é válida, adiciona à fila e marca como visitada
                if (posicaoValida(matriz, visitado, L, C, novaLinha, novaColuna)) {
                    visitado[novaLinha][novaColuna] = true;
                    fila[fim] = {novaLinha, novaColuna};
                    fim++;
                }
            }
        }

        passos++;
    }

    for (int i = 0; i < L; i++) {
        delete[] visitado[i];
    }

    // Se o destino não foi encontrado, retorna -1
    return -1;
}
int main(){

    int L, C;
    cin >> L >> C;

    int** grafo = new int*[L];
    for (int i = 0; i < L; i++) {
        grafo[i] = new int[C];
    }

    Posicao origem;
    for(int i=0; i<L; i++){
        for(int j=0; j<C; j++){
            cin >> grafo[i][j];
            if(grafo[i][j] == 2){
                origem = {i, j};
            }
        }
    }
   
    //se tiver caminho possivel, imprimir o número mínimo de movimentos 
    int resultado = bfs(grafo, L, C, origem);
    if (resultado != -1) {
        cout << resultado << endl;
    } else {
        cout << "Labirinto Impossivel" << endl;
    }

    return 0;
}
