#include <numeric>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;
//NO!
int main(){
	//global
	//double A[4] = {-0.0313012, -0.0254383, -0.0146673, -0.0144338};
	//double Aerr[4] = {0.0125372, 0.0128256, 0.0120383, 0.0113202};
	//region 1
	//double A[4] = {0.701119, 0.753391, 0.810294, 0.820278};
	//double Aerr[4] = {0.0540506, 0.0426108, 0.040638, 0.0348778};
	//region 2
	double A[4] = {-0.252728, -0.296213, -0.278104, -0.252722};
	//double Aerr[4] = {0.0611534, 0.0717751, 0.0614498, 0.0573224};
	
	double Am = 0;
	for(int i = 0; i < 4; ++i){
		Am += A[i] / 4;
		
	}
	
	double s = 0;
	for(int j = 0; j < 4; ++j){
		s += (1./4.)*pow(A[j]-Am,2);
	}
	double systerr = pow(s, 0.5);
	
	cout << "std: " << systerr << "(syst) \n";
		
	
	
}