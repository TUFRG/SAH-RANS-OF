# SAH-RANS-OF
Spalart-Allmaras turbulence model with Liu et al.'s helicity correction. Originally implemented in OpenFOAM by Zhifan Yu, updated for more recent OpenFOAM versions by Jeff Defoe
Developed by the Turbomachinery and Unsteady Flows Research Group, from the University of Windsor.

## Target Platform
This code is implemented for the OpenFOAM .com branch and is tested to work on both v2312 and v2406.

## Compilation Instructions
1. Clone repository to a folder.
   
3. Make the 'compileSAH.sh' Bash script executable (e.g. 'chmod +x compileSAH.sh')
   
5. Execute the script to compile both incompressible and compressible versions of the model

      Compile libraries will be located in $FOAM_USER_LIBBIN

      Libraries:
      - libSAHIncompressibleTurbulenceModel.so
      - libSAHCompressibleTurbulenceModel.so

## Instructions For Use
1. In the system/controlDict file of the case where you want to use the model, add the line:
   
   ``` 
   libs			("libSAHCompressibleTurbulenceModel.so");
   ```
   or
   ```
   libs			("libSAHIncompressibleTurbulenceModel.so");
   ```
     
2. In the constant/turbulenceProperties file of the case where you want to use the model, put:
   
   ```
   simulationType          RAS;
   
    RAS
   
    {
   
      RASModel            SpalartAllmarasH; // H at the end for "helicity correction"
   
      turbulence          on;
   
      printCoeffs         on;
   
    }
   ```
## Citing

Please cite the following papers, which include the first implemenation and its validation:

Yu, Z, Raza, H, & Defoe, J. "Assessment of Fan Stall Point Identification Ability of Steady RANS Computations With the Helicity-Corrected Spalart-Allmaras Turbulence Model." Proceedings of the ASME Turbo Expo 2023: Turbomachinery Technical Conference and Exposition. Volume 13C: Turbomachinery — Deposition, Erosion, Fouling, and Icing; Design Methods and CFD Modeling for Turbomachinery; Ducts, Noise, and Component Interactions. Boston, Massachusetts, USA. June 26–30, 2023. V13CT32A039. ASME. https://doi.org/10.1115/GT2023-104039

Yu, Zhifan, and Jeff Defoe. "Validation of helicity-corrected Spalart-Allmaras model for corner separation prediction in incompressible flow with OpenFOAM". Journal of the Global Power and Propulsion Society 8 (2024): 73-83. doi:10.33737/jgpps/186057.
