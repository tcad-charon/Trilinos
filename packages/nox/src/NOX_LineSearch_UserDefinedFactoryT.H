// $Id$
// $Source$

//@HEADER
// ************************************************************************
//
//            NOX: An Object-Oriented Nonlinear Solver Package
//                 Copyright (2002) Sandia Corporation
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
// Questions? Contact Roger Pawlowski (rppawlo@sandia.gov) or
// Eric Phipps (etphipp@sandia.gov), Sandia National Laboratories.
// ************************************************************************
//  CVS Information
//  $Source$
//  $Author$
//  $Date$
//  $Revision$
// ************************************************************************
//@HEADER

#ifndef NOX_LINESEARCH_USERDEFINED_FACTORY_TEMPLATE_H
#define NOX_LINESEARCH_USERDEFINED_FACTORY_TEMPLATE_H

#include "Teuchos_RCP.hpp"
#include "NOX_LineSearch_UserDefinedFactory.H"
#include "NOX_Common.H"

namespace NOX {
namespace LineSearch {

/*!  \brief Concrete instantiation of a NOX::LineSearch::UserDefinedFactory object that uses the base objects only for constuction.

   If the user writes their own line search and that object has the same
   constructor arguments as the nox line searches (the \c gd and \c
   params as in the buildDirection method), then users can use this
   object instead of having to write their own factory.

   For example, if a user writes their own line search object:
   \code
   class MyLineSearch : public NOX::LineSearch::Generic {

     // Ctor that takes the standard line search arguments.
     MyLineSearch(const Teuchos::RCP<NOX::GlobalData>& gd,
                  Teuchos::ParameterList& params);

     .
     .
     .

   }
   \endcode

   They can build that object using this factory and do not
   have to write their own factory

   \code
   ParameterList dl& = nox_params.sublist("Line Search");
   RCP<NOX::LineSearch::UserDefinedFactory> udlsf =
     rcp(new NOX::LineSearch::UserDefinedFactoryT<MyLineSearch>);
   dl.set("User Defined LineSearch Factory", udlsf);
   \endcode

   It is critical that the user defined factory be set in the
   parameter list as a base class type object:
   NOX::LineSearch::UserDefinedFactory.

 */
template <typename T>
class UserDefinedFactoryT : public NOX::LineSearch::UserDefinedFactory {

public:

  //! Constructor
  UserDefinedFactoryT() {}

  //! Destructor
  ~UserDefinedFactoryT() {}

  Teuchos::RCP<NOX::LineSearch::Generic>
  buildLineSearch(const Teuchos::RCP<NOX::GlobalData>& gd,
          Teuchos::ParameterList& params) const
  {
    using namespace Teuchos;
    RCP<NOX::LineSearch::Generic> ls = rcp(new T(gd, params));
    return ls;
  }

};
} // namespace LineSearch
} // namespace NOX
#endif
