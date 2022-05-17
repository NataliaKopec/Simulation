#include "stepping.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
{
	fEventAction = eventAction;
  
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step) // Collect energy and track length step by step
{
  
  // get volume of the current step
  auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

  if (!volume->GetName().compareTo("target"))
  {
    
	  G4double edep = step->GetTotalEnergyDeposit();
    G4double x = step->GetPreStepPoint()->GetPosition().x();
    G4double y = step->GetPreStepPoint()->GetPosition().y();
    G4double z = 0.*mm;//step->GetPreStepPoint()->GetPosition().z();
        
    //G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    //step->GetTrack()->SetTrackStatus(fStopAndKill);
    
    auto analysisManager = G4AnalysisManager::Instance();
    
    analysisManager->FillNtupleDColumn(0, edep);
	  analysisManager->FillNtupleDColumn(1, x);
    analysisManager->FillNtupleDColumn(2, y );
    analysisManager->FillNtupleDColumn(3, z);
    //removed theta from here to detector
    // analysisManager->AddNtupleRow();
  }
 }

void MySteppingAction::Reset()
{
	fEnergyDep = 0.0;
	fxPos = 0.0;
	fyPos = 0.0;
	fzPos = 0.0;
	isItFirstHit = true;
}


