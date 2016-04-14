// @HEADER
// ************************************************************************
//
//                           Intrepid2 Package
//                 Copyright (2007) Sandia Corporation
//
// Under terms of Contract DE-AC04-94AL85000, there is a non-exclusive
// license for use of this work by or on behalf of the U.S. Government.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact Kyungjoo Kim  (kyukim@sandia.gov), or
//                    Mauro Perego  (mperego@sandia.gov)
//
// ************************************************************************
// @HEADER

/** \file   Intrepid_HCURL_QUAD_I1_FEMDef.hpp
    \brief  Definition file for default FEM basis functions of degree 1 for H(curl) functions on Qadrilateral cells.
    \author Created by P. Bochev, D. Ridzal and K. Peterson.
            Kokkorized by Kyungjoo Kim
*/

#ifndef __INTREPID2_HCURL_QUAD_I1_FEM_DEF_HPP__
#define __INTREPID2_HCURL_QUAD_I1_FEM_DEF_HPP__


namespace Intrepid2 {

  template<typename ExecSpaceType>
  Basis_HCURL_QUAD_I1_FEM<ExecSpaceType>::
  Basis_HCURL_QUAD_I1_FEM()  {
    this->basisCardinality_  = 4;
    this->basisDegree_       = 1;
    this->basisCellTopology_ = shards::CellTopology(shards::getCellTopologyData<shards::Quadrilateral<4> >() );
    this->basisType_         = BASIS_FEM_DEFAULT;
    this->basisCoordinates_  = COORDINATES_CARTESIAN;

    // initialize tags
    {
      // Basis-dependent intializations
      const ordinal_type tagSize  = 4;        // size of DoF tag
      const ordinal_type posScDim = 0;        // position in the tag, counting from 0, of the subcell dim 
      const ordinal_type posScOrd = 1;        // position in the tag, counting from 0, of the subcell ordinal
      const ordinal_type posDfOrd = 2;        // position in the tag, counting from 0, of DoF ordinal relative to the subcell
      
      // An array with local DoF tags assigned to basis functions, in the order of their local enumeration 
      const ordinal_type tags[]  = { 1, 0, 0, 1,
                                     1, 1, 0, 1,
                                     1, 2, 0, 1,
                                     1, 3, 0, 1 };

      // Basis-independent function sets tag and enum data in tagToOrdinal_ and ordinalToTag_ arrays:
      this->setOrdinalTagData(this->tagToOrdinal_,
                              this->ordinalToTag_,
                              tagView,
                              this->basisCardinality_,
                              tagSize,
                              posScDim,
                              posScOrd,
                              posDfOrd);
    }
  }

  
  template<typename ExecSpaceType>
  template<typename outputValueValueType, class ...outputValueProperties,
           typename inputPointValueType,  class ...inputPointProperties,
           typename scratchValueType,     class ...scratchProperties>
  void
  Basis_HCURL_QUAD_I1_FEM<ExecSpaceType>::
  getValues( /**/  Kokkos::DynRankView<outputValueValueType,outputValueProperties...> outputValues,
             const Kokkos::DynRankView<inputPointValueType, inputPointProperties...>  inputPoints,
             const Kokkos::DynRankView<scratchValueType,    scratchProperties...>     scratch,
             const EOperator operatorType = OPERATOR_VALUE ) const {
#ifdef HAVE_INTREPID2_DEBUG
    Intrepid2::getValues_HCURL_Args(outputValues,
                                    inputPoints,
                                    operatorType,
                                    this->getBaseCellTopology(),
                                    this->getCardinality() );
#endif
    
    typedef Kokkos::DynRankView<outputValueValueType,outputValueProperties...> outputValueViewType;
    typedef Kokkos::DynRankView<inputPointValueType, inputPointProperties...>  inputPointViewType;

    // Number of evaluation points = dim 0 of inputPoints
    const auto loopSize = inputPoints.dimension(0);
    Kokkos::RangePolicy<ExecSpaceType,Kokkos::Schedule<Kokkos::Static> > policy(0, loopSize);
  
    switch (operatorType) {
    case OPERATOR_VALUE: {
      struct FunctorValue : FunctorBaseWithoutScratch<outputValueViewType,inputPointViewType> {
        KOKKOS_INLINE_FUNCTION
        void operator()(const size_type i0) const {
          const auto x = _inputPoints(i0, 0);
          const auto y = _inputPoints(i0, 1);

          // outputValues is a rank-3 array with dimensions (basisCardinality_, dim0, spaceDim)
          _outputValues(0, i0, 0) = (1.0 - y)/4.0;
          _outputValues(0, i0, 1) =  0.0;
          
          _outputValues(1, i0, 0) =  0.0;
          _outputValues(1, i0, 1) = (1.0 + x)/4.0;
          
          _outputValues(2, i0, 0) =-(1.0 + y)/4.0;
          _outputValues(2, i0, 1) =  0.0;
          
          _outputValues(3, i0, 0) =  0.0;
          _outputValues(3, i0, 1) =-(1.0 - x)/4.0;
        }
      };
      Kokkos::parallel_for( policy, FunctorValue(outputValues, inputPoints) );
      break;
    }
    case OPERATOR_CURL: {
      struct FunctorCurl : FunctorBaseWithoutScratch<outputValueViewType,inputPointViewType> {
        KOKKOS_INLINE_FUNCTION
        void operator()(const size_type i0) const {
          const auto x = _inputPoints(i0,0);
          const auto y = _inputPoints(i0,1);

          // outputValues is a rank-2 array with dimensions (basisCardinality_, dim0)
          _outputValues(0, i0) = 0.25;
          _outputValues(1, i0) = 0.25;
          _outputValues(2, i0) = 0.25;
          _outputValues(3, i0) = 0.25;
        }
      };
      Kokkos::parallel_for( policy, FunctorCurl(outputValues, inputPoints) );
      break;
    }
    case OPERATOR_DIV: {
      INTREPID2_TEST_FOR_EXCEPTION( operatorType == OPERATOR_DIV, std::invalid_argument,
                                    ">>> ERROR (Basis_HCURL_QUAD_I1_FEM::getValues): DIV is invalid operator for HCURL Basis Functions");
      break;
    }
    case OPERATOR_GRAD: {
      INTREPID2_TEST_FOR_EXCEPTION( operatorType == OPERATOR_GRAD, std::invalid_argument,
                                    ">>> ERROR (Basis_HCURL_QUAD_I1_FEM::getValues): GRAD is invalid operator for HCURL Basis Functions");
      break;
    }
    case OPERATOR_D1:
    case OPERATOR_D2:
    case OPERATOR_D3:
    case OPERATOR_D4:
    case OPERATOR_D5:
    case OPERATOR_D6:
    case OPERATOR_D7:
    case OPERATOR_D8:
    case OPERATOR_D9:
    case OPERATOR_D10: {
      INTREPID2_TEST_FOR_EXCEPTION( (operatorType == OPERATOR_D1)    ||
                                    (operatorType == OPERATOR_D2)    ||
                                    (operatorType == OPERATOR_D3)    ||
                                    (operatorType == OPERATOR_D4)    ||
                                    (operatorType == OPERATOR_D5)    ||
                                    (operatorType == OPERATOR_D6)    ||
                                    (operatorType == OPERATOR_D7)    ||
                                    (operatorType == OPERATOR_D8)    ||
                                    (operatorType == OPERATOR_D9)    ||
                                    (operatorType == OPERATOR_D10),
                                    std::invalid_argument,
                                    ">>> ERROR (Basis_HCURL_QUAD_I1_FEM::getValues): Invalid operator type");
      break;
    }
    default: {
      INTREPID2_TEST_FOR_EXCEPTION( (operatorType != OPERATOR_VALUE) &&
                                    (operatorType != OPERATOR_GRAD)  &&
                                    (operatorType != OPERATOR_CURL)  &&
                                    (operatorType != OPERATOR_DIV)   &&
                                    (operatorType != OPERATOR_D1)    &&
                                    (operatorType != OPERATOR_D2)    &&
                                    (operatorType != OPERATOR_D3)    &&
                                    (operatorType != OPERATOR_D4)    &&
                                    (operatorType != OPERATOR_D5)    &&
                                    (operatorType != OPERATOR_D6)    &&
                                    (operatorType != OPERATOR_D7)    &&
                                    (operatorType != OPERATOR_D8)    &&
                                    (operatorType != OPERATOR_D9)    &&
                                    (operatorType != OPERATOR_D10),
                                    std::invalid_argument,
                                    ">>> ERROR (Basis_HCURL_QUAD_I1_FEM::getValues): Invalid operator type");
    }
    }
  }

  template<typename ExecSpaceType>
  template<typename dofCoordValueType, class ...dofCoordProperties>
  void
  Basis_HCURL_QUAD_I1_FEM<ExecSpaceType>::
  getDofCoords( Kokkos::DynRankView<dofCoordValueType,dofCoordProperties...> dofCoords ) const {
#ifdef HAVE_INTREPID2_DEBUG
    // Verify rank of output array.
    INTREPID2_TEST_FOR_EXCEPTION( dofCoords.rank() != 2, std::invalid_argument,
                                  ">>> ERROR: (Intrepid2::Basis_HCURL_QUAD_I1_FEM::getDofCoords) rank = 2 required for dofCoords array");
    // Verify 0th dimension of output array.
    INTREPID2_TEST_FOR_EXCEPTION( dofCoords.dimension(0) != this->basisCardinality_, std::invalid_argument,
                                  ">>> ERROR: (Intrepid2::Basis_HCURL_QUAD_I1_FEM::getDofCoords) mismatch in number of dof and 0th dimension of dofCoords array");
    // Verify 1st dimension of output array.
    INTREPID2_TEST_FOR_EXCEPTION( dofCoords.dimension(1) != this->basisCellTopology_.getDimension(), std::invalid_argument,
                                  ">>> ERROR: (Intrepid2::Basis_HCURL_QUAD_I1_FEM::getDofCoords) incorrect reference cell (1st) dimension in dofCoords array");
#endif
    dofCoords(0,0) =  0.0;   dofCoords(0,1) = -1.0;
    dofCoords(1,0) =  1.0;   dofCoords(1,1) =  0.0;
    dofCoords(2,0) =  0.0;   dofCoords(2,1) =  1.0;
    dofCoords(3,0) = -1.0;   dofCoords(3,1) =  0.0;
  }

}// namespace Intrepid2

#endif
