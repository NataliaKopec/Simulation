#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
	G4Track *track = aStep->GetTrack();
    track->SetTrackStatus(fStopAndKill);

    auto detX = aStep->GetTrack()->GetPosition().x();
    auto detY = aStep->GetTrack()->GetPosition().y();
    auto detZ = aStep->GetTrack()->GetPosition().z();

    //Get analysis manager
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    //It only works if you have target hit at (0.0,0.0,0.0)
    //since it's X(det) - X(tar), Y(det) - Y(tar)
    //maybe it should be moved to stepping action so that we know position of hit at the target
    //or you can do simple script for postprocessing 
    G4double theta = acos(detZ/sqrt(detX*detX+detY*detY+detZ*detZ))/deg;

    //printf("Detector\n");
    //Fill ntuple
    man->FillNtupleDColumn(4, theta);
    man->FillNtupleDColumn(5, detX);
    man->FillNtupleDColumn(6, detY);
    man->FillNtupleDColumn(7, detZ);
    man->AddNtupleRow();

    /*Energy info about the track, TrackID, Name of Process, Replica Number;
    auto kineticEnergy = track->GetKineticEnergy();
    auto TotalEnergy = track->GetTotalEnergy();
    auto trackID = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    auto processName = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    G4int ReplicaNo = touchable->GetReplicaNumber();
    G4cout << "Replica Number: " << ReplicaNo << G4endl;
    */
   return true;
}
