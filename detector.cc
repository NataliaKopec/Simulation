#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    G4Track *track = aStep->GetTrack();
    track->SetTrackStatus(fStopAndKill);

    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

    auto detX = aStep->GetTrack()->GetPosition().x();
    auto detY = aStep->GetTrack()->GetPosition().y();
    auto detZ = aStep->GetTrack()->GetPosition().z();

    auto momX = aStep->GetTrack()->GetMomentum().x();
    auto momY = aStep->GetTrack()->GetMomentum().y();
    auto momZ = aStep->GetTrack()->GetMomentum().z();

    //Get analysis manager
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    //It only works if you have target hit at (0.0,0.0,0.0)
    //since it's X(det) - X(tar), Y(det) - Y(tar)
    //maybe it should be moved to stepping action so that we know position of hit at the target
    //or you can do simple script for postprocessing 
    G4double theta = acos(detZ/sqrt(detX*detX+detY*detY+detZ*detZ))/deg;

    //	Energy deposit
    auto edep = aStep->GetTotalEnergyDeposit();
    if (edep==0.) return true;

    auto kineticEnergy = track->GetKineticEnergy();
    auto TotalEnergy = track->GetTotalEnergy();
    auto trackID = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    auto processName = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();

    G4StepPoint* preStep = aStep->GetPreStepPoint();
    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
    G4int sectorNo = touchable->GetReplicaNumber();
    //G4cout << "sectorNo: " << sectorNo << G4endl;

    //printf("Detector\n");
    //Fill ntuple
    man->FillNtupleDColumn(3, theta);
    man->FillNtupleDColumn(4, detX);
    man->FillNtupleDColumn(5, detY);
    man->FillNtupleDColumn(6, detZ);
    man->FillNtupleDColumn(7, momX);
    man->FillNtupleDColumn(8, momY);
    man->FillNtupleDColumn(9, momZ);
    man->FillNtupleDColumn(10, edep);
    man->FillNtupleDColumn(11, kineticEnergy);
    man->FillNtupleDColumn(12, TotalEnergy);
    man->FillNtupleDColumn(13, sectorNo);
    man->AddNtupleRow();

   return true;
}
