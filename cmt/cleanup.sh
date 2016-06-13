# echo "cleanup TriggerObjectMatching TriggerObjectMatching-00-00-00 in /home/burr/Programs/Projects/DualUse/TriggerObjectMatching"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/atlas.cern.ch/repo/sw/software/AthAnalysisBase/x86_64-slc6-gcc49-opt/2.4.10/CMT/v1r25p20140131; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtTriggerObjectMatchingtempfile=`${CMTROOT}/${CMTBIN}/cmt.exe -quiet build temporary_name`
if test ! $? = 0 ; then cmtTriggerObjectMatchingtempfile=/tmp/cmt.$$; fi
${CMTROOT}/${CMTBIN}/cmt.exe cleanup -sh -pack=TriggerObjectMatching -version=TriggerObjectMatching-00-00-00 -path=/home/burr/Programs/Projects/DualUse/TriggerObjectMatching  $* >${cmtTriggerObjectMatchingtempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/${CMTBIN}/cmt.exe cleanup -sh -pack=TriggerObjectMatching -version=TriggerObjectMatching-00-00-00 -path=/home/burr/Programs/Projects/DualUse/TriggerObjectMatching  $* >${cmtTriggerObjectMatchingtempfile}"
  cmtcleanupstatus=2
  /bin/rm -f ${cmtTriggerObjectMatchingtempfile}
  unset cmtTriggerObjectMatchingtempfile
  return $cmtcleanupstatus
fi
cmtcleanupstatus=0
. ${cmtTriggerObjectMatchingtempfile}
if test $? != 0 ; then
  cmtcleanupstatus=2
fi
/bin/rm -f ${cmtTriggerObjectMatchingtempfile}
unset cmtTriggerObjectMatchingtempfile
return $cmtcleanupstatus

