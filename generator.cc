#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{ 

    fParticleGun = new G4ParticleGun(1);
    particleTable = G4ParticleTable::GetParticleTable();
    iontable = G4IonTable::GetIonTable();
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{ 
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    G4ParticleDefinition *defBeamParticle = iontable->GetIon(20,40);
    G4ThreeVector pos(0.,0.,-0.095*m);
    G4ThreeVector mom(0.,0.,1.);
    fParticleGun->SetParticleEnergy(170.0*MeV);
    fParticleGun->SetParticleDefinition(defBeamParticle);
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->GeneratePrimaryVertex(anEvent);
}

