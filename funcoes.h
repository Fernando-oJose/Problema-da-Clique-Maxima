#include<bits/stdc++.h>
using namespace std;
void  printa_clique();
void inicializa_grafo();
void inicializa_clique();
void adiciona_na_clique();
void adiciona_no_grafo(int x, int y);
void copia(vector<int>& vet1, vector<int>& vet2);
void atualiza_k(int v);
void adiciona_v(int v);
void cria_vet_vertices();
void le_entrada();
bool * retorna_vizinhos(int vert);
bool faz_parte(int vert);
int tam_clique();
