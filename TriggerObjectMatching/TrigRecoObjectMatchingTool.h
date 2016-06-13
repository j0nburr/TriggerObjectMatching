#ifndef TRIGGEROBJECTMATCHING_TRIGRECOOBJECTMATCHINGTOOL_H
#define TRIGGEROBJECTMATCHING_TRIGRECOOBJECTMATCHINGTOOL_H 1

///
///Example usage code:
///Athena only:
///To configure the tool, add the following to your joboptions:
/// myTool = CfgMgr.TrigRecoObjectMatchingTool("ToolInstanceName",Property=4.0)
/// import ROOT
/// myTool.ENumProperty = ROOT.TrigRecoObjectMatchingTool.Val2
///To use the tool in your algorithm (can use regular ToolHandle or asg::AnaToolHandle):
/// #include "TriggerObjectMatching/ITrigRecoObjectMatchingTool.h"
/// ToolHandle<ITrigRecoObjectMatchingTool> myTool("TrigRecoObjectMatchingTool/ToolInstanceName")
/// CHECK( myTool.retrieve() );
/// myTool->isSelected(...); //or whatever methods are implemented in ITrigRecoObjectMatchingTool
///
///Dual use: Alternative for c++ configuration and usage (with or without athena):
/// #include "AsgTools/AnaToolHandle.h"
/// #include "TriggerObjectMatching/ITrigRecoObjectMatchingTool.h"
/// asg::AnaToolHandle<ITrigRecoObjectMatchingTool> myTool("TrigRecoObjectMatchingTool/ToolInstanceName");
/// myTool.setProperty( "Property", 4.0 );
/// myTool.setProperty( "ENumProperty", 
/// myTool.initialize();
/// myTool->isSelected(....); //or whatever methods are implemented in ITrigRecoObjectMatchingTool



#include "AsgTools/AsgTool.h"

#include "TriggerObjectMatching/ITrigRecoObjectMatchingTool.h"



class TrigRecoObjectMatchingTool: public asg::AsgTool, public virtual ITrigRecoObjectMatchingTool { 
 public: 
   //constructor for athena can be created using special macro
   //Note: if you add a second interface to your tool, you must use: ASG_TOOL_CLASS2( ToolName, Interface1, Interface2) 
   ASG_TOOL_CLASS( TrigRecoObjectMatchingTool , ITrigRecoObjectMatchingTool )
   //add another constructor for non-athena use cases
   TrigRecoObjectMatchingTool( const std::string& name );

   /// Initialize is required by AsgTool base class
   virtual StatusCode  initialize() override;

   // Example code: (part of skeleton code, delete as necessary)
   // Following method is required by ITrigRecoObjectMatchingTool base class (part of skeleton code, delete as necessary)
   // DO NOT put default argument values here ... only put them in the interface class
   virtual bool isSelected(const xAOD::IParticle& particle, bool someAdditionalArgument) const override;

 private: 
   double m_nProperty;
   unsigned int m_enumProperty; //do not make the actual property an enum - not supported in athena
}; 

#endif //> !TRIGGEROBJECTMATCHING_TRIGRECOOBJECTMATCHINGTOOL_H
