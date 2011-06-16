/*
 *  TestEvolvableCTRNN.h
 *  openDynmx
 *
 *  Created by Thomas Buhrmann on 11/01/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _TEST_EVOLVABLE_CTRNN_
#define _TEST_EVOLVABLE_CTRNN_

#include "GARunner.h"
#include "CTRNN.h"

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class TestEvolvableCTRNN : public dmx::Evolvable
{
public:

  TestEvolvableCTRNN(int numNeurons = 1) : m_fitness(0.0), m_numSteps(0)
  {
    m_ctrnn = new CTRNN(numNeurons);
    reset();
  };
  
  ~TestEvolvableCTRNN() { delete m_ctrnn; };

  // inherited from ofxEvolvable 
  virtual int getNumGenes();
  virtual void decodeGenome(const double* genome);
  virtual float getFitness();
  virtual void update(float dt);
  virtual void reset();
  
  CTRNN* m_ctrnn;
  float m_fitness;
  int m_numSteps;
};

//----------------------------------------------------------------------------------------------------------------------
// Implementation right here in header file
//----------------------------------------------------------------------------------------------------------------------
int TestEvolvableCTRNN::getNumGenes() 
{ 
  return m_ctrnn->getNumRequiredParams(m_ctrnn->getSize(), 0); 
}

//----------------------------------------------------------------------------------------------------------------------
void TestEvolvableCTRNN::decodeGenome(const double* g)
{
  m_ctrnn->decodeGenome(g, 0);
}

//----------------------------------------------------------------------------------------------------------------------
float TestEvolvableCTRNN::getFitness()
{
  float fitness = 1.0 - fabs(0.5 - m_fitness / m_numSteps); 
  return fitness;
}

//----------------------------------------------------------------------------------------------------------------------
void TestEvolvableCTRNN::update(float dt)
{
  m_ctrnn->update(dt);
  
  // update fitness information
  float avgOutput = 0.0f;
  for(int i = 0; i < m_ctrnn->getSize(); i++)
  {
    avgOutput += m_ctrnn->getOutput(i);
  }
  avgOutput /= m_ctrnn->getSize();
  m_fitness += avgOutput;
  
  m_numSteps++;
};

//----------------------------------------------------------------------------------------------------------------------
void TestEvolvableCTRNN::reset()
{
  m_fitness = 0.0;
  m_numSteps = 0;
  m_ctrnn->randomizeState(-0.01, 0.01);
};

//----------------------------------------------------------------------------------------------------------------------
#endif