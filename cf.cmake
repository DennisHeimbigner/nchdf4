# Visual Studio
#VS=1

#CFG="RelWithDebInfo"
CFG=Release

FLAGS="$FLAGS -DCMAKE_INSTALL_PREFIX=`pwd`/ignore"

rm -fr build
mkdir build
cd build

if test "x$VS" != x ; then
# Visual Studio
CFG="Release"
cmake $FLAGS ..
cmake --build . --config ${CFG}
cmake --build . --config ${CFG} --target RUN_TESTS
else
# GCC
G="-GUnix Makefiles"
cmake "${G}" $FLAGS ..
#make all
#make test
fi
exit
