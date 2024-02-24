R__LOAD_LIBRARY(libktracker)
void ana_result(){
	//std::string fname("/darkquest/git_directory/DarkQuest/e1039-analysis/DataHits/macro/result.root");
	std::string fname("/darkquest/data/resulttest.root");
	//std::string fname("/darkquest/data/result_master_Feb24.root");
	std::unique_ptr<TFile> file(TFile::Open(fname.c_str(),"READ"));
	TTree * tree=(TTree*) file->Get("T");
	TBranch * branch=tree->GetBranch("DST.SRecEvent");
	SRecEvent* recevent=new SRecEvent;
	tree->SetBranchStatus("*",false);
	tree->SetBranchStatus("DST.SRecEvent",true);
	tree->SetBranchAddress("DST.SRecEvent",&recevent);
	
	TH1* hntracks=new TH1D("hntracks","NTracks",10,0,10);
	TH1* hndimuons=new TH1D("hndimuons","NDimuons",10,0,10);
	TH1* htrack_chisq=new TH1D("htrack_chisq","Track_chisq",200,0,1000);
	TH1* hdimuon_chisq=new TH1D("hdimuon_chisq","Dimuon_chisq",150,0,450);
	TH1* htrack_pz_vtx=new TH1D("htrack_pz_vtx","Track_pz_vtx",80,0,240);
	TH1* htrack_nhits=new TH1D("htrack_nhits","Track_NHits",10,10,20);
	TH1* hdimuon_z_vtx=new TH1D("hdimuon_z_vtx","Dimuon_z_vtx",100,-500,400);
	TH1* hdimuon_mass=new TH1D("hdimuon_mass","Dimuon_mass",80,0,8);
	//std::cout<<tree->GetEntries()<<std::endl;
	std::vector<SRecTrack> tracks;
	for(int i=0; i<tree->GetEntries();i++){
		tree->GetEntry(i);
		//std::cout<<recevent->getNTracks()<<" ";
		hntracks->Fill(recevent->getNTracks());
		hndimuons->Fill(recevent->getNDimuons());	
		for (int j=0;j<recevent->getNTracks();j++){
			htrack_chisq->Fill(recevent->getTrack(j).get_chisq());
			htrack_pz_vtx->Fill(recevent->getTrack(j).get_mom_vtx().Pz());
			htrack_nhits->Fill(recevent->getTrack(j).getNHits());
		}
		for (int j=0;j<recevent->getNDimuons();j++){
		//std::cout<<"test"<<std::endl;
			hdimuon_chisq->Fill(recevent->getDimuon(j).get_chisq());
			hdimuon_z_vtx->Fill(recevent->getDimuon(j).get_pos().Z());
			hdimuon_mass->Fill(recevent->getDimuon(j).get_mass());
		}
		
	}
	tree->Scan("DST.SRecEvent.fAllTracks.fChisq:DST.SRecEvent.fAllTracks.fVertexMom.fZ");
	TCanvas *canvas1=new TCanvas();
	hntracks->DrawCopy();
	canvas1->Print("NTracks.pdf");
	TCanvas *canvas2=new TCanvas();	
	hndimuons->DrawCopy();
	canvas2->Print("NDimuons.pdf");
	TCanvas *canvas3=new TCanvas();	
	htrack_chisq->DrawCopy();
	gPad->SetLogy(true);
	canvas3->Print("Track_chisq.pdf");
	TCanvas *canvas4=new TCanvas();	
	hdimuon_chisq->DrawCopy();
	gPad->SetLogy(true);
	canvas4->Print("Dimuon_chisq.pdf");
	TCanvas *canvas5=new TCanvas();	
	htrack_pz_vtx->DrawCopy();
	gPad->SetLogy(true);
	canvas5->Print("Track_pz_vtx.pdf");
	TCanvas *canvas6=new TCanvas();	
	htrack_nhits->DrawCopy();
	canvas6->Print("Track_NHits.pdf");
	TCanvas *canvas7=new TCanvas();	
	hdimuon_z_vtx->DrawCopy();
	canvas7->Print("Dimuon_z_vtx.pdf");
	TCanvas *canvas8=new TCanvas();	
	hdimuon_mass->DrawCopy();
	canvas8->Print("Dimuon_mass.pdf");
	tree->Show(0);
	gSystem->Exit(0);
}
