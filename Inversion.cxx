#if !defined (__CINT__) || defined (__MAKECINT__)
#include <Riostream.h>
#include <TRandom3.h>
#include <TMath.h>
#include <TH1D.h>
#include <TStopwatch.h>
#endif

using namespace TMath;

TH1D* Inversion(Double_t a,Int_t n, Int_t nbins,Int_t seed){
  gRandom->Delete();
  gRandom = new TRandom3(seed);
  Double_t asqrt = Sqrt(a);
  TH1D* hist = new TH1D("Inversion Histogram","Inversion Method Extraction",nbins,0,2*Pi());
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
  
  hist->Scale((2*Pi()/Sqrt(a))/(n*2*Pi()/nbins));
  return hist;
}