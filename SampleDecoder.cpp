#include<bits/stdc++.h>
#include"funcoes-variaveis.h"
using namespace std;
/*
 * SampleDecoder.cpp
 *
 *  Created on: Jan 14, 2011
 *      Author: rtoso
 */



#include "SampleDecoder.h"

SampleDecoder::SampleDecoder() { }

SampleDecoder::~SampleDecoder() { }

// Runs in \Theta(n \log n):
double SampleDecoder::decode(const std::vector< double >& chromosome) const {
	
double fit=0.0;


	std::vector< std::pair< double, unsigned > > ranking(chromosome.size());

	for(unsigned i = 0; i < chromosome.size(); ++i) {
		ranking[i] = std::pair< double, unsigned >(chromosome[i], i);
	}

	// Here we sort 'permutation', which will then produce a permutation of [n] in pair::second:
	std::sort(ranking.begin(), ranking.end());
       vector<int>vet;//clique
        int tam=chromosome.size();

      for(int i=0;i<tam;i++){//adiciona no vetor e dpois verifica se forma clique
		vet.push_back(ranking[i].second);//coloca no vetor o vertice
               //for(int i=0;i<vet.size();i++)cout<<vet[i]<<" "<<endl;
               
               if(eh_clique(vet)){
		 fit++;
               // cout<<"fitness:"<<fit<<endl;	
               }
              else{
              break;

              };//na primeira ocorrencia de nao clique retornara o ultimo valor guardado em fit

      }


return N_VERTICES-fit;
}

 void SampleDecoder::setGrafo(int N_VERT,int N_ARES,bool** graf)
{
   N_VERTICES=N_VERT;
   N_ARESTAS=N_ARES;
   grafo=graf;
}
