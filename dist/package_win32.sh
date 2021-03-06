#!/bin/bash
set -e
if ! [ $1 ]; then
  echo "must specify dir name"
  exit 2;
fi


for ARCH in win64; do
PLATFORM=windows
SRC_DIR=../${ARCH}/src/main/Release
#DIST_DIR=devsim_${PLATFORM}_${ARCH}
DIST_DIR=$1_${ARCH}
DIST_BIN=${DIST_DIR}/bin
DIST_DATE=`date +%Y%m%d`
DIST_VER=${DIST_DIR}_${DIST_DATE}
MT_EXE="`cygpath 'c:\Program Files (x86)\Windows Kits\8.1\bin\x64\mt.exe'`"




# make the bin directory and copy binary in
mkdir -p ${DIST_BIN}
cp ${SRC_DIR}/devsim_py.exe ${DIST_BIN}/devsim.exe
cp ${SRC_DIR}/devsim_tcl ${DIST_BIN}/devsim_tcl.exe
##### update the manifest
(cd ${DIST_BIN} &&
"${MT_EXE}" -inputresource:"c:\Anaconda\python.exe;#1" -out:devsim.exe.manifest &&
"${MT_EXE}" -manifest devsim.exe.manifest -outputresource:"devsim.exe;#1"
)







mkdir -p ${DIST_DIR}/doc
cp ../doc/devsim.pdf ${DIST_DIR}/doc
for i in INSTALL NOTICE LICENSE COPYING RELEASE windows.txt; do
cp ../$i ${DIST_DIR}
done


#### Python files and the examples
for i in python_packages examples testing
do
(cd ../$i; git clean -f -d -x )
rsync -aP --delete ../$i ${DIST_DIR}
done



COMMIT=`git rev-parse --verify HEAD`
cat <<EOF > ${DIST_DIR}/VERSION
Package released as:
${DIST_VER}.zip

Source available from:
http://www.github.com/devsim/devsim 
commit ${COMMIT}
EOF



zip -r ${DIST_VER}.zip ${DIST_DIR}
done
