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


using namespace std;


typedef vector<string> pob;
const float PI = 3.14159;
std::vector<float> costos;
std::vector<float> vectRuleta;
typedef std::vector < vector <int > > matriz;
int inf = 10000;


priority_queue<pair <int,char> > otroVect1, otroVect2;

priority_queue<pair <float,string> > mypq;

int part_ent = 2; int part_dec = 5;

pob a;
int tam = 5;
int tam_pob=4;
int puntocruz=3;
float por_mutacion = 0.05;
float por_cruzamiento = 0.9;
int ite=30;
string tipo_mutacion = "mutacion simple";
matriz mat;

map <char, int > tabla;

float fitness(float x){
    return  x * sin(10*PI*x) + 1;
}

void inicio2()
{

    mat.resize(5);
    for(int i=0;i<5;i++)
        mat[i].resize(5);

tabla.insert(pair<char,int> ('A',0));
tabla.insert(pair<char,int> ('B',1));
tabla.insert(pair<char,int> ('C',2));
tabla.insert(pair<char,int> ('D',3));
tabla.insert(pair<char,int> ('E',4));

mat[0][0] = inf;
mat[0][1] = 2;
mat[0][2] = 2 ;
mat[0][3] = 1;
mat[0][4] = 4;

mat[1][0] = 2;
mat[1][1] = inf;
mat[1][2] = 3;
mat[1][3] = 2;
mat[1][4] = 3;

mat[2][0] = 2;
mat[2][1] = 3;
mat[2][2] = inf;
mat[2][3] = 2;
mat[2][4] =2;

mat[3][0] = 1;
mat[3][1] = 2;
mat[3][2] = 2;
mat[3][3] = inf;
mat[3][4] = 4;

mat[4][0] = 4;
mat[4][1] = 3;
mat[4][2] = 2;
mat[4][3] = 4;
mat[4][4] = inf;

a.push_back("ABCDE");
a.push_back("CEDAB");
a.push_back("DBCAE");
a.push_back("AECDB");

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

vector<string> cruzamiento_cromosoma_OBX(int p1, int p2 )
{
	bool flags[tam];
	char hijo1[tam], hijo2[tam];


    for (int i =0 ;i <tam ;i++ )
        flags[i]=seleccionGen();

    for (int i = 0;i <tam ;i++ )
    {

        if(flags[i])
        {
        	//cout<<"fa"<<endl;
        	int v = sorting(a[p1][i],p2);
        	otroVect1.push(pair<int , char> (-1*v, a[p1][i]));
        	v = sorting(a[p2][i],p1);
        	otroVect2.push(pair<int , char> (-1*v, a[p2][i]));
        }
    	else
    	{
    		hijo1[i]=a[p1][i];
    	//	cout<<"f : "<<a[p1][i]<<" "<<hijo1[i]<<endl;
    		hijo2[i]=a[p2][i];
    	}
    }

	//cout<< hijo1<< "   $$$ " << hijo2 <<endl;	
    for(int j=0;j<tam;j++)
    {
    	if(flags[j])
    	{
    		hijo1[j]=otroVect1.top().second;
	    	otroVect1.pop();
	    	hijo2[j]=otroVect2.top().second;
	    	otroVect2.pop();
    	}
    }
        vector<string> r ;
        string c(hijo1);
        string s(hijo2);
        r.push_back(c);
        r.push_back(s);

      //cout<<c<<" -> "<<s<<endl;
    return r;
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
             cout<<"\n"<<h[i]<<endl;
         }
     }
 }
void cruzamiento_OBX()
{
	int padre , madre ;
    pair<int,int> padres = seleccionpadres();
    padre = padres.first;
    madre = padres.second;
    if (padre== madre)
    {
    	madre =  rand() % tam-padre+ padre;
    }

    cout<<"\nPadre:\n"<< padre+1 << endl;
    cout<<"\nMadre:\n"<< madre+1 << endl;
     vector<string> hijos;
    if(rand()%100 <por_cruzamiento*100)
    {
        cout<<"\nCruzamiento:"<<endl;
        hijos = cruzamiento_cromosoma_OBX(padre, madre);
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
        cruzamiento_OBX();
        seleccion();
    }
	return 0;
}
