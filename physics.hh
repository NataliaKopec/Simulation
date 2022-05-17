#ifndef PHYSICS_HH
#define PHYSICS_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4DecayPhysics.hh"

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class G4VPhysicsConstructor;

class MyPhysicsList : public G4VModularPhysicsList
{
public:
  public:
    explicit MyPhysicsList();
   ~MyPhysicsList() override;
   
    void ConstructParticle() override;
    void ConstructProcess() override;
    
    void AddPhysicsList(const G4String& name);
    
  private:
    G4VPhysicsConstructor*  fEmPhysicsList;
    G4String                fEmName;
};

#endif