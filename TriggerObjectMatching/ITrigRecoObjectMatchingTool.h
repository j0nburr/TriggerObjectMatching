#ifndef TRIGGEROBJECTMATCHING_ITRIGRECOOBJECTMATCHINGTOOL_H
#define TRIGGEROBJECTMATCHING_ITRIGRECOOBJECTMATCHINGTOOL_H 1

#include "AsgTools/IAsgTool.h"

#include "xAODBase/IParticle.h"
#include "xAODBase/IParticleContainer.h"
#include <vector>

class ITrigRecoObjectMatchingTool : public virtual asg::IAsgTool {
  public:
    ASG_TOOL_INTERFACE( ITrigRecoObjectMatchingTool ) //declares the interface to athena
    // Match trigger objects to a provided set of reco objects. If maxDR is not negative then any returned match with a DR > maxDR
    // will not be used (a null link will be set instead). If maxDR is negative the tool's internal value will be used.
    //
    // The trigObjects will be decorated with an element link to the matched object (if linked)
    virtual StatusCode matchObjects(const std::vector<const xAOD::IParticle*>& recoObjects, const xAOD::IParticleContainer* trigObjects, float maxDR = -1.) const = 0;
};

#endif //> !TRIGGEROBJECTMATCHING_ITRIGRECOOBJECTMATCHINGTOOL_H
