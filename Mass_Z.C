//----------------------------
// ** This code calculate the mass of the Z boson using the data of its decay to double muons
// ** We work on the CMS, it means that the 4-momentum of the muon is P_{\mu_{+}} = (M_Z/2 , \vec{0}) because
// the En = M_Z/2, where En is the energy of the \mu_{+}
//----------------------------


void Mass_Z() {

  TH1F *hist1 = new TH1F("hist1", "hist1", 100, -200., 200.0);
  TH1F *hist2 = new TH1F("hist2", "hist2", 100, -200., 200.0);
  TH1F *hist3 = new TH1F("hist3", "hist3", 100, -200., 200.0);
  TH1F *hist4 = new TH1F("P_Z", "Momentum of Z boson", 100, -200., 1000.0);
  TH1F *hist5 = new TH1F("M_Z", "Masse of Z boson", 100, -100., 1000.);

  TFile *f = new TFile("ntuple_array.root");
  TTree *t1 = (TTree*)f->Get("ntupleProducer/tree;1");

  Float_t muonPx,muonPy,muonPz,En,P_mu,M_Z(91.),deltaMZ(10.);

  t1->SetBranchAddress("muonPx",&muonPx);
  t1->SetBranchAddress("muonPy",&muonPy);
  t1->SetBranchAddress("muonPz",&muonPz);

  Int_t nentries = (Int_t)t1->GetEntries();

  for (Int_t i = 0; i<nentries; i++) {
    t1->GetEntry(i);

    hist1->Fill(muonPx);
    hist1->Fill(muonPy);
    hist1->Fill(muonPz);
    En = sqrt(muonPx*muonPx+muonPy*muonPy+muonPz*muonPz);
    P_mu = sqrt(En*En+muonPx*muonPx+muonPy*muonPy+muonPz*muonPz);
    hist4->Fill(P_mu);
    if(abs(2*En-M_Z) <= deltaMZ){
    hist5->Fill(2*En);
    }
  
  }
  TCanvas *c1 = new TCanvas();
  hist4->GetXaxis()->SetTitle("Momentum of Z boson");
  hist4->Draw();
  hist4->SetFillColor(kBlue-9);
  c1->SaveAs("P_Z.pdf");

  TCanvas *c2 = new TCanvas();
  hist5->GetXaxis()->SetTitle("Masse of Z boson");
  hist5->Draw();
  hist5->SetFillColor(kBlue-9);
  c2->SaveAs("Mass_Z.pdf");

  //TF1 *fit = new TF1("lissage", "gaus", 81., 101.);
  //hist5->Fit("lissage");

  
  f->Close();
}

