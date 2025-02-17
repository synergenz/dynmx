/*
 *  main.cpp
 *  cinder_dynmx
 *
 *  Created by Thomas Buhrmann on 05/02/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Dynmx.h"
#include "Log.h"
#include "Simulation.h"
#include "SimulationFactory.h"

#include "cinder/cocoa/CinderCocoa.h"

#include <memory>

//----------------------------------------------------------------------------------------------------------------------
int main( int argc, char * const argv[] )
{
    
#if defined( CINDER_COCOA )
  ci::cocoa::SafeNsAutoreleasePool pool;
#endif
  
  // Process command line arguments, if any
  if(argc > 1)
  {
    std::string configFnm = argv[1];
    dmx::Globals::Inst(configFnm);
  }
  
  // Createa a simulation, using the global config file as input
  dmx::Simulation* sim = dmx::SimulationFactory::create();
  
  // Kick off the simulation. If non-visual this returns whenever the model's hasFinished functions returns true.
  // If visual, might run until window is closed. 
  if (sim)
  {
    sim->start();
  }
   
  // Everything went fine apparently.
  return 0;
}

