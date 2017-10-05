#include <numeric>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

void drawDalitz() {
	TFile *f = new TFile("outputPhaseSpace.root");
	TFile *ft = new TFile("outputDataAll.root");
	
	//Dalitz plots for simulation
	TH2F *hdalitz_sim = (TH2F*)f->Get("h_dalitz_sim");
    TCanvas *c1 = new TCanvas("c1","",600,400);
    hdalitz_sim->SetStats(0);
    hdalitz_sim->GetXaxis()->SetTitle("Mass_{K#pi}^{2} [GeV^{2}/c^{4}]");
    hdalitz_sim->GetYaxis()->SetTitle("Mass_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
    hdalitz_sim->Draw("colz");                          // draw with a colour scale
    c1->SaveAs("dalitz_sim.pdf");
	
	
	//Dalitz plots
	TH2F *hdalitz = (TH2F*)ft->Get("h_dalitz");
    TCanvas *c2 = new TCanvas("c2","",600,400);
    hdalitz->SetStats(0);
    hdalitz->GetXaxis()->SetTitle("Mass_{K#pi}^{2} [GeV^{2}/c^{4}]");
    hdalitz->GetYaxis()->SetTitle("Mass_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
    hdalitz->Draw("colz");                          // draw with a colour scale
    c2->SaveAs("dalitz.pdf");
}
