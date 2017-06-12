/*
Eddy Rene Caceres Huacarpuma
Algoritmos Geneticos

*/
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
#include <map>
#include <list>

using namespace std;


typedef vector<string> pob;
const float PI = 3.14159;
std::vector<float> costos;
std::vector<float> vectRuleta;
typedef std::vector < vector <int > > matriz;
int inf = 10000;


priority_queue<pair <int,char> > otroVect1, otroVect2;
 
queue <char>  orderx , ordery ; 

priority_queue<pair <float,string> > mypq;

int part_ent = 2; int part_dec = 5;

pob a;
int tam = 10;
int tam_pob=15;
int puntocruz=3;
float por_mutacion = 0.05;
float por_cruzamiento = 0.9;
int ite=100;
string tipo_mutacion = "mutacion simple";
matriz mat;

map <char, int > tabla;

float fitness(float x){
    return  x * sin(10*PI*x) + 1;
}

void inicio2()
{

    mat.resize(tam);
    for(int i=0;i<tam;i++)
        mat[i].resize(tam);

tabla.insert(pair<char,int> ('A',0));
tabla.insert(pair<char,int> ('B',1));
tabla.insert(pair<char,int> ('C',2));
tabla.insert(pair<char,int> ('D',3));
tabla.insert(pair<char,int> ('E',4));
tabla.insert(pair<char,int> ('F',5));
tabla.insert(pair<char,int> ('G',6));
tabla.insert(pair<char,int> ('H',7));
tabla.insert(pair<char,int> ('I',8));
tabla.insert(pair<char,int> ('J',9));


mat[0][0] = inf;
mat[0][1] = 12;
mat[0][2] = 3 ;
mat[0][3] = 23;
mat[0][4] = 1;
mat[0][5] = 5;
mat[0][6] = 23;
mat[0][7] = 56;
mat[0][8] = 12;
mat[0][9] = 11;


mat[1][0] = 12;
mat[1][1] = inf;
mat[1][2] = 9;
mat[1][3] = 18;
mat[1][4] = 3;
mat[1][5] = 41;
mat[1][6] = 45;
mat[1][7] = 5;
mat[1][8] = 41;
mat[1][9] = 27;

mat[2][0] = 3;
mat[2][1] = 9;
mat[2][2] = inf;
mat[2][3] = 89;
mat[2][4] =56;
mat[2][5] =21;
mat[2][6] =12;
mat[2][7] =48;
mat[2][8] =14;
mat[2][9] =29;


mat[3][0] = 23;
mat[3][1] = 18;
mat[3][2] = 89;
mat[3][3] = inf;
mat[3][4] = 87;
mat[3][5] = 46;
mat[3][6] = 75;
mat[3][7] = 17;
mat[3][8] = 50;
mat[3][9] = 42;


mat[4][0] = 1;
mat[4][1] = 3;
mat[4][2] = 56;
mat[4][3] = 87;
mat[4][4] = inf;
mat[4][5] = 55;
mat[4][6] = 22;
mat[4][7] = 86;
mat[4][8] = 14;
mat[4][9] = 33;


mat[4][0] = 5;
mat[5][1] = 41;
mat[5][2] = 21;
mat[5][3] = 46;
mat[5][4] = 55;
mat[5][5] = inf;
mat[5][6] = 21;
mat[5][7] = 76;
mat[5][8] = 54;
mat[5][9] = 81;


mat[6][0] = 23;
mat[6][1] = 45;
mat[6][2] = 12;
mat[6][3] = 75;
mat[6][4] = 22;
mat[6][5] = 21;
mat[6][6] = inf;
mat[6][7] = 11;
mat[6][8] = 57;
mat[6][9] = 48;


mat[7][0] = 56;
mat[7][1] = 5;
mat[7][2] = 48;
mat[7][3] = 17;
mat[7][4] = 86;
mat[7][5] = 76;
mat[7][6] = 11;
mat[7][7] = inf;
mat[7][8] = 63;
mat[7][9] = 24;


mat[8][0] = 12;
mat[8][1] = 41;
mat[8][2] = 14;
mat[8][3] = 50;
mat[8][4] = 14;
mat[8][5] = 54;
mat[8][6] = 57;
mat[8][7] = 63;
mat[8][8] = inf;
mat[8][9] = 9;

mat[9][0] = 11;
mat[9][1] = 27;
mat[9][2] = 29;
mat[9][3] = 42;
mat[9][4] = 33;
mat[9][5] = 81;
mat[9][6] = 48;
mat[9][7] = 24;
mat[9][8] = 9;
mat[9][9] = inf;


a.push_back("ABCDEFGHIJ");
a.push_back("CEDABJIHFG");
a.push_back("DBCAEHFGIJ");
a.push_back("CAIEJHDGBF");
a.push_back("BAHFJDCEGI");
a.push_back("GDHJFBACIE");
a.push_back("FAIJHECGBD");
a.push_back("BIGACEJHFD");
a.push_back("AECDBJIGHF");
a.push_back("ABHCFEIDGJ");
a.push_back("EDAJFGHCIB");
a.push_back("FAIJCEDBGH");
a.push_back("GDHJFBACIE");
a.push_back("BJAFICGHDE");
a.push_back("DAJFHGBCIE");
a.push_back("ACEGFDJHIB");



/*char mygen[] = {'A','B','c','D','E','F','G','H','I','J'};

  std::cout << "The 3! possible permutations with 3 elements:\n";
  do {
      for(int i=0;i<10;i++)
            cout << mygen[i];
      cout<<endl;
  } while ( std::next_permutation(mygen,mygen+10) );*/

 /* std::string cadena = "ABCDEFGHIJ";
  do
  {
    std::cout << cadena << std::endl;
  } while ( std::next_permutation( cadena.begin( ), cadena.end( ) ) );*/



float final;

for(int i =0 ;i<tam_pob;i++)
{
    final=0;
    for(int j=0 ;j< tam;j++)
    {
            if (j==tam-1)
            {
                int ff = tabla.find(a[i][j])->second;
                int ss = tabla.find(a[i][0])->second;
                final += mat[ff][ss];break;            }
            else{

                int f = tabla.find(a[i][j])->second;
                int s = tabla.find(a[i][j+1])->second;
                final += mat[f][s];
            }
    }
    costos.push_back(final*-1);
    cout<<"\n"<<i+1<<')'<<a[i]<<" =  "<<costos[i]*-1<<endl;
    mypq.push(pair<float,string>(costos[i],a[i]));
}
}

void clean_queue()
{
    while(!mypq.empty())
    {
        mypq.pop();
    }
}
void evaluacion()
{
    cout<<"\nEvaluando Individuos "<<endl;
    costos.clear();a.clear();
    int i =0;
    while(i<tam_pob)
    {
            costos.push_back(mypq.top().first);
            //cout<<mypq.top().first<<endl;
            a.push_back(mypq.top().second);
            mypq.pop();
            cout<<"\n"<<i+1<<')'<<a[i]<<" = "<<costos[i]*-1<<endl;
            i++;
    }
}

void seleccion()
{
    cout<< "\nSelección de Siguiente Población"<<endl;
    clean_queue();
    float final;
    int ent=0;
    int dec=0;
    costos.clear();
    for(int i =0; i< a.size() ; i++)
    {
	    final=0;
	    for(int j=0 ;j< tam;j++)
	    {
	            if (j==tam-1)
	            {
	                int ff = tabla.find(a[i][j])->second;
	                int ss = tabla.find(a[i][0])->second;
	                final += mat[ff][ss];break;            }
	            else{

	                int f = tabla.find(a[i][j])->second;
	                int s = tabla.find(a[i][j+1])->second;
	                final += mat[f][s];
	            }
	    }
    costos.push_back(final*-1);
    cout<<"\n"<<i+1<<')'<<a[i]<<" =  "<<costos[i]*-1<<endl;
    mypq.push(pair<float,string>(costos[i],a[i]));
    }
}
void ruleta()
{
    cout<<"\nSelección de Individuos - Método de la Ruleta"<<endl;
    double sum_ruleta= 0;
    vectRuleta.clear();
    for (int i =0; i < a.size() ; i++)
        sum_ruleta+= 1/costos[i];
    for (int i =0; i < a.size() ; i++)
        vectRuleta.push_back( 100/(costos[i])/sum_ruleta);
    for (int i =0; i < a.size() ; i++)
        cout<<"\n"<<i+1<<')'<< a[i] <<" = "<<costos[i]*-1<<" - "<<vectRuleta[i]<<endl;
}

pair<int,int> seleccionpadres()
{

	pair<int, int > pp(0,0);
  int num = rand()%100;
  int num2 = rand()%100;
  //cout<<num<<endl;
  int s =0;
  for (int i =0; i < a.size() ; i++)
  {
        s += vectRuleta[i];
  	if(num<s)
  	{
  		pp.first=i;
  		break;
  	}
  }
  for (int i =0; i < a.size() ; i++)
  {
  	   s += vectRuleta[i];
  	if(num2<s)
  	{
  		pp.second=i;
  		break;
  	}
  }
  return pp;
}
float valorcito(string g)
{
	float final=0;

	    for(int j=0 ;j< tam;j++)
	    {
	            if (j==tam-1)
	            {
	                int ff = tabla.find(g[j])->second;
	                int ss = tabla.find(g[0])->second;
	                final += mat[ff][ss];break;            }
	            else{

	                int f = tabla.find(g[j])->second;
	                int s = tabla.find(g[j+1])->second;
	                final += mat[f][s];
	            }
	        
	    }
	    //cout<<final;	
	return final;
}
bool seleccionGen()
{
	int num = rand()%10;

  if(num<5)
  	 return true;
  	return false;

}
int sorting(char c, int p)
{
	for(int i =0 ;i < tam; i++)
	{
		if(a[p][i]==c)
		return i;
	}
}

vector<string> cruzamiento_cromosoma_PBX(int p1, int p2 )
{
  bool flags[tam];
  char hijo1[tam], hijo2[tam];
  list<char> papa, mama;
  list<char> elem_hijo1, elem_hijo2;

    for (int i =0 ;i <tam ;i++ )
        flags[i]=seleccionGen();

    for (int i = 0;i <tam ;i++ )
    {
        papa.push_back(a[p1][i]);
        mama.push_back(a[p2][i]);
        if(flags[i])
        {
        	//cout<<"i:" <<i <<endl;
        	hijo1[i]= a[p2][i]; 
        	hijo2[i]= a[p1][i];

                cout<<" "<<a[p2][i]<<endl;

                elem_hijo2.push_back(a[p1][i]);  //hijo2  // los que no tienen que repetirse
                elem_hijo1.push_back(a[p2][i]);  //hijo1
          }
     }
      while(!elem_hijo1.empty())
      {
           char t = elem_hijo1.front();
           papa.remove(t);
           elem_hijo1.pop_front();
            char u = elem_hijo2.front();
           mama.remove(u);
           elem_hijo2.pop_front();
      }

      for(int i =0;i < tam;i++)
      {
          if(!flags[i])
          {
                hijo1[i]=papa.front();
                papa.pop_front();

                hijo2[i]=mama.front();
                mama.pop_front();
          }
      }
        vector<string> r ;

        string c = string(hijo1,10);
        string s = string(hijo2,10);


        r.push_back(c);
        r.push_back(s);
        return r;
        }



 bool comp_string(string c , string d)
 {
 	for(int i =0 ;i<c.size();i++ )
 		if (c[i]!=d[i])
 			return false;
 		return true;
 }



pair<float, string> permutacion(string c , int h  )
{
	priority_queue<pair <float,string> > fit;

	int i =0;
	while ( i<h )
	{
		int first = rand() % tam;
		int second = rand() % tam;
		char tmp = c[first];
		c[first] = c[second];
		c[second] = tmp;

		int final=valorcito(c);
		fit.push(pair<float,string> (final*(-1), c ));
		i++;
		cout<<"hijo-p"<<final*(-1)<<" "<<c<<endl; 
	}
	cout<<"\n mejor: "<<fit.top().first * -1<<" "<< fit.top().second<< endl;
	return fit.top();

}
 string busqueda_escalada(string cadena)
{
	pair<float,string> nuevo ;
	string antigua = " ";
	while(comp_string(cadena, antigua)==false)
	{
		antigua = cadena;	
		//string nuevo= "";
		nuevo = permutacion(cadena, 5);
		//cout<<"este :"<<nuevo.first <<endl;
		if( (nuevo.first)*(-1) < valorcito(cadena))
		{
			cadena=nuevo.second;
				//cout<<"dffffff : "<<cadena<<endl;	
		}

	}
	//cout<<"return: "<<nuevo<<endl;
	return antigua;
}
void mutacion2(float prob ,vector<string> & h)
 {
    int mut_pos1 =tam-1;
    int mut_pos2 = 0;

     for(int i =0 ;i < h.size();i++)
     {
         int rango = rand()%100;

         if(rango>prob*100)
         {
         //	cout<<"imprime hijos"<<endl;
             cout<<"\n"<<h[i]<<endl;
             continue;
         }
         else
         {
             char tmp; 
             tmp=h[i][mut_pos1];
             h[i][mut_pos1]= h[i][mut_pos2];
             h[i][mut_pos2]=tmp;

             cout<<"\nMuto: "<< i+1<<endl;
             cout<<"\n"<<h[i]<<" "<<valorcito(h[i]) <<endl;
             cout<<"\nBusqueda por escalada: "<<endl;
             string c=busqueda_escalada(h[i]);	
             //string
             cout<<"\n"<<c<<endl;
         }
     }
 }


void cruzamiento_PBX()
{
  int padre , madre ;
    pair<int,int> padres = seleccionpadres();
    padre = padres.first;
    madre = padres.second;
    if (padre== madre)
    {
      madre =  rand() % tam-padre+ padre;
    }

    cout<<"\nPadre:\n"<< padre+1 <<" "<< a[padre]<< endl;
    cout<<"\nMadre:\n"<< madre+1 <<" "<<a[madre]<< endl;
     vector<string> hijos;
    if(rand()%100 <por_cruzamiento*100)
    {
        cout<<"\nCruzamiento:"<<endl;
        hijos = cruzamiento_cromosoma_PBX(padre, madre);
        mutacion2(por_mutacion,hijos);
    }
    else
    {
        cout<<"\nSin cruzamiento:\n"<<endl;
        hijos.push_back(a[padre]);
        hijos.push_back(a[madre]);
        cout<< hijos[0] <<"\n\n"<<hijos[1]<<endl;

    }
    a.push_back(hijos[0]);
    a.push_back(hijos[1]);
}

void run()
{
    cout<<"run: "<<endl;
    cout<<"Tamaño de la Población: "<< tam_pob<<endl;
    cout<<"Tamaño de los Cromosomas: "<< tam<<endl;
    cout<<"Cantidad de Iteraciones: "<< ite<<endl;
    cout<<"Probabilidad de Cruzamiento: "<< por_cruzamiento<<endl;
    cout<<"Cruzamiento de un Punto: "<< puntocruz<<endl;
    cout<<"Probabilidad de Mutación:"<< por_mutacion<<endl;
    cout<<tipo_mutacion<<endl;
}

int main ()
{
    /*cout<<"Algoritmos Geneticos \n\n";
    cout<<"Tamaño de poblacion: "; cin>>tam_pob;
    cout<<"Tamaño de los Cromosomas: ";cin>>tam;
    cout<<"Cantidad de Iteraciones: ";cin>> ite;
    cout<<"Probabilidad de Cruzamiento: ";cin>>por_cruzamiento;
    cout<<"Cruzamiento de un Punto: ";cin>> puntocruz;
    cout<<"Probabilidad de Mutación:";cin>> por_mutacion;
    cout<<tipo_mutacion<<endl;*/

    srand (time(NULL));
    run();
    inicio2();

    for(int i =0 ;i<ite;i++ )
    {
        cout<<"\nIteracion "<< i <<endl;
        evaluacion();
        ruleta();
        cruzamiento_PBX();
        seleccion();
    }

   	 //cout<<"valor :"<<valorcito("ABCDEFGHIJ");
	return 0;
}
