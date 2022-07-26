#define MyAnalysis_cxx
#include "MyAnalysis.h"

#include <numeric>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

void MyAnalysis::BookHistos() {
  // This function is only called once at the start of the program.
  // Book your histograms here. The format is object_name, histogram_name, number_of_bins, minimum, maximum
  // For a 2D histogram, use TH2F with first the number of bins and limits for the x axis and then for the y axis
  h_PX = new TH1F("h_PX","",100,-1e4,1e4);
  h_PY = new TH1F("h_PY","",100,-1e4,1e4);
  h_PZ = new TH1F("h_PZ","",100,-1e5,1e5);
  h_ProbK = new TH1F("h_ProbK","",100,0,1);
  h_ProbPi = new TH1F("h_ProbPi","",100,0,1);
  h_massB = new TH1F("h_massB", "", 500, 5279,5279.5);
  h_TXTY = new TH2F("h_TXTY","",100,-1,1,100,-1,1);
  // Add all histograms to a vector. This will take care of writing out histograms later on.
  v_Histos.push_back( h_PX );
  v_Histos.push_back( h_PY );
  v_Histos.push_back( h_PZ );
  v_Histos.push_back( h_ProbK);
  v_Histos.push_back( h_ProbPi);
  v_Histos.push_back( h_massB );
  v_Histos.push_back( h_TXTY );
}

Bool_t MyAnalysis::Cut() {
  // This function is called for every event from the Execute function to define whether or not to accept this event.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  // This example checks if the PZ component of particle 3 is greater than 0. 
  if ( H3_PZ < 0 ) return false;
  return true;
}

void MyAnalysis::Execute() {
  // This method gets called on every event.
  // In this example the momentum components are filled into histograms.

  // Call the Cut function to decide whether to plot this event or not
  // it returns if the cut function returns false
  if ( !Cut() ) return;

  // Fill your histograms below.
  // fill the momentum of all three particles 
  h_PX->Fill( H1_PX );
  h_PX->Fill( H2_PX );
  h_PX->Fill( H3_PX );
  // the PY of all three particles
  h_PY->Fill( H1_PY );
  h_PY->Fill( H2_PY );
  h_PY->Fill( H3_PY );
  // the PZ of all three particles
  h_PZ->Fill( H1_PZ );
  h_PZ->Fill( H2_PZ );
  h_PZ->Fill( H3_PZ );
  // Fill the K  probabilities
  h_ProbK->Fill( H1_ProbK );
  h_ProbK->Fill( H2_ProbK );
  h_ProbK->Fill( H3_ProbK );
  // Fill the Pi  probabilities
  h_ProbPi->Fill( H1_ProbPi);
  h_ProbPi->Fill( H2_ProbPi);
  h_ProbPi->Fill( H3_ProbPi);
  // 2D histogram of PX/PZ vs PY/PZ
  h_TXTY->Fill( H1_PX / H1_PZ, H1_PY / H1_PZ );

  //INVARIANT MASS
  double massK = 493.677; // MeV/c2 
  double E1 = pow((pow(H1_PX,2) + pow(H1_PY,2) + pow(H1_PZ,2) + pow(massK,2)),(0.5));
  double E2 = pow((pow(H2_PX,2) + pow(H2_PY,2) +pow(H2_PZ,2) + pow(massK,2)),(0.5));
  double E3 = pow((pow(H3_PX,2) + pow(H3_PY,2) +pow(H3_PZ,2) + pow(massK,2)),(0.5));
  double Etot = E1 + E2 + E3;
  double PXtot = H1_PX + H2_PX + H3_PX;
  double PYtot = H1_PY + H2_PY + H3_PY;
  double PZtot = H1_PZ + H2_PZ + H3_PZ;
  double massB = pow((pow(Etot,2) - (pow(PXtot,2) + pow(PYtot,2) + pow(PZtot,2))),(0.5));

  h_massB->Fill(massB);

  //FURTHER SELECTION
  double probK[3] = {H1_ProbK, H2_ProbK, H3_ProbK};
  double probPi[3] =  {H1_ProbPi, H2_ProbPi, H3_ProbPi};
  int indK = 0;
  bool keep = False;

  for(int i = 1; i < 3; ++i){
    if(probK[i] >= probK[indK]){
      indK = i;
    }
  }
  
  int nPi = 0;
  if(probK[indK] >= 0.9){
    for(int i = 0; i < 3; ++i){
      if(i =! indK && probPi[i] >= 0.7){
	++nPi;
      }
  } 
  else{
    return;
  }
  
  if(nPi =! 2){
    return;
  }

}

