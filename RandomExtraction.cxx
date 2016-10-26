#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TStyle.h>
#include "Inversion.cxx"
#include "Rejection.cxx"
#endif

using namespace TMath;

int main(){
  gStyle->SetOptStat(0);
//   TStyle* style = new TStyle("MyStyle","Style");
//   style->SetOptStat(0);
//   style->cd();
  Double_t a;
  Int_t n,nbins,seed;
  std::cout << "Inserire il valore di a: ";
  std::cin >> a;  
  std::cout<<std::endl;  
  std::cout << "Inserire il numero di punti da generare: ";
  std::cin >> n;  
  std::cout<<std::endl;  
  std::cout << "Inserire il numero di bin nell'istogramma: ";
  std::cin >> nbins;  
  std::cout<<std::endl;  
  std::cout << "Inserire il seed del generatore di numeri casuali: ";
  std::cin >> seed;  
  std::cout<<std::endl;
  TF1* fun = new TF1("Custom Distribution","1/(sin(x)*sin(x)+[0]*cos(x)*cos(x))",0,2*Pi());
  fun->SetParameter(0,a);
  TH1D* ihist;
  TH1D* rhist;
  ihist = Inversion(a,n,nbins,seed);
  rhist = Rejection(a,n,nbins,seed);
//   gStyle->SetOptStat(0);
  ihist->SetLineColor(kBlue);
  ihist->SetLineColor(kGreen);
  
  TCanvas* c1 = new TCanvas("Random Extraction","RandomExtraction");
  c1->Draw();
  ihist->SetMinimum(0);
  ihist->SetTitle("Random Extraction");
  ihist->Draw("same");
  rhist->Draw("same");
  fun->Draw("same");
  TFile* foo = new TFile("Histos.root","recreate");
  c1->Write();
  foo->Close();
  
  fun->Delete();
  ihist->Delete();
  rhist->Delete();
  return 0;
}