#include <iostream>
#include <climits>

using namespace std;

const int infinito = 50000000;

struct Caminho{
    int custo = infinito;
    int to = -1;
};

int m;
Caminho **grafo;
bool *visitado;
Caminho *minPeso;

int prim(){
    int custoTotal = 0;
    minPeso = new Caminho[m];
    visitado = new bool[m];

    for(int i=0; i<m; i++){
        visitado[i] = false;
        minPeso[i] = {infinito, -1};
    }
    minPeso[0].custo = 0;

    for(int i=0; i<m; i++){
        int v = -1;
        
        for(int j=0; j<m; j++){
            if(!visitado[j] && (v==-1 || minPeso[j].custo < minPeso[v].custo)){
                v = j;
            }
        }

        if(v == -1 || minPeso[v].custo == infinito){
            custoTotal = -1;
            break;
        }

        visitado[v] = true;
        custoTotal = custoTotal + minPeso[v].custo;

        for(int to=0; to<m; to++){
            if(!visitado[to] && grafo[v][to].custo < minPeso[to].custo){
                minPeso[to] = {grafo[v][to].custo, v};
            }
        }
    }

    delete[] minPeso;
    delete[] visitado;

    return custoTotal;
}

int main(){

    int numAeroportos, numTrechos;
    cin >> numAeroportos >> numTrechos;
    
    m = numAeroportos;

    grafo = new Caminho*[numAeroportos];

    for(int i=0; i<numAeroportos; i++){
        grafo[i] = new Caminho[numAeroportos];
        
        for(int j=0; j<numAeroportos; j++){
            grafo[i][j] = {infinito, -1};
        }
    }

    for(int i=0; i<numTrechos; i++){
        int ida, volta, custo;
        cin >> ida >> volta >> custo;
        grafo[ida][volta] = {custo, volta};
        grafo[volta][ida] = {custo, ida};
    }

    int custoTotal = prim();

    if(custoTotal != -1){
        cout << custoTotal << endl;
    }
    
    for(int i=0; i<numAeroportos; i++){
        delete[] grafo[i];
    }
    delete[] grafo;

    return 0;
}