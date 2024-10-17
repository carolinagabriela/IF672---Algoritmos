#include <iostream>
#include <climits>

using namespace std;

struct Edge{
    int destino;
    int peso;
    Edge *proximo;  //ponteiro p formar uma lista encadeada pra cada vértice
};

//função p adicionar uma aresta ao grafo
void adicionar(Edge *grafo[], int origem, int destino, int peso){
    Edge *novaAresta = new Edge;
    novaAresta->destino = destino;
    novaAresta->peso = peso;
    novaAresta->proximo = grafo[origem];
    grafo[origem] = novaAresta;
}

//encontra o vértice com a menor distância q ainda não foi visitado
int extractMin(int dist[], bool visitado[], int quadras){
    int minDist = INT_MAX;
    int minIndex = -1;

    for (int i = 0; i < quadras; i++){
        if (!visitado[i] && dist[i] < minDist){
            minDist = dist[i];
            minIndex = i;
        }
    }

    return minIndex;
}

void dijkstra(Edge *grafo[], int quadras, int source, int destino){
    int dist[quadras];
    int antecessor[quadras];
    bool visitado[quadras];

    for (int i = 0; i < quadras; i++){
        dist[i] = INT_MAX;
        antecessor[i] = -1;
        visitado[i] = false;
    }

    dist[source] = 0;

    for (int i = 0; i < quadras; i++){
        int u = extractMin(dist, visitado, quadras);

        if (u == -1 || dist[u] == INT_MAX)
            break;

        visitado[u] = true;

        Edge *atual = grafo[u];
        while (atual != nullptr){
            int v = atual->destino;
            int peso = atual->peso;

            if (!visitado[v] && dist[u] != INT_MAX && (dist[u] + peso) < dist[v]){
                dist[v] = dist[u] + peso;
                antecessor[v] = u;
            }

            atual = atual->proximo;
        }
    }

    if (dist[destino] != INT_MAX){
        cout << dist[destino] << endl;
    }
    else{
        cout << "-1" << endl;
    }
}

int main(){
    int quadras, ruas, eventos, A, B, M, acao;
    cin >> quadras >> ruas >> eventos;

    Edge *G[quadras] = {nullptr};

    for (int i = 0; i < ruas; i++){
        cin >> A >> B >> M;
        adicionar(G, A, B, M);
    }

    for (int i = 0; i < eventos; i++){
        cin >> acao;
        if (acao == 1){
            cin >> A >> B >> M;
            adicionar(G, A, B, M);
        }
        else{
            cin >> A >> B;
            dijkstra(G, quadras, A, B);
        }
    }

    return 0;
}
