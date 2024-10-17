#include <iostream>

using namespace std;

void bfs(int origem, int n, int** grafo, int* tamListaAdj, int* componente, int contador) {
    int* fila = new int[n * n];
    int inicio = 0, final = 0;

    fila[final++] = origem;
    componente[origem] = contador;

    while (inicio < final) {
        int atual = fila[inicio++];

        for (int i = 0; i < tamListaAdj[atual]; i++) {
            int prox = grafo[atual][i];
            if (componente[prox] == -1) {  // Se ainda não foi visitado
                fila[final++] = prox;
                componente[prox] = contador;
            }
        }
    }

    delete[] fila;
}

int main() {
    int numCasos;
    cin >> numCasos;

    for (int i = 0; i < numCasos; i++) {
        int tamLab, m, q;
        cin >> tamLab >> m >> q;

        int** grafo = new int*[tamLab * tamLab];
        int* tamListaAdj = new int[tamLab * tamLab]();
        int* componente = new int[tamLab * tamLab];

        for (int j = 0; j < tamLab * tamLab; j++) {
            grafo[j] = new int[4];  // Cada célula pode ter no máximo 4 vizinhos
            tamListaAdj[j] = 0;
            componente[j] = -1;  // Inicialmente, nenhum nó pertence a qualquer componente
        }

        for (int j = 0; j < m; j++) {
            int parRemovidas;
            cin >> parRemovidas;
            int celula;

            if (parRemovidas % (2 * tamLab - 1) < tamLab - 1) {
                celula = tamLab * (parRemovidas / (2 * tamLab - 1)) + parRemovidas % (2 * tamLab - 1);
                grafo[celula][tamListaAdj[celula]++] = celula + 1;  // Conexão horizontal
                grafo[celula + 1][tamListaAdj[celula + 1]++] = celula;
            } else {
                celula = tamLab * (parRemovidas / (2 * tamLab - 1)) + parRemovidas % (2 * tamLab - 1) - (tamLab - 1);
                grafo[celula][tamListaAdj[celula]++] = celula + tamLab;  // Conexão vertical
                grafo[celula + tamLab][tamListaAdj[celula + tamLab]++] = celula;
            }
        }

        int contador = 0;
        for (int j = 0; j < tamLab * tamLab; j++) {
            if (componente[j] == -1) {  // Se o nó não foi visitado ainda
                bfs(j, tamLab, grafo, tamListaAdj, componente, contador++);
            }
        }

        for (int j = 0; j < q; j++) {
            int a, b;
            cin >> a >> b;

            if (componente[a] == componente[b]) {
                cout << i << "." << j << " 1" << endl;
            } else {
                cout << i << "." << j << " 0" << endl;
            }
        }

        for (int j = 0; j < tamLab * tamLab; j++) {
            delete[] grafo[j];
        }
        delete[] grafo;
        delete[] tamListaAdj;
        delete[] componente;

        cout << endl;
    }

    return 0;
}
