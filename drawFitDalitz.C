#include <numeric>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

void drawFitDalitz() {
  TFile *f = new TFile("outputPhaseSpace.root");
  TFile *ft = new TFile("outputDataAll.root");
  
  //5.5 Fitting
  // Get pointers to the example histograms that were made 
  //TOTAL
  TH1F *hmass_sel2 = (TH1F*)ft->Get("h_massB_sel2");

  // Create a canvas onto which the histograms are plotted and which can be saved
  TCanvas *c10f = new TCanvas("c10f","",600,400);
  // Draw the first histogram with a blue line, and an x-axis title
  gStyle->SetOptStat("e");
  gStyle->SetOptFit(1111);
  gStyle->SetStatFormat("6.6g");
  
  hmass_sel2->SetLineColor(kBlue);
  hmass_sel2->GetXaxis()->SetTitle("Mass [MeV/c^{2}]");
  

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
  total->SetParNames("Signal G C", "Signal G M", "Signal G #sigma", "BG E C", "BG E M", "Comb BG G C", "Comb BG G M", "Comb BG G #sigma");
  
  
  TF1 *DrawSignal = new TF1("DrawSignal", "gausn", 5050 ,5700);
  TF1 *DrawBackground = new TF1("DrawBackground", "expo", 5050 ,5700);
  TF1 *DrawCombBG = new TF1("DrawCombBG", "gausn", 5050 ,5700);
  DrawSignal->SetParameters(&parfinal[0]);
  DrawBackground->SetParameters(&parfinal[3]);
  DrawCombBG->SetParameters(&parfinal[5]);
  
  TH1F *subtracted = (TH1F*)hmass_sel2->Clone("subtracted"); //new TH1F(*hmass_sel2);
  subtracted->Add(DrawBackground, -1);
  subtracted->Add(DrawCombBG, -1);
  
  //subtracted->Fit(DrawSignal, "ROME");
  //gStyle->SetOptFit(1111);
  
  hmass_sel2->Draw("E1");
  hmass_sel2->SetAxisRange(-50., 1200., "Y");
  
  total->Draw("same");
  total->SetLineStyle(3);
  total->SetLineColor(2);
  total->SetLineWidth(2);
  
  DrawSignal->Draw("same");
  DrawSignal->SetLineColor(8);
  DrawSignal->SetLineWidth(2);
	  
  DrawBackground->Draw("same");
  DrawBackground->SetLineColor(6);
  DrawBackground->SetLineWidth(1);
  
  DrawCombBG->Draw("same");
  DrawCombBG->SetLineColor(38);
  DrawCombBG->SetLineWidth(1);
  
  //subtracted->Draw("same");
  //subtracted->SetLineColor(9);
  
 
  c10f->SaveAs("massB_sel2.pdf");
  
	//Gets integral of function between fit limits
   	//printf("Integral of function = %g\n",func->Integral(-2,2));
  
  
  
  //MATTER---------------------------------------------
  //p = plus = M
  TH1F *hmass_p = (TH1F*)ft->Get("h_massB_p");

  // Create a canvas onto which the histograms are plotted and which can be saved
  TCanvas *c11f = new TCanvas("c11f","",600,500);
  // Draw the first histogram with a blue line, and an x-axis title
  gStyle->SetOptStat("e");
  gStyle->SetOptFit(1111);
  gStyle->SetStatFormat("6.6g");
  
  hmass_p->SetLineColor(kBlue);
  hmass_p->GetXaxis()->SetTitle("Invariant Mass [MeV/c^{2}]");
  hmass_p->GetXaxis()->SetTitleSize(.05);
  hmass_p->GetXaxis()->SetLabelSize(.05);
  hmass_p->GetYaxis()->SetTitle("Events/Bin");
  hmass_p->GetYaxis()->SetTitleSize(.05);
  hmass_p->GetYaxis()->SetLabelSize(.05);
  

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
  hmass_p->Fit(Mtotal, "ROMEN");
	
  
  Double_t Mparfinal[8];
  Mtotal->GetParameters(Mparfinal);
  
  Mtotal->SetParNames("Signal G C", "Signal G M", "Signal G #sigma", "BG E C", "BG E M", "Comb BG G C", "Comb BG G M", "Comb BG G #sigma");
	  
  
  TF1 *MDrawSignal = new TF1("MDrawSignal", "gausn", 5050 ,5700);
  TF1 *MDrawBackground = new TF1("MDrawBackground", "expo", 5050 ,5700);
  TF1 *MDrawCombBG = new TF1("MDrawCombBG", "gausn", 5050 ,5700);
  MDrawSignal->SetParameters(&Mparfinal[0]);
  MDrawBackground->SetParameters(&Mparfinal[3]);
  MDrawCombBG->SetParameters(&Mparfinal[5]);
  
  TH1F *Msubtracted = new TH1F(*hmass_p);
  Msubtracted->Add(MDrawBackground, -1);
  Msubtracted->Add(MDrawCombBG, -1);
  
  hmass_p->Draw("E1");
  hmass_p->SetAxisRange(-5., 620., "Y");
  hmass_p->SetAxisRange(5050, 5500, "X");
  hmass_p->GetXaxis()->SetNdivisions(506);
  hmass_p->SetLineColor(kBlack);
  
  Mtotal->Draw("same");
  Mtotal->SetLineColor(kBlue);
  Mtotal->SetLineWidth(2);
  //Mtotal->SetLineStyle(9);
  
  MDrawSignal->Draw("same");
  MDrawSignal->SetLineColor(kMagenta+1);
  MDrawSignal->SetLineWidth(2);
  //MDrawSignal->SetLineStyle(7);
   
  MDrawBackground->Draw("same");
  MDrawBackground->SetLineColor(kGreen+3);
  MDrawBackground->SetLineWidth(2);
  MDrawBackground->SetLineStyle(9);
  
  MDrawCombBG->Draw("same");
  MDrawCombBG->SetLineColor(38);
  MDrawCombBG->SetLineWidth(2);
  MDrawCombBG->SetLineStyle(7);
  
  //Msubtracted->Draw("same");
  
  auto legend1 = new TLegend(0.6,0.7,0.95,0.95);
  legend1->AddEntry(Mtotal,"Total","l");
  legend1->AddEntry(MDrawSignal,"Signal","l");
  legend1->AddEntry(MDrawBackground,"Combinatorial","l");
  legend1->AddEntry(MDrawCombBG,"4-body","l");
  legend1->Draw();
  
 
  c11f->SaveAs("massB_matter.pdf");
  
  
  //ANTIMATTER
  //m = minus = A
  TH1F *hmass_m = (TH1F*)ft->Get("h_massB_m");

  // Create a canvas onto which the histograms are plotted and which can be saved
  TCanvas *c12f = new TCanvas("c12f","",600,500);
  // Draw the first histogram with a blue line, and an x-axis title
  gStyle->SetOptStat("e");
  gStyle->SetOptFit(1111);
  gStyle->SetStatFormat("6.6g");
  
  hmass_m->SetLineColor(kBlue);
  hmass_m->GetXaxis()->SetTitle("Invariant Mass [MeV/c^{2}]");
  hmass_m->GetXaxis()->SetTitleSize(.05);
  hmass_m->GetXaxis()->SetLabelSize(.05);
  hmass_m->GetYaxis()->SetTitle("Events/Bin");
  hmass_m->GetYaxis()->SetTitleSize(.05);
  hmass_m->GetYaxis()->SetLabelSize(.05);
  

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
  
  Atotal->SetParNames("Signal G C", "Signal G M", "Signal G #sigma", "BG E C", "BG E M", "Comb BG G C", "Comb BG G M", "Comb BG G #sigma");
	  
  
  TF1 *ADrawSignal = new TF1("ADrawSignal", "gausn", 5050 ,5700);
  TF1 *ADrawBackground = new TF1("ADrawBackground", "expo", 5050 ,5700);
  TF1 *ADrawCombBG = new TF1("ADrawCombBG", "gausn", 5050 ,5700);
  ADrawSignal->SetParameters(&Aparfinal[0]);
  ADrawBackground->SetParameters(&Aparfinal[3]);
  ADrawCombBG->SetParameters(&Aparfinal[5]);
  
  TH1F *Asubtracted = new TH1F(*hmass_m);
  Asubtracted->Add(ADrawBackground, -1);
  Asubtracted->Add(ADrawCombBG, -1);
  
  hmass_m->Draw("E1");
  hmass_m->SetAxisRange(-5., 620., "Y");
  hmass_m->SetAxisRange(5050, 5500, "X");
  hmass_m->GetXaxis()->SetNdivisions(506);
  hmass_m->SetLineColor(kBlack);
  
  Atotal->Draw("same");
  Atotal->SetLineColor(kBlue);
  Atotal->SetLineWidth(2);
  //Mtotal->SetLineStyle(9);
  
  ADrawSignal->Draw("same");
  ADrawSignal->SetLineColor(kMagenta+1);
  ADrawSignal->SetLineWidth(2);
  //MDrawSignal->SetLineStyle(7);
   
  ADrawBackground->Draw("same");
  ADrawBackground->SetLineColor(kGreen+3);
  ADrawBackground->SetLineWidth(2);
  ADrawBackground->SetLineStyle(9);
  
  ADrawCombBG->Draw("same");
  ADrawCombBG->SetLineColor(38);
  ADrawCombBG->SetLineWidth(2);
  ADrawCombBG->SetLineStyle(7);
  
  //Msubtracted->Draw("same");
  
  auto legend2 = new TLegend(0.6,0.7,0.95,0.95);
  legend2->AddEntry(Mtotal,"Total","l");
  legend2->AddEntry(MDrawSignal,"Signal","l");
  legend2->AddEntry(ADrawBackground,"Combinatorial","l");
  legend2->AddEntry(MDrawCombBG,"4-body","l");
  legend2->Draw();
 
  c12f->SaveAs("massB_antimatter.pdf");
  
  //CP ASSYMETRY
  double scale = hmass_sel2->GetXaxis()->GetBinWidth(1);
  double pi = 3.1415926535897932384626433832795028841971693993;
  double Np = Mparfinal[0]/scale;
  double Nm = Aparfinal[0]/scale;
  double A = (Nm-Np)/(Nm+Np);
  
  double Aerr = pow(((1-pow(A,2))/(Nm+Np)),0.5);
  double Aerr2 = (2/pow(Np+Nm, 2))*pow((pow(Np*Atotal->GetParError(0)/scale,2) + pow(Nm*Mtotal->GetParError(0)/scale,2)), 0.5);
  
  cout << "scale " << scale << "\n";
  cout << "Mparfinal[0]: " << Mparfinal[0] << "\n";
  cout << "Mparfinal[2]: " << Mparfinal[2] << "\n";
  cout << "Aparfinal[0]: " << Aparfinal[0] << "\n";
  cout << "Aparfinal[2]: " << Aparfinal[2] << "\n";
  cout << "Np: " << Np << "\n";
  cout << "Nm: " << Nm << "\n";
  cout << "\n\n\nCP Assymetry: " << A<< "+/-"<< Aerr <<"+/-"<< Aerr2 <<"\n\n\n";
  
  
  //DALITZ-----------------------------------------------------------------------------
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;

  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);
  
  //Dalitz plot for simulation
  TH2F *hdalitz_sim = (TH2F*)f->Get("h_dalitz_sim");
  TCanvas *c1 = new TCanvas("c1","",600,400);
  hdalitz_sim->SetStats(0);
  hdalitz_sim->GetXaxis()->SetTitle("Mass_{K_{1} K_{2} high}^{2} [GeV^{2}/c^{4}]");
  hdalitz_sim->GetYaxis()->SetTitle("Mass_{K_{1} K_{3} low}^{2} [GeV^{2}/c^{4}]");
  hdalitz_sim->Draw("colz");                          // draw with a colour scale
  c1->SaveAs("dalitz_sim.pdf");
  
  
  //Dalitz plot for complete data
  
  TH2F *hdalitz = (TH2F*)ft->Get("h_dalitz");
  TCanvas *c2 = new TCanvas("c2","",600,500);
  hdalitz->SetStats(0);
  hdalitz->GetXaxis()->SetTitle("M_{K#pi}^{2} [GeV^{2}/c^{4}]");
  hdalitz->GetXaxis()->SetTitleSize(.05);
  hdalitz->GetXaxis()->SetLabelSize(.05);
  hdalitz->GetYaxis()->SetTitle("M_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
  hdalitz->GetYaxis()->SetTitleSize(.05);
  hdalitz->GetYaxis()->SetLabelSize(.05);
  hdalitz->GetZaxis()->SetLabelSize(.05);
  hdalitz->GetXaxis()->SetRange(-3, 35);
  hdalitz->GetYaxis()->SetRange(-3, 35);
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
  hdalitzp->GetXaxis()->SetRange(-1, 32);
  hdalitzp->GetYaxis()->SetRange(-1, 27);
    
  
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
  //TCanvas *c5 = new TCanvas("c5","",600,400);
  //hdalitzbgp->SetStats(0);
  //hdalitzbgp->GetXaxis()->SetTitle("Mass_{K#pi}^{2} [GeV^{2}/c^{4}]");
  //hdalitzbgp->GetYaxis()->SetTitle("Mass_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
  //hdalitzbgp->Draw("colz");                          // draw with a colour scale
  //c5->SaveAs("dalitz_bgp.pdf");
  
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
  
  hdalitzp->Draw("colz");                          // draw with a colour scale
  c4->SaveAs("dalitz_p.pdf");
  
  
  //B- Dalitz plot with cuts
  TH2F *hdalitzm = (TH2F*)ft->Get("h_dalitz_m");
  hdalitzp->Sumw2();
  TCanvas *c6 = new TCanvas("c6","",600,400);
  hdalitzm->SetStats(0);
  hdalitzm->GetXaxis()->SetTitle("Mass_{K#pi}^{2} [GeV^{2}/c^{4}]");
  hdalitzm->GetYaxis()->SetTitle("Mass_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
  hdalitzm->GetXaxis()->SetRange(-1, 32);
  hdalitzm->GetYaxis()->SetRange(-1, 27);
  
  //B- background
  TH2F *hdalitzbgm = (TH2F*)ft->Get("h_dalitz_bgm");
  hdalitzbgm->Scale(bgscale_m);
  //TCanvas *c7 = new TCanvas("c7","",600,400);
  //hdalitzbgm->SetStats(0);
  //hdalitzbgm->GetXaxis()->SetTitle("Mass_{K#pi}^{2} [GeV^{2}/c^{4}]");
  //hdalitzbgm->GetYaxis()->SetTitle("Mass_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
  //hdalitzbgm->Draw("colz");                          // draw with a colour scale
  //c7->SaveAs("dalitz_bgm.pdf");
  
  hdalitzm->Add(hdalitzbgm, -1);
  
  for(int i = 0; i < xbin; i++){
  	for(int j = 0; j < ybin; j++){
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
  hdalitzsub->GetXaxis()->SetRange(-1, 32);
  hdalitzsub->GetYaxis()->SetRange(-1, 27);
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
  hdalitzadd->GetXaxis()->SetRange(-1, 32);
  hdalitzadd->GetYaxis()->SetRange(-1, 27);
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
  hdalitzass2->GetXaxis()->SetRange(-1, 32);
  hdalitzass2->GetYaxis()->SetRange(-1, 27);
  hdalitzass2->Draw("colz");                          // draw with a colour scale
  c10->SaveAs("dalitz_ass2.pdf");
  
  
  
  //ASSYMETRY
  TH2F *hdalitzass = (TH2F*) hdalitzm -> GetAsymmetry(hdalitzp);
  hdalitzass->Sumw2();
  TCanvas *c11 = new TCanvas("c11","",600,400);
  hdalitzass->SetStats(0);
  hdalitzass->GetXaxis()->SetTitle("Mass_{K#pi}^{2} [GeV^{2}/c^{4}]");
  hdalitzass->GetYaxis()->SetTitle("Mass_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
  hdalitzass->GetXaxis()->SetRange(-1, 32);
  hdalitzass->GetYaxis()->SetRange(-1, 27);
  hdalitzass->Draw("colz");                          // draw with a colour scale
  c11->SaveAs("dalitz_ass.pdf");
  
  TH2F *hdalitzass_err = (TH2F*) hdalitzass->Clone();
  hdalitzass_err->Sumw2();
  
  //double err;
  for(int a = 0; a < xbin; a++){
  	for(int b = 0; b < ybin; b++){
  		//err = pow((1-pow(hdalitzass->GetBinContent(a,b), 2)) / (hdalitzadd->GetBinContent(a,b)), 0.5);
  		hdalitzass_err->SetBinContent(a, b, hdalitzass->GetBinError(a,b));

  	}
  }
  
  TCanvas *c12 = new TCanvas("c12","",600,400);
  hdalitzass_err->SetStats(0);
  //hdalitzass_err->SetTitle();
  hdalitzass_err->GetXaxis()->SetTitle("Mass_{K#pi}^{2} [GeV^{2}/c^{4}]");
  hdalitzass_err->GetYaxis()->SetTitle("Mass_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
  hdalitzass_err->GetXaxis()->SetRange(-1, 32);
  hdalitzass_err->GetYaxis()->SetRange(-1, 27);
  hdalitzass_err->Draw("colz");                          // draw with a colour scale
  c12->SaveAs("dalitz_ass_err.pdf");
  
 
  TH2F *hdalitzsig = (TH2F*) hdalitzass->Clone();
  hdalitzsig->Sumw2();
  hdalitzsig->Divide(hdalitzass_err);
  TCanvas *c13 = new TCanvas("c13","",600,400);
  hdalitzsig->SetStats(0);
  hdalitzsig->GetXaxis()->SetTitle("Mass_{K#pi}^{2} [GeV^{2}/c^{4}]");
  hdalitzsig->GetYaxis()->SetTitle("Mass_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
  hdalitzsig->GetXaxis()->SetRange(-1, 32);
  hdalitzsig->GetYaxis()->SetRange(-1, 27);
  hdalitzsig->Draw("colz");                          // draw with a colour scale
  c13->SaveAs("dalitz_sig.pdf");
  
  
  TH2F *hdalitzass_corr = (TH2F*) hdalitzass->Clone();
  hdalitzass_corr->Sumw2();
  for(int o = 0; o < xbin; o++){
  	for(int p = 0; p < ybin; p++){
		if(hdalitzass_err->GetBinContent(o,p) <= 0. || hdalitzass_err->GetBinContent(o,p) >= 0.4){
  			hdalitzass_corr->SetBinContent(o,p, 0);
  		}
  	}
  }
  
  for(int r = 0; r < xbin; r++){
  	for(int t = 0; t < ybin; t++){
		if(hdalitzm->GetBinContent(r,t) == 0 || hdalitzp->GetBinContent(r,t) == 0){
			//cout << "a " <<hdalitzass_corr->GetBinContent(r,t)<< "\n";
  			hdalitzass_corr->SetBinContent(r,t, -2);
			//cout << "b " <<hdalitzass_corr->GetBinContent(r,t)<< "\n";
  		}
  	}
  }
  
  
  TCanvas *c14 = new TCanvas("c14","",600,500);
  hdalitzass_corr->SetStats(0);
  hdalitzass_corr->GetXaxis()->SetTitle("M_{K#pi}^{2} [GeV^{2}/c^{4}]");
  hdalitzass_corr->GetXaxis()->SetTitleSize(.05);
  hdalitzass_corr->GetXaxis()->SetLabelSize(.05);
  hdalitzass_corr->GetYaxis()->SetTitle("M_{#pi#pi}^{2} [GeV^{2}/c^{4}]");
  hdalitzass_corr->GetYaxis()->SetTitleSize(.05);
  hdalitzass_corr->GetYaxis()->SetLabelSize(.05);
  hdalitzass_corr->GetZaxis()->SetLabelSize(.05);
  hdalitzass_corr->GetXaxis()->SetRange(-1, 32);
  hdalitzass_corr->GetYaxis()->SetRange(-1, 30);
  hdalitzass_corr->SetMaximum(1);
  hdalitzass_corr->SetMinimum(-1);
  c14->SetBottomMargin(0.11);
  c14->SetLeftMargin(0.11);
  c14->SetRightMargin(0.13);
  hdalitzass_corr->Draw("colz");                          // draw with a colour scale
  
  //hdalitzass_corr->SetFrameFillColor(1);
  c14->SaveAs("dalitz_ass_corr.pdf");


  //specified region 3 body ----------------------------------
  //B TOTAL---------------------------------------------

  TH1F *hmass_CP = (TH1F*)ft->Get("h_CP_massB");

  // Create a canvas onto which the histograms are plotted and which can be saved
  TCanvas *c15t = new TCanvas("c15t","",600,400);
  // Draw the first histogram with a blue line, and an x-axis title
  gStyle->SetOptStat("e");
  gStyle->SetOptFit(1111);
  gStyle->SetStatFormat("6.6g");
  
  hmass_CP->SetLineColor(kBlue);
  hmass_CP->GetXaxis()->SetTitle("Mass [GeV/c^{2}]");
  

  //fit
  //(1/([2]*pow(2*pi, 0.5)))*[0]*exp(-(1./2)*pow(((x-[1])/[2]), 2))
  TF1 *Signal_CP = new TF1("Signal_CP", "gausn", 5240, 5300); //5279.29-40 ,5279.29+50);
  TF1 *Background_CP = new TF1("Background_CP", "expo", 5279.29+80, 5700 );
  TF1 *CombBG_CP = new TF1("CombBG_CP", "gausn", 5035, 5279.29-80);
  TF1 *total_CP = new TF1("total_CP","gausn(0) + expo(3) + gausn(5)",5035,5700);
  
  hmass_CP->Fit(Signal_CP, "R");
  hmass_CP->Fit(Background_CP, "RN+");
  hmass_CP->Fit(CombBG_CP, "RN+");
  
  
  Double_t par_CP[8];
  Signal_CP->GetParameters(&par_CP[0]);
  Background_CP->GetParameters(&par_CP[3]);
  CombBG_CP->GetParameters(&par_CP[5]);
	
  total_CP->SetParameters(par_CP);
  hmass_CP->Fit(total_CP, "ROME");
	
  
  Double_t parfinal_CP[8];
  total_CP->GetParameters(parfinal_CP);
  
  total_CP->SetParNames("Signal G C", "Signal G M", "Signal G #sigma", "BG E C", "BG E M", "Comb BG G C", "Comb BG G M", "Comb BG G #sigma");
	  
  
  TF1 *DrawSignal_CP = new TF1("DrawSignal_CP", "gausn", 5035 ,5700);
  TF1 *DrawBackground_CP = new TF1("DrawBackground_CP", "expo", 5035 ,5700);
  TF1 *DrawCombBG_CP = new TF1("DrawCombBG_CP", "gausn", 5035 ,5700);
  DrawSignal_CP->SetParameters(&parfinal_CP[0]);
  DrawBackground_CP->SetParameters(&parfinal_CP[3]);
  DrawCombBG_CP->SetParameters(&parfinal_CP[5]);
  
  TH1F *subtracted_CP = new TH1F(*hmass_CP);
  subtracted_CP->Add(DrawBackground_CP, -1);
  subtracted_CP->Add(DrawCombBG_CP, -1);
  
  hmass_CP->Draw("E1");
  
  hmass_CP->SetAxisRange(5090, 5500., "X");
  hmass_CP->SetAxisRange(-2., 150., "Y");
  
  total_CP->Draw("same");
  total_CP->SetLineColor(2);
  total_CP->SetLineWidth(2);
  
  DrawSignal_CP->Draw("same");
  DrawSignal_CP->SetLineColor(8);
  DrawSignal_CP->SetLineWidth(2);
   
  DrawBackground_CP->Draw("same");
  DrawBackground_CP->SetLineColor(6);
  DrawBackground_CP->SetLineWidth(1);
  
  DrawCombBG_CP->Draw("same");
  DrawCombBG_CP->SetLineColor(38);
  DrawCombBG_CP->SetLineWidth(1);
  
  //Msubtracted_CP->Draw("same");
  
  
  c15t->SaveAs("CP_massB.pdf");
  
  //B PLUS---------------------------------------------
  //p = plus = M
  TH1F *hmass_CP_p = (TH1F*)ft->Get("h_CP_massB_p");

  // Create a canvas onto which the histograms are plotted and which can be saved
  TCanvas *c15 = new TCanvas("c15","",600,500);
  // Draw the first histogram with a blue line, and an x-axis title
  gStyle->SetOptStat("e");
  gStyle->SetOptFit(1111);
  gStyle->SetStatFormat("6.6g");
  
  hmass_CP_p->SetLineColor(kBlue);
  hmass_CP_p->GetXaxis()->SetTitle("Invariant Mass [MeV/c^{2}]");
  hmass_CP_p->GetXaxis()->SetTitleSize(.05);
  hmass_CP_p->GetXaxis()->SetLabelSize(.05);
  hmass_CP_p->GetYaxis()->SetTitle("Events/Bin");
  hmass_CP_p->GetYaxis()->SetTitleSize(.05);
  hmass_CP_p->GetYaxis()->SetLabelSize(.05);
  
  

  //fit
  //(1/([2]*pow(2*pi, 0.5)))*[0]*exp(-(1./2)*pow(((x-[1])/[2]), 2))
  TF1 *MSignal_CP = new TF1("MSignal_CP", "gausn", 5240, 5300); //5279.29-40 ,5279.29+50);
  TF1 *MBackground_CP = new TF1("MBackground_CP", "expo", 5279.29+80, 5700 );
  TF1 *MCombBG_CP = new TF1("MCombBG_CP", "gausn", 5035, 5279.29-80);
  TF1 *Mtotal_CP = new TF1("Mtotal_CP","gausn(0) + expo(3) + gausn(5)",5035,5700);
  
  MSignal_CP->SetParLimits(1, parfinal_CP[1]-2*total_CP->GetParError(1), parfinal_CP[1]+2*total_CP->GetParError(1));
  MSignal_CP->SetParLimits(2, parfinal_CP[2]-2*total_CP->GetParError(2), parfinal_CP[2]+2*total_CP->GetParError(2));
  
  hmass_CP_p->Fit(MSignal_CP, "RNB");
  hmass_CP_p->Fit(MBackground_CP, "RN+");
  hmass_CP_p->Fit(MCombBG_CP, "RN+");
  
  
  Double_t Mpar_CP[8];
  MSignal_CP->GetParameters(&Mpar_CP[0]);
  MBackground_CP->GetParameters(&Mpar_CP[3]);
  MCombBG_CP->GetParameters(&Mpar_CP[5]);
	
  //Mpar_CP[2] = abs(Mpar_CP[2]);
  cout << "mean " << Mpar_CP[1] << "\n";
  cout << "sigma " << Mpar_CP[2] << "\n";
  Mtotal_CP->SetParameters(Mpar_CP);
  Mtotal_CP->SetParLimits(1, parfinal_CP[1]-2*total_CP->GetParError(1), parfinal_CP[1]+2*total_CP->GetParError(1));
  Mtotal_CP->SetParLimits(2, parfinal_CP[2]-2*total_CP->GetParError(2), parfinal_CP[2]+2*total_CP->GetParError(2));
  hmass_CP_p->Fit(Mtotal_CP, "ROMEB");
	
  
  Double_t Mparfinal_CP[8];
  Mtotal_CP->GetParameters(Mparfinal_CP);
  
  Mtotal_CP->SetParNames("Signal G C", "Signal G M", "Signal G #sigma", "BG E C", "BG E M", "Comb BG G C", "Comb BG G M", "Comb BG G #sigma");
	  
  
  TF1 *MDrawSignal_CP = new TF1("MDrawSignal_CP", "gausn", 5035 ,5700);
  TF1 *MDrawBackground_CP = new TF1("MDrawBackground_CP", "expo", 5035 ,5700);
  TF1 *MDrawCombBG_CP = new TF1("MDrawCombBG_CP", "gausn", 5035 ,5700);
  MDrawSignal_CP->SetParameters(&Mparfinal_CP[0]);
  MDrawBackground_CP->SetParameters(&Mparfinal_CP[3]);
  MDrawCombBG_CP->SetParameters(&Mparfinal_CP[5]);
  
  TH1F *Msubtracted_CP = new TH1F(*hmass_CP_p);
  Msubtracted_CP->Add(MDrawBackground_CP, -1);
  Msubtracted_CP->Add(MDrawCombBG_CP, -1);
  
  hmass_CP_p->Draw("E1");
  hmass_CP_p->SetAxisRange(-1., 90., "Y");
  hmass_CP_p->SetAxisRange(5090, 5500, "X");
  hmass_CP_p->GetXaxis()->SetNdivisions(506);
  hmass_CP_p->SetLineColor(kBlack);
  
  Mtotal_CP->Draw("same");
  Mtotal_CP->SetLineColor(kBlue);
  Mtotal_CP->SetLineWidth(2);
  //Mtotal->SetLineStyle(9);
  
  MDrawSignal_CP->Draw("same");
  MDrawSignal_CP->SetLineColor(kMagenta+1);
  MDrawSignal_CP->SetLineWidth(2);
  //MDrawSignal->SetLineStyle(7);
   
  MDrawBackground_CP->Draw("same");
  MDrawBackground_CP->SetLineColor(kGreen+3);
  MDrawBackground_CP->SetLineWidth(2);
  MDrawBackground_CP->SetLineStyle(9);
  
  MDrawCombBG_CP->Draw("same");
  MDrawCombBG_CP->SetLineColor(38);
  MDrawCombBG_CP->SetLineWidth(2);
  MDrawCombBG_CP->SetLineStyle(7);
  
  auto legend4 = new TLegend(0.6,0.7,0.95,0.95);
  legend4->AddEntry(Mtotal_CP,"Total","l");
  legend4->AddEntry(MDrawSignal_CP,"Signal","l");
  legend4->AddEntry(MDrawBackground_CP,"Combinatorial","l");
  legend4->AddEntry(MDrawCombBG_CP,"4-body","l");
  legend4->Draw();
  
  
  c15->SaveAs("CP_massB_p.pdf");

  //B MINUS---------------------------------------------
  //m = minus = A
  TH1F *hmass_CP_m = (TH1F*)ft->Get("h_CP_massB_m");

  // Create a canvas onto which the histograms are plotted and which can be saved
  TCanvas *c16 = new TCanvas("c16","",600,500);
  // Draw the first histogram with a blue line, and an x-axis title
  gStyle->SetOptStat("e");
  gStyle->SetOptFit(1111);
  gStyle->SetStatFormat("6.6g");
  
  hmass_CP_m->SetLineColor(kBlue);
  hmass_CP_m->GetXaxis()->SetTitle("Invariant Mass [MeV/c^{2}]");
  hmass_CP_m->GetXaxis()->SetTitleSize(.05);
  hmass_CP_m->GetXaxis()->SetLabelSize(.05);
  hmass_CP_m->GetYaxis()->SetTitle("Events/Bin");
  hmass_CP_m->GetYaxis()->SetTitleSize(.05);
  hmass_CP_m->GetYaxis()->SetLabelSize(.05);
  

  //fit
 
  TF1 *ASignal_CP = new TF1("ASignal_CP", "gausn", 5279.29-40 ,5279.29+50);
  TF1 *ABackground_CP = new TF1("ABackground_CP", "expo", 5279.29+80, 5700 );
  TF1 *ACombBG_CP = new TF1("ACombBG_CP", "gausn", 5035, 5279.29-80);
  TF1 *Atotal_CP = new TF1("Atotal_CP","gausn(0) + expo(3) + gausn(5)",5035,5700);
  
  ASignal_CP->SetParLimits(1, parfinal_CP[1]-2*total_CP->GetParError(1), parfinal_CP[1]+2*total_CP->GetParError(1));
  ASignal_CP->SetParLimits(2, parfinal_CP[2]-2*total_CP->GetParError(2), parfinal_CP[2]+2*total_CP->GetParError(2));
  

  hmass_CP_m->Fit(ASignal_CP, "RN");
  hmass_CP_m->Fit(ABackground_CP, "RN+");
  hmass_CP_m->Fit(ACombBG_CP, "RN+");
  
  Double_t Apar_CP[8];
  ASignal_CP->GetParameters(&Apar_CP[0]);
  ABackground_CP->GetParameters(&Apar_CP[3]);
  ACombBG_CP->GetParameters(&Apar_CP[5]);

  Atotal_CP->SetParameters(Apar_CP);
  Atotal_CP->SetParLimits(1, parfinal_CP[1]-2*total_CP->GetParError(1), parfinal_CP[1]+2*total_CP->GetParError(1));
  Atotal_CP->SetParLimits(2, parfinal_CP[2]-2*total_CP->GetParError(2), parfinal_CP[2]+2*total_CP->GetParError(2));
  hmass_CP_m->Fit(Atotal_CP, "ROME");
	
  
  Double_t Aparfinal_CP[8];
  Atotal_CP->GetParameters(Aparfinal_CP);
  
  Mtotal_CP->SetParNames("Signal G C", "Signal G M", "Signal G #sigma", "BG E C", "BG E M", "Comb BG G C", "Comb BG G M", "Comb BG G #sigma");
	  
  
  TF1 *ADrawSignal_CP = new TF1("ADrawSignal_CP", "gausn", 5035 ,5700);
  TF1 *ADrawBackground_CP = new TF1("ADrawBackground_CP", "expo", 5035 ,5700);
  TF1 *ADrawCombBG_CP = new TF1("ADrawCombBG_CP", "gausn", 5035 ,5700);
  ADrawSignal_CP->SetParameters(&Aparfinal_CP[0]);
  ADrawBackground_CP->SetParameters(&Aparfinal_CP[3]);
  ADrawCombBG_CP->SetParameters(&Aparfinal_CP[5]);
  
  TH1F *Asubtracted_CP = new TH1F(*hmass_CP_m);
  Asubtracted_CP->Add(ADrawBackground_CP, -1);
  Asubtracted_CP->Add(ADrawCombBG_CP, -1);
  
  hmass_CP_m->Draw("E1");
  hmass_CP_m->SetAxisRange(-1., 90., "Y");
  hmass_CP_m->SetAxisRange(5090, 5500, "X");
  hmass_CP_m->GetXaxis()->SetNdivisions(506);
  hmass_CP_m->SetLineColor(kBlack);
  
  Atotal_CP->Draw("same");
  Atotal_CP->SetLineColor(kBlue);
  Atotal_CP->SetLineWidth(2);
  //Mtotal->SetLineStyle(9);
  
  ADrawSignal_CP->Draw("same");
  ADrawSignal_CP->SetLineColor(kMagenta+1);
  ADrawSignal_CP->SetLineWidth(2);
  //MDrawSignal->SetLineStyle(7);
   
  ADrawBackground_CP->Draw("same");
  ADrawBackground_CP->SetLineColor(kGreen+3);
  ADrawBackground_CP->SetLineWidth(2);
  ADrawBackground_CP->SetLineStyle(9);
  
  ADrawCombBG_CP->Draw("same");
  ADrawCombBG_CP->SetLineColor(38);
  ADrawCombBG_CP->SetLineWidth(2);
  ADrawCombBG_CP->SetLineStyle(7);
  
  auto legend3 = new TLegend(0.6,0.7,0.95,0.95);
  legend3->AddEntry(Atotal_CP,"Total","l");
  legend3->AddEntry(ADrawSignal_CP,"Signal","l");
  legend3->AddEntry(ADrawBackground_CP,"Combinatorial","l");
  legend3->AddEntry(ADrawCombBG_CP,"4-body","l");
  legend3->Draw();
 
  
  //Asubtracted_CP->Draw("same");
  
  
  c16->SaveAs("CP_massB_m.pdf");
  
  //CP ASSYMETRY
  double scale_CP = hmass_CP->GetXaxis()->GetBinWidth(1);
  double Np_CP = Mparfinal_CP[0]/scale;
  double Nm_CP = Aparfinal_CP[0]/scale;
  double A_CP = (Nm_CP-Np_CP)/(Nm_CP+Np_CP);
  
  double Aerr_CP = pow(((1-pow(A_CP,2))/(Nm_CP+Np_CP)),0.5);
  double Aerr2_CP = (2/pow(Np_CP+Nm_CP, 2))*pow((pow(Np_CP*Atotal_CP->GetParError(0)/scale,2) + pow(Nm_CP*Mtotal_CP->GetParError(0)/scale_CP,2)), 0.5);
  
  cout << "scale " << scale_CP << "\n";
  cout << "Mparfinal_CP[0]: " << Mparfinal_CP[0] << "\n";
  cout << "Aparfinal_CP[0]: " << Aparfinal_CP[0] << "\n";
  cout << "Np: " << Np_CP << "\n";
  cout << "Nm: " << Nm_CP << "\n";
  cout << "\nCP Asymmetry 1: " << A_CP<< "+/-"<< Aerr_CP << "+/-"<< Aerr2_CP << "\n\n\n";
  
  
  //specified region TWO 3 body ----------------------------------
  //B TOTAL---------------------------------------------

  TH1F *hmass_CP2 = (TH1F*)ft->Get("h_CP_massB2");

  // Create a canvas onto which the histograms are plotted and which can be saved
  TCanvas *c17 = new TCanvas("c17","",600,400);
  // Draw the first histogram with a blue line, and an x-axis title
  gStyle->SetOptStat("e");
  gStyle->SetOptFit(1111);
  gStyle->SetStatFormat("6.6g");
  
  cout << "\n bin: "<< hmass_CP2->GetBinContent(6) << "\n";
  
  for (int x; x < 65; x++){
	  cout << "\n bin: "<< hmass_CP2->GetBinContent(x) << "\n";
  }
  
  hmass_CP2->SetLineColor(kBlue);
  hmass_CP2->GetXaxis()->SetTitle("Mass [GeV/c^{2}]");
  

  //fit
  //(1/([2]*pow(2*pi, 0.5)))*[0]*exp(-(1./2)*pow(((x-[1])/[2]), 2))
  TF1 *Signal_CP2 = new TF1("Signal_CP2", "gausn", 5240, 5300); //5279.29-40 ,5279.29+50);
  TF1 *Background_CP2 = new TF1("Background_CP2", "expo", 5279.29+80, 5700 );
  TF1 *CombBG_CP2 = new TF1("CombBG_CP2", "landau", 5035, 5279.29-80);
  TF1 *total_CP2 = new TF1("total_CP2","gausn(0) + expo(3) + landau(5)",5035,5700);
  
  hmass_CP2->Fit(Signal_CP2, "R");
  hmass_CP2->Fit(Background_CP2, "RN+");
  hmass_CP2->Fit(CombBG_CP2, "RN+");
  
  
  Double_t par_CP2[8];
  Signal_CP2->GetParameters(&par_CP2[0]);
  Background_CP2->GetParameters(&par_CP2[3]);
  CombBG_CP2->GetParameters(&par_CP2[5]);
	
  total_CP2->SetParameters(par_CP2);
  hmass_CP2->Fit(total_CP2, "ROME");
	
  
  Double_t parfinal_CP2[8];
  total_CP2->GetParameters(parfinal_CP2);
  
  total_CP2->SetParNames("Signal G C", "Signal G M", "Signal G #sigma", "BG E C", "BG E M", "Comb BG G C", "Comb BG G M", "Comb BG G #sigma");
	  
  
  TF1 *DrawSignal_CP2 = new TF1("DrawSignal_CP2", "gausn", 5035 ,5700);
  TF1 *DrawBackground_CP2 = new TF1("DrawBackground_CP2", "expo", 5035 ,5700);
  TF1 *DrawCombBG_CP2 = new TF1("DrawCombBG_CP2", "landau", 5035 ,5700);
  DrawSignal_CP2->SetParameters(&parfinal_CP2[0]);
  DrawBackground_CP2->SetParameters(&parfinal_CP2[3]);
  DrawCombBG_CP2->SetParameters(&parfinal_CP2[5]);
  
  TH1F *subtracted_CP2 = new TH1F(*hmass_CP2);
  subtracted_CP2->Add(DrawBackground_CP2, -1);
  subtracted_CP2->Add(DrawCombBG_CP2, -1);
  
  hmass_CP2->Draw("E1");
          
  hmass_CP2->SetAxisRange(5090, 5500., "X");
  hmass_CP2->SetAxisRange(-2., 150., "Y");
          
  total_CP2->Draw("same");
  total_CP2->SetLineColor(2);
  total_CP2->SetLineWidth(2);
  
  DrawSignal_CP2->Draw("same");
  DrawSignal_CP2->SetLineColor(8);
  DrawSignal_CP2->SetLineWidth(2);
   
  DrawBackground_CP2->Draw("same");
  DrawBackground_CP2->SetLineColor(6);
  DrawBackground_CP2->SetLineWidth(1);
  
  DrawCombBG_CP2->Draw("same");
  DrawCombBG_CP2->SetLineColor(38);
  DrawCombBG_CP2->SetLineWidth(1);
  
  //Msubtracted_CP2->Draw("same");
  
  
  c17->SaveAs("CP_massB2.pdf");
  
  //B PLUS---------------------------------------------
  //p = plus = M
  TH1F *hmass_CP2_p = (TH1F*)ft->Get("h_CP_massB2_p");

  // Create a canvas onto which the histograms are plotted and which can be saved
  TCanvas *c18 = new TCanvas("c18","",600,500);
  // Draw the first histogram with a blue line, and an x-axis title
  gStyle->SetOptStat("e");
  gStyle->SetOptFit(1111);
  gStyle->SetStatFormat("6.6g");
  
  hmass_CP2_p->SetLineColor(kBlue);
  hmass_CP2_p->GetXaxis()->SetTitle("Invariant Mass [MeV/c^{2}]");
  hmass_CP2_p->GetXaxis()->SetTitleSize(.05);
  hmass_CP2_p->GetXaxis()->SetLabelSize(.05);
  hmass_CP2_p->GetYaxis()->SetTitle("Events/Bin");
  hmass_CP2_p->GetYaxis()->SetTitleSize(.05);
  hmass_CP2_p->GetYaxis()->SetLabelSize(.05);
  

  //fit
  //(1/([2]*pow(2*pi, 0.5)))*[0]*exp(-(1./2)*pow(((x-[1])/[2]), 2))
  TF1 *MSignal_CP2 = new TF1("MSignal_CP2", "gausn", 5240, 5300); //5279.29-40 ,5279.29+50);
  TF1 *MBackground_CP2 = new TF1("MBackground_CP2", "expo", 5279.29+80, 5700 );
  TF1 *MCombBG_CP2 = new TF1("MCombBG_CP2", "landau", 5035, 5279.29-80);
  TF1 *Mtotal_CP2 = new TF1("Mtotal_CP2","gausn(0) + expo(3) + landau(5)",5035,5700);
  
  MSignal_CP2->SetParLimits(1, parfinal_CP2[1]-2*total_CP2->GetParError(1), parfinal_CP2[1]+2*total_CP2->GetParError(1));
  MSignal_CP2->SetParLimits(2, parfinal_CP2[2]-2*total_CP2->GetParError(2), parfinal_CP2[2]+2*total_CP2->GetParError(2));
  
  hmass_CP2_p->Fit(MSignal_CP2, "RNB");
  hmass_CP2_p->Fit(MBackground_CP2, "RN+");
  hmass_CP2_p->Fit(MCombBG_CP2, "RN+");
  
  
  Double_t Mpar_CP2[8];
  MSignal_CP2->GetParameters(&Mpar_CP2[0]);
  MBackground_CP2->GetParameters(&Mpar_CP2[3]);
  MCombBG_CP2->GetParameters(&Mpar_CP2[5]);
  	
  //Mpar_CP[2] = abs(Mpar_CP[2]);
  cout << "mean2 " << Mpar_CP2[1] << "\n";
  cout << "sigma2 " << Mpar_CP2[2] << "\n";
  Mtotal_CP2->SetParameters(Mpar_CP2);
  Mtotal_CP2->SetParLimits(1, parfinal_CP2[1]-2*total_CP2->GetParError(1), parfinal_CP2[1]+2*total_CP2->GetParError(1));
  Mtotal_CP2->SetParLimits(2, parfinal_CP2[2]-2*total_CP2->GetParError(2), parfinal_CP2[2]+2*total_CP2->GetParError(2));
  Mtotal_CP2->SetParNames("Signal G C", "Signal G M", "Signal G #sigma", "BG E C", "BG E M", "Comb BG G C", "Comb BG G M", "Comb BG G #sigma");
  hmass_CP2_p->Fit(Mtotal_CP2, "ROMEB");
	
  
  Double_t Mparfinal_CP2[8];
  Mtotal_CP2->GetParameters(Mparfinal_CP2);
  
  Mtotal_CP2->SetParNames("Signal G C", "Signal G M", "Signal G #sigma", "BG E C", "BG E M", "Comb BG G C", "Comb BG G M", "Comb BG G #sigma");
	  
  
  TF1 *MDrawSignal_CP2 = new TF1("MDrawSignal_CP2", "gausn", 5035 ,5700);
  TF1 *MDrawBackground_CP2 = new TF1("MDrawBackground_CP2", "expo", 5035 ,5700);
  TF1 *MDrawCombBG_CP2 = new TF1("MDrawCombBG_CP2", "landau", 5035 ,5700);
  MDrawSignal_CP2->SetParameters(&Mparfinal_CP2[0]);
  MDrawBackground_CP2->SetParameters(&Mparfinal_CP2[3]);
  MDrawCombBG_CP2->SetParameters(&Mparfinal_CP2[5]);
  
  TH1F *Msubtracted_CP2 = new TH1F(*hmass_CP2_p);
  Msubtracted_CP2->Add(MDrawBackground_CP2, -1);
  Msubtracted_CP2->Add(MDrawCombBG_CP2, -1);
  
  hmass_CP2_p->Draw("E1");
  hmass_CP2_p->SetAxisRange(-1., 90., "Y");
  hmass_CP2_p->SetAxisRange(5090, 5500, "X");
  hmass_CP2_p->GetXaxis()->SetNdivisions(506);
  hmass_CP2_p->SetLineColor(kBlack);
  
  Mtotal_CP2->Draw("same");
  Mtotal_CP2->SetLineColor(kBlue);
  Mtotal_CP2->SetLineWidth(2);
  //Mtotal->SetLineStyle(9);
  
  MDrawSignal_CP2->Draw("same");
  MDrawSignal_CP2->SetLineColor(kMagenta+1);
  MDrawSignal_CP2->SetLineWidth(2);
  //MDrawSignal->SetLineStyle(7);
   
  MDrawBackground_CP2->Draw("same");
  MDrawBackground_CP2->SetLineColor(kGreen+3);
  MDrawBackground_CP2->SetLineWidth(2);
  MDrawBackground_CP2->SetLineStyle(9);
  
  MDrawCombBG_CP2->Draw("same");
  MDrawCombBG_CP2->SetLineColor(38);
  MDrawCombBG_CP2->SetLineWidth(2);
  MDrawCombBG_CP2->SetLineStyle(7);
  
  auto legend5 = new TLegend(0.6,0.7,0.95,0.95);
  legend5->AddEntry(Mtotal_CP2,"Total","l");
  legend5->AddEntry(MDrawSignal_CP2,"Signal","l");
  legend5->AddEntry(MDrawBackground_CP2,"Combinatorial","l");
  legend5->AddEntry(MDrawCombBG_CP2,"4-body","l");
  legend5->Draw();
  
  
  //Msubtracted_CP2->Draw("same");
  
  
  c18->SaveAs("CP_massB2_p.pdf");

  //B MINUS---------------------------------------------
  //m = minus = A
  TH1F *hmass_CP2_m = (TH1F*)ft->Get("h_CP_massB2_m");
  
  // Create a canvas onto which the histograms are plotted and which can be saved
  TCanvas *c19 = new TCanvas("c19","",600,500);
  // Draw the first histogram with a blue line, and an x-axis title
  gStyle->SetOptStat("e");
  gStyle->SetOptFit(1111);
  gStyle->SetStatFormat("6.6g");
  
  hmass_CP2_m->SetLineColor(kBlue);
  hmass_CP2_m->GetXaxis()->SetTitle("Invariant Mass [MeV/c^{2}]");
  hmass_CP2_m->GetXaxis()->SetTitleSize(.05);
  hmass_CP2_m->GetXaxis()->SetLabelSize(.05);
  hmass_CP2_m->GetYaxis()->SetTitle("Events/Bin");
  hmass_CP2_m->GetYaxis()->SetTitleSize(.05);
  hmass_CP2_m->GetYaxis()->SetLabelSize(.05);
  

  //fit
 
  TF1 *ASignal_CP2 = new TF1("ASignal_CP2", "gausn", 5279.29-40 ,5279.29+50);
  TF1 *ABackground_CP2 = new TF1("ABackground_CP2", "expo", 5279.29+80, 5700 );
  TF1 *ACombBG_CP2 = new TF1("ACombBG_CP2", "landau", 5035, 5279.29-80);
  TF1 *Atotal_CP2 = new TF1("Atotal_CP2","gausn(0) + expo(3) + landau(5)",5035,5700);
  
  ASignal_CP2->SetParLimits(1, parfinal_CP2[1]-2*total_CP2->GetParError(1), parfinal_CP2[1]+2*total_CP2->GetParError(1));
  ASignal_CP2->SetParLimits(2, parfinal_CP2[2]-2*total_CP2->GetParError(2), parfinal_CP2[2]+2*total_CP2->GetParError(2));
  

  hmass_CP2_m->Fit(ASignal_CP2, "RNB");
  hmass_CP2_m->Fit(ABackground_CP2, "RN+");
  hmass_CP2_m->Fit(ACombBG_CP2, "RN+");
  
  Double_t Apar_CP2[8];
  ASignal_CP2->GetParameters(&Apar_CP2[0]);
  ABackground_CP2->GetParameters(&Apar_CP2[3]);
  ACombBG_CP2->GetParameters(&Apar_CP2[5]);

  Atotal_CP2->SetParameters(Apar_CP);
  Atotal_CP2->SetParLimits(1, parfinal_CP[1]-2*total_CP->GetParError(1), parfinal_CP[1]+2*total_CP->GetParError(1));
  Atotal_CP2->SetParLimits(2, parfinal_CP[2]-2*total_CP->GetParError(2), parfinal_CP[2]+2*total_CP->GetParError(2));
  hmass_CP2_m->Fit(Atotal_CP2, "ROMEB");
	
  
  Double_t Aparfinal_CP2[8];
  Atotal_CP2->GetParameters(Aparfinal_CP2);
  
  Mtotal_CP2->SetParNames("Signal G C", "Signal G M", "Signal G #sigma", "BG E C", "BG E M", "Comb BG G C", "Comb BG G M", "Comb BG G #sigma");
	  
  
  TF1 *ADrawSignal_CP2 = new TF1("ADrawSignal_CP2", "gausn", 5035 ,5700);
  TF1 *ADrawBackground_CP2 = new TF1("ADrawBackground_CP2", "expo", 5035 ,5700);
  TF1 *ADrawCombBG_CP2 = new TF1("ADrawCombBG_CP2", "landau", 5035 ,5700);
  ADrawSignal_CP2->SetParameters(&Aparfinal_CP2[0]);
  ADrawBackground_CP2->SetParameters(&Aparfinal_CP2[3]);
  ADrawCombBG_CP2->SetParameters(&Aparfinal_CP2[5]);
  
  TH1F *Asubtracted_CP2 = new TH1F(*hmass_CP2_m);
  Asubtracted_CP2->Add(ADrawBackground_CP2, -1);
  Asubtracted_CP2->Add(ADrawCombBG_CP2, -1);
  
  hmass_CP2_m->Draw("E1");
  hmass_CP2_m->SetAxisRange(-1., 90., "Y");
  hmass_CP2_m->SetAxisRange(5090, 5500, "X");
  hmass_CP2_m->GetXaxis()->SetNdivisions(506);
  hmass_CP2_m->SetLineColor(kBlack);
  
  Atotal_CP2->Draw("same");
  Atotal_CP2->SetLineColor(kBlue);
  Atotal_CP2->SetLineWidth(2);
  //Mtotal->SetLineStyle(9);
  
  ADrawSignal_CP2->Draw("same");
  ADrawSignal_CP2->SetLineColor(kMagenta+1);
  ADrawSignal_CP2->SetLineWidth(2);
  //MDrawSignal->SetLineStyle(7);
   
  ADrawBackground_CP2->Draw("same");
  ADrawBackground_CP2->SetLineColor(kGreen+3);
  ADrawBackground_CP2->SetLineWidth(2);
  ADrawBackground_CP2->SetLineStyle(9);
  
  ADrawCombBG_CP2->Draw("same");
  ADrawCombBG_CP2->SetLineColor(38);
  ADrawCombBG_CP2->SetLineWidth(2);
  ADrawCombBG_CP2->SetLineStyle(7);
  
  auto legend6 = new TLegend(0.6,0.7,0.95,0.95);
  legend6->AddEntry(Atotal_CP2,"Total","l");
  legend6->AddEntry(ADrawSignal_CP2,"Signal","l");
  legend6->AddEntry(ADrawBackground_CP2,"Combinatorial","l");
  legend6->AddEntry(ADrawCombBG_CP2,"4-body","l");
  legend6->Draw();
  
  
  
  //Asubtracted_CP->Draw("same");
  
  
  c19->SaveAs("CP_massB2_m.pdf");
  
  //CP ASSYMETRY
  double scale_CP2 = hmass_CP->GetXaxis()->GetBinWidth(1);
  double Np_CP2 = Mparfinal_CP2[0]/scale;
  double Nm_CP2 = Aparfinal_CP2[0]/scale;
  double A_CP2 = (Nm_CP2-Np_CP2)/(Nm_CP2+Np_CP2);
  
  double Aerr_CP2 = pow(((1-pow(A_CP2,2))/(Nm_CP2+Np_CP2)),0.5);
  double Aerr2_CP2 = (2/pow(Np_CP2+Nm_CP2, 2))*pow((pow(Np_CP2*Atotal_CP2->GetParError(0)/scale,2) + pow(Nm_CP2*Mtotal_CP2->GetParError(0)/scale_CP2,2)), 0.5);
  
  cout << "scale " << scale_CP2 << "\n";
  cout << "Mparfinal_CP[0]: " << Mparfinal_CP2[0] << "\n";
  cout << "Aparfinal_CP[0]: " << Aparfinal_CP2[0] << "\n";
  cout << "Np: " << Np_CP2 << "\n";
  cout << "Nm: " << Nm_CP2 << "\n";
  cout << "\nCP Asymmetry 2: " << A_CP2<< "+/-"<< Aerr_CP2 <<"+/-"<< Aerr2_CP2 <<"\n\n\n";
}

