#include "ParticleType.h"
#include "ResonanceType.h"
#include "Particle.h"
#include "TRandom.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TStyle.h"
#include <iostream> 

using namespace std;
void generate () {


Particle::AddParticleType("pione+",0.13957,1.0);
Particle::AddParticleType("pione-",0.13957,-1.0);
Particle::AddParticleType("kaone+",0.49367,1.0);
Particle::AddParticleType("kaone-",0.49367,-1.0);
Particle::AddParticleType("protone+",0.93827,1.0);
Particle::AddParticleType("protone-",0.93827,-1.0);
Particle::AddParticleType("k*",0.89166,0,0.050);

//creazione degli istogrammi e impostazioni di cosmetica

TFile* file = new TFile("histograms.root", "recreate");

//Particle types

TH1F* TypeParticles = new TH1F("Particle types", "Particle types", 7, 0, 7);
TypeParticles -> SetFillColor(46);
TypeParticles->SetLineColor(kBlue);
TypeParticles->SetMarkerStyle(20);
TypeParticles-> GetXaxis()-> SetTitle("Distribution of Generated Particles");
TypeParticles-> GetYaxis()-> SetTitle("Occorrenze");

//Phi Distribution

TH1F* PhiDistribution = new TH1F("Phi distribution", "Phi distribution", 1000, 0, 2*M_PI);
PhiDistribution -> SetFillColor(5);
PhiDistribution -> GetXaxis()-> SetTitle("Phi");
PhiDistribution -> GetYaxis()-> SetTitle("Occorrenze");

//Theta Distribution

TH1F* ThetaDistribution = new TH1F("Theta distribution", "Theta distribution", 1000, 0, M_PI);
ThetaDistribution -> SetFillColor(46);
ThetaDistribution -> GetXaxis() -> SetTitle("Theta");
ThetaDistribution -> GetYaxis() -> SetTitle("Occorrenze");

//Impulse Distribution

TH1F* PDistribution = new TH1F("Impulse distribution", "Impulse distribution", 1000, 0,10);
PDistribution->SetFillColor(46);
PDistribution -> GetXaxis()-> SetTitle("P Module");
PDistribution -> GetYaxis()-> SetTitle("Occorrenze");

//Transverse P

TH1F* TransverseP = new TH1F("Transverse impulse distribution", "Transverse impulse distribution", 1000, 0, 5);
TransverseP -> SetFillColor(46);
TransverseP -> GetXaxis() -> SetTitle("Transverse P");
TransverseP -> GetYaxis() -> SetTitle("Occorrenze");

//Energy 

TH1F* Energy = new TH1F("Energy distribution", "Energy distribution",1000, 0, 6);
Energy -> SetFillColor(46);
Energy -> GetXaxis() -> SetTitle("Energia delle particelle generate");
Energy -> GetYaxis() -> SetTitle("Occorrenze");

//Inv Mass

TH1F* InvMass = new TH1F("Inv mass distribution", "Inv mass distribution",100, 0, 2.5);
InvMass -> SetFillColor(46);
InvMass -> GetXaxis() -> SetTitle("Invariant Mass");
InvMass -> GetYaxis() -> SetTitle("Occorrenze");

//Inv Mass discordant charge

TH1F* OInvMass = new TH1F("Inv mass distribution discordant charge ","Inv mass distribution discordant charge",100, 0,6 );
OInvMass -> SetFillColor(46);
OInvMass -> GetXaxis() -> SetTitle("Invariant Mass ");
OInvMass -> GetYaxis() -> SetTitle("Occorrenze");

//Inv Mass same charge

TH1F* SInvMass = new TH1F("Inv mass distribution concordant charge ","Inv mass distribution concordant charge",100, 0,6 );
SInvMass -> SetFillColor(46);
SInvMass -> GetXaxis() -> SetTitle("Invariant Mass");
SInvMass -> GetYaxis() -> SetTitle("Occorrenze");

//Invariant Mass for pi+/k- and pi-/K+ Particles

TH1F* h10 = new TH1F("Inv mass distribution (Pione-Kaone discordant) ","Inv mass (Pione-Kaone discordant) ",100, 0,2.5);
h10 -> SetLineColor(kRed);
h10 -> GetXaxis() -> SetTitle("Invariant Mass");
h10 -> GetYaxis() -> SetTitle("Occorrenze");

//Invariant Mass for pi+/k+ and pi-/K- Particles

TH1F* h11 = new TH1F("Inv mass distribution (Pione-Kaone concordant) ","Inv mass distribution (Pione-Kaone concordant)",100, 0, 2.5 );
h11 -> SetLineColor(kRed);
h11 -> GetXaxis() -> SetTitle("Invariant Mass");
h11 -> GetYaxis() -> SetTitle ("Occorrenze");

//Invariant Mass for Decay

TH1F* HDecay = new TH1F("Inv mass distribution K* decay", "Inv mass distribution K* decay",500, 0.6, 1.2);
HDecay -> SetLineColor(kRed);
HDecay -> GetXaxis()-> SetTitle("Invariant Mass");
HDecay -> GetYaxis()-> SetTitle("Occorrenze");


//Fine creazione grafici e cosmetica





Particle particles [120];
int k, decayedparticles;
     
     for (int i= 0; i < 100000; i++){
          k=99; //posizione delle particelle decadute nell'array
          decayedparticles=0; //numero di particelle decadute
          for(int j = 0; j < 100; j++) {
               double phi = gRandom -> Uniform (0, 2*M_PI);
               PhiDistribution->Fill(phi);
               double theta = gRandom -> Uniform (0, M_PI);
               ThetaDistribution->Fill(theta);
               double P = gRandom -> Exp(1);
               
               //grazie alle coordinate cilindriche trasformo p in px, py, pz
               double Px = P*sin(theta)*cos(phi);
               double Py = P*sin(theta)*sin(phi);
               double Pz = P*cos(theta);
               PDistribution->Fill(sqrt(pow(Px,2)+pow(Py,2)+pow(Pz,2)));
               TransverseP->Fill(sqrt(Px*Px + Py*Py));
               particles[j].SetP(Px,Py,Pz);
               
               //genero le particelle secondo definite proporzioni

               double num_random = gRandom -> Uniform(0,1);
              if (num_random < 0.4)  particles[j].SetIParticle(0);
               else if (num_random < 0.8) particles[j].SetIParticle(1);
               else if (num_random< 0.85) particles[j].SetIParticle(2);
               else if (num_random<0.9) particles[j].SetIParticle(3);
               else if (num_random<0.945) particles[j].SetIParticle(4);
               else if (num_random< 0.99) particles[j].SetIParticle(5);
               else if (num_random<0.995) { 
               
                              particles[j].SetIParticle(6);
                              ++k; 
                              particles[k].SetIParticle(0);
                              particles[k+1].SetIParticle(3);
                              particles[j].decay2body(particles[k], particles[k+1]);
                              HDecay->Fill(particles[k].InvMass(particles[k+1]));
                              ++k;
                              decayedparticles += 2;
               }

               else {         

                              particles[j].SetIParticle(6);
                              ++k;
                              particles[k].SetIParticle(1);
                              particles[k+1].SetIParticle(2);
                              particles[j].decay2body(particles[k], particles[k+1]);
                              HDecay->Fill(particles[k].InvMass(particles[k+1]));
                              ++k;
                              decayedparticles += 2;
               }
                         
               
                    
//Riempio gli istogrammi relativi all'energia e al tipo di particelle generate     
          TypeParticles -> Fill(particles[j].GetIParticle());
          Energy -> Fill(particles[j].GetEnergy());
          }

//Grazie a questo for riempio gli istogrammi delle masse invarianti         
for (int m = 0; m < 100 + decayedparticles; m ++) {
          for (int n = 0; n < m; n ++) {
               InvMass->Fill(particles[m].InvMass(particles[n]));
          
          //controllo se le cariche sono discordi
          if((particles[m].GetCharge()*particles[n].GetCharge())<0){
               //riempio istogramma massa invariante carica discorde
               OInvMass->Fill(particles[m].InvMass(particles[n]));
          }

          //controllo se le cariche sono concordi
          if((particles[m]).GetCharge()*particles[n].GetCharge()>0){
               //riempio istogramma massa invariante carica concorde
               SInvMass->Fill(particles[m].InvMass(particles[n]));
          }
//faccio un controllo e successivamente riempio l'istogramma della massa invariante pione- kaone discordi
          if(((particles[m].GetIParticle()==0) && (particles[n].GetIParticle()==3)) ||
          ((particles[m].GetIParticle()==1)&& (particles[n].GetIParticle()==2)) || 
          ((particles[m].GetIParticle()==3)&& (particles[n].GetIParticle()==0)) || 
          ((particles[m].GetIParticle()==2) && (particles[n].GetIParticle()==1))){  
          h10->Fill(particles[m].InvMass(particles[n]));
          }
//controllo e dopo riempio l'istogramma della massa invariante pione - kaone concordi 
          if(((particles[m].GetIParticle()==0) && (particles[n].GetIParticle()==2)) || 
          ((particles[m].GetIParticle()==1) && (particles[n].GetIParticle()==3))||
          ((particles[m].GetIParticle()==2) && (particles[n].GetIParticle()==0)) ||
          ((particles[m].GetIParticle()==3) && (particles[n].GetIParticle()==1))){
               h11->Fill(particles[m].InvMass(particles[n]));
          }

          }

    }
          
}






//Creo la canvas e inizio l'analisi degli istogrammi

TCanvas *c = new TCanvas("c","Particle,Boost, Theta and Phi Distribution",200,10,600,400);
c->Divide(2,2);

gStyle->SetOptFit(1111); //necessario per visualizzare info sul fit

//operazioni su TypeParticles
c->cd(1);
int confronto[7]={4000000,4000000,500000,500000,450000,450000,100000};
double chi_square=0, chi_reduced=0;
for(int i=1; i<8; i++){
     double binContent= TypeParticles->GetBinContent(i);
     double error= TypeParticles->GetBinError(i);
     cout<<i<<'\n'<< "Content:\t"<<binContent<<'\n'<<"Correct number:\t"<<confronto[i-1]<<'\n'<<'\n'<<"Difference:\t"<<binContent-confronto[i-1]<<'\n'<<"Error:\t"<<error<<'\n';
     chi_square+=pow(binContent-confronto[i-1],2)/confronto[i-1];
}
 TypeParticles->Draw();
//c->Update();
c->Print("output/particlestypes.png");

//Operazioni su PhiDistribution
c->cd(2);
PhiDistribution->Draw();
//fit 
TF1 *f1 = new TF1("f1","[0]",0,2*M_PI);
f1->SetParameter(0,1000);
f1->SetLineColor(kRed);
PhiDistribution-> Fit("f1");
PhiDistribution-> Draw("SAME");
c->Print("output/phi.png");
cout << '\n';
cout << "Risultati del fit di Phi"<< endl;
cout << "Chi quadro" << f1->GetChisquare() << endl;
cout << "DOF:" << f1-> GetNDF() << endl;
cout << "Chi quadro ridotto" << f1 -> GetChisquare()/ f1->GetNDF()<< endl;
cout << "Par0" << f1 -> GetParameter(0) << "+/-" << f1 -> GetParError(0) << endl;


c->cd(3);
ThetaDistribution->Draw();
//fit
TF1 *f2 = new TF1("f2", "[0]", 0, M_PI);
f2 -> SetParameter(0,1000);
f2 -> SetLineColor(kRed);
ThetaDistribution -> Fit("f2");
ThetaDistribution -> Draw("SAME");
c->Print("output/theta.png");
cout << '\n';
cout << "Risultati del fit di Theta"<< endl;
cout << "Chi quadro" << f2->GetChisquare() << endl;
cout << "DOF:" << f2-> GetNDF() << endl;
cout << "Chi quadro ridotto" << f2 -> GetChisquare()/ f2->GetNDF()<< endl;
cout << "Par0" << f2 -> GetParameter(0) << "+/-" << f2 -> GetParError(0) << endl;

c->cd(4);
PDistribution-> Draw();
c->Print("output/Impulse.png");
//fit
TF1 *f3 = new TF1("f3", "[0]*exp(-x/[1])", 0, 10);
f3->SetParameter(0,10000);
f3->SetParameter(1,1);
f3->SetLineColor(kRed);
PDistribution->Fit("f3");
PDistribution->Draw("SAME");
cout << '\n';
cout << "Risultati del fit di P"<< endl;
cout << "Chi quadro" << f3->GetChisquare() << endl;
cout << "DOF:" << f3-> GetNDF() << endl;
cout << "Chi quadro ridotto" << f3 -> GetChisquare()/ f3->GetNDF()<< endl;
cout << "Par1" << f3 -> GetParameter(1) << "+/-" << f3 -> GetParError(1) << endl;


TCanvas *c1 = new TCanvas("c1","c1",200,10,600,400);

c1->Divide(2,2);

c1->cd(1);
TransverseP->Draw();
//c->Update();
c1->Print("output/Transverse_impulse.png");


c1->cd(2);
Energy ->Draw();
//c1->Update();
c1->Print("output/energy.png");



c1->cd(4);
InvMass->Draw();
//c1->Update();
c1->Print("output/invmassdistribution.png");

TCanvas *c2 = new TCanvas("c2","c2",200,10000,600,400);

c2->Divide(2,2);
c2->cd(1);
OInvMass->Draw();
//c1->Update();
c2->Print("output/invmass_Charge_discordant.png");


c2->cd(2);
SInvMass->Draw();
//c1->Update();
c2->Print("output/invmass_charge_concordant.png");


c2->cd(3);
h10->Draw();
//c1->Update();
c2->Print("output/Pione_Kaone_discordant.png");


c2->cd(4);
h11->Draw();
//c1->Update();
c2->Print("output/Pione_Kaone_concordant.png");

TCanvas *c3 = new TCanvas ("K*, Subtract, Subtract2", "K*, Subtract, Subtract2", 200, 10000, 600, 400);
c3 -> Divide(3,1);
c3 -> cd(1);
//operazioni sul grafico della massa invariante delle k*
HDecay -> Draw();
//fit
HDecay->Fit("gaus");
TF1 * f4 = HDecay->GetFunction("gaus");
cout << '\n';
cout << "Risultati del fit della massa invariante delle k*"<< endl;
cout<< "K* media: "<< HDecay -> GetMean() <<endl;
cout << "Sigma:" << HDecay -> GetRMS() << endl;
cout<<"chi quadro ridotto"<< f4-> GetChisquare()/ f4->GetNDF() <<endl;
c3-> Print("output/invmass_k*");

c3 -> cd(2);

//Sottrazione Istogrammi
TH1F * Subtract= new TH1F (*h10); 
Subtract -> Sumw2();
Subtract -> Add(h10, h11, 1.0, -1.0);
Subtract->GetXaxis()-> SetTitle("Mass [GeV/c^2]");
Subtract->GetYaxis()-> SetTitle("Entries");
Subtract->Draw();
Subtract->Fit("gaus");


c3 -> cd(3);
//secondo istogramma di sottrazione 
TH1F * Subtract2 = new TH1F (*OInvMass); 
Subtract2->GetXaxis()-> SetTitle("Mass [GeV/c^2]");
Subtract2->GetYaxis()-> SetTitle("Occorrenze");
Subtract2 -> Sumw2();
Subtract2 -> Add(OInvMass, SInvMass, 1.0, -1.0);
Subtract2->Draw();
Subtract2->Fit("gaus");






file->Write();
//file->Close();




}