#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <TMath.h>
#include <TH1D.h>
#endif
using namespace TMath;
Double_t func(Double_t ,Double_t );
TH1D* Rejection(Double_t a,Int_t n, Int_t nbins,Int_t seed){
  gRandom->Delete();
  gRandom = new TRandom3(seed);
  Double_t beginning = 0;
  Double_t end = 2*Pi();
  TH1D* hist = new TH1D("Rejection Histogram","Rejection Method Extraction",nbins,beginning,end);
  TStopwatch *timer = new TStopwatch();
  Double_t m = 2;
  Double_t u1, u2, xt, yt;
  Int_t counter = 0;
  while(counter < n){
    u1 = gRandom -> Rndm();
    u2 = gRandom -> Rndm();
    xt = beginning + (end - beginning)*u1;
    yt = m*u2;
    if (func(a,xt) > yt){
      hist->Fill(xt);
      counter++;
    }
  }
  timer->Stop();
  using namespace std;
  cout << "--------------------------------" << endl << "Rejection Method Statistics:" << endl;
  timer->Print("u");
  cout << "--------------------------------" << endl;
  hist->Scale((2*Pi()/Sqrt(a))/(n*2*Pi()/nbins));
  return hist;
}

Double_t func(Double_t a, Double_t xx){
Double_t f = 1/(sin(xx)*sin(xx)+a*cos(xx)*cos(xx));
return f;
} 

