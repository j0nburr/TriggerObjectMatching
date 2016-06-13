# echo "setup TriggerObjectMatching TriggerObjectMatching-00-00-00 in /home/burr/Programs/Projects/DualUse/TriggerObjectMatching"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/atlas.cern.ch/repo/sw/software/AthAnalysisBase/x86_64-slc6-gcc49-opt/2.4.10/CMT/v1r25p20140131
endif
source ${CMTROOT}/mgr/setup.csh
set cmtTriggerObjectMatchingtempfile=`${CMTROOT}/${CMTBIN}/cmt.exe -quiet build temporary_name`
if $status != 0 then
  set cmtTriggerObjectMatchingtempfile=/tmp/cmt.$$
endif
${CMTROOT}/${CMTBIN}/cmt.exe setup -csh -pack=TriggerObjectMatching -version=TriggerObjectMatching-00-00-00 -path=/home/burr/Programs/Projects/DualUse/TriggerObjectMatching  -no_cleanup $* >${cmtTriggerObjectMatchingtempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/${CMTBIN}/cmt.exe setup -csh -pack=TriggerObjectMatching -version=TriggerObjectMatching-00-00-00 -path=/home/burr/Programs/Projects/DualUse/TriggerObjectMatching  -no_cleanup $* >${cmtTriggerObjectMatchingtempfile}"
  set cmtsetupstatus=2
  /bin/rm -f ${cmtTriggerObjectMatchingtempfile}
  unset cmtTriggerObjectMatchingtempfile
  exit $cmtsetupstatus
endif
set cmtsetupstatus=0
source ${cmtTriggerObjectMatchingtempfile}
if ( $status != 0 ) then
  set cmtsetupstatus=2
endif
/bin/rm -f ${cmtTriggerObjectMatchingtempfile}
unset cmtTriggerObjectMatchingtempfile
exit $cmtsetupstatus
