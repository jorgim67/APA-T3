/*COMPILAR USANDO FLAG -std=c++11 

*********************************
Aluno: George Nunes de Moura Filho
Matrícula: 11328786
Disciplina: Análise e Projeto de Algoritmo
Período: 2016.2
Trabaho 3 ordenação*/

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>

void print_vector(std::vector<int>);
void fail();

std::vector<int> countingSort( const std::vector<int> &vec ){

   if(vec.empty())
      return std::vector<int>{};

   auto min = *std::min_element( vec.begin(), vec.end() );
   auto max = *std::max_element( vec.begin(), vec.end() );

   std::vector<int> count( max - min + 1, 0 );
  
   auto it = vec.begin();
   while(it!=vec.end()){
   		++count[*it - min];
   		++it;
   }

   std::partial_sum( count.begin(), count.end(), count.begin() );

   std::vector<int> ordenado( vec.size() );
   for ( auto it2= vec.rbegin(); it2 != vec.rend(); ++it2 )
      ordenado[ --count[ *it2 - min ] ] = *it2;

   return ordenado;
}

void bucketSort(std::vector<int> &vet, int size){

    int matrix[10][size], aux[size], cont=1, num, w=0, i, j; 
    
    do{
      for(i=0;i<size;i++){aux[i] = 0;}
      for(i=0;i<10;i++)  {
            for(j=0;j<size;j++){
              matrix[i][j] = -1;
              }
      }
      for (i=0;i<size;i++) {
        num = (vet[i]/cont)%10;
        matrix[num][aux[num]] = vet[i];
        aux[num]++;
      }
      
      for(i=0;i<10;i++) {
          for(j=0;j<size;j++){
            if(matrix[i][j] != -1){
            vet[w] = matrix[i][j];
            w++;
            }
          }
      }
      w = 0; 
      cont=cont*10;
      }while(aux[0] < size);
}

void radixSort(std::vector<int> &vec, int size) {

    int i;
    int *b;
    int maior = vec[0];
    int exp = 1;

    b = (int *)calloc(size, sizeof(int));

    for (i = 0; i < size; i++) {
        if (vec[i] > maior)
          maior = vec[i];
    }
 
    while (maior/exp > 0) {
        int bucket[10] = { 0 };
      for (i = 0; i < size; i++)
          bucket[(vec[i] / exp) % 10]++; 
      for (i = 1; i < 10; i++)
          bucket[i] += bucket[i - 1];
      for (i = size - 1; i >= 0; i--)
          b[--bucket[(vec[i] / exp) % 10]] = vec[i];
      for (i = 0; i < size; i++)
          vec[i] = b[i];
      exp *= 10;
    }

    free(b);
}

int main(int argc, char* argv[]){
	
	int in, len_vec;
	std::cin >> len_vec;
	std::vector<int> vec(len_vec);

  for(int i=0; i<len_vec; i++)std::cin>>in, vec[i]=in;
	
	if(argc==2){

		int param = atoi(argv[1]);
		
    if(param==1)
      vec = countingSort(vec);

    else if(param==2)
      bucketSort(vec, vec.size());

    else if(param==3)
      radixSort(vec, vec.size());

    else{
      fail();
      return 1;
    }
		print_vector(vec);
 	}else{
		fail();
	}

	return 0;
}

void print_vector(std::vector<int> vec){
	int len = vec.size();
	for(int i=0; i<len; i++)
		std::cout << vec[i] << std::endl;
}

void fail(){
	std::cout << "Selecione um algoritmo como argumento:\n" << std::endl;
	std::cout << "1 - Counting Sort" << std::endl;
	std::cout << "2 - Bucket Sort" << std::endl;
	std::cout << "3 - Radix Sort" << std::endl;
}