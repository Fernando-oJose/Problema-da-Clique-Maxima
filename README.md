# Problema-da-Clique-Maxima
Resolução do problema da Clique Máxima usando a metaheurística

Para compilar a meta heurística:
abra um terminal em src e digite
 g++ ./BRKGA.h ./MTRand.h ./Population.h ./SampleDecoder.h ./funcoes-variaveis.h ./samplecode.cpp ./SampleDecoder.cpp -o meta



Para compilar o método exato :
abra um terminal em src e digite 
g++ ./Maximum_Clique.cpp -o m  

Para compilar o gerador: 

abra um terminal em src e digite 

g++ ./gerador.cpp -o ger

obs:talvez você deverá digitar onde quer que grave as saídas e abra as entradas:

Em Maximum_Clique.cpp(método exato) L3 (leitura de arquivo)

Em samplecode.cpp(meta heurística) L24(leitura de arquivo)

Em gerador.cpp(gerador)     L18(gravação de arquivo)
