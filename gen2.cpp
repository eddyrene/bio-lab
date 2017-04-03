/*
Eddy Rene Caceres Huacarpuma
Algoritmos Geneticos

*/
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>



using namespace std;


typedef vector<string> pob;
const float PI = 3.14159;
std::vector<float> costos;
std::vector<float> vectRuleta;
priority_queue<pair <int,string> > mypq;


int part_ent = 2; int part_dec = 6; 

pob a;
int tam = 8;
int tam_pob=4;
int puntocruz=3;
float por_mutacion = 0.05;
float por_cruzamiento = 0.9;
int ite=100;
string tipo_mutacion = "mutacion simple";


float fitness(float x){
    return  x * sin(10*PI*x) + 1;
}
void inicio2()
{
    a.push_back("10101000");
    a.push_back("10101111");
    a.push_back("10101110");
    a.push_back("10101110");
    float final; 
    int ent=0;
    int dec=0;
    for(int i =0 ;i<tam_pob;i++)
    {
        final=0;
        int e=0; float d=0;
        for (int j=0 ; j < part_ent ; j++)
        {
                int t = a[i][j]-'0';
                    e+=pow(2,part_ent-j-1)*t;
        }
        for (int j=1; j <= tam-part_ent; j++)    
        {

                    int t = a[i][part_ent+j-1]-'0';
                    d+=pow(2,-(j))*t;
                    //cout<<"t :"<<t <<"d : "<<d<<" "<<j<<endl;
        }
        final = fitness( e+d);
        costos.push_back(final);
        cout<<"\n"<<i+1<<')'<<a[i]<<"--"<<costos[i]<<endl;
        mypq.push(pair<int,string>(costos[i],a[i]));
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
            a.push_back(mypq.top().second);
            mypq.pop();
            cout<<"\n"<<i+1<<')'<<a[i]<<" - "<<costos[i]<<endl;
            i++;
    }
}

void seleccion()
{
    cout<< "\nSelección de Siguiente Población"<<endl;
    //clean_queue();
    float final;
    int ent=0;
    int dec=0;
    for(int i =0; i< a.size() ; i++)
    {
        final=0;
        int e=0; float d=0;
        for (int j=0 ; j < part_ent ; j++)
        {
                int t = a[i][j]-'0';
                    e+=pow(2,part_ent-j-1)*t;
        }
        for (int j=1; j <= tam-part_ent; j++)
        {

                    int t = a[i][part_ent+j-1]-'0';
                    d+=pow(2,-(j))*t;
                    //cout<<"t :"<<t <<"d : "<<d<<" "<<j<<endl;
        }
        final = fitness( e+d);
        costos.push_back(final);
        cout<<"\n"<<i+1<<')'<<a[i]<<" - "<<costos[i]<<endl;
        mypq.push(pair<int,string>(costos[i],a[i]));
    }
}
void ruleta()
{
    cout<<"\nSelección de Individuos - Método de la Ruleta"<<endl;
    double sum_ruleta= 0;

    for (int i =0; i < a.size() ; i++)
        sum_ruleta+= costos[i];
    for (int i =0; i < a.size() ; i++)
        vectRuleta.push_back( (costos[i]*100)/sum_ruleta);
    for (int i =0; i < a.size() ; i++)
        cout<<"\n"<<i+1<<')'<< a[i] <<" - "<<costos[i]<<" - "<<vectRuleta[i]<<endl;
}

int seleccionpadres()
{
  int num = rand()%100;
  //cout<<num<<endl;
  int s =0;
  for (int i =0; i < a.size() ; i++)
  {
        s += vectRuleta[i];
  	if(num<s)
  		return i;
  }
  return a.size() - 1;
}
 vector<string> cruzamiento_cromosoma(int p1, int p2 , int punto)
{

    string hijo1=""; string hijo2= "";

    for (int i =0 ;i <tam ;i++ )
    {
        if (i<punto)
            hijo1+=a[p1][i];
        else
            hijo2+=a[p1][i];
    }
    string tmp="";
    for (int i = 0;i <tam ;i++ )
    {
        if (i<punto)
        {

             tmp+= a[p2][i];
        }
        else
            hijo1+=a[p2][i];

    }
    hijo2=tmp+hijo2;
        vector<string> r ;
        r.push_back(hijo1);
        r.push_back(hijo2);
    return r;
}


 void mutacion(float prob ,vector<string> h)
 {
    int mut_pos =tam-1;
     for(int i =0 ;i < h.size();i++)
     {
         int rango = rand()%100;
         if(rango>prob*100)
         {
             cout<<"\n"<<h[i]<<endl;
             continue;
         }
         else
         {
             cout<<"\nMuto: "<< i+1<<endl;
             if (h[i][mut_pos]=='0')
                 h[i][mut_pos]='1';
             else
                 h[i][mut_pos]='0';

             cout<<"\n"<<h[i]<<endl;
         }
     }
 }

void cruzamiento()
{
    int padre , madre ;
    padre = seleccionpadres();
    madre = seleccionpadres();

    cout<<"\nPadre:\n"<< padre+1 << endl;
    cout<<"\nMadre:\n"<< madre+1 << endl;

    vector<string> hijos;
    if(rand()%100 <por_cruzamiento*100)
    {
        cout<<"\nCruzamiento:"<<endl;
        hijos = cruzamiento_cromosoma(padre, madre, puntocruz);
        mutacion(por_mutacion,hijos);
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

    inicio2();
    //run();


    for(int i =0 ;i<ite;i++ )
    {
        cout<<"\nIteracion "<< i <<endl;
        evaluacion();
        ruleta();
        cruzamiento();
        seleccion();
    }
	return 0;
}
