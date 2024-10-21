# Spalart-Allmaras turbulence model with Liu et al.'s helicity correction

Originally implemented in OpenFOAM by Zhifan Yu
Updated for more recent OpenFOAM versions by Jeff Defoe
Turbomachinery and Unsteady Flows Research Group
University of Windsor

Implemented for the OpenFOAM .com branch
Tested to work on both v2312 and v2406

Compilation Instructions:
1. Clone repository to a folder.
2. Make the 'compileSAH.sh' Bash script executable (e.g. 'chmod +x compileSAH.sh')
3. Execute the script to compile both incompressible and compressible versions of the model

Compile libraries will be located in $FOAM_USER_LIBBIN

Libraries:

libSAHIncompressibleTurbulenceModel.so

libSAHCompressibleTurbulenceModel.so

Instructions for use:
1. In the system/controlDict file of the case where you want to use the model, add the line:
   
  libs			("libSAHCompressibleTurbulenceModel.so");
  
    or
    
  libs			("libSAHIncompressibleTurbulenceModel.so");
  
2. In the constant/turbulenceProperties file of the case where you want to use the model, put:

   simulationType          RAS;
   
    RAS
   
    {
   
      RASModel            SpalartAllmarasH; // H at the end for "helicity correction"
   
      turbulence          on;
   
      printCoeffs         on;
   
    }
