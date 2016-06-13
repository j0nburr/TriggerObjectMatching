// TriggerObjectMatching includes
#include "TriggerObjectMatching/TrigRecoObjectMatchingTool.h"



TrigRecoObjectMatchingTool::TrigRecoObjectMatchingTool( const std::string& name ) : asg::AsgTool( name ){

  declareProperty( "Property", m_nProperty = 3.0 , "Please describe the property here"); //example property declaration with it's default value
  declareProperty( "ENumProperty", m_enumProperty = Val1 , "Please define enums inside your classes, not just in namespaces" );
}


StatusCode TrigRecoObjectMatchingTool::initialize() {
  ATH_MSG_INFO ("Initializing " << name() << "...");
  //
  //Make use of the property values to configure the tool
  //Tools should be designed so that no method other than setProperty is called before initialize
  //

  return StatusCode::SUCCESS;
}

//
//the lines below for the example interface method implementation
//This example is for a tool that selects particles with |eta| < "Property" value .. using 'someAdditionalArgument' to flip the cut
//
bool TrigRecoObjectMatchingTool::isSelected( const xAOD::IParticle& particle , bool someAdditionalArgument ) const {
   if(someAdditionalArgument) return ( fabs(particle.eta()) >= m_nProperty );
   return ( fabs(particle.eta()) < m_nProperty );
}



