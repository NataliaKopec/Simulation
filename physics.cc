#include "physics.hh"
#include "EMphysics.hh"

#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"

#include "G4LossTableManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4EmParameters.hh"

#include "G4Gamma.hh"
// Bosons
#include "G4Electron.hh"
#include "G4Positron.hh"


// Baryons
#include "G4Proton.hh"
#include "G4AntiProton.hh"
#include "G4Neutron.hh"
#include "G4AntiNeutron.hh"

// Nuclei
#include "G4Deuteron.hh"
#include "G4Triton.hh"
#include "G4Alpha.hh"
#include "G4GenericIon.hh"

MyPhysicsList::MyPhysicsList() : G4VModularPhysicsList(), fEmPhysicsList(nullptr), fEmName("")
{    
  AddPhysicsList("local");
  
  G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(100*eV,1*GeV);

}

MyPhysicsList::~MyPhysicsList()
{}

void MyPhysicsList::ConstructParticle()
{
// gamma
  G4Gamma::GammaDefinition();

// leptons
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();


// barions
  G4Proton::ProtonDefinition();
  G4Neutron::NeutronDefinition();

// ions
  G4Deuteron::DeuteronDefinition();
  G4Triton::TritonDefinition();
  G4Alpha::AlphaDefinition();
  G4GenericIon::GenericIonDefinition();
}


void MyPhysicsList::ConstructProcess()
{
  // Transportation
  AddTransportation();

  // Electromagnetic physics list
  fEmPhysicsList->ConstructProcess();
}

void MyPhysicsList::AddPhysicsList(const G4String& name)
{
  fEmPhysicsList = new PhysListEmStandard(name);
  //
  G4EmParameters::Instance()->SetBuildCSDARange(true);    
  G4EmParameters::Instance()->SetGeneralProcessActive(false);
}