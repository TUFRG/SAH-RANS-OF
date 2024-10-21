#!/bin/bash

set -e

cd incompressible
wclean
wmakeLnInclude -u ../turbulenceModels
wmake

cd ..

cd compressible
wclean
wmakeLnInclude -u ../turbulenceModels
wmake
