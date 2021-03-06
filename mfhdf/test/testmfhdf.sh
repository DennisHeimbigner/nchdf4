#! /bin/sh
# Tests for the hdiff tool

srcdir=.

CMP='cmp -s'
DIFF='diff -c'

nerrors=0
verbose=yes

# Print message with formats according to message level ($1)
MESG() {
  level=$1
  shift
  case $level in
    0)
      echo '============================='
      echo $*
      echo '============================='
      ;;
    3)
      echo '-----------------------------'
      echo $*
      echo '-----------------------------'
      ;;
    6)
      echo "*** $* ***"
      ;;
    *)
      echo "MESG(): Unknown level ($level)"
      exit 1
      ;;
  esac
}


# Report the result and exit
FINISH()
{
    if [ $nerrors -eq 0 ]
    then
        MESG 0 "All mfhdf tests passed"
    else
        MESG 0 "mfhdf tests failed: $nerrors"
    fi
    exit $nerrors
}

# Print a line-line message left justified in a field of 70 characters
# beginning with the word "Testing".
#
TESTING() {
   SPACES="                                                               "
   echo "Testing $* $SPACES" | cut -c1-70 | tr -d '\012'
}

# Run a test and print PASS or *FAIL*.  If a test fails then increment
# the `nerrors' global variable
#
RUN() {
   # Run test.
   # Tflops interprets "$@" as "" when no parameter is given (e.g., the
   # case of missing file name).  Changed it to use $@ till Tflops fixes it.

   MESG 0 "HDF-SD C interface tests"
   ${TESTS_ENVIRONMENT} ./hdftest
   RET=$?
   if [ $RET -eq 1 ]; then
      echo "*FAILED*"
      nerrors="`expr $nerrors + 1`"
   fi
   
   MESG 0 "HDF-nc C interface tests"
   ${TESTS_ENVIRONMENT} ./hdfnctest
   RET=$?
   if [ $RET -eq 1 ]; then
      echo "*FAILED*"
      nerrors="`expr $nerrors + 1`"
   fi
   
   MESG 0 "netCDF formatted tests"
   ${TESTS_ENVIRONMENT} ./cdftest > cdfout.new
   cmd="$DIFF cdfout.new $srcdir/testout.sav";                \
   echo $cmd;                                                   \
   if $cmd; then                                                \
      echo "*** netCDF passes formatted test ***";                \
   else                                                          \
      echo "*** netCDF fails formatted test ***";                 \
      echo "The above differences are OK if small"
   fi
}

##############################################################################
###                       T H E   T E S T S                                ###
##############################################################################

# Print a beginning banner
MESG 0 "Running mfhdf tests"

# compare output
RUN

# End of test, return exit code
FINISH
    
