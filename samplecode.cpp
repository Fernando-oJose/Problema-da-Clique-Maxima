#include"time.h"
#include <iostream>
#include "SampleDecoder.h"
#include "MTRand.h"
#include "BRKGA.h"
FILE*arq3=NULL;
#include"funcoes-variaveis.h"
int N_VERTICES;
int N_ARESTAS;
bool **grafo; //GRAFO COM SUAS LIGACOES
FILE *arq;

int main(int argc, char* argv[]) {
	const unsigned n = 200;		// size of chromosomes
	const unsigned p = 1000;	// size of population
	const double pe = 0.20;		// fraction of population to be the elite-set
	const double pm = 0.10;		// fraction of population to be replaced by mutants
	const double rhoe = 0.70;	// probability that offspring inherit an allele from elite parent
	const unsigned K = 3;		// number of independent populations
	const unsigned MAXT = 2;	// number of threads for parallel decoding
	
	SampleDecoder decoder;			// initialize the decoder

	arq=fopen("instancias/instancia(6).txt","r");
	if(arq==NULL)return 0;
		
	fscanf(arq,"%d %d",&N_VERTICES,&N_ARESTAS);
	inicializa_grafo();
        le_entrada();


        decoder.setGrafo(N_VERTICES,N_ARESTAS,grafo);
	
	const long unsigned rngSeed = 0;	// seed to the random number generator
	MTRand rng(rngSeed);				// initialize the random number generator
	
	// initialize the BRKGA-based heuristic
	BRKGA< SampleDecoder, MTRand > algorithm(n, p, pe, pm, rhoe, decoder, rng, K, MAXT);
	
	unsigned generation = 0;		// current generation
	const unsigned X_INTVL = 100;	// exchange best individuals at every 100 generations
	const unsigned X_NUMBER = 2;	// exchange top 2 best
	const unsigned MAX_GENS = 100;	// run for 100 gens
clock_t begin = clock();
   do {cout<<generation<<endl;
		algorithm.evolve();	// evolve the population for one generation
		
		if((++generation) % X_INTVL == 0) {
			algorithm.exchangeElite(X_NUMBER);	// exchange top individuals
		}
	} while (generation < MAX_GENS);
	clock_t end = clock();  
 	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

 //arq3=fopen("stdout2.txt","a+");	
         //fprintf(arq3, "Best solution found has objective value %d\n", n-algorithm.getBestFitness());
         cout<<"Best solution found has objective value :"<<n-algorithm.getBestFitness()<<" "<<elapsed_secs<<endl;

//fclose(arq3);
fclose(arq);
libera();	
	return 0;
}
void le_entrada()
{


	for(int i = 0; i < N_ARESTAS; i++)
	{
	
		int x, y;
		fscanf(arq,"%d %d",&x,&y);
        
		adiciona_no_grafo(x, y);
     

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

bool eh_clique(vector<int> vet)
{
int tam=vet.size();

for(int i=0;i<tam;i++){

	for(int j=i;j<tam;j++)
		if(!grafo[vet[i]][vet[j]]&&i!=j){//se nao  estao ligado entao vet nao forma clique
                   
                 return false;
		}

	}
return true;
}
void libera(){
int i;
	for(i = 0; i < N_VERTICES; i++)free(grafo[i]);
free(grafo);
}
