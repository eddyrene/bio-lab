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
	int rank;
	float dist;
	int n;
}ind;

vector<vector <ind > > fronter;
vector<vector <ind > > sols;
	
class poblacion
{
	private:
		const int size_pob=5;
		const int size_ind;
		vector<ind> pob;
		//int sol[];
	public:

		void inicio()
		{
			pob.resize(size_pob);
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
				ind a;
				a.val = pair_ff(r1,r2);
				pob.push_back(a);	
			}
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

		void fast_non_dominated_sort()
		{
			fronter.resize(1);
			sols.resize(size_pob);
			for(int i = 0;i<size_pob;i++)
			{
				for(int j= 0;j<size_pob;j++)
				{
					if(domina(pob[i].val,pob[j].val))
						sols[i].push_back(pob[j]);
					else
						pob[i].n++;
				}	
				if(pob[i].n==0)
				{
					pob[i].n=1;
					fronter[0].push_back(pob[i]);
				}
			}

			int g=1;
			while(g<=fronter.size())
			{
				vector<ind> Q;
				for(int i=0;i<fronter.size();i++)
				{
					for( auto q :sols[i])
					{
						q.n--;
						if(q.n=0)
						{
							q.rank=g+1;
							Q.push_back(q);
						}	
					}
				}
				g=g+1;
				fronter[g-1]=Q;
			}

		}
		/*void eval_dist()
		{

		}*/
};






int main()
{

	vector<int> a;
	vector<int> b;
	a.push_back(2);
	b=a;
	cout<<b[0]<<endl;
	return 0;
}