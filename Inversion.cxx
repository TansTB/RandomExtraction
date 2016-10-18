#if !defined (__CINT__) || defined (__MAKECINT__)
#include <Riostream.h>
#include <TRandom3.h>
#include <TMath.h>
#include <TH1I.h>
#include <TStopwatch.h>
#endif

using namespace TMath;

TH1I* Inversion(Double_t a,Int_t n, Int_t nbins,Int_t seed){
  gRandom->Delete();
  gRandom = new TRandom3(seed);
  Double_t asqrt = Sqrt(a);
  TH1I* hist = new TH1I("hist","Inversion Method",nbins,0,2*Pi());
  hist->SetMinimum(0);
  hist->SetFillColorAlpha(38,0.35);
  TStopwatch *timer = new TStopwatch();
  for (Int_t i=0;i<n/4;i++){
    hist->Fill(Abs(ATan(asqrt*Tan(2*Pi()*(gRandom->Rndm())))));
  }
  for (Int_t i=n/4;i<3*n/4;i++){
    hist->Fill(ATan(asqrt*Tan(2*Pi()*(gRandom->Rndm())))+Pi());
  }
  for (Int_t i=3*n/4;i<n;i++){
    hist->Fill(2*Pi()-Abs(ATan(asqrt*Tan(2*Pi()*(gRandom->Rndm())))));
  }
  timer->Stop();
  using namespace std;
  cout << "--------------------------------" << endl << "Inversion Method Statistics:" << endl;
  timer->Print("u");
  cout << "--------------------------------" << endl;
  
  return hist;
}