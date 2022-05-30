#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}


G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    //Get nist material manager
    G4NistManager *nist = G4NistManager::Instance();
    G4Material *matVacuum = nist->FindOrBuildMaterial("G4_Galactic");
    G4Material *matSi = nist->FindOrBuildMaterial("G4_Si");
    G4Material *matPb = nist->FindOrBuildMaterial("G4_Pb");

    //World
    G4Orb *solidWorld = new G4Orb("solidWorld", 9.5*cm);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, matVacuum, "logWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(   0,
                                                        G4ThreeVector(0.0, 0.0, 0.0),
                                                        logicWorld,
                                                        "physWorld",
                                                        0,          //mother log vol
                                                        false,      //is many?
                                                        0,          //copyNo
                                                        true);      //SurfCheck


    //Target
    G4Tubs *solidTarget = new G4Tubs(   "solidTarget",
                                        0.0*mm,     //inner radius
                                        28*mm,      //outer radius
                                        0.01*mm,    //half thickness
                                        0.0,        //starting angle
                                        2.0 * M_PI);//ending angle
    G4LogicalVolume *logicTarget = new G4LogicalVolume(solidTarget, matPb, "logicTarget");
    new G4PVPlacement(  0,
                        G4ThreeVector(0., 0., 0.*mm),
                        logicTarget,
                        "physTarget",
                        logicWorld,          //mother log vol
                        false,      //is many?
                        0,          //copyNo
                        true);      //SurfCheck

 
    //Detector case
    G4double detThickness = 0.03*mm;
    G4Tubs *solidDet = new G4Tubs(   "tubeDetector",
                                            28*mm,
                                            83*mm,
                                            detThickness/2.0,    //half thickness
                                            0.0,                 //starting angle
                                            2.0 * M_PI);         //ending angle

   G4LogicalVolume *logDet = new G4LogicalVolume(solidDet, matVacuum, "logDet");

    G4ThreeVector vDetPosition(0.0, 0.0, -(30.0+detThickness/2.0));
    new G4PVPlacement(  0,
                        vDetPosition,
                        logDet,
                        "physDet",
                        logicWorld,          //mother log vol
                        false,               //is many?
                        0,                   //copyNo
                        true);               //SurfCheck
    logDet->SetVisAttributes(G4VisAttributes::GetInvisible());

    G4Tubs *solidSector = new G4Tubs("solidSector",
                                            28*mm,
                                            83*mm,
                                            detThickness/2.0,    //half thickness
                                            0.0,                 //starting angle
                                            2.0 * M_PI/32.0);         //ending angle

    G4LogicalVolume *logSector = new G4LogicalVolume(solidSector, matVacuum, "logSector");

    
    G4RotationMatrix *sectorRotMtrx = new G4RotationMatrix();

    for (int sectorNo = 0; sectorNo < 32; sectorNo++)
    {
        sectorRotMtrx->rotateZ(11.25*deg);
        G4Transform3D transform(*sectorRotMtrx, G4ThreeVector(0.0, 0.0, 0.0));
           
        new G4PVPlacement(  transform,
                            logSector,
                            "physSector",
                            logDet,          //mother log vol
                            true,               //is many?
                            sectorNo,                   //copyNo
                            true);               //SurfCheck
        
    }
    


    G4Tubs *solidRings = new G4Tubs("solidRings",
                                    28*mm,
                                    83*mm,
                                    detThickness/2.0,    //half thickness
                                    0.0,                 //starting angle
                                    2.0 * M_PI/32.0);         //ending angle
    
    logRings = new G4LogicalVolume(solidRings, matSi, "solidRings");
    
    new G4PVDivision(   "rings",
                        logRings,
                        logSector,
                        kRho,
                        32,
                        0);
    return physWorld;   
}

void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

    logRings->SetSensitiveDetector(sensDet);
}

