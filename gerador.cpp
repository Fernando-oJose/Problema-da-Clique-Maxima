#include<bits/stdc++.h>
using namespace std;
int N_VERTICES,N_ARESTAS;
set<pair<int,int>>lista_arestas;
void gera_instancia();
int main()
{
	cout<<"DIGITE O n vert. e n ares.";
	cin>>N_VERTICES>>N_ARESTAS;
	gera_instancia();
	return 0;
}


void gera_instancia()
{FILE* arq=NULL;

arq=fopen("instancias/instancia(9).txt","w");
	while(lista_arestas.size()!=N_ARESTAS){
		vector<int>v;
        	v.push_back(rand()%N_VERTICES);
        	v.push_back(rand()%N_VERTICES);

	  	
        		 sort(v.begin(),v.end());

	                lista_arestas.insert(make_pair(v[0],v[1]));         
  		

	}
fprintf(arq,"%d %d\n",N_VERTICES,N_ARESTAS);



for(pair<int,int>p:lista_arestas){
	fprintf(arq,"%d %d\n",p.first,p.second);

}

fclose(arq);
}
