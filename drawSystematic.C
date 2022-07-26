#include <numeric>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;


void drawSystematic() {
  double pi = 3.1415926535897932384626433832795028841971693993;
  TFile *ft = new TFile("outputDataMagnetUp.root");
  
  TH2F *UPass_corr 		= (TH2F*)ft->Get("h_dalitz_m");
  TH2F *UPass_err 		= (TH2F*) UPass_corr->Clone();
  TH2F *DOWNass_corr 	        = (TH2F*) UPass_corr->Clone();
  TH2F *DOWNass_err 	        = (TH2F*) UPass_corr->Clone();
  TH2F *UpDownSig 		= (TH2F*) UPass_corr->Clone();
  
  UPass_corr 	->Reset();
  UPass_err 	->Reset();
  DOWNass_corr  ->Reset();
  DOWNass_err   ->Reset();
  UpDownSig 	->Reset();
  
  for(int I = 0; I<2; I++){
  	  cout << "I:" << I << "\n";
  	  if(I==0){
  		ft = new TFile("outputDataMagnetUp.root");
  	  } else if (I == 1){
  	  	ft = new TFile("outputDataMagnetDown.root");
  	  }
  	  
  	//5.5 Fitting
  	// Get pointers to the example histograms that were made 
  	//TOTAL
  	TH1F *hmass_sel2 = (TH1F*)ft->Get("h_massB_sel2");
  	   
  	// Create a canvas onto which the histograms are plotted and which can be saved
  	TCanvas *c10f = new TCanvas("c10f","",600,400);
  	// Draw the first histogram with a blue line, and an x-axis title
  	
  	   
  	//fit
  	   	 
  	TF1 *Signal = new TF1("Signal", "gausn", 5279.29-40 ,5279.29+50);
  	TF1 *Background = new TF1("Background", "expo", 5279.29+80, 5700 );
  	TF1 *CombBG = new TF1("CombBG", "gausn", 5050, 5279.29-80);
  	TF1 *total = new TF1("total","gausn(0) + expo(3) +gausn(5)",5050,5700);
  	
  	   
  	hmass_sel2->Fit(Signal, "RN");
  	hmass_sel2->Fit(Background, "RN+");
  	hmass_sel2->Fit(CombBG, "RN+");
  	
  	Double_t par[8];
  	Signal->GetParameters(&par[0]);
  	Background->GetParameters(&par[3]);
  	CombBG->GetParameters(&par[5]);
  	   
  	total->SetParameters(par);
  	hmass_sel2->Fit(total, "ROME");
  	   	
  	
  	Double_t parfinal[8];
  	total->GetParameters(parfinal);
  	
  	//MATTER---------------------------------------------
  	//p = plus = M
  	TH1F *hmass_p = (TH1F*)ft->Get("h_massB_p");
  	   
  	// Create a canvas onto which the histograms are plotted and which can be saved
  	TCanvas *c11f = new TCanvas("c11f","",600,400);
  	// Draw the first histogram with a blue line, and an x-axis title
  	   
  	//fit
  	   	 
  	TF1 *MSignal = new TF1("MSignal", "gausn", 5279.29-40 ,5279.29+50);
  	TF1 *MBackground = new TF1("MBackground", "expo", 5279.29+80, 5700 );
  	TF1 *MCombBG = new TF1("MCombBG", "gausn", 5050, 5279.29-80);
  	TF1 *Mtotal = new TF1("Mtotal","gausn(0) + expo(3) + gausn(5)",5050,5700);
  	   
  	hmass_p->Fit(MSignal, "RN");
  	hmass_p->Fit(MBackground, "RN+");
  	hmass_p->Fit(MCombBG, "RN+");
  	
  	Double_t Mpar[8];
  	MSignal->GetParameters(&Mpar[0]);
  	MBackground->GetParameters(&Mpar[3]);
  	MCombBG->GetParameters(&Mpar[5]);
  	   
  	Mtotal->SetParameters(Mpar);
  	hmass_p->Fit(Mtotal, "ROME");
  	   	
  	Double_t Mparfinal[8];
  	Mtotal->GetParameters(Mparfinal);
  	
  	//ANTIMATTER
  	//m = minus = A
  	TH1F *hmass_m = (TH1F*)ft->Get("h_massB_m");
  	   
  	// Create a canvas onto which the histograms are plotted and which can be saved
  	TCanvas *c12f = new TCanvas("c12f","",600,400);
  	// Draw the first histogram with a blue line, and an x-axis title
  	
  	//fit
  	   	 
  	TF1 *ASignal = new TF1("ASignal", "gausn", 5279.29-40 ,5279.29+50);
  	TF1 *ABackground = new TF1("ABackground", "expo", 5279.29+80, 5700 );
  	TF1 *ACombBG = new TF1("ACombBG", "gausn", 5050, 5279.29-80);
  	TF1 *Atotal = new TF1("total","gausn(0) + expo(3) + gausn(5)",5050,5700);
  	
  	hmass_m->Fit(ASignal, "RN");
  	hmass_m->Fit(ABackground, "RN+");
  	hmass_m->Fit(ACombBG, "RN+");
  	
  	Double_t Apar[8];
  	ASignal->GetParameters(&Apar[0]);
  	ABackground->GetParameters(&Apar[3]);
  	ACombBG->GetParameters(&Apar[5]);
  	   
  	Atotal->SetParameters(Apar);
  	hmass_m->Fit(Atotal, "ROME");
  	   	
  	Double_t Aparfinal[8];
  	Atotal->GetParameters(Aparfinal);
  	
  	
  	//CP ASSYMETRY
  	double scale = hmass_sel2->GetXaxis()->GetBinWidth(1);
  	double Np = Mparfinal[0]/scale;
  	double Nm = Aparfinal[0]/scale;
  	double A = (Nm-Np)/(Nm+Np);
  	
  	double Aerr = pow(((1-pow(A,2))/(Nm+Np)),0.5);
  	
  	cout << "scale " << scale << "\n";
  	cout << "Mparfinal[0]: " << Mparfinal[0] << "\n";
  	cout << "Mparfinal[2]: " << Mparfinal[2] << "\n";
  	cout << "Aparfinal[0]: " << Aparfinal[0] << "\n";
  	cout << "Aparfinal[2]: " << Aparfinal[2] << "\n";
  	cout << "Np: " << Np << "\n";
  	cout << "Nm: " << Nm << "\n";
  	cout << "\n\n\nCP Assymetry: " << A<< "+/-"<< Aerr <<"\n\n\n";
  	
  	
  	//DALITZ-----------------------------------------------------------------------------
  	const Int_t NRGBs = 5;
  	const Int_t NCont = 255;
  	   
  	Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  	Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  	Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  	Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  	TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  	gStyle->SetNumberContours(NCont);
  	
  	
  	//Dalitz plots for B+ and B-
  	//B+ Dalitz plot with cuts
  	TH2F *hdalitzp = (TH2F*)ft->Get("h_dalitz_p");
  	hdalitzp->Sumw2();
  	TCanvas *c4 = new TCanvas("c4","",600,400);
  	  
  	
  	//B+ background
  	//scaling
  	double Ip_p = ((1./Mparfinal[4]) * exp(Mparfinal[3]) * (exp(Mparfinal[4]*(5.28437e+03 + 40)) - exp(Mparfinal[4]*(5.28437e+03 - 40))))/scale;
  	double Im_p = ((1./Aparfinal[4]) * exp(Aparfinal[3]) * (exp(Aparfinal[4]*(5.28437e+03 + 40)) - exp(Aparfinal[4]*(5.28437e+03 - 40))))/scale;
  	
  	double Ip_b = ((1./Mparfinal[4]) * exp(Mparfinal[3]) * (exp(Mparfinal[4]*5430) - exp(Mparfinal[4]*5350)))/scale;
  	double Im_b = ((1./Aparfinal[4]) * exp(Aparfinal[3]) * (exp(Aparfinal[4]*5430) - exp(Aparfinal[4]*5350)))/scale;
  	
  	double bgscale_p = Ip_p/Ip_b;
  	double bgscale_m = Im_p/Im_b;
  	
  	cout << "bgscale_p: " << bgscale_p << "\n";
  	cout << "bgscale_m: " << bgscale_m << "\n";
  	
  	TH2F *hdalitzbgp = (TH2F*)ft->Get("h_dalitz_bgp");
  	hdalitzbgp->Scale(bgscale_p);
  	
  	hdalitzp->Add(hdalitzbgp, -1);
  	
  	int xbin = 20;
  	int ybin = 20;
  	
  	for(int k = 0; k < xbin; k++){
  		for(int l = 0; l < ybin; l++){
  			if(hdalitzp->GetBinContent(k, l) < 0){
  				hdalitzp->SetBinContent(k, l, 0);
  			}
  		}
  	}
  	
  	
  	//B- Dalitz plot with cuts
  	TH2F *hdalitzm = (TH2F*)ft->Get("h_dalitz_m");
  	hdalitzp->Sumw2();
  	TCanvas *c6 = new TCanvas("c6","",600,400);
  	
  	
  	//B- background
  	TH2F *hdalitzbgm = (TH2F*)ft->Get("h_dalitz_bgm");
  	hdalitzbgm->Scale(bgscale_m);
  	
  	hdalitzm->Add(hdalitzbgm, -1);
  	
  	for(int i = 0; i < xbin; i++){
  		for(int j = 0; j < ybin; j++){
  			if(hdalitzm->GetBinContent(i, j) < 0){
  				hdalitzm->SetBinContent(i, j, 0);
  			}
  		}
  	}
  	
  	//ASSYMETRY
  	TH2F *hdalitzass = (TH2F*) hdalitzm -> GetAsymmetry(hdalitzp);
  	hdalitzass->Sumw2();
	
  	
  	
  	TH2F *ass_err = (TH2F*) hdalitzass->Clone();
  	//double err;
  	for(int a = 0; a < xbin; a++){
  		for(int b = 0; b < ybin; b++){
  			ass_err->SetBinContent(a, b, hdalitzass->GetBinError(a,b));
  		}
  	}
	
  	
  	TH2F *ass_corr = (TH2F*) hdalitzass->Clone();
  	ass_corr->Sumw2();
  	for(int o = 0; o < xbin; o++){
  		for(int p = 0; p < ybin; p++){
  	   		if(ass_err->GetBinContent(o,p) <= 0. || ass_err->GetBinContent(o,p) >= 0.8){
  				ass_corr->SetBinContent(o,p, 0);
  				ass_err->SetBinContent(o,p, 0);
  			}
  		}
  	}
  	
  	for(int r = 0; r < xbin; r++){
  		for(int t = 0; t < ybin; t++){
  	   		if(hdalitzm->GetBinContent(r,t) == 0 || hdalitzp->GetBinContent(r,t) == 0){
  	   			//cout << "a " <<hdalitzass_corr->GetBinContent(r,t)<< "\n";
  				ass_corr->SetBinContent(r,t, 0);
				ass_err->SetBinContent(r,t, 0);
  	   			//cout << "b " <<hdalitzass_corr->GetBinContent(r,t)<< "\n";
  			}
  		}
  	}
  	
  	if(I == 0){
  		UPass_corr->Add(ass_corr);
  		UPass_err->Add(ass_err);
  	} else if (I == 1){
  		DOWNass_corr->Add(ass_corr);
  		DOWNass_err->Add(ass_err);
  	}
  
  }


TCanvas *c1 = new TCanvas("c1","",600,400);
UPass_corr->Sumw2();
UPass_corr->SetStats(0);
UPass_corr->GetXaxis()->SetTitle("Mass_{K#pi}^{2} [GeV^{2}/c^{4}]");
UPass_corr->GetYaxis()->SetTitle("Mass_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
UPass_corr->GetXaxis()->SetRange(-1, 32);
UPass_corr->GetYaxis()->SetRange(-1, 27);
UPass_corr->Draw("colz");                          // draw with a colour scale
c1->SaveAs("UP_ass_corr.pdf");

TCanvas *c2 = new TCanvas("c2","",600,400);
DOWNass_corr->Sumw2();
DOWNass_corr->SetStats(0);
DOWNass_corr->GetXaxis()->SetTitle("Mass_{K#pi}^{2} [GeV^{2}/c^{4}]");
DOWNass_corr->GetYaxis()->SetTitle("Mass_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
DOWNass_corr->GetXaxis()->SetRange(-1, 32);
DOWNass_corr->GetYaxis()->SetRange(-1, 27);
DOWNass_corr->Draw("colz");                          // draw with a colour scale
c2->SaveAs("DOWN_ass_corr.pdf");

TCanvas *c3 = new TCanvas("c3","",600,400);
UPass_err->Sumw2();
UPass_err->SetStats(0);
UPass_err->GetXaxis()->SetTitle("Mass_{K#pi}^{2} [GeV^{2}/c^{4}]");
UPass_err->GetYaxis()->SetTitle("Mass_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
UPass_err->GetXaxis()->SetRange(-1, 32);
UPass_err->GetYaxis()->SetRange(-1, 27);
UPass_err->Draw("colz");                          // draw with a colour scale
c3->SaveAs("UP_ass_err.pdf");

TCanvas *c4 = new TCanvas("c4","",600,400);
DOWNass_err->Sumw2();
DOWNass_err->SetStats(0);
DOWNass_err->GetXaxis()->SetTitle("Mass_{K#pi}^{2} [GeV^{2}/c^{4}]");
DOWNass_err->GetYaxis()->SetTitle("Mass_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
DOWNass_err->GetXaxis()->SetRange(-1, 32);
DOWNass_err->GetYaxis()->SetRange(-1, 27);
DOWNass_err->Draw("colz");                          // draw with a colour scale
c4->SaveAs("DOWN_ass_err.pdf");


UpDownSig->Sumw2();
TCanvas *c5 = new TCanvas("c5","",600,500);
UpDownSig->SetStats(0);
UpDownSig->GetXaxis()->SetTitle("M_{K#pi}^{2} [GeV^{2}/c^{4}]");
UpDownSig->GetXaxis()->SetTitleSize(.05);
UpDownSig->GetXaxis()->SetLabelSize(.05);
UpDownSig->GetYaxis()->SetTitle("M_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
UpDownSig->GetYaxis()->SetTitleSize(.05);
UpDownSig->GetYaxis()->SetLabelSize(.05);
UpDownSig->GetZaxis()->SetTitle("Significance");
UpDownSig->GetZaxis()->SetTitleSize(.05);
UpDownSig->GetZaxis()->SetLabelSize(.05);
UpDownSig->GetXaxis()->SetRange(-1, 32);
UpDownSig->GetYaxis()->SetRange(-1, 27);
for(int q = 0; q < 30; q++){
	for(int w = 0; w < 30; w++){
		if(UPass_err->GetBinContent(q,w) > 0 && DOWNass_err->GetBinContent(q,w) > 0){
			UpDownSig->SetBinContent(q,w, (DOWNass_corr->GetBinContent(q,w) - UPass_corr->GetBinContent(q,w))/sqrt(pow(UPass_err->GetBinContent(q,w),2) + pow(DOWNass_err->GetBinContent(q,w),2)));
		}
	}
}

UpDownSig->SetMaximum(3);
UpDownSig->SetMinimum(-3);
int xbin = 20;
int ybin = 20;
for(int r = 0; r < xbin; r++){
      for(int t = 0; t < ybin; t++){
	      if(UPass_corr->GetBinContent(r,t) == 0 || DOWNass_corr->GetBinContent(r,t) == 0){
		      //cout << "a " <<UPass_corr->GetBinContent(r,t)<< "\n";
  		      UpDownSig->SetBinContent(r,t, -5);
		      //cout << "b " <<DOWNass_corr->GetBinContent(r,t)<< "\n";
  	      }
      }
}


 
UpDownSig->Draw("colz");                          // draw with a colour scale
c5->SaveAs("UpDown_sig.pdf");

TH1F *sign =  new TH1F("sign","",20,-3,3);

for(int i = 0; i < 30; i++){
	for(int j = 0; j < 30; j++){
		if(UpDownSig->GetBinContent(i,j) != 0){
			sign->Fill(UpDownSig->GetBinContent(i,j));
		}
	}
}
TCanvas *c6 = new TCanvas("c6","",600,500);
// Draw the first histogram with a blue line, and an x-axis title
gStyle->SetOptStat("e");
gStyle->SetOptFit(1111);
gStyle->SetStatFormat("6.6g");
sign->SetLineColor(kBlack);
sign->GetXaxis()->SetTitle("Significance");
sign->GetXaxis()->SetTitleSize(.05);
sign->GetXaxis()->SetLabelSize(.05);
sign->GetYaxis()->SetTitle("Bin Count");
sign->GetYaxis()->SetTitleSize(.05);
sign->GetYaxis()->SetLabelSize(.05);

TF1 *bellc = new TF1("bellc", "gausn", -3, 3);
sign->Fit(bellc, "ROME");



sign->Draw("E1");
c6->SaveAs("UpDownsig1D.pdf");
}
