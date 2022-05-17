#include "run.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
	// Get analysis manager
    G4AnalysisManager *man = G4AnalysisManager::Instance();

	// Open an output file
	G4int runID = run->GetRunID();
    std::stringstream strRunID;
    strRunID << runID;
    
    man->OpenFile("Simulation"+strRunID.str()+".root");
    man->SetVerboseLevel(0);

    // set printing event number per each event
	G4RunManager::GetRunManager()->SetPrintProgress(0);

	// Creating ntuple
	man->CreateNtuple("Hits", "Energy deposition and target and detector vertex");
	man->CreateNtupleDColumn("edep");
	man->CreateNtupleDColumn("X_target");
	man->CreateNtupleDColumn("Y_target");
	man->CreateNtupleDColumn("Z_target");
	man->CreateNtupleDColumn("theta");	
	man->CreateNtupleDColumn("X_detector");
	man->CreateNtupleDColumn("Y_detector");
	man->CreateNtupleDColumn("Z_detector");	
	man->FinishNtuple(0);
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
	// save histograms & ntuple
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->Write();
    man->CloseFile();
}
