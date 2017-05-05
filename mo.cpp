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

vector<vector <ind > > fronter;
vector<vector <ind > > sols;
	
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
			//pob.resize(size_pob);
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
					//cout<<"r1 "<<r1<<"r2 "<<r2<<endl;
					if(((pow((r1-5),2)+ r2*r2 - 25) <= 0) && ((-1*pow((r1-8),2)-pow((r2+3),2) + 7.7))<=0) 
							req = true;	
				}
				ind a;
				a.val = pair_ff(r1,r2);
				pob.push_back(a);
				ind ind_= 	pob[i];
				//cout<<"a.vall: "<< ind_.val.first<<endl;
			}
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
			//fronter.resize(20);
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
							sols[i].push_back(pob[j]);
						}
						else
						{
							pob[i].n++;
						}
					}
				}	
				
				if(pob[i].n==0)
				{
					//pob[i].n=0;
					
					c.push_back(pob[i]); 	
					//cout<<"ce"<<endl;	
				}
				cout<<i<<" :"<< pob[i].n<<endl;
			}
			fronter.push_back(c);
			int g=0;
			cout<<"f: "<<fronter.size()<<endl;	

			while(g<fronter.size())
			{
				cout<<"entra"<<endl;
				vector<ind> Q;
				for(int i=0;i<fronter.size();i++)
				{
					for( auto q :sols[i])
					{
						//q.n--;
						cout<<"fawfe"<<q.n<<endl;
						if(q.n==0)
						{
							cout<<"tr"<<endl;
							q.rank++;
							Q.push_back(q);
						}	
					}
				}
				g++;
				cout<<"hasta aqui"<<endl;
				fronter.push_back(Q);
				//fronter[g]=Q;
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