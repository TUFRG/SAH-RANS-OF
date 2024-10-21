/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
    Copyright (C) 2019-2021 OpenCFD Ltd.
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::RASModels::SpalartAllmarasH

Group
    grpRASTurbulence

Description
    Spalart-Allmaras one-transport-equation linear-eddy-viscosity turbulence
    closure model for incompressible and compressible external flows.

    Required fields
    \verbatim
        nuTilda   | Modified kinematic viscosity [m2/s]
    \endverbatim

    References:
    \verbatim
        Standard model:
            Spalart, P.R., & Allmaras, S.R. (1994).
            A one-equation turbulence model for aerodynamic flows.
            La Recherche Aerospatiale, 1, 5-21.

        Standard model without trip and ft2 terms (tag:R):
            Rumsey, C. (2020).
            The Spalart-Allmaras Turbulence Model.
            Spalart-Allmaras One-Equation Model without ft2 Term (SA-noft2).
            https://turbmodels.larc.nasa.gov/spalart.html#sanoft2
            (Retrieved:12-01-2021).

		This file:
        Modified to include helicity correction:
            Rumsey, C. (2024).
            The Spalart-Allmaras Turbulence Model.
            Spalart-Allmaras One-Equation Model with Velocity Helicity (SA-noft2-Helicity).
            https://turbmodels.larc.nasa.gov/spalart.html#helicity
            (Retrieved:21-10-2024).
    \endverbatim

Usage
    Example by using \c constant/turbulenceProperties:
    \verbatim
    RAS
    {
        // Mandatory entries (unmodifiable)
        RASModel        SpalartAllmarasH;

        // Optional entries (runtime modifiable)
        turbulence      on;
        printCoeffs     on;

        SpalartAllmarasCoeffs
        {
            sigmaNut    0.66666;
            kappa       0.41;
            Cb1         0.1355;
            Cb2         0.622;
            Cw2         0.3;
            Cw3         2.0;
            Cv1         7.1;
            Cs          0.3;
        }
    }
    \endverbatim

Note
  - The model is implemented without the trip-term since the model has almost
    always been used in fully turbulent applications rather than those where
    laminar-turbulent transition occurs.
  - The \c Stilda generation term should never be allowed to be zero or negative
    to avoid potential numerical issues and unphysical results for complex
    flows. To this end, a limiter proposed by Spalart (R:Note-1(b)) is applied
    onto \c Stilda where \c Stilda is clipped at \c Cs*Omega with the default
    value of \c Cs=0.3.
  - The model does not produce \c k, \c epsilon or \c omega. Nevertheless,
    these quantities can be estimated by using an approximate expressions for
    turbulent kinetic energy and dissipation rate reported in (B:Eq. 4.50).

SourceFiles
    SpalartAllmarasH.C

\*---------------------------------------------------------------------------*/

#ifndef Foam_SpalartAllmarasH_H
#define Foam_SpalartAllmarasH_H

#include "RASModel.H"
#include "eddyViscosity.H"
#include "SpalartAllmarasHBase.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace RASModels
{

/*---------------------------------------------------------------------------*\
                      Class SpalartAllmarasH Declaration
\*---------------------------------------------------------------------------*/

template<class BasicTurbulenceModel>
class SpalartAllmarasH
:
    public SpalartAllmarasHBase<eddyViscosity<RASModel<BasicTurbulenceModel>>>
{
    // Private Member Functions

        //- No copy construct
        SpalartAllmarasH(const SpalartAllmarasH&) = delete;

        //- No copy assignment
        void operator=(const SpalartAllmarasH&) = delete;


protected:

    // Protected Member Functions

        //- Return the length scale
        virtual tmp<volScalarField> dTilda
        (
            const volScalarField& chi,
            const volScalarField& fv1,
            const volTensorField& gradU
        ) const;

        virtual void correctNut();


public:

    typedef typename BasicTurbulenceModel::alphaField alphaField;
    typedef typename BasicTurbulenceModel::rhoField rhoField;
    typedef typename BasicTurbulenceModel::transportModel transportModel;


    //- Runtime type information
    TypeName("SpalartAllmarasH");


    // Constructors

        //- Construct from components
        SpalartAllmarasH
        (
            const alphaField& alpha,
            const rhoField& rho,
            const volVectorField& U,
            const surfaceScalarField& alphaRhoPhi,
            const surfaceScalarField& phi,
            const transportModel& transport,
            const word& propertiesName = turbulenceModel::propertiesName,
            const word& type = typeName
        );


    //- Destructor
    virtual ~SpalartAllmarasH() = default;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace RASModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "SpalartAllmarasH.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
