#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
	fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");


    fMessenger->DeclareProperty("nCols1", nCols1, "Number of parts of I detector");
    fMessenger->DeclareProperty("nCols2", nCols2, "Number of parts of II detector");
    fMessenger->DeclareProperty("distance1", ndistance1, "Distance I detector from target");
    fMessenger->DeclareProperty("distance2", ndistance2, "Distance II detector from target");

    nCols1 = 64;
    nCols2 = 32;

    ndistance1 = -3.03*cm;
    ndistance2 = -3.0301*cm;
}

MyDetectorConstruction::~MyDetectorConstruction()
{}


G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    //Get nist material manager
    G4NistManager *nist = G4NistManager::Instance();
/*
    G4double atomicNumber = 1.;
    G4double massOfMole = 1.008*g/mole;
    G4double density = 1.e-25*g/cm3;
    G4double temperature = 2.73*kelvin;
    G4double pressure = 3.e-15*pascal;
    G4Material* Vacuum = new G4Material("interGalactic", atomicNumber, massOfMole, density, kStateGas, temperature, pressure);

    //Material of Detectors
    G4double zSi = 14;
    G4double aSi = 28;
    G4double densitySi = 2.33*g/cm3;
    G4Material* Si = new G4Material("Silicon", zSi, aSi, densitySi);

    //Material of Target
    G4double zPb = 82;
    G4double aPb = 207;
    G4double densityPb = 0.001*g/cm3;
    G4Material* Pb = new G4Material("Lead", zPb, aPb, densityPb);
*/
    G4Material *matLead = nist->FindOrBuildMaterial("G4_Pb");
    G4Material *matVacuum = nist->FindOrBuildMaterial("G4_Galactic");
    G4Material *matSi = nist->FindOrBuildMaterial("G4_Si");


    //World
    G4Orb*solidWorld = new G4Orb("solidWorld", 9.5*cm);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, matVacuum, "lodicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    //Target
    G4double tube_dPhi_target = 2.* M_PI * rad;
    G4Tubs*solidTarget = new G4Tubs("solidTarget", 0.*cm, 2.8*cm, 0.88*micrometer, 0., tube_dPhi_target);
    G4LogicalVolume *logicTarget = new G4LogicalVolume(solidTarget, matLead, "logicTarget");
    G4VPhysicalVolume *physTarget = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.*m), logicTarget, "physTarget", logicWorld, false, 0, true);


    //Detector1
    G4double tube_dPhi_detector = 2.* M_PI * rad;
    G4Tubs*tubeDetector = new G4Tubs("tubeDetector", 2.8*cm, 8.3*cm, 0.1*cm, 0., tube_dPhi_detector);
    logicDetector1 = new G4LogicalVolume(tubeDetector, matSi, "logicDetector1", 0, 0, 0);
    G4VPhysicalVolume *physDetector1 = new G4PVPlacement(0, G4ThreeVector(0., 0., ndistance1), logicDetector1, "physDetector1", logicWorld, false, 0, true);
    fScoringVolume = logicDetector1;

    G4double divided_tube_dPhi_detector = tube_dPhi_detector/nCols1;
    G4Tubs*div_tubeDetector = new G4Tubs("div_tube", 2.8*cm, 8.3*cm, 0.1*cm, -divided_tube_dPhi_detector/2., divided_tube_dPhi_detector);
    div_tubeDetector_log = new G4LogicalVolume(div_tubeDetector, matSi, "div_logicDetector1");
    G4VPhysicalVolume *div_tubeDetector_phys = new G4PVReplica("div_tubeDetector_phys", div_tubeDetector_log, logicDetector1, kPhi, nCols1, divided_tube_dPhi_detector);

    
    //Detector2
    G4double tube_dRadial_detector = 2.* M_PI * rad;
    G4Tubs*tubeRadialDetector = new G4Tubs("tubeRadialDetector", 2.8*cm, 8.3*cm, 0.1*cm, 0., tube_dRadial_detector);
    logicDetector2 = new G4LogicalVolume(tubeRadialDetector, matSi, "logicDetector2");
    G4VPhysicalVolume *physDetector2 = new G4PVPlacement(0, G4ThreeVector(0., 0., ndistance2), logicDetector2, "physDetector2", logicWorld, false, 0, true);
    fScoringVolume = logicDetector1;
    
    G4double divided_tube_dRadial_detector = tube_dRadial_detector/nCols2;
    G4Tubs*div_tubeRadialDetector = new G4Tubs("div_tube_Radial", 2.8*cm, 8.3*cm, 0.1*cm, -divided_tube_dRadial_detector/2., divided_tube_dRadial_detector);
    div_tubeRadialDetector_log = new G4LogicalVolume(div_tubeRadialDetector, matSi, "div_logicDetector2", 0, 0, 0);
    G4VPhysicalVolume *div_tubeRadialDetector_phys = new G4PVDivision("div_tubeRadialDetector_phys", div_tubeRadialDetector_log, logicDetector2, kRho, nCols2, divided_tube_dRadial_detector);  
    

    return physWorld;   
}

void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

    div_tubeDetector_log->SetSensitiveDetector(sensDet);
    div_tubeRadialDetector_log->SetSensitiveDetector(sensDet);
}

