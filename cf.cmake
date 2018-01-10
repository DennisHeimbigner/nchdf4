VS=1 #default
CP=1 #default
for var in "$@" ; do
case "$var" in
vs) VS=1 ;; # visual studio
sz|szip) SZIP=1 ;;
linux|nix) unset VS ;;
cp) CP=1 ;;
*) echo "Unknown argument: $var"; exit 1; ;;
esac
done

CFG=Release

FLAGS="$FLAGS -DCMAKE_INSTALL_PREFIX=/tmp/hdf4"
if test "x$SZIP" = x1 ; then
FLAGS="$FLAGS -DENABLE_SZIP"
fi

if test "x$VS" = x1 ; then
PWD=`pwd`
MFHDFLIB="$PWD/build/liblib/Release"
PATH="${MFHDFLIB}:/cygdrive/c/tools/nccmake/bin:/cygdrive/c/tools/nccmake/lib:${PATH}"
export PATH
fi

dobuild() {
if test x$1 = x1 ; then
BLD=build1;
FLAGS="$FLAGS -DCP=on"
else
BLD=build
fi
rm -fr $BLD
mkdir $BLD
cd $BLD
if test "x$VS" != x ; then # Visual Studio
cmake $FLAGS .. >& ./log
cmake --build . --config ${CFG} >& ./b0
#cmake --build . --config ${CFG} --target RUN_TESTS >& ./t
sed -e '/: error/p' -e '/: fatal error/p' -e d <./b0 >> ./warn
sed -e '/: warning.*signed\/unsigned/'d -e '/: warning.*possible loss/d' <./b0 >./b 
sed -e '/: warning/p' -e d <./b >> ./warn
else # GCC
G="-GUnix Makefiles"
cmake "${G}" $FLAGS .. >& ./log
#make all
#make test
fi
cd ..
}

if test x$CP = x1 ; then
dobuild
dobuild 1
else
dobuild
fi
