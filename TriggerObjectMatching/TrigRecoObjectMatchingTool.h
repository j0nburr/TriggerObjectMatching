#ifndef TRIGGEROBJECTMATCHING_TRIGRECOOBJECTMATCHINGTOOL_H
#define TRIGGEROBJECTMATCHING_TRIGRECOOBJECTMATCHINGTOOL_H 1

#include "AsgTools/AsgTool.h"

#include "TriggerObjectMatching/ITrigRecoObjectMatchingTool.h"
#include "TriggerObjectMatching/IAssociationStrategy.h"


class TrigRecoObjectMatchingTool: public asg::AsgTool, public virtual ITrigRecoObjectMatchingTool { 
  public: 
    //constructor for athena can be created using special macro
    //Note: if you add a second interface to your tool, you must use: ASG_TOOL_CLASS2( ToolName, Interface1, Interface2) 
    ASG_TOOL_CLASS( TrigRecoObjectMatchingTool , ITrigRecoObjectMatchingTool )
    //add another constructor for non-athena use cases
    TrigRecoObjectMatchingTool( const std::string& name );

    /// Initialize is required by AsgTool base class
    virtual StatusCode  initialize() override;

    virtual StatusCode matchObjects(const std::vector<const xAOD::IParticle*>& recoObjects, const xAOD::IParticleContainer* trigObjects, float maxDR = -1.) const override;
  private:
    std::unique_ptr<IAssociationStrategy> m_minSumAssoc;
    float m_maxDR;
    std::string m_auxDataName;
}; 

#endif //> !TRIGGEROBJECTMATCHING_TRIGRECOOBJECTMATCHINGTOOL_H
