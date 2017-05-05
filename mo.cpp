#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
#include <list>
#include <ctime>

using namespace std;

const int size_crom = 7;
static int size_pob =4;

typedef pair<float,float> pair_ff;
typedef pair<bool,pair_ff> pair_b_ff;

typedef struct {

	pair_ff val;
	int rank=0;
	float dist=0;
	int n=0;
}ind;

vector<vector <int > > fronter;
vector<list <int > > sols;
	
class poblacion
{

	public:

		 //int size_pob;
		 int size_ind;

		vector<ind> pob;

		poblacion()
		{
			size_pob=5;
			size_ind=2;	
		}
		void inicio()
		{

			    

			/*srand (static_cast <unsigned> (time(0)));
			for( int i=0 ;i< size_pob ;i++ )
			{
				bool req = false;
				float r1,r2;
				while(!req)
				{
					float xmin = 0.0; float xmax = 5.0 ; float ymin = 0.0; float ymax= 3.0;
					r1 = xmin + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(xmax-xmin)));
					r2 = ymin + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(ymax-ymin)));
					//cout<<"r1 "<<r1<<"r2 "<<r2<<endl;
					if(((pow((r1-5),2)+ r2*r2 - 25) <= 0) && ((-1*pow((r1-8),2)-pow((r2+3),2) + 7.7))<=0) 
							req = true;	
				}
				ind a;
				a.val = pair_ff(r1,r2);
				pob.push_back(a);
				ind ind_= 	pob[i];
				//cout<<"a.vall: "<< ind_.val.first<<endl;
			}*/

			ind e ,f,g,h,i;
			e.val = pair_ff(1,1);
			f.val = pair_ff(5,1);
			g.val = pair_ff(1,8);
			h.val = pair_ff(4,6);
			i.val = pair_ff(7,5);
			pob.push_back(e);pob.push_back(f);pob.push_back(g);pob.push_back(h);pob.push_back(i);

		}
		void print_poblaccion()
		{
			for(auto i:pob)
				cout<<i.val.first<<" "<<i.val.second<<endl;
		}
		bool domina(pair_ff a, pair_ff b)
		{
			//cout<<"\n comparando:"<<a.first<<" con "<<b.first <<"  y  "<<a.second <<" con "<< b.second<<endl;
			//cout << a.first <<"----" <<b.first <<endl;
			if(a.first < b.first || a.second < b.second )
			{
				return true;
			}
			return false;
		}

		void fast_non_dominated_sort()
		{
			fronter.resize(1);
			sols.resize(size_pob);
			//cout<<"size_pob  "<<size_pob<<endl;	
			//print_poblaccion();
			vector<ind> c;
			for(int i = 0;i<size_pob;i++)
			{
				for(int j= 0;j<size_pob;j++)
				{
					//cout << pob[i].val.first<<"*********"<<pob[j].val.first<<endl;
					if(i!=j)
					{
						if(domina(pob[i].val,pob[j].val))
						{
							//cout<<"d****************: "<<pob[i].n<<endl;
							sols[i].push_back(j);
							cout<<"dominancia:"<<i<<" "<<j<<endl;
						}
						else
						{
							pob[i].n++;
						}
					}
				}	
				
			//	cout<<"imprimiendo niveles"<<endl;

				if(pob[i].n==0)
				{
					pob[i].rank=1;
					fronter[0].push_back(i);
				}
				cout<<i<<" :"<< pob[i].n<<" "<<endl;
			}
		//	cout<<endl;
			int g=0;
			cout<<"tiene que ser uno: "<<fronter.size()<<endl;	
			cout<<"Esta 3 : "<<fronter[0].size()<<endl;	
			for(auto i : fronter[g])
				cout<<"t: "<<i<<endl;


			for(auto a : sols[2])
				cout<<"soles: "<<a<<endl;

			while(fronter[g].size()<5000)
			{
				cout<<"tamaño del array:******************************"<<fronter[g].size()<<endl;
				cout<<"entra"<<endl;
				vector<int> Q;
				bool flag=false;
				for(auto i : fronter[g])
				{
					cout<<"p en fi  "<<i<<endl;
					
					for( auto q :sols[i])
					{
						cout<<"index "<<q<<endl;

						pob[q].n--;
						cout<<"peso"<<pob[q].n<<endl;
						if(pob[q].n==0)
						{
							flag=true;
							cout<<"tr"<<endl;
							pob[q].rank=i+1;
							Q.push_back(q);
						}	
					}
				}
				g++;
				cout<<"g: "<<g<<endl;
				if(flag)
					fronter.push_back(Q);
				//fronter[g]=Q;
			}

			//cout<<"________________"<<fronter.size()<<endl;
		}


		void print_front()
		{
		//	cout<<"imprimiendo frontera"<<endl;
		//	cout<<"________________"<<fronter.size()<<endl;


			for( int i=0 ;i<fronter.size();i++ )
			{
						//	cout<<"________________*********************************"<<fronter[i].size()<<endl;
				for(int j=0; j< fronter[i].size();j++ )
				{
					cout<<fronter[i][j]<<" ";
				}
				cout<<endl;
			}
		}
/*
		void eval_dist()
		{

		}*/
};


int main()
{
	poblacion p;
	p.inicio();
	p.print_poblaccion();
	p.fast_non_dominated_sort();
 	p.print_front();
	/*vector<int> a;
	vector<int> b;
	a.push_back(2);
	b=a;
	cout<<b[0]<<endl;*/
	return 0;
}


		/*	
			int i =0;
			for(auto x : pob)
			{
				int j=0;
				for(auto y : pob)
				{
					if(domina(x.val,y.val))
						sols[i].push_back(y);
					else
						x.n++;
				}
				if(x.n)
				{
					x.n=1;
					vector<ind> c ;
					c.push_back(x); 
					fronter.push_back(c);
				}
				i++;
			}	

			*/