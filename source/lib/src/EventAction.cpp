#include "EventAction.h"
#include "RunAction.h"

#include "G4Event.hh"
#include "G4RunManager.hh"


EventAction::EventAction(RunAction* runAction)
: fRunAction(runAction)
{}

void EventAction::BeginOfEventAction(const G4Event*)
{
  fEdep = 0.;
}

void EventAction::EndOfEventAction(const G4Event*)
{
  // accumulate statistics in run action
  fRunAction->AddEdep(fEdep);
}
