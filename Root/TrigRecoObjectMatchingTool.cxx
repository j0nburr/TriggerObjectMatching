// TriggerObjectMatching includes
#include "TriggerObjectMatching/TrigRecoObjectMatchingTool.h"
#include "FourMomUtils/xAODP4Helpers.h"
#include "AthLinks/ElementLink.h"


TrigRecoObjectMatchingTool::TrigRecoObjectMatchingTool( const std::string& name ) 
  : asg::AsgTool( name )
{
  declareProperty( "MaxDR", m_maxDR = 1.0 );
  declareProperty( "AuxDataName", m_auxDataName = "MatchedRecoObject");
}


StatusCode TrigRecoObjectMatchingTool::initialize() {
  ATH_MSG_INFO ("Initializing " << name() << "...");
  //
  //Make use of the property values to configure the tool
  //Tools should be designed so that no method other than setProperty is called before initialize
  //

  return StatusCode::SUCCESS;
}

StatusCode TrigRecoObjectMatchingTool::matchObjects(const std::vector<const xAOD::IParticle*>& recoObjects, const xAOD::IParticleContainer* trigObjects, float maxDR) const
{
  // We expect the reco objects to be a subset of the trigger objects - can modify in the future if necessary...
  if (recoObjects.size() > trigObjects->size() ) {
    ATH_MSG_ERROR( "More reco objects supplied than trigger objects!" );
    return StatusCode::FAILURE;
  }

  ATH_MSG_DEBUG( "Calculating DRs between the objects" );
  // Calculate the full set of DRs between the reco and the trigger objects
  std::vector<std::vector<double> > recoTrigDRs;
  recoTrigDRs.reserve(recoObjects.size() );
  for (const auto& reco : recoObjects) {
    recoTrigDRs.push_back(std::vector<double>() );
    recoTrigDRs.back().reserve(trigObjects->size() );
    for (const auto& trig : *trigObjects) {
      recoTrigDRs.back().push_back(xAOD::P4Helpers::deltaR(reco, trig) );
    }
  }

  ATH_MSG_DEBUG( "About to match objects" );
  // Match based on the DRs. If the default tool is used then the Munkres (Hungarian) algorithm is used
  auto associationMap = m_minSumAssoc->associate(recoTrigDRs);
  if (maxDR < 0) maxDR = m_maxDR;
  static SG::AuxElement::Decorator<ElementLink<xAOD::IParticleContainer> > dec_link(m_auxDataName);
  for (const auto& matchPair : associationMap) {
    // Make sure the DR is within the threshold
    const xAOD::IParticle* matchedObject = 0;
    if (maxDR < 0 || recoTrigDRs.at(matchPair.first).at(matchPair.second) < maxDR) matchedObject = recoObjects.at(matchPair.first); 
    if (matchedObject) {
      const xAOD::IParticleContainer* container = dynamic_cast<const xAOD::IParticleContainer*>(matchedObject->container() );
      if (!container) {
        ATH_MSG_ERROR( "Failed to retrieve a reco object's container! All the reco objects must come from containers or the element link won't work..." );
        return StatusCode::FAILURE;
      }
      dec_link(*(trigObjects->at(matchPair.first) ) ) = ElementLink<xAOD::IParticleContainer>(*container, matchedObject->index() );
    }
    dec_link(*(trigObjects->at(matchPair.first) ) ) = ElementLink<xAOD::IParticleContainer>(); // Set a null link
  }
  ATH_MSG_DEBUG( "Successfully matched objects!" );
  return StatusCode::SUCCESS;
}
