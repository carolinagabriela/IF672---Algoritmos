#include <iostream>

using namespace std;

int diversao(int t, int S, int B){
    int St = S - (t-1)*(t-1)*B;  //indice de diversão na t-esima ida
    if(St <= 0){
        return 0;
    }                   
    return St;
}

int *knapSackParque(int s[], int b[], int c[], int k[], int n, int maxK){

    int *tabela = new int[maxK+1];

    for(int i=0; i<n; i++){   //p percorrer todos os briquedos
        for(int j = maxK; j>= c[i]; j--){   //se o custo do brinquedo i for menor q o total de créditos, para de executar essa parte
            int maxS = 0;  //diversao maxima
            int var = s[i];   //variavel p armazenar a diversao 
            int usos = 1;
            while(usos * c[i] <= j){
                int soma = tabela[j - usos * c[i]] + var;
                if (soma > maxS){
                    maxS = soma;
                }
                var += diversao(usos+1, s[i], b[i]);
                usos++;
            }

            if (maxS > tabela[j]){
                tabela[j] = maxS;
            }
        }
    }
    return tabela;
}


int main(){

    int n, v;  //numero de brinquedos e numero de visitas
    cin >> n;
    int S[n], B[n], C[n];  //diversao, aborrecimento e creditos

    for(int i = 0; i<n; i++){
        cin >> S[i] >> B[i] >> C[i];
    }

    cin >> v;  
    int K[v], maxK = 0;  

    for(int j = 0; j<v; j++){
        cin >> K[j];
        if(K[j] > maxK){
            maxK = K[j];
        }
    }

    int *tabela = nullptr;
    tabela = knapSackParque(S, B, C, K, n, maxK);

    for(int j = 0; j<v; j++){
        cout << j << ": " << tabela[K[j]] << endl;
    }

    delete[] tabela;

    return 0;
}
