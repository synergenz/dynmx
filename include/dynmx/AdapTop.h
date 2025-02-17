//
//  AdapTop.h
//  dynmx
//
//  Created by Thomas Buhrmann on 09/09/14.
//
//

#ifndef dynmx_AdapTop_h
#define dynmx_AdapTop_h

#include "Topology.h"
#include "AdapNN.h"

namespace dmx
{

// Helper for storing the ranges of parameters
//--------------------------------------------------------------------------------------------------------------------
struct AdapNetLimits
{
  AdapNetLimits() : meanDecay(0,1), noiseVar(-10,10), weightDecay(0,0.1), learnRate(0, 1), synScale(0,1),
                    prePostFac(-1,1), preMeanFac(0,1) {};
  void toXml(ci::XmlTree& xml) const;
  void fromXml(const ci::XmlTree& xml);
  
  Range meanDecay, noiseVar, weightDecay, learnRate, synScale, prePostFac, preMeanFac;
};
  
//----------------------------------------------------------------------------------------------------------------------
// Defines a topology for decoding a neural network
//----------------------------------------------------------------------------------------------------------------------
class AdapTop : public Topology
{
  
public:
  
  virtual ~AdapTop() {};
  
  typedef void (AdapNN::*ConnSetter)(int, int, double);
  
  AdapTop();
  AdapTop(const ci::XmlTree& xml);
  
  virtual void reset(CTRNN* net);
  
  // These are crucial for GA
  virtual int getNumParameters() const;
  virtual bool decode(CTRNN& ctrnn, const double* params);
  virtual bool encode(CTRNN& ctrnn, double* params) const;
  
  virtual void toXml(ci::XmlTree& xml) const;
  virtual void fromXml(const ci::XmlTree& xml);
  
  virtual bool isAdaptive() const { return true; };
  
  bool m_evolveBiases;
  bool m_evolveTaus;
  bool m_evolveSynScaleMode;
  bool m_evolvePrePostFac;
  bool m_evolvePreMeanFac;

protected:
  
  int getNumAdapParams() const;
  void decodeAdap(AdapNN& net, const double* params, int& I);
  void encodeAdap(AdapNN& net, double* params, int& I) const;
  
  bool m_useReward;
  bool m_initialWeights;
  bool m_rulePerConnection;
  bool m_noiseUniform;
  bool m_useAntiHebb;
  std::string m_actFunc;
  AdapNN::SynScaling m_scaling;
  
  AdapNetLimits m_limits;
};
  
}
#endif
