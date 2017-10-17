#include <numeric>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

void drawFitAlt() {
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
  
 
  //c10f->SaveAs("massB_sel2.pdf");
  
	//Gets integral of function between fit limits
   	//printf("Integral of function = %g\n",func->Integral(-2,2));
  
  
  
  //MATTER---------------------------------------------
  //p = plus = M
  TH1F *hmass_p = (TH1F*)ft->Get("h_massB_p");

  // Create a canvas onto which the histograms are plotted and which can be saved
  TCanvas *c11f = new TCanvas("c11f","",600,400);
  // Draw the first histogram with a blue line, and an x-axis title
  gStyle->SetOptStat("e");
  gStyle->SetOptFit(1111);
  gStyle->SetStatFormat("6.6g");
  
  hmass_p->SetLineColor(kBlue);
  hmass_p->GetXaxis()->SetTitle("Mass [MeV/c^{2}]");
  

  //fit
	 
  TF1 *MSignal = new TF1("MSignal", "gausn", 5279.29-40 ,5279.29+50);
  TF1 *MBackground = new TF1("MBackground", "expo", 5279.29+80, 5700 );
  TF1 *MCombBG = new TF1("MCombBG", "gausn", 5050, 5279.29-80);
  TF1 *Mtotal = new TF1("Mtotal","gausn(0) + expo(3) + gausn(5)",5050,5700);
  
  MSignal->SetParLimits(1, parfinal[1]-2*total->GetParError(1), parfinal[1]+2*total->GetParError(1));
  MSignal->SetParLimits(2, parfinal[2]-2*total->GetParError(2), parfinal[2]+2*total->GetParError(2));
  

  hmass_p->Fit(MSignal, "RN");
  hmass_p->Fit(MBackground, "RN+");
  hmass_p->Fit(MCombBG, "RN+");
  
  Double_t Mpar[8];
  MSignal->GetParameters(&Mpar[0]);
  MBackground->GetParameters(&Mpar[3]);
  MCombBG->GetParameters(&Mpar[5]);
  
  Mtotal->SetParLimits(1, parfinal[1]-2*total->GetParError(1), parfinal[1]+2*total->GetParError(1));
  Mtotal->SetParLimits(2, parfinal[2]-2*total->GetParError(2), parfinal[2]+2*total->GetParError(2));

  Mtotal->SetParameters(Mpar);
  hmass_p->Fit(Mtotal, "ROME");
	
  
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
  hmass_p->SetAxisRange(-50., 800., "Y");
  
  Mtotal->Draw("same");
  Mtotal->SetLineColor(2);
  Mtotal->SetLineWidth(2);
  
  MDrawSignal->Draw("same");
  MDrawSignal->SetLineColor(8);
  MDrawSignal->SetLineWidth(2);
   
  MDrawBackground->Draw("same");
  MDrawBackground->SetLineColor(6);
  MDrawBackground->SetLineWidth(1);
  
  MDrawCombBG->Draw("same");
  MDrawCombBG->SetLineColor(38);
  MDrawCombBG->SetLineWidth(1);
  
  //Msubtracted->Draw("same");
  
 
  //c11f->SaveAs("massB_matter.pdf");
  
  
  //ANTIMATTER
  //m = minus = A
  TH1F *hmass_m = (TH1F*)ft->Get("h_massB_m");

  // Create a canvas onto which the histograms are plotted and which can be saved
  TCanvas *c12f = new TCanvas("c12f","",600,400);
  // Draw the first histogram with a blue line, and an x-axis title
  gStyle->SetOptStat("e");
  gStyle->SetOptFit(1111);
  gStyle->SetStatFormat("6.6g");
  
  hmass_m->SetLineColor(kBlue);
  hmass_m->GetXaxis()->SetTitle("Mass - [MeV/c^{2}]");
  

  //fit
	 
  TF1 *ASignal = new TF1("ASignal", "gausn", 5279.29-40 ,5279.29+50);
  TF1 *ABackground = new TF1("ABackground", "expo", 5279.29+80, 5700 );
  TF1 *ACombBG = new TF1("ACombBG", "gausn", 5050, 5279.29-80);
  TF1 *Atotal = new TF1("total","gausn(0) + expo(3) + gausn(5)",5050,5700);
  ABackground->SetParameters(1,1);
  
  ASignal->SetParLimits(1, parfinal[1]-2*total->GetParError(1), parfinal[1]+2*total->GetParError(1));
  ASignal->SetParLimits(2, parfinal[2]-2*total->GetParError(2), parfinal[2]+2*total->GetParError(2));

  hmass_m->Fit(ASignal, "RN");
  hmass_m->Fit(ABackground, "RN+");
  hmass_m->Fit(ACombBG, "RN+");
  
  Double_t Apar[8];
  ASignal->GetParameters(&Apar[0]);
  ABackground->GetParameters(&Apar[3]);
  ACombBG->GetParameters(&Apar[5]);
  
  Atotal->SetParLimits(1, parfinal[1]-2*total->GetParError(1), parfinal[1]+2*total->GetParError(1));
  Atotal->SetParLimits(2, parfinal[2]-2*total->GetParError(2), parfinal[2]+2*total->GetParError(2));

  Atotal->SetParameters(Apar);
  hmass_m->Fit(Atotal, "ROME");
	
  Double_t Aparfinal[8];
  Atotal->GetParameters(Aparfinal);
  
  Atotal->SetParNames("Signal G C", "Signal G M", "Signal G #sigma", "BG E C", "BG E M", "Comb BG G C", "Comb BG G M", "Comb BG G #sigma");
	  
  //[0]*([1]-x)^2
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
  hmass_m->SetAxisRange(-50., 800., "Y");
  
  Atotal->Draw("same");
  Atotal->SetLineColor(2);
  Atotal->SetLineWidth(2);
  
  ADrawSignal->Draw("same");
  ADrawSignal->SetLineColor(8);
  ADrawSignal->SetLineWidth(2);
    
  ADrawBackground->Draw("same");
  ADrawBackground->SetLineColor(6);
  ADrawBackground->SetLineWidth(1);
 
  ADrawCombBG->Draw("same");
  ADrawCombBG->SetLineColor(38);
  ADrawCombBG->SetLineWidth(1);
 
  //Asubtracted->Draw("same E1");
  
 
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
  
  }