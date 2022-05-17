#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"

//#include "G4AnalysisManager.hh"
#include "g4root.hh"
#include "generator.hh"
#include "run.hh"
#include "event.hh"
#include "stepping.hh"

class MyActionInitialization : public G4VUserActionInitialization
{
public:
    MyActionInitialization();
    ~MyActionInitialization();
    
    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif
