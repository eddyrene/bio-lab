/*
 **************************************************************
 *         C++ Mathematical Expression Toolkit Library        *
 *                                                            *
 * Simple Example 1                                           *
 * Author: Arash Partow (1999-2017)                           *
 * URL: http://www.partow.net/programming/exprtk/index.html   *
 *                                                            *
 * Copyright notice:                                          *
 * Free use of the Mathematical Expression Toolkit Library is *
 * permitted under the guidelines and in accordance with the  *
 * most current version of the MIT License.                   *
 * http://www.opensource.org/licenses/MIT                     *
 *                                                            *
 **************************************************************
*/


#include <cstdio>
#include <string>
#include "exprtk.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
#include <list>
#include <ctime>

using namespace std;

vector<double> entrada;
vector<double> salida;
vector<double> actual;
vector<double> diferencia;
vector<string > poblacion;
std::vector<float> vectRuleta;
std::vector<float> costos;

priority_queue< pair <double,string> > mypq;
string fun = "+-*/";
int puntocruz=8;
int size_crom = 20; 
float por_mutacion = 0.9;
float por_cruzamiento = 0.9;
int size_pob=5;
int ite=100;

double fitness(string formula)
{
   typedef exprtk::symbol_table<double> symbol_table_t;
   typedef exprtk::expression<double>     expression_t;
   typedef exprtk::parser<double>             parser_t;

   std::string expression_string = formula;
   double x;
   symbol_table_t symbol_table;
   symbol_table.add_variable("x",x);
   symbol_table.add_constants();

   expression_t expression;
   expression.register_symbol_table(symbol_table);

   parser_t parser;
   parser.compile(expression_string,expression);

   x= 10;
   double y ; 
   actual.clear();
   for (int i = 0 ; i< entrada.size(); i++)
   {
      x= entrada[i];
      actual.push_back(expression.value());   
   }
   
   //Calculado el error 
   double sum=0;
   for (int i = 0 ; i< entrada.size(); i++)
   {
      sum+=pow(entrada[i]-actual[i],2);
   }
   return  sum/entrada.size(); 
}
void clean_queue()
{
    while(!mypq.empty())
    {
        mypq.pop();
    }
}
void evaluando()
{
   cout<<"Nueva Población"<<endl;
   for(int i = 0; i< poblacion.size();i++)
   {
         mypq.push(pair<double,string>(fitness(poblacion[i])*-1, poblacion[i]));
         costos.push_back(fitness(poblacion[i]));
         cout<< poblacion[i] <<" "<< costos [i]<<endl;
   }
}

void mostrando()
{
   cout<< "\nSelección de Siguiente Población"<<endl;
   clean_queue();
   costos.clear();
   for(int i = 0; i< poblacion.size();i++)
   {
      mypq.push(pair<double,string>(fitness(poblacion[i])*-1, poblacion[i]));
      costos.push_back(fitness(poblacion[i]));
      cout<< poblacion[i] <<" "<< costos [i]<<endl;
   }   
}

void sn()
{
   cout<<"\nEvaluando Individuos "<<endl;
   costos.clear();poblacion.clear();
   int i;
   while(i<size_pob)
   {
      costos.push_back(mypq.top().first);
      //cout<<mypq.top().first<<endl;
      poblacion.push_back(mypq.top().second);
      mypq.pop();
      cout<<"\n"<<i+1<<')'<<poblacion[i]<<" = "<<costos[i]*-1<<endl;
      i++;
   }

}

void mutacion(float prob ,vector<string> h)
 {
    int mut_pos =size_crom-1;
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
             if (h[i][mut_pos]=='x')
                 h[i][mut_pos]=rand()% 1+5 +'0';
             else
             {
               if(h[i][mut_pos]== '+' || h[i][mut_pos]== '-' || h[i][mut_pos]== '*' || h[i][mut_pos]== '/' )
               {
                  int t= rand() % 4;
                  h[i][mut_pos]=fun[t];
               }
                 
              } 
             cout<<"\n"<<h[i]<<endl;
         }
     }
 }


 vector<string> cruzamiento_cromosoma(int p1, int p2 , int punto)
{
    string hijo1=""; string hijo2= "";

    for (int i =0 ;i <size_crom ;i++ )
    {
        if (i<punto)
        {
            hijo1+=poblacion[p1][i];
            hijo2+=poblacion[p2][i];
        } 
        else
        {
            hijo1+=poblacion[p2][i];
            hijo2+=poblacion[p1][i]; 
        }
   }   
   vector<string> r ; 
   r.push_back(hijo1);
   r.push_back(hijo2);
    return r;
}

void ruleta()
{
    cout<<"\nSelección de Individuos - Método de la Ruleta"<<endl;
    double sum_ruleta= 0;
    for (int i =0; i < poblacion.size() ; i++)
        sum_ruleta+= 1/costos[i];
    for (int i =0; i < poblacion.size() ; i++)
        vectRuleta.push_back( (100/costos[i])/sum_ruleta);
    for (int i =0; i < poblacion.size() ; i++)
        cout<<"\n"<<i+1<<')'<< poblacion[i] <<" - "<<costos[i]<<" - "<<vectRuleta[i]<<endl;
}
int seleccionpadres()
{
  int num = rand()%100;
  //cout<<num<<endl;
  int s =0;
  for (int i =0; i < poblacion.size() ; i++)
  {
        s += vectRuleta[i];
   if(num<s)
      return i;
  }
  return poblacion.size() - 1;
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
        hijos.push_back(poblacion[padre]);
        hijos.push_back(poblacion[madre]);
        cout<< hijos[0] <<"\n\n"<<hijos[1]<<endl;

    }
    poblacion.push_back(hijos[0]);
    poblacion.push_back(hijos[1]);
}



void inicio()
{  
   int t=0;
   //cout<<"#1"<<endl;
   while(t<5)
   {
      //cout<<"#2"<<endl;
      string cade = "( x - x) + ( x - x )";
      //cout<<"#3"<<endl;
      for(int i=0;i<size_crom;i++)
      {
        // cout<<"#4"<<endl;
         cout<<i<<endl;
         int p =rand()%10;
         if(i==2)
         { 
            if(p<5)
               cade[i]= 'x';
            else
               cade[i]=rand()% 1 + (5)+'0';
         }
         p =rand()%10;
         if(i==6)
         {
            if(p<5)
               cade[i]= 'x';
            else
               cade[i]=rand()% 1 + (5)+'0';  
         }
         p =rand()%10;
         if(i==13)   
         {
            if(p<5)
               cade[i]= 'x';
            else
               cade[i]=rand()% 1 + (5)+'0'; 
         }
         p =rand()%10;
         if(i==17)
         {
            if(p<5)
               cade[i]= 'x';
            else
               cade[i]=rand()% 1 + (5)+'0'; 
         }
         if (i==4)
         {
            cade[i]= fun[rand()%4]; 
         }
         if (i==9)
          {
               cade[i]= fun[rand()%4]; 
          } 
          if(i==15)
          {
               cade[i]= fun[rand()%4]; 
          }
      }

      poblacion.push_back(cade);
      //cout<<"fafe"<<endl;
      t++;
   }

  /* poblacion.push_back("( x - x) + ( x - x )");
   poblacion.push_back("( 3 - 2) + ( 5 * x )");
   poblacion.push_back("( x * x) - ( x - 2 )");
   poblacion.push_back("( x + x) / ( 2 - 1 )");
   poblacion.push_back("( x + 4) / ( x - 3 )");*/

   entrada.push_back(0); 
   entrada.push_back(0.1);
   entrada.push_back(0.2);
   entrada.push_back(0.3);
   entrada.push_back(0.4);
   entrada.push_back(0.5);
   entrada.push_back(0.6); 
   entrada.push_back(0.7);
   entrada.push_back(0.8);
   entrada.push_back(0.9);
   
   salida.push_back(0);
   salida.push_back(0.005);
   salida.push_back(0.02);
   salida.push_back(0.045);
   salida.push_back(0.08);
   salida.push_back(0.125);
   salida.push_back(0.18);
   salida.push_back(0.245);
   salida.push_back(0.32);
   salida.push_back(0.405);
   evaluando();

}
int main()
{

   srand (time(NULL));
   //trig_function<double>();
   cout<<"pasa esto"<<endl;
   inicio();
   cout<<"pasa esto"<<endl;
   for(int i =0 ;i<10;i++ )
    {
        cout<<"\nIteracion "<< i <<endl;
        mostrando();
        ruleta();
        cruzamiento();
        evaluando();
        sn();

    }

   return 0;
}