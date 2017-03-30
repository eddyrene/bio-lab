

/*
Eddy Rene Caceres Huacarpuma
Algoritmos Geneticos 

*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;




typedef vector<string> pob;

std::vector<float> costos;
std::vector<float> vectRuleta;
pob a; 
int tam = 5;
void inicio ()
{
	a.push_back("00110");
	a.push_back("10001");
	a.push_back("11011");
	a.push_back("11101");
}

void imprimir()
{
	for (int i =0 ;i< a.size(); i++)
		cout<<a[i]<<endl;
}

void evaluacion()
{
	
	for(int i =0; i< a.size() ; i++)
	{
		float sum =0;
		for (int j=0 ; j < tam ; j++)
		{
			int t = a[i][j]-'0';
			sum+=pow(2,j)*t;
		}
		costos.push_back(sum);
		cout<<a[i]<<"--"<<costos[i]<<endl;

	}
}

/*Poblacion.prototype.ruleta = function() {
  console.log("Selección de Individuos - Método de la Ruleta");
  var sum_ruleta = 0;
  this.ruleta_vect = [];

  for(var i = 0; i<this.population.length; i++) { 
    sum_ruleta += 1 / this.population[i].cost;  // los pesos son inversamente proporcionales
  }

  for(var i = 0; i<this.population.length; i++) {
    this.ruleta_vect.push((1 / this.population[i].cost * 100) / sum_ruleta); //llenamos sus vec
  }
  
  //Imprime la población y sus valores en la ruleta
  for(var i = 0; i < this.population.length; i++) {
    c_gen = '';
    for(var j = 0; j < this.population[i].size; j++){
      c_gen += this.population[i].genotype[j];
    }
    console.log(i + 1 + ") " + c_gen + " - " + this.population[i].cost + " -- " + this.ruleta_vect[i]); 
  }
}*/

void ruleta()
{
	double sum_ruleta= 0;

	for (int i =0; i < a.size() ; i++)
	{
		sum_ruleta+= costos[i];
	}

	for (int i =0; i < a.size() ; i++)
	{
		vectRuleta.push_back( (costos[i]*100)/sum_ruleta);
	}

	for (int i =0; i < a.size() ; i++)
	{

		cout<< a[i] <<"-"<<costos[i]<<"-"<<vectRuleta[i]<<endl;
	}
}

int seleccionpadres()
{
	
  int num = random() % 100;
  int s =0;
  for (int i =0; i < a.size() ; i++)
  {
  	s + = vectRuleta[i];
  	if(num<s)
  		return i;
  }
  return a.size() - 1;
}

void cruzamiento()
{
	int padre , madre ; 
	padre = seleccionpadres();
	madre = seleccionpadres();

	

}

void seleccionpoblacion()
{

}
int main ()
{

	inicio();
	//imprimir();
	evaluacion();
	ruleta();

	return 0;
}