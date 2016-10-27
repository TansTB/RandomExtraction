#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <TMath.h>
#include <TH1D.h>
#endif
using namespace TMath;
Double_t func(Double_t ,Double_t );
TH1D* ImportanceSampling(Double_t a,Int_t n, Int_t nbins,Int_t seed){
  gRandom->Delete();
  gRandom = new TRandom3(seed);
  Double_t beginning = 0;
  Double_t end = 2*Pi();
  TH1D* hist = new TH1D("Importance Sampling Histogram","Importance Sampling Extraction",nbins,beginning,end);
  const Int_t divisions = 5;
  Double_t m[divisions];
  Double_t u1, u2, xt, yt;
  Double_t maxm=0;
  Int_t counter = 0;
  TStopwatch *timer = new TStopwatch();
  TF1* fun = new TF1("Custom Distribution","1/(sin(x)*sin(x)+[0]*cos(x)*cos(x))",0,2*Pi());
  fun->SetParameter(0,a);
  for(Int_t i=0;i<divisions;i++){
    m[i]=fun->GetMaximum(i*(end-beginning)/divisions,(i+1)*(end-beginning)/divisions);
    maxm = (m[i]>maxm) ? m[i]:maxm ;
  }
  for(Int_t i=0;i<divisions;i++){
    while((counter >= i*((static_cast<double>(n))/divisions))&&(counter<((i+1)*((static_cast<double>(n))/divisions)))){
      u1 = gRandom -> Rndm();
      xt = i*((end-beginning)/divisions) + ((end-beginning)/divisions)*u1;
      u2 = gRandom -> Rndm();
      yt = u2*m[i];
      if (func(a,xt) > yt){
	hist->Fill(xt,m[i]/maxm);
	counter++;
      }
    }
  }
  timer->Stop();
  using namespace std;
  cout << "---------------------------------------" << endl << "Importance Sampling Statistics:" << endl;
  timer->Print("u");
  cout << "---------------------------------------" << endl;
  hist->Scale((2*Pi()/Sqrt(a))/(hist->Integral("width")));
  return hist;
}

// Double_t func(Double_t a, Double_t xx){
// Double_t f = 1./(sin(xx)*sin(xx)+a*cos(xx)*cos(xx));
// return f;
// }