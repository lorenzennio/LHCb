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
  h_massB_sel = new TH1F("h_massB_sel", "", 500, 4750,5750);
  h_massR_K  = new TH1F("h_massR_K", "", 500, 0, 5500);
  h_massR_Pi  = new TH1F("h_massR_Pi", "", 500, 0, 5500);
  h_massR_K_Dmas  = new TH1F("h_massR_K_Dmas", "", 500, 1750, 1950);
  h_massR_K_Bmas  = new TH1F("h_massR_K_Bmas", "", 100, 5200, 5400);
  h_massR_Pi_Jmas  = new TH1F("h_massR_Pi_Jmas", "", 100, 3000, 3200);
  h_massB_sel2 = new TH1F("h_massB_sel2", "", 200, 5050,5650);
  h_massB_p = new TH1F("h_massB_p", "", 200, 5050,5650);
  h_massB_m = new TH1F("h_massB_m", "", 200, 5050,5650);
  h_dalitz_sim = new TH2F("h_dalitz_sim","",100,0,25,100,0,25);
  h_dalitz = new TH2F("h_dalitz","",100,-3,40,100,-3,40);

  
  h_TXTY = new TH2F("h_TXTY","",100,-1,1,100,-1,1);
  // Add all histograms to a vector. This will take care of writing out histograms later on.
  v_Histos.push_back( h_PX );
  v_Histos.push_back( h_PY );
  v_Histos.push_back( h_PZ );
  v_Histos.push_back( h_ProbK);
  v_Histos.push_back( h_ProbPi);
  v_Histos.push_back( h_massB );
  v_Histos.push_back( h_massB_sel );
  v_Histos.push_back( h_massR_K );
  v_Histos.push_back( h_massR_Pi );
  v_Histos.push_back( h_massR_K_Dmas );
  v_Histos.push_back( h_massR_K_Bmas );
  v_Histos.push_back( h_massR_Pi_Jmas );
  v_Histos.push_back( h_massB_sel2 );
  v_Histos.push_back( h_massB_p );
  v_Histos.push_back( h_massB_m );
  v_Histos.push_back( h_dalitz_sim );
  v_Histos.push_back( h_dalitz );
  
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

double invMass(double H1_PX, double H1_PY, double H1_PZ, double H2_PX, double H2_PY, double H2_PZ, double H3_PX, double H3_PY, double H3_PZ, double m1, double m2, double m3){
  double E1 = pow((pow(H1_PX,2) + pow(H1_PY,2) + pow(H1_PZ,2) + pow(m1,2)),(0.5));
  double E2 = pow((pow(H2_PX,2) + pow(H2_PY,2) +pow(H2_PZ,2) + pow(m2,2)),(0.5));
  double E3 = pow((pow(H3_PX,2) + pow(H3_PY,2) +pow(H3_PZ,2) + pow(m3,2)),(0.5));
  double Etot = E1 + E2 + E3;
  double PXtot = H1_PX + H2_PX + H3_PX;
  double PYtot = H1_PY + H2_PY + H3_PY;
  double PZtot = H1_PZ + H2_PZ + H3_PZ;
  double invmass = pow((pow(Etot,2) - (pow(PXtot,2) + pow(PYtot,2) + pow(PZtot,2))),(0.5));
  return invmass;
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

  //5.2 INVARIANT MASS
  double massK = 493.677; // MeV/c2 
  double massPi = 139.570; // MeV/c2
  double massD = 1864.84; // MeV/c2
  double massB = invMass(H1_PX, H1_PY, H1_PZ, H2_PX, H2_PY, H2_PZ, H3_PX, H3_PY, H3_PZ, massK, massK, massK);

  h_massB->Fill(massB);
  
  //5.6 SIMULATION DALITZ
  //if simulation data used:

  double E1sim = pow((pow(H1_PX,2) + pow(H1_PY,2) + pow(H1_PZ,2) + pow(massK,2)),(0.5));
  double E2sim = pow((pow(H2_PX,2) + pow(H2_PY,2) + pow(H2_PZ,2) + pow(massK,2)),(0.5));
  double E3sim = pow((pow(H3_PX,2) + pow(H3_PY,2) + pow(H3_PZ,2) + pow(massK,2)),(0.5));
  double massR_sim1 = pow((pow( E1sim + E2sim ,2) - (pow(H1_PX + H2_PX ,2) + pow(H1_PY + H2_PY,2) + pow(H1_PZ + H2_PZ,2))),(0.5));
  double massR_sim2 = pow((pow( E1sim + E3sim ,2) - (pow(H1_PX + H3_PX ,2) + pow(H1_PY + H3_PY,2) + pow(H1_PZ + H3_PZ,2))),(0.5));
  
  h_dalitz_sim->Fill(pow(massR_sim1/1000, 2), pow(massR_sim2/1000, 2));
  
  //5.3 i FURTHER SELECTION
  double probK[3] = {H1_ProbK, H2_ProbK, H3_ProbK};
  double probPi[3] =  {H1_ProbPi, H2_ProbPi, H3_ProbPi};
  int indK = 0;  //index of highly probable kaon
  for(int i = 1; i < 3; ++i){
    if(probK[i] >= probK[indK]){
      indK = i;
    }
  }
  
  int nPi = 0;
  int indPi [2]; //indeces of highly probable pions
  int k = 0;
  if(probK[indK] >= 0.9){
    for(int i = 0; i < 3; ++i){
      if(i != indK && probPi[i] >= 0.7){
	indPi[k++] = i;
	++nPi;
      }
    }
  } else {
    return;
  }

  if(nPi != 2){
    return;
  }
  
  //check if we have a muon
  if( H1_isMuon == 1 || H2_isMuon == 1 || H3_isMuon == 1){ return;}
  
  //Variable reasignment
  double HK_PX;
  double HK_PY;
  double HK_PZ;
  double HK_Charge;

  double HPi1_PX;
  double HPi1_PY;
  double HPi1_PZ;
  double HPi1_Charge;

  double HPi2_PX;
  double HPi2_PY;
  double HPi2_PZ;
  double HPi2_Charge;

  if(indK == 0){
    HK_PX = H1_PX;
    HK_PY = H1_PY;
    HK_PZ = H1_PZ;
    HK_Charge = H1_Charge;

    HPi1_PX = H2_PX;
    HPi1_PY = H2_PY;
    HPi1_PZ = H2_PZ;
    HPi1_Charge = H2_Charge;

    HPi2_PX = H3_PX;
    HPi2_PY = H3_PY;
    HPi2_PZ = H3_PZ;
    HPi2_Charge = H3_Charge;

  } else if (indK == 1) {
    HK_PX = H2_PX;
    HK_PY = H2_PY;
    HK_PZ = H2_PZ;
    HK_Charge = H2_Charge;

    HPi1_PX = H1_PX;
    HPi1_PY = H1_PY;
    HPi1_PZ = H1_PZ;
    HPi1_Charge = H1_Charge;

    HPi2_PX = H3_PX;
    HPi2_PY = H3_PY;
    HPi2_PZ = H3_PZ;
    HPi2_Charge = H3_Charge;
 
  } else if (indK == 2){
    HK_PX = H3_PX;
    HK_PY = H3_PY;
    HK_PZ = H3_PZ;
    HK_Charge = H3_Charge;

    HPi1_PX = H2_PX;
    HPi1_PY = H2_PY;
    HPi1_PZ = H2_PZ;
    HPi1_Charge = H2_Charge;

    HPi2_PX = H1_PX;
    HPi2_PY = H1_PY;
    HPi2_PZ = H1_PZ;
    HPi2_Charge = H1_Charge;

  } else {
  cout << "FAIL";
  return;
  }

  //check poin charge
  if( HPi1_Charge + HPi2_Charge != 0 ){
    return;
  }
  
  //5.3 ii INVARIANT MASS
  double massB2  = invMass(HK_PX, HK_PY, HK_PZ, HPi1_PX, HPi1_PY, HPi1_PZ, HPi2_PX, HPi2_PY, HPi2_PZ, massK, massPi, massPi);
  double massB_known = 5279.29; //MeV/c2
  

  h_massB_sel->Fill(massB2);


  //5.4 i Two pair resonance
  double massR_K;
  double massR_Pi;

  double E1 = pow((pow(HK_PX,2) + pow(HK_PY,2) + pow(HK_PZ,2) + pow(massK,2)),(0.5));
  double E2 = pow((pow(HPi1_PX,2) + pow(HPi1_PY,2) + pow(HPi1_PZ,2) + pow(massPi,2)),(0.5));
  double E3 = pow((pow(HPi2_PX,2) + pow(HPi2_PY,2) + pow(HPi2_PZ,2) + pow(massPi,2)),(0.5));
  if(HK_Charge + HPi1_Charge == 0){
    massR_K = pow((pow( E1+E2 ,2) - (pow(HK_PX + HPi1_PX ,2) + pow(HK_PY + HPi1_PY,2) + pow(HK_PZ + HPi1_PZ,2))),(0.5));
  } else if (HK_Charge + HPi2_Charge == 0){
    massR_K = pow((pow( E1+E3 ,2) - (pow(HK_PX + HPi2_PX ,2) + pow(HK_PY + HPi2_PY,2) + pow(HK_PZ + HPi2_PZ,2))),(0.5));
  } else {
    return;
  }
  
  massR_Pi = pow((pow( E2+E3 ,2) - (pow(HPi1_PX + HPi2_PX ,2) + pow(HPi1_PY + HPi2_PY,2) + pow(HPi1_PZ + HPi2_PZ,2))),(0.5));
	
  //5.6 Dalitz plots
  h_dalitz->Fill(pow(massR_K/1000, 2), pow(massR_Pi/1000, 2));
  
  //cut D meson
  if( massR_K > massD - 40 &&  massR_K < massD + 40){
    return;
  }
  
  
 //apply cuts +/-60MeV/c2 around b mason mass
  if( massB2 > massB_known - 60 && massB2 < massB_known + 60){
  	h_massR_K->Fill(massR_K);
  	h_massR_Pi->Fill(massR_Pi);
  	
  	h_massR_K_Dmas->Fill(massR_K);
  	h_massR_K_Bmas->Fill(massR_K);
  	
  	h_massR_Pi_Jmas->Fill(massR_Pi);
	
  }
 

  //5.5
   double massB3  = invMass(HK_PX, HK_PY, HK_PZ, HPi1_PX, HPi1_PY, HPi1_PZ, HPi2_PX, HPi2_PY, HPi2_PZ, massK, massPi, massPi);
   h_massB_sel2->Fill(massB3);
   
   
   //MATTER or ANTIMATTER
   
   if(HK_Charge == 1){
	   //matter
	   h_massB_p->Fill(massB3);
   } else if (HK_Charge == -1){
	   //antimatter
	   h_massB_m->Fill(massB3);
   }
   
}

