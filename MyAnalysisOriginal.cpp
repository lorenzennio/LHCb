#define MyAnalysis_cxx
#include "MyAnalysis.h"

void MyAnalysis::BookHistos() {
  // This function is only called once at the start of the program.
  // Book your histograms here. The format is object_name, histogram_name, number_of_bins, minimum, maximum
  // For a 2D histogram, use TH2F with first the number of bins and limits for the x axis and then for the y axis
  h_PX = new TH1F("h_PX","",100,-1e4,1e4);
  h_PY = new TH1F("h_PY","",100,-1e4,1e4);
  h_PZ = new TH1F("h_PZ","",100,-1e5,1e5);
  h_TXTY = new TH2F("h_TXTY","",100,-1,1,100,-1,1);
  // Add all histograms to a vector. This will take care of writing out histograms later on.
  v_Histos.push_back( h_PX );
  v_Histos.push_back( h_PY );
  v_Histos.push_back( h_PZ );
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
  // 2D histogram of PX/PZ vs PY/PZ
  h_TXTY->Fill( H1_PX / H1_PZ, H1_PY / H1_PZ );
}
