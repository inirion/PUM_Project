#!/bin/bash

function resizeallfiles {

for file in half_*
do
  rm $file
done

for file in *.png
do
  outfile=half_`basename $file .png`.png
  echo convert -verbose -resize 50% "'$file'" "'$outfile'"
done | gm batch -echo on -feedback on -
}




cd assets/img
resizeallfiles

cd enemy
resizeallfiles
cd ..
cd fx
resizeallfiles
cd ..
cd map
resizeallfiles
cd ..

cd tower
cd coil
resizeallfiles
cd ..
cd emp
resizeallfiles
cd ..
cd gatling
resizeallfiles
cd ..
cd lightcannon
resizeallfiles
cd ..
cd rocketlauncher
resizeallfiles
cd ..
cd ../..