// @HEADER
//
// ***********************************************************************
//
//        MueLu: A package for multigrid based preconditioning
//                  Copyright 2012 Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
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
// Questions? Contact
//                    Jonathan Hu       (jhu@sandia.gov)
//                    Andrey Prokopenko (aprokop@sandia.gov)
//                    Ray Tuminaro      (rstumin@sandia.gov)
//
// ***********************************************************************
//
// @HEADER

#ifndef MUELU_BLOCKEDCOARSEMAPFACTORY_DECL_HPP_
#define MUELU_BLOCKEDCOARSEMAPFACTORY_DECL_HPP_
#include "Xpetra_StridedMapFactory_fwd.hpp"

#include "MueLu_ConfigDefs.hpp"
#include "MueLu_CoarseMapFactory.hpp"

#include "MueLu_Level_fwd.hpp"
#include "MueLu_Aggregates_fwd.hpp"
#include "MueLu_Exceptions.hpp"

namespace MueLu {

/*!
    @class BlockedCoarseMapFactory class.
    @brief Factory for generating coarse level map. Used by BlockedPFactory.

    Overloads @c CoarseMapFactory. Uses a @c CoarseMapFactory as input parameter in the constructor and
    automatically calculates the domain offset using the max gid from the given coarse map.

    @ingroup MueLuTransferClasses

    ## Input/output ##

    ### User parameters for this factory ###
    Parameter | type | default | master.xml | validated | requested | description
    ----------|------|---------|:----------:|:---------:|:---------:|------------
    Aggregates | Factory | null | | * | * | Generating factory for aggregates. We basically need only the number of aggregates in this factory.
    Nullspace  | Factory | null |   | * | * | Generating factory of the fine nullspace vectors (of type "MultiVector"). In the default case the same instance of the TentativePFactory is also the generating factory for the null space vectors (on the next coarser levels). Therefore, it is recommended to declare the TentativePFactory to be the generating factory of the "Nullspace" variable globally using the FactoryManager object! For defining the near null space vectors on the finest level one should use the NullspaceFactory.
    Striding info | std::string | {} |  | * | | String containing the striding information, e.g. {2,1} for a fixed block size of 3 with sub blocks of size 2 and 1 in each node.
    Strided block id | LocalOrdinal | -1 |  | * | | Strided block id in strided information vector or -1 (=default) for the full block information.
    Coarse Map | Factory | null | | * | | Generating factory of another coarse to be used for calculating the GID offset for the map to be generated.

    The * in the @c master.xml column denotes that the parameter is defined in the @c master.xml file.<br>
    The * in the @c validated column means that the parameter is declared in the list of valid input parameters (see @c GetValidParameters ).<br>
    The * in the @c requested column states that the data is requested as input with all dependencies (see @c DeclareInput ).

    ### Variables provided by this factory ###

    After @c Build(), the following data is available (if requested)

    Parameter | generated by | description
    ----------|--------------|------------
    | CoarseMap | BlockedCoarseMapFactory | Map containing the coarse map used as domain map in the tentative prolongation operator

 */

template <class Scalar = DefaultScalar,
          class LocalOrdinal = DefaultLocalOrdinal,
          class GlobalOrdinal = DefaultGlobalOrdinal,
          class Node = DefaultNode>
class BlockedCoarseMapFactory : public MueLu::CoarseMapFactory<Scalar, LocalOrdinal, GlobalOrdinal, Node>
{
#undef MUELU_BLOCKEDCOARSEMAPFACTORY_SHORT
#include "MueLu_UseShortNames.hpp"

public:

  //! @name Input
  //@{

  RCP<const ParameterList> GetValidParameterList() const final;

  /*! @brief Specifies the data that this class needs, and the factories that generate that data.

      If the Build method of this class requires some data, but the generating factory is not specified in DeclareInput, then this class
      will fall back to the settings in FactoryManager.
   */

  void DeclareInput(Level &currentLevel) const final;

  //@}

  //! @name Build methods.
  //@{

  //! Build an object with this factory.
  void Build(Level &currentLevel) const final;

  //@}

protected:

  //! Compute domain GID offset from another CoarseMap
  virtual GlobalOrdinal GetDomainGIDOffset(Level& currentLevel) const final;

}; //class BlockedCoarseMapFactory

} //namespace MueLu

#define MUELU_BLOCKEDCOARSEMAPFACTORY_SHORT
#endif /* MUELU_BLOCKEDCOARSEMAPFACTORY_DECL_HPP_ */
