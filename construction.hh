#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4PVReplica.hh"
#include "G4PVDivision.hh"
#include "G4Box.hh"
#include "G4Orb.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VTouchable.hh"
#include "G4GenericMessenger.hh"

#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();

    G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }

    virtual G4VPhysicalVolume *Construct();
    

private:
    G4LogicalVolume *logicDetector1;
    G4LogicalVolume *div_tubeDetector_log;
    G4LogicalVolume *logicDetector2;
    G4LogicalVolume *div_tubeRadialDetector_log;

    
    void DefineMaterials();
    virtual void ConstructSDandField();

    G4int nCols1, nCols2, ndistance1, ndistance2;
    G4GenericMessenger *fMessenger;

    G4LogicalVolume *fScoringVolume;
};

#endif