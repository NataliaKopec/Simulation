#ifndef STEPPING_HH
#define STEPPING_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "globals.hh"

#include "construction.hh"
#include "event.hh"


class MySteppingAction : public G4UserSteppingAction
{
public:
	MySteppingAction(MyEventAction* eventAction);
	~MySteppingAction();

	virtual void UserSteppingAction(const G4Step*);
	  		  void Add(G4double edep,  G4double x, G4double y, G4double z);
  			  void FillPerEvent();

  void Reset();

private:
	  MyEventAction *fEventAction;
	  G4double  fEnergyDep;
    G4double  fxPos;
    G4double  fyPos;
    G4double  fzPos;
    G4bool isItFirstHit = true;
};

inline void MySteppingAction::Add(G4double edep, G4double x, G4double y, G4double z)
{
  fEnergyDep += edep;
  if (isItFirstHit)
  {
    fxPos = x;
    fyPos = y;
    fzPos = z;
    isItFirstHit = false;
  }
}
#endif