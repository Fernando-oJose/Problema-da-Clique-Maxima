#include"funcoes.h"
#include <time.h>

FILE * arq=NULL;
int N_VERTICES;
int N_ARESTAS;
std::stack<pair<vector<int>, vector<int> > >pilha; //PILHA DE ESTADOS(VERTICES NA CLIQUE/VERTICES QUE NAO ESTAO)
std::vector<int>Q, K; //estao /nao estao
bool **grafo, *clique; //GRAFO COM SUAS LIGACOES
void libera();

int main()
{
        arq=fopen("instancias/instancia(1).txt","r");
        if(arq==NULL){
	   cout<<"Instancia não encontrada!"<<endl;
	   exit(1);
        }
      
        fscanf(arq,"%d %d",&N_VERTICES,&N_ARESTAS); //le o numero de vertices e arestas
        
        inicializa_grafo();
	inicializa_clique();	
	le_entrada();
       

	cria_vet_vertices();

	pilha.push(std::make_pair(std::vector<int>(Q), std::vector<int>(K))); //inicializa a pilha de estados

    clock_t begin = clock();
	while(!pilha.empty())
	{ 
        //clock_t end2 = clock();    	
      //double elapsed_secs2 = double(end2 - begin) / CLOCKS_PER_SEC;
    //cout<<tam_clique()<<" "<<elapsed_secs2<<" \n";
 
		pair<vector<int>, vector<int> >auxiliar; //remove o estado do topo da pilha
		auxiliar = pilha.top();
		pilha.pop();

		copia(Q, auxiliar.first); //Q<= first
		copia(K, auxiliar.second); //K<=second

		int counter = 1;
		while(K.size() != 0 && tam_clique() < Q.size() + K.size())
		{
		
			
			//vector<int>::iterator vert_dt = --K.end(); //deletou o  vértice v de K
			//std::cout << "*vert_dt value: " << *vert_dt << std::endl;
			int v = K[0];
		
			//K.pop_back();
			K.erase(K.begin());
		
		
                        pilha.push(make_pair(std::vector<int>(Q), std::vector<int>(K))); //L 7
		
			//se v está ligado com todos os vértices de Q ele é adicionado em Q
			//obs : se clique vazia v eh adicionado, o "novo" K serah os vizinhos de v que
			//nao estao em Q
			//adiciona_v(*vert_dt);//Passa o Q e vértice deletado de K
			
			adiciona_v(v);
			
			//atualiza_k(*vert_dt);
			atualiza_k(v);

	

		}
	if(tam_clique() < Q.size())
		{
			adiciona_na_clique();//atualiza clique
		}



	}
	clock_t end = clock();    	
   double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
cout<<"Tempo: "<<elapsed_secs<<" s\n";
 fclose(arq);
 printa_clique();
libera();

	return 0;
}




void  printa_clique()
{
 
//Printa a Clique



	for(int i = 0; i < N_VERTICES; i++)
	{
		if(faz_parte(i))
            cout<<i<<" ";
	}
         
	cout << "(" << tam_clique() << ")" << std::endl;




}
void copia(vector<int>& vet1, vector<int>& vet2)
{
	vet1.clear();
	for(vector<int>::iterator it = vet2.begin(); it != vet2.end(); ++it)
	{

		vet1.push_back(*it);

	}

}
void adiciona_na_clique()
{
	memset(clique, false, sizeof(bool) * N_VERTICES);//zerou clique
	vector<int>::iterator it ;

	for(it = Q.begin(); it != Q.end(); ++it)
	{
		clique[*it] = true; //atualiza a clique de acordo com a posicao
	}

}

void atualiza_k(int v)
{
	/*vector<int>::iterator it;
	std::cout << "inside atualiza_k (1)" << std::endl;
	bool *aux = retorna_vizinhos(v);
	std::cout << "inside atualiza_k (2)" << std::endl;
	sort(K.begin(), K.end());
	std::cout << "inside atualiza_k (3)" << std::endl;

	std::cout << "vector K: ";
	for(std::vector<int>::iterator _it = K.begin(); _it != K.end(); ++_it)
		std::cout << *_it << " ";
	std::cout << std::endl;

	//Verifica  os vértices de Q
	int counter = 1;

	std::vector<int> erase_elements;
	for(it = K.begin(); it != K.end(); ++it)
	{
		std::cout << "inside atualiza_k (4) (" << counter++ << ")" << std::endl;
		//se v nao for vizinho de um vértice de Q sai do laço
		std::cout << (*it ? "!= NULL" : "== NULL") << std::endl;
		if(!aux[*it]) //se nao for vizinho de v
		{
			std::cout << "*it = " << *it << std::endl;
			std::cout << "before if" << std::endl;

			for(std::vector<int>::iterator _it = K.begin(); _it != K.end(); ++_it)
				std::cout << *_it << " ";
			std::cout << std::endl;

			erase_elements.push_back(*it);

			std::cout << "after if" << std::endl;
		}

	}

	for(std::vector<int>::iterator erase = erase_elements.begin(); erase != erase_elements.end(); ++erase)
	{
		std::vector<int>::iterator find = std::find(K.begin(), K.end(), *erase);

		if(find == K.end()) continue;
		std::cout << "removing element: " << *find << std::endl;

		K.erase(find);
	}

	std::cout << "inside atualiza_k (5)" << std::endl;*/

	bool* neighbours = retorna_vizinhos(v);
	std::vector<int> new_K, v_neighbours;



	for(int i = 0; i < N_VERTICES; i++)
	{
		bool is_neighbour = neighbours[i];

		if(!is_neighbour) continue;

	

		v_neighbours.push_back(i);
	}

	for(std::vector<int>::iterator it = K.begin(); it != K.end(); it++)
	{
		
		std::vector<int>::iterator find = std::find(v_neighbours.begin(), v_neighbours.end(), *it);

		if(find == v_neighbours.end())
		{
			
			continue;
		}
		
		new_K.push_back(*it);
	}
	


	copia(K, new_K);
	
}

void adiciona_v(int v)
{
	/*vector<int>::iterator it;
	bool esta = true;
	bool *aux = retorna_vizinhos(v);
	sort(Q.begin(), Q.end());

	if(Q.empty())
	{

		Q.push_back(v);
		return;
	}
	//Verifica  os vértices de Q
	for(it = Q.begin(); it != Q.end(); ++it)
	{
		//se v nao for vizinho de um vértice de Q sai do laço
		if(!aux[*it]) //se nao for vizinho de v
		{
			esta = false;
			break;
		}

	}

	if(esta)
	{
		Q.push_back(v);
	}
	return;*/
	Q.push_back(v);
}


int tam_clique()
{
	int i = 0, tam = 0;

	while(i < N_VERTICES)
	{

		if(faz_parte(i))tam++;
		i++;
	}

	return tam;
}
//adiciona  os VERTICES  ao vetor K
void cria_vet_vertices()
{

	for(int i = 0; i < N_VERTICES; i++)
	{
		K.push_back(i); //k[i]=i

	}



}
void le_entrada()
{
int i;
char c;

    for(i=0;i<N_ARESTAS;i++){
                             int x,y;
                             
        		      fscanf(arq," %d %d",&x,&y);
        
                             adiciona_no_grafo(x,y);
        
    }
    

}
void inicializa_clique()
{clique=(bool*)malloc(sizeof(bool)*N_VERTICES);
	int i;
	for(i = 0; i < N_VERTICES; i++)
	{

		clique[i] = false;
	}


}
void inicializa_grafo()
{ grafo=(bool**)malloc(sizeof(bool*)*N_VERTICES);
	int i, j;
	for(i = 0; i < N_VERTICES; i++)
	{grafo[i]=(bool*)malloc(sizeof(bool)*N_VERTICES);
		for(j = 0; j < N_VERTICES; j++)
		{
			grafo[i][j] = false;

		}
	}


}
void adiciona_no_grafo(int x, int y)
{
	grafo[x][y] = true;
        grafo[y][x] = true;

}
//vai retornar vizinhos do vértices removidos que não estão na clique
bool * retorna_vizinhos(int vert)
{
	return grafo[vert];
}

bool faz_parte(int vert)
{
	return clique[vert];

}

void libera(){
free(clique);
int i, j;
	for(i = 0; i < N_VERTICES; i++)free(grafo[i]);
free(grafo);
}
