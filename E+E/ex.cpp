#include "decimal.h"
#include <iostream>
#include <cmath>
using namespace dec;
using namespace std;



typedef decimal<15> BIGDECIMAL; 

typedef struct {
	//vector<double> val,varianza;
	BIGDECIMAL fit;
	double porcent=0;
}individuo;


int main()
{
// the following declares currency variable with 2 decimal points
// initialized with integer value (can be also floating-point)
/*decimal<6> value(143125);

// displays: Value #1 is: 143125.00
cout << "Value #1 is: " << value << endl;

// declare precise value with digits after decimal point
decimal<6> b("0.11");

// perform calculations as with any other numeric type
value += b;

// displays: Value #2 is: 143125.11
cout << "Value #2 is: " << value << endl;

// automatic rounding performed here
value /= 1000;

// displays: Value #3 is: 143.13
cout << "Value #3 is: " << value << endl;

// integer multiplication and division can be used directly in expression
// displays: Value: 143.13 * 2 is: 286.26
cout << "Value: " << value << " * 2 is: " << (value * 2) << endl;

// to use non-integer constants in expressions you need to use decimal_cast
value = value * decimal_cast<2>("3.33") / decimal_cast<2>(333.0);

// displays: Value #4 is: 1.43
cout << "Value #4 is: " << value << endl;

// to mix decimals with different precision use decimal_cast
// it will round result automatically
decimal<6> exchangeRate(12.1234);
value = decimal_cast<6>(decimal_cast<6>(value) * exchangeRate);

// displays: Value #5 is: 17.34
cout << "Value #5 is: " << value << endl;
	*/
;
	double pi = 1.0;
	double c= 3.0;
	decimal<18> r(exp(2));
	double d = pi/c;
	cout<<r<<endl;
	cout<<std::setprecision(32)<<exp(2)<<endl;
	cout<<decimal_cast<15>(exp(2))<<endl;
	//cout<<decimal_cast<18>(r)<<endl;
	return 0;

}