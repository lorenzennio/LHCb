void drawOutput() {
  //////////////////////
  // Example Root Macro for third year B->hhh Lab
  ////////////////////// 

  // Open the root file that was produced by running the example program
  TFile *f = new TFile("outputPhaseSpace.root");

  gStyle->SetOptStat(0000);
  
  // Get pointers to the example histograms that were made 
  TH1F *hx = (TH1F*)f->Get("h_PX");
  TH1F *hy = (TH1F*)f->Get("h_PY");
  TH2F *hxy = (TH2F*)f->Get("h_TXTY");

  // Create a canvas onto which the histograms are plotted and which can be saved
  TCanvas *c1 = new TCanvas("c1","",600,400);
  // Draw the first histogram with a blue line, and an x-axis title
  hx->SetLineColor(kBlue);
  hx->GetXaxis()->SetTitle("Momentum [MeV/c^{2}]");
  hx->Draw();

  // Draw the second histogram on the same plot with a red line
  hy->SetLineColor(kRed);
  hy->Draw("same");

  // Save the canvas as pdf file. Other possible formats include root (for later editing) eps, png.
  c1->SaveAs("hx_hy.pdf");

  // Repeat the above for the 2D histogram
  TCanvas *c2 = new TCanvas("c2","",600,400);
  hxy->SetStats(0);                           // remove the statistics box
  hxy->GetXaxis()->SetTitle("Slope in x");    // add axis titles
  hxy->GetYaxis()->SetTitle("Slope in y");
  hxy->Draw("colz");                          // draw with a colour scale
  c2->SaveAs("hxy.pdf");
  
  //Open DataAll file
  TFile *ft = new TFile("outputDataAll.root");

   // Get pointers to the example histograms that were made 
  TH1F *hxp = (TH1F*)ft->Get("h_ProbK");
  TH1F *hyp = (TH1F*)ft->Get("h_ProbPi");

  // Create a canvas onto which the histograms are plotted and which can be saved
  TCanvas *c3 = new TCanvas("c3","",600,400);
  // Draw the first histogram with a blue line, and an x-axis title
  hxp->SetLineColor(kBlue);
  hxp->GetXaxis()->SetTitle("Probability");
  hxp->Draw();

  // Draw the second histogram on the same plot with a red line
  hyp->SetLineColor(kRed);
  hyp->Draw("same");

   auto legend = new TLegend(0.55,0.75,0.75,0.85);
   legend->AddEntry(hxp,"Kaon Probability","l");
   legend->AddEntry(hyp,"Pion Probability","l");
   legend->Draw();
  
  c3->SaveAs("prob.pdf");

  //5.2
  // Get pointers to the example histograms that were made 
  TH1F *hmass = (TH1F*)f->Get("h_massB");

  // Create a canvas onto which the histograms are plotted and which can be saved
  TCanvas *c4 = new TCanvas("c4","",600,400);
  // Draw the first histogram with a blue line, and an x-axis title
  gStyle->SetOptStat("eM");
  gStyle->SetStatFormat("6.6g");
  hmass->SetLineColor(kBlue);
  hmass->GetXaxis()->SetTitle("Mass [MeV/c^{2}]");
  hmass->Draw();
  c4->SaveAs("massB.pdf");

  //5.3
 // Get pointers to the example histograms that were made 
  TH1F *hmass_sel = (TH1F*)ft->Get("h_massB_sel");

  // Create a canvas onto which the histograms are plotted and which can be saved
  TCanvas *c5 = new TCanvas("c5","",600,400);
  // Draw the first histogram with a blue line, and an x-axis title
  gStyle->SetOptStat("e");
  gStyle->SetStatFormat("6.6g");
  hmass_sel->SetLineColor(kBlue);
  hmass_sel->GetXaxis()->SetTitle("Mass [MeV/c^{2}]");
  hmass_sel->Draw();
  c5->SaveAs("massB_sel.pdf");


  //5.4
 // Get pointers to the example histograms that were made 
  TH1F *massR_K = (TH1F*)ft->Get("h_massR_K");
  TH1F *massR_Pi = (TH1F*)ft->Get("h_massR_Pi");

  // Create a canvas onto which the histograms are plotted and which can be saved
  TCanvas *c6 = new TCanvas("c6","",600,400);
  // Draw the first histogram with a blue line, and an x-axis title
  massR_K->SetLineColor(kBlue);
  massR_K->GetXaxis()->SetTitle("Mass [MeV/c^{2}]");
  massR_K->Draw();

  // Draw the second histogram on the same plot with a red line
  massR_Pi->SetLineColor(kRed);
  massR_Pi->Draw("same");

  auto legend2 = new TLegend(0.55,0.75,0.75,0.85);
  legend2->AddEntry(massR_K,"Kaon Pion Decay","l");
  legend2->AddEntry(massR_Pi,"Pion Pion Decay","l");
  legend2->Draw();
  
  c6->SaveAs("resonance.pdf");

  //D meson peak in 5.3
  // Get pointers to the example histograms that were made 
  TH1F *massR_K_Dmas = (TH1F*)ft->Get("h_massR_K_Dmas");

  // Create a canvas onto which the histograms are plotted and which can be saved
  TCanvas *c7 = new TCanvas("c7","",600,400);
  // Draw the first histogram with a blue line, and an x-axis title
  gStyle->SetOptStat("e");
  gStyle->SetStatFormat("6.6g");
  massR_K_Dmas->SetLineColor(kBlue);
  massR_K_Dmas->GetXaxis()->SetTitle("Mass [MeV/c^{2}]");
  massR_K_Dmas->Draw();
  c7->SaveAs("resonance_Dmas.pdf");


  //B meson peak in 5.3
  // Get pointers to the example histograms that were made 
  TH1F *massR_K_Bmas = (TH1F*)ft->Get("h_massR_K_Bmas");

  // Create a canvas onto which the histograms are plotted and which can be saved
  TCanvas *c8 = new TCanvas("c8","",600,400);
  // Draw the first histogram with a blue line, and an x-axis title
  gStyle->SetOptStat("e");
  gStyle->SetStatFormat("6.6g");
  massR_K_Bmas->SetLineColor(kBlue);
  massR_K_Bmas->GetXaxis()->SetTitle("Mass [MeV/c^{2}]");
  massR_K_Bmas->Draw();
  c8->SaveAs("resonance_Bmas.pdf");


 //J/gamma  peak in 5.3
  // Get pointers to the example histograms that were made 
  TH1F *massR_Pi_Jmas = (TH1F*)ft->Get("h_massR_Pi_Jmas");

  // Create a canvas onto which the histograms are plotted and which can be saved
  TCanvas *c9 = new TCanvas("c9","",600,400);
  // Draw the first histogram with a blue line, and an x-axis title
  gStyle->SetOptStat("e");
  gStyle->SetStatFormat("6.6g");
  massR_Pi_Jmas->SetLineColor(kBlue);
  massR_Pi_Jmas->GetXaxis()->SetTitle("Mass [MeV/c^{2}]");
  massR_Pi_Jmas->Draw();
  c9->SaveAs("resonance_Jmas.pdf");

  //5.5 Fitting
  // Get pointers to the example histograms that were made 
  TH1F *hmass_sel2 = (TH1F*)ft->Get("h_massB_sel2");

  // Create a canvas onto which the histograms are plotted and which can be saved
  TCanvas *c10 = new TCanvas("c10","",600,400);
  // Draw the first histogram with a blue line, and an x-axis title
  gStyle->SetOptStat("e");
  gStyle->SetStatFormat("6.6g");
  hmass_sel2->SetLineColor(kBlue);
  hmass_sel2->GetXaxis()->SetTitle("Mass [MeV/c^{2}]");
  

  //fit
  //Signal = new TF1("Signal", "gaus", 5279.29-40 ,5279.29+50);
  //Background = new TF1("Background", "expo", 5279.29+80, 5700 );
  //total = new TF1("total","gaus(0)+expo(3)",5279.29-40,5700);
  //hmass_sel2->Fit(Signal, "R");
  //hmass_sel2->Fit(Background, "R");
  
  //Double_t par[5];
  //Signal->GetParameters(&par[0]);
  //Background->GetParameters(&par[3]);

  //total->SetParameters(par);
  //hmass_sel2->Fit(total, "R");

  hmass_sel2->Draw();
  //total->Draw("same");
  

 
  c10->SaveAs("massB_sel2.pdf");
}
