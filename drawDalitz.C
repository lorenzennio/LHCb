#include <numeric>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

void drawDalitz() {
	TFile *f = new TFile("outputPhaseSpace.root");
	TFile *ft = new TFile("outputDataAll.root");
	
	gStyle->SetPalette(1);
	
	//Dalitz plot for simulation
	TH2F *hdalitz_sim = (TH2F*)f->Get("h_dalitz_sim");
    TCanvas *c1 = new TCanvas("c1","",600,400);
    hdalitz_sim->SetStats(0);
    hdalitz_sim->GetXaxis()->SetTitle("Mass_{K_{1} K_{2} high}^{2} [GeV^{2}/c^{4}]");
    hdalitz_sim->GetYaxis()->SetTitle("Mass_{K_{1} K_{3} low}^{2} [GeV^{2}/c^{4}]");
    hdalitz_sim->Draw("colz");                          // draw with a colour scale
    c1->SaveAs("dalitz_sim.pdf");
	
	
	//Dalitz plot for complete data
	//variable bin width
	const Int_t xNBINS = 20;
   	Double_t xedges[xNBINS + 1] = {0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3., 3.5, 4., 5., 6., 7., 8., 10., 12., 15., 18., 21., 25., 30., 35.};
	const Int_t yNBINS = 20;
   	Double_t yedges[yNBINS + 1] = {0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3., 3.5, 4., 5., 6., 7., 8., 10., 12., 15., 18., 21., 25., 30., 35.};
   	// Bin 1 corresponds to range [0.0, 0.2]
   	// Bin 2 corresponds to range [0.2, 0.3] etc...
	
	
	TH2F *hdalitz = (TH2F*)ft->Get("h_dalitz");
    TCanvas *c2 = new TCanvas("c2","",600,400);
    hdalitz->SetStats(0);
    hdalitz->GetXaxis()->SetTitle("Mass_{K#pi}^{2} [GeV^{2}/c^{4}]");
	hdalitz->GetXaxis()->SetRange(-3, 40);
    hdalitz->GetYaxis()->SetTitle("Mass_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
	hdalitz->GetYaxis()->SetRange(-3, 40);
    hdalitz->Draw("colz");                          // draw with a colour scale
    c2->SaveAs("dalitz.pdf");
	
	//Dalitz plot with cuts
	TH2F *hdalitzcut = (TH2F*)ft->Get("h_dalitz_cut");
    TCanvas *c3 = new TCanvas("c3","",600,400);
    hdalitzcut->SetStats(0);
    hdalitzcut->GetXaxis()->SetTitle("Mass_{K#pi}^{2} [GeV^{2}/c^{4}]");
    hdalitzcut->GetYaxis()->SetTitle("Mass_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
    hdalitzcut->Draw("colz");                          // draw with a colour scale
    c3->SaveAs("dalitz_cut.pdf");
	
	//Dalitz plots for B+ and B-
	//B+ Dalitz plot with cuts
	TH2F *hdalitzp = (TH2F*)ft->Get("h_dalitz_p");
	hdalitzp->Sumw2();
    TCanvas *c4 = new TCanvas("c4","",600,400);
    hdalitzp->SetStats(0);
    hdalitzp->GetXaxis()->SetTitle("Mass_{K#pi}^{2} [GeV^{2}/c^{4}]");
    hdalitzp->GetYaxis()->SetTitle("Mass_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
    
	
	//B+ background
	TH2F *hdalitzbgp = (TH2F*)ft->Get("h_dalitz_bgp");
    //TCanvas *c5 = new TCanvas("c5","",600,400);
    //hdalitzbgp->SetStats(0);
    //hdalitzbgp->GetXaxis()->SetTitle("Mass_{K#pi}^{2} [GeV^{2}/c^{4}]");
    //hdalitzbgp->GetYaxis()->SetTitle("Mass_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
    //hdalitzbgp->Draw("colz");                          // draw with a colour scale
    //c5->SaveAs("dalitz_bgp.pdf");
	
	hdalitzp->Add(hdalitzbgp, -1);
	
	int bin = 40;
	
	for(int k = 0; k < bin; k++){
		for(int l = 0; l < bin; l++){
			if(hdalitzp->GetBinContent(k, l) < 0){
				hdalitzp->SetBinContent(k, l, 0);
			}
		}
	}
	
    hdalitzp->Draw("colz");                          // draw with a colour scale
    c4->SaveAs("dalitz_p.pdf");
	
	
	//B- Dalitz plot with cuts
	TH2F *hdalitzm = (TH2F*)ft->Get("h_dalitz_m");
	hdalitzp->Sumw2();
    TCanvas *c6 = new TCanvas("c6","",600,400);
    hdalitzm->SetStats(0);
    hdalitzm->GetXaxis()->SetTitle("Mass_{K#pi}^{2} [GeV^{2}/c^{4}]");
    hdalitzm->GetYaxis()->SetTitle("Mass_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
	
	//B- background
	TH2F *hdalitzbgm = (TH2F*)ft->Get("h_dalitz_bgm");
    //TCanvas *c7 = new TCanvas("c7","",600,400);
    //hdalitzbgm->SetStats(0);
    //hdalitzbgm->GetXaxis()->SetTitle("Mass_{K#pi}^{2} [GeV^{2}/c^{4}]");
    //hdalitzbgm->GetYaxis()->SetTitle("Mass_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
    //hdalitzbgm->Draw("colz");                          // draw with a colour scale
    //c7->SaveAs("dalitz_bgm.pdf");
	
	hdalitzm->Add(hdalitzbgm, -1);
	
	for(int i = 0; i < bin; i++){
		for(int j = 0; j < bin; j++){
			if(hdalitzm->GetBinContent(i, j) < 0){
				hdalitzm->SetBinContent(i, j, 0);
			}
		}
	}
	
    hdalitzm->Draw("colz");                          // draw with a colour scale
    c6->SaveAs("dalitz_m.pdf");
	
	
	//subtracted
	TH2F *hdalitzsub = new TH2F(*hdalitzm);
	hdalitzsub->Sumw2();
	hdalitzsub-> Add(hdalitzp, -1);
    TCanvas *c8 = new TCanvas("c8","",600,400);
    hdalitzsub->SetStats(0);
    hdalitzsub->GetXaxis()->SetTitle("Mass_{K#pi}^{2} [GeV^{2}/c^{4}]");
    hdalitzsub->GetYaxis()->SetTitle("Mass_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
    hdalitzsub->Draw("colz");                          // draw with a colour scale
    c8->SaveAs("dalitz_sub.pdf");
	
	//added
	TH2F *hdalitzadd = new TH2F(*hdalitzm);
	hdalitzadd->Sumw2();
	hdalitzadd-> Add(hdalitzp);
    TCanvas *c9 = new TCanvas("c9","",600,400);
    hdalitzadd->SetStats(0);
    hdalitzadd->GetXaxis()->SetTitle("Mass_{K#pi}^{2} [GeV^{2}/c^{4}]");
    hdalitzadd->GetYaxis()->SetTitle("Mass_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
    hdalitzadd->Draw("colz");                          // draw with a colour scale
    c9->SaveAs("dalitz_add.pdf");
	
	//assymetry
	TH2F *hdalitzass2 = new TH2F(*hdalitzsub);
	hdalitzass2->Sumw2();
	hdalitzass2->Divide(hdalitzadd);
    TCanvas *c10 = new TCanvas("c10","",600,400);
    hdalitzass2->SetStats(0);
    hdalitzass2->GetXaxis()->SetTitle("Mass_{K#pi}^{2} [GeV^{2}/c^{4}]");
    hdalitzass2->GetYaxis()->SetTitle("Mass_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
    hdalitzass2->Draw("colz");                          // draw with a colour scale
    c10->SaveAs("dalitz_ass2.pdf");
	
	
	
	//ASSYMETRY
	TH2F *hdalitzass = (TH2F*) hdalitzm -> GetAsymmetry(hdalitzp);
	hdalitzass->Sumw2();
    TCanvas *c11 = new TCanvas("c11","",600,400);
    hdalitzass->SetStats(0);
    hdalitzass->GetXaxis()->SetTitle("Mass_{K#pi}^{2} [GeV^{2}/c^{4}]");
    hdalitzass->GetYaxis()->SetTitle("Mass_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
    hdalitzass->Draw("colz");                          // draw with a colour scale
    c11->SaveAs("dalitz_ass.pdf");
	
	TH2F *hdalitzass_err = (TH2F*) hdalitzass->Clone();
	hdalitzass->Sumw2();
	
	double err;
	for(int a = 0; a < bin; a++){
		for(int b = 0; b < bin; b++){
			err = pow((1-pow(hdalitzass->GetBinContent(a,b), 2)) / hdalitzadd->GetBinContent(a,b), 0.5);
			hdalitzass_err->SetBinContent(a, b, err);
		}
	}
	
    TCanvas *c12 = new TCanvas("c12","",600,400);
    hdalitzass_err->SetStats(0);
	//hdalitzass_err->SetTitle();
    hdalitzass_err->GetXaxis()->SetTitle("Mass_{K#pi}^{2} [GeV^{2}/c^{4}]");
    hdalitzass_err->GetYaxis()->SetTitle("Mass_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
    hdalitzass_err->Draw("colz");                          // draw with a colour scale
    c12->SaveAs("dalitz_ass_err.pdf");
	
	
	TH2F *hdalitzsig = (TH2F*) hdalitzass->Clone();
	hdalitzsig->Sumw2();
	hdalitzsig->Divide(hdalitzass_err);
    TCanvas *c13 = new TCanvas("c13","",600,400);
    hdalitzsig->SetStats(0);
    hdalitzsig->GetXaxis()->SetTitle("Mass_{K#pi}^{2} [GeV^{2}/c^{4}]");
    hdalitzsig->GetYaxis()->SetTitle("Mass_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
    hdalitzsig->Draw("colz");                          // draw with a colour scale
    c13->SaveAs("dalitz_sig.pdf");
	
	
	TH2F *hdalitzass_corr = (TH2F*) hdalitzass->Clone();
	hdalitzass_corr->Sumw2();
	for(int o = 0; o < bin; o++){
		for(int p = 0; p < bin; p++){
			if(abs(hdalitzsig->GetBinContent(o,p)) < 1.){
				hdalitzass_corr->SetBinContent(o,p, 0);
			}
		}
	}
    TCanvas *c14 = new TCanvas("c14","",600,400);
    hdalitzass_corr->SetStats(0);
    hdalitzass_corr->GetXaxis()->SetTitle("Mass_{K#pi}^{2} [GeV^{2}/c^{4}]");
    hdalitzass_corr->GetYaxis()->SetTitle("Mass_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
    hdalitzass_corr->Draw("colz");                          // draw with a colour scale
    c14->SaveAs("dalitz_ass_corr.pdf");
	
}
