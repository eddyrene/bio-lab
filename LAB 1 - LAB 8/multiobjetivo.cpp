/*
Eddy Rene Caceres Huacarpuma
Algoritmos Geneticos

*/
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
#include <list>
#include <ctime>

using namespace std;

const float PI = 3.14159;
typedef pair<float,float> pair_ff;
typedef pair<bool,pair_ff> pair_b_ff;
typedef vector<pair_ff> pob;

std::vector<pair_ff> costos;
list<pair <bool, pair_ff> > lista;

std::vector<float> vectRuleta;
vector<pair_ff> vectTorneo;

pob poblacion;
int size_crom = 7;
int size_pob =4;
int puntocruz=3;
float por_mutacion = 0.05;
float por_cruzamiento = 0.9;
int ite=100;
string tipo_mutacion = "mutacion simple";


typedef struct {
{ 
	pair_ff val;
	int rank;
	float dist;
}individuo;


class poblacion
{

}



pair_ff funcion_objetivo(float x, float y )
{

	float f1 = 4*x*x + 4*y*y;  
	float f2 = pow((x - 5 ),2) + pow((y- 5),2); 
    return  pair_ff(f1,f2);
}

bool domina(pair_ff a, pair_ff b)
{
	//cout<<"\n comparando:"<<a.first<<" con "<<b.first <<"  y  "<<a.second <<" con "<< b.second<<endl;
	if(a.first < b.first || a.second < b.second )
	{
		//cout << "se cumple"<<endl;
		return true;
	}
	return false;
}
/*void ruleta()
{
    cout<<"\nSelección de Individuos - Método de la Ruleta"<<endl;
    double sum_ruleta= 0;
    vectRuleta.clear();

    for (int i =0; i < poblacion.size() ; i++)
        sum_ruleta+= costos[i];
    for (int i =0; i < poblacion.size() ; i++)
        vectRuleta.push_back( (costos[i]*100)/sum_ruleta);
    for (int i =0; i < poblacion.size() ; i++)
    	cout<<"ruleta"<<endl;
        //cout<<"\n"<<i+1<<')'<< [i] <<" - "<<costos[i]<<" - "<<vectRuleta[i]<<endl;
}
*/
void torneo()
{
	cout<<"\nSelección de Individuos - Método de Torneo"<<endl;
	vectTorneo.clear();
	int elegidos = size_pob/2;
	for(int i =0 ;i< elegidos ; i++ )
	{
		vectTorneo.push_back(poblacion[rand() % size_crom]);
	}
}
void inicio2()
{
    /*poblacion.push_back(pair_ff(2.24,1.3));
    poblacion.push_back(pair_ff(4.24,2.3));
    poblacion.push_back(pair_ff(3.24,0.3));*/

    costos.clear();
    lista.clear();
    poblacion.clear();
	srand (static_cast <unsigned> (time(0)));
	for( int i=0 ;i< size_pob ;i++ )
	{
		bool req = false;
		float r1,r2;
		while(!req)
		{
			float xmin = 0.0; float xmax = 5.0 ; float ymin = 0.0; float ymax= 3.0;
			r1 = xmin + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(xmax-xmin)));
			r2 = ymin + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(ymax-ymin)));
			cout<<"r1"<<r1<<"r2"<<r2<<endl;
			if(((pow((r1-5),2)+ r2*r2 - 25) <= 0) && ((-1*pow((r1-8),2)-pow((r2+3),2) + 7.7))<=0) 
					req = true;	
		}
		poblacion.push_back(pair_ff(r1,r2));	
	}
    pair_ff result; 
 	for(auto p: poblacion)
 	{
 		result = funcion_objetivo(p.first, p.second); 
 		costos.push_back(result);
 	}   
    
    int i =0;
    int j= 0;
	bool flag=false; 
	for(i =0; i<size_pob ; i++)
	{
		for(j=i;j< size_pob; j++)
		{
			flag= false;
			if(i!=j)
			{
				if(domina(costos[i], costos[j]))
					flag=true;
				//cout<<"flag: "<<flag<<endl;
			}
		}
	lista.push_back(pair_b_ff(flag,pair_ff(costos[i])));	
	cout<<"\n"<<i+1<<')'<<" ("<<poblacion[i].first<<","<<poblacion[i].second<<')'<<": ("<<costos[i].first<<','<<costos[i].second<<") -> "<<flag<<endl;	   
	}
}

/*
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
    clean_queue();

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

        }
        cout<<"e  : "<<e <<"  d : "<<d<<" "<<endl;
        final = fitness( e+d);
        costos.push_back(final);
        cout<<"\n"<<i+1<<')'<<a[i]<<" - "<<costos[i]<<endl;
        mypq.push(pair<float,string>(costos[i],a[i]));
    }
}
void ruleta()
{
    cout<<"\nSelección de Individuos - Método de la Ruleta"<<endl;
    double sum_ruleta= 0;
    vectRuleta.clear();

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
*/
int main ()
{

	inicio2();
    /*cout<<"Algoritmos Geneticos \n\n";
    cout<<"Tamaño de poblacion: "; cin>>tam_pob;
    cout<<"Tamaño de los Cromosomas: ";cin>>tam;
    cout<<"Cantidad de Iteraciones: ";cin>> ite;
    cout<<"Probabilidad de Cruzamiento: ";cin>>por_cruzamiento;
    cout<<"Cruzamiento de un Punto: ";cin>> puntocruz;
    cout<<"Probabilidad de Mutación:";cin>> por_mutacion;
    cout<<tipo_mutacion<<endl;*/

    /*run();
    inicio2();



    for(int i =0 ;i<ite;i++ )
    {
        cout<<"\nIteracion "<< i <<endl;
        evaluacion();
        ruleta();
        cruzamiento();
        seleccion();
    }*/



	return 0;
}
