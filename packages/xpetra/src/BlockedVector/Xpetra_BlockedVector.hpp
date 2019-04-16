// @HEADER
//
// ***********************************************************************
//
//             Xpetra: A linear algebra interface package
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
//                    Tobias Wiesner    (tawiesn@sandia.gov)
//                    Ray Tuminaro      (rstumin@sandia.gov)
//
// ***********************************************************************
//
// @HEADER
#ifndef XPETRA_BLOCKEDVECTOR_HPP
#define XPETRA_BLOCKEDVECTOR_HPP

/* this file is automatically generated - do not edit (see script/interfaces.py) */

#include "Xpetra_ConfigDefs.hpp"
#include "Xpetra_Map.hpp"
#include "Xpetra_Vector.hpp"

#include "Xpetra_BlockedMap.hpp"

namespace Xpetra {

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  // forward declaration of Vector, needed to prevent circular inclusions
  template<class S, class LO, class GO, class N> class Vector;
  template<class S, class LO, class GO, class N> class MapExtractor;
  template<class S, class LO, class GO, class N> class VectorFactory;
#endif

  template <class Scalar = double,
            class LocalOrdinal = Map<>::local_ordinal_type,
            class GlobalOrdinal = typename Map<LocalOrdinal>::global_ordinal_type,
            class Node = typename Map<LocalOrdinal, GlobalOrdinal>::node_type>
  class BlockedVector
    : public virtual Xpetra::Vector< Scalar, LocalOrdinal, GlobalOrdinal, Node >,
      public virtual Xpetra::BlockedMultiVector< Scalar, LocalOrdinal, GlobalOrdinal, Node>
  {
  public:
    typedef Scalar scalar_type;
    typedef LocalOrdinal local_ordinal_type;
    typedef GlobalOrdinal global_ordinal_type;
    typedef Node node_type;

    using Vector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::dot;          // overloading, not hiding
    using Vector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::norm1;        // overloading, not hiding
    using Vector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::norm2;        // overloading, not hiding
    using Vector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::normInf;      // overloading, not hiding
    using Vector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::meanValue;    // overloading, not hiding
    using Vector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::replaceGlobalValue; // overloading, not hiding
    using Vector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::sumIntoGlobalValue; // overloading, not hiding
    using Vector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::replaceLocalValue; // overloading, not hiding
    using Vector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::sumIntoLocalValue; // overloading, not hiding


  private:
#undef XPETRA_BLOCKEDVECTOR_SHORT
#include "Xpetra_UseShortNames.hpp"

  public:
    //! @name Constructor/Destructor Methods
    //@{

    //! Constructor

    /*!
     * Const version of constructor which accepts a const version
     * of a blocked map
     *
     * \param map BlockedMap defining the block structure of the vector
     * \param zeroOut If true initialize vector with zeros
     */
    BlockedVector(const Teuchos::RCP< const BlockedMap > &map,
        bool zeroOut=true) :
          BlockedMultiVector(map,1,zeroOut) {    };

    /*!
     * Const version of constructor which accepts a const version
     * of the vector
     *
     * \note If you change the information in input vector v the data in the
     *       blocked vector are not affected (and vice versa). Consider
     *       the blocked vector to be a copy of the input vector (not a view)
     *
     * \param bmap BlockedMap object containing information about the block splitting
     * \param v Vector that is to be splitted into a blocked vector
     */
    BlockedVector(Teuchos::RCP<const Xpetra::BlockedMap<LocalOrdinal,GlobalOrdinal,Node> > bmap,
                     Teuchos::RCP<const Vector> v) :
                     BlockedMultiVector(bmap,v) {    }

    /*!
     * NonConst version of constructor which accepts a const version
     * of the vector
     *
     * \note If you change the information in input vector v the data in the
     *       blocked vector are not affected (and vice versa). Consider
     *       the blocked vector to be a copy of the input vector (not a view)
     *
     * \param bmap BlockedMap object containing information about the block splitting
     * \param v Vector that is to be splitted into a blocked vector
     */
    BlockedVector(Teuchos::RCP<const Xpetra::BlockedMap<LocalOrdinal,GlobalOrdinal,Node> > bmap,
                     Teuchos::RCP<Vector> v) :
                     BlockedMultiVector(bmap,v) {    }

    /*!
     * Const version of constructor which accepts a const version
     * of the vector
     *
     * \note If you change the information in input vector v the data in the
     *       blocked vector are not affected (and vice versa). Consider
     *       the blocked vector to be a copy of the input vector (not a view)
     *
     * \param mapExtractor MapExtractor object containing information about the block splitting
     * \param v Vector that is to be splitted into a blocked vector
     */
    BlockedVector(Teuchos::RCP<const Xpetra::MapExtractor<Scalar,LocalOrdinal,GlobalOrdinal,Node> > mapExtractor,
                     Teuchos::RCP<const Vector> v) :
                     BlockedMultiVector(mapExtractor,v) {    }

    /*!
     * Non-const version of constructor which accepts a non-const version
     * of the vector
     *
     * \note If you change the information in input vector v the data in the
     *       blocked vector are not affected (and vice versa). Consider
     *       the blocked vector to be a copy of the input vector (not a view)
     *
     * \param mapExtractor MapExtractor object containing information about the block splitting
     * \param v Vector that is to be splitted into a blocked vector
     */
    BlockedVector(Teuchos::RCP<const Xpetra::MapExtractor<Scalar,LocalOrdinal,GlobalOrdinal,Node> > mapExtractor,
                     Teuchos::RCP<Vector> v) :
                     BlockedMultiVector(mapExtractor,v) {    }

    //! Destructor.
    virtual ~BlockedVector() { }

    /// \brief Assignment operator: Does a deep copy.
    ///
    /// The assignment operator does a deep copy, just like
    /// subclasses' copy constructors.
    ///
    /// \note This currently only works if both <tt>*this</tt> and the
    ///   input argument are instances of the same subclass.
    BlockedVector<Scalar,LocalOrdinal,GlobalOrdinal,Node>&
    operator= (const MultiVector& rhs) {
      assign (rhs); // dispatch to protected virtual method
      return *this;
    }

    //@}
    //! @name Post-construction modification routines
    //@{

    //! Replace value, using global (row) index.
    virtual void replaceGlobalValue(GlobalOrdinal globalRow, size_t vectorIndex, const Scalar &value) {
      BlockedMultiVector::replaceGlobalValue(globalRow, vectorIndex, value);
    }

    //! Add value to existing value, using global (row) index.
    virtual void sumIntoGlobalValue(GlobalOrdinal globalRow, size_t vectorIndex, const Scalar &value) {
      BlockedMultiVector::sumIntoGlobalValue(globalRow, vectorIndex, value);
    }

    //! Replace value, using local (row) index.
    virtual void replaceLocalValue(LocalOrdinal myRow, size_t vectorIndex, const Scalar &value) {
      BlockedMultiVector::replaceLocalValue(myRow, vectorIndex, value);
    }

    //! Add value to existing value, using local (row) index.
    virtual void sumIntoLocalValue(LocalOrdinal myRow, size_t vectorIndex, const Scalar &value) {
      BlockedMultiVector::sumIntoLocalValue(myRow, vectorIndex, value);
    }

    //! Replace value, using global (row) index.
    virtual void replaceGlobalValue(GlobalOrdinal globalRow, const Scalar &value) {
      BlockedMultiVector::replaceGlobalValue(globalRow, 0, value);
    }

    //! Add value to existing value, using global (row) index.
    virtual void sumIntoGlobalValue(GlobalOrdinal globalRow, const Scalar &value) {
      BlockedMultiVector::sumIntoGlobalValue(globalRow, 0, value);
    }

    //! Replace value, using local (row) index.
    virtual void replaceLocalValue(LocalOrdinal myRow, const Scalar &value) {
      BlockedMultiVector::replaceLocalValue(myRow, 0, value);
    }

    //! Add value to existing value, using local (row) index.
    virtual void sumIntoLocalValue(LocalOrdinal myRow, const Scalar &value) {
      BlockedMultiVector::sumIntoLocalValue(myRow, 0, value);
    }


    //! Set all values in the vector with the given value.
    virtual void putScalar(const Scalar &value) {
      BlockedMultiVector::putScalar(value);
    }

    //@}

    //! @name Data Copy and View get methods
    //@{

    //! Return a Vector which is a const view of column j.
    virtual Teuchos::RCP< const Xpetra::Vector<Scalar,LocalOrdinal,GlobalOrdinal,Node> > getVector(size_t j) const {
      return BlockedMultiVector::getVector(j);
    }

    //! Return a Vector which is a nonconst view of column j.
    virtual Teuchos::RCP< Xpetra::Vector<Scalar,LocalOrdinal,GlobalOrdinal,Node> > getVectorNonConst(size_t j) {
      return BlockedMultiVector::getVectorNonConst(j);
    }

    //! Const view of the local values in a particular vector of this vector.
    virtual Teuchos::ArrayRCP< const Scalar > getData(size_t j) const {
      return BlockedMultiVector::getData(j);
    }

    //! View of the local values in a particular vector of this vector.
    virtual Teuchos::ArrayRCP< Scalar > getDataNonConst(size_t j) {
      return BlockedMultiVector::getDataNonConst(j);
    }

    //@}

    //! @name Mathematical methods
    //@{

    //! Compute dot product of each corresponding pair of vectors, dots[i] = this[i].dot(A[i]).
    virtual void dot(const MultiVector&A, const Teuchos::ArrayView< Scalar > &dots) const {
      BlockedMultiVector::dot(A,dots);
      return;
    }

    virtual Scalar dot(const Vector&A) const {
      Teuchos::Array< Scalar > dots = Teuchos::Array<Scalar>(1);
      BlockedMultiVector::dot(A,dots);
      return dots[0];
    }


    //! Put element-wise absolute values of input vector in target: A = abs(this).
    virtual void abs(const MultiVector&A) {
      BlockedMultiVector::abs(A);
      return;
    }

    //! Put element-wise reciprocal values of input vector in target, this(i,j) = 1/A(i,j).
    virtual void reciprocal(const MultiVector&A) {
      BlockedMultiVector::reciprocal(A);
      return;
    }

    //! Scale the current values of a vector, this = alpha*this.
    virtual void scale(const Scalar &alpha) {
      BlockedMultiVector::scale(alpha);
      return;
    }

    //! Scale the current values of a vector, this[j] = alpha[j]*this[j].
    virtual void scale (Teuchos::ArrayView< const Scalar > alpha) {
      BlockedMultiVector::scale(alpha);
      return ;
    }

    virtual void update(const Scalar &alpha, const MultiVector&A, const Scalar &beta) {
      BlockedMultiVector::update(alpha,A,beta);
      return;
    }


    //! Update vector with scaled values of A and B, this = gamma*this + alpha*A + beta*B.
    virtual void update(const Scalar &alpha, const MultiVector&A, const Scalar &beta, const MultiVector&B, const Scalar &gamma) {
      BlockedMultiVector::update(alpha,A,beta,B,gamma);
      return;
    }

    //! Compute 1-norm of vector.
    virtual typename Teuchos::ScalarTraits< Scalar >::magnitudeType norm1() const {
      Teuchos::Array< typename Teuchos::ScalarTraits< Scalar>::magnitudeType > norm =
          Teuchos::Array< typename Teuchos::ScalarTraits< Scalar>::magnitudeType >(1);
      this->norm1(norm);
      return norm[0];
    }

    //! Compute 2-norm of vector.
    virtual typename Teuchos::ScalarTraits< Scalar >::magnitudeType norm2() const {
      Teuchos::Array< typename Teuchos::ScalarTraits< Scalar>::magnitudeType > norm =
          Teuchos::Array< typename Teuchos::ScalarTraits< Scalar>::magnitudeType >(1);
      this->norm2(norm);
      return norm[0];
    }

    //! Compute Inf-norm in vector.
    virtual typename Teuchos::ScalarTraits< Scalar >::magnitudeType normInf() const {
      Teuchos::Array< typename Teuchos::ScalarTraits< Scalar>::magnitudeType > norm =
          Teuchos::Array< typename Teuchos::ScalarTraits< Scalar>::magnitudeType >(1);
      this->normInf(norm);
      return norm[0];
    }

    //! Compute 1-norm of each vector in multi-vector.
    virtual void norm1(const Teuchos::ArrayView< typename Teuchos::ScalarTraits< Scalar >::magnitudeType > &norms) const {
      BlockedMultiVector::norm1(norms);
    }

    //!
    virtual void norm2(const Teuchos::ArrayView< typename Teuchos::ScalarTraits< Scalar >::magnitudeType > &norms) const {
      BlockedMultiVector::norm2(norms);
    }

    //! Compute Inf-norm of each vector in multi-vector.
    virtual void normInf(const Teuchos::ArrayView< typename Teuchos::ScalarTraits< Scalar >::magnitudeType > &norms) const {
      BlockedMultiVector::normInf(norms);
    }

    //! Compute mean (average) value of each vector in vector. The outcome of this routine is undefined for non-floating point scalar types (e.g., int).
    virtual void meanValue(const Teuchos::ArrayView< Scalar > &/* means */) const {
      throw Xpetra::Exceptions::RuntimeError("BlockedVector::meanValue: Not (yet) supported by BlockedVector.");
    }

    virtual Scalar meanValue() const {
      throw Xpetra::Exceptions::RuntimeError("BlockedVector::meanValue: Not (yet) supported by BlockedVector.");
    }

    //! Matrix-matrix multiplication: this = beta*this + alpha*op(A)*op(B).
    virtual void multiply(Teuchos::ETransp /* transA */, Teuchos::ETransp /* transB */, const Scalar &/* alpha */, const Vector&/* A */, const Vector&/* B */, const Scalar &/* beta */) {
      throw Xpetra::Exceptions::RuntimeError("BlockedVector::multiply: Not (yet) supported by BlockedVector.");
    }

    virtual void multiply(Teuchos::ETransp /* transA */, Teuchos::ETransp /* transB */, const Scalar &/* alpha */, const MultiVector&/* A */, const MultiVector&/* B */, const Scalar &/* beta */) {
      throw Xpetra::Exceptions::RuntimeError("BlockedVector::multiply: Not (yet) supported by BlockedVector.");
    }


    virtual void elementWiseMultiply(Scalar /* scalarAB */, const Xpetra::Vector<Scalar,LocalOrdinal,GlobalOrdinal,Node>&/* A */, const MultiVector&/* B */, Scalar /* scalarThis */) {
      throw Xpetra::Exceptions::RuntimeError("BlockedVector::elementWiseMultiply: Not (yet) supported by BlockedVector.");
    }

    //! Element-wise multiply of a Vector A with a Vector B.
    virtual void elementWiseMultiply(Scalar /* scalarAB */, const Xpetra::Vector<Scalar,LocalOrdinal,GlobalOrdinal,Node>&A, const Vector&B, Scalar /* scalarThis */) {
      XPETRA_TEST_FOR_EXCEPTION(B.getMap()->isSameAs(*(this->getMap()))==false, Xpetra::Exceptions::RuntimeError, "BlockedVector::elementWiseMultipy: B must have same blocked map than this.");
      TEUCHOS_TEST_FOR_EXCEPTION(A.getMap()->getNodeNumElements() != B.getMap()->getNodeNumElements(), Xpetra::Exceptions::RuntimeError, "BlockedVector::elementWiseMultipy: A has " << A.getMap()->getNodeNumElements() << " elements, B has " << B.getMap()->getNodeNumElements() << ".");
      TEUCHOS_TEST_FOR_EXCEPTION(A.getMap()->getGlobalNumElements() != B.getMap()->getGlobalNumElements(), Xpetra::Exceptions::RuntimeError, "BlockedVector::elementWiseMultipy: A has " << A.getMap()->getGlobalNumElements() << " elements, B has " << B.getMap()->getGlobalNumElements() << ".");

      RCP<const BlockedMap> bmap = this->getBlockedMap();
      RCP<const Xpetra::Vector<Scalar,LocalOrdinal,GlobalOrdinal,Node>> rcpA = Teuchos::rcpFromRef(A);
      RCP<const Vector> bmvec = Teuchos::rcpFromRef(B);
      RCP<const BlockedVector> bbmvec = Teuchos::rcp_dynamic_cast<const BlockedVector>(bmvec);
      TEUCHOS_TEST_FOR_EXCEPTION(bbmvec.is_null() == true, Xpetra::Exceptions::RuntimeError, "BlockedVector::elementWiseMultipy: B must be a BlockedVector.");

      // TODO implement me
      /*RCP<Xpetra::MapExtractor<Scalar,LocalOrdinal,GlobalOrdinal,Node> > me = Teuchos::rcp(new Xpetra::MapExtractor<Scalar,LocalOrdinal,GlobalOrdinal,Node>(bmap));

      for(size_t m = 0; m < bmap->getNumMaps(); m++) {
        // TODO introduce BlockedVector objects and "skip" this expensive ExtractVector call
        RCP<const Xpetra::Vector<Scalar,LocalOrdinal,GlobalOrdinal,Node> > pd = me->ExtractVector(rcpA,m,bmap->getThyraMode());
        XPETRA_TEST_FOR_EXCEPTION(pd->getMap()->isSameAs(*(this->getBlockedMap()->getMap(m,bmap->getThyraMode())))==false, Xpetra::Exceptions::RuntimeError, "BlockedVector::elementWiseMultipy: sub map of B does not fit with sub map of this.");
        this->getMultiVector(m,bmap->getThyraMode())->elementWiseMultiply(scalarAB,*pd,*(bbmvec->getMultiVector(m,bmap->getThyraMode())),scalarThis);
      }*/
    }

    //@}

    //! @name Attribute access functions
    //@{

    //! Number of columns in the Vector.
    virtual size_t getNumVectors() const {
      return 1;
    }

    //! Local number of rows on the calling process.
    virtual size_t getLocalLength() const {
      throw Xpetra::Exceptions::RuntimeError("BlockedVector::getLocalLength: routine not implemented. It has no value as one must iterate on the partial vectors.");
      TEUCHOS_UNREACHABLE_RETURN(0);
    }

    //! Global number of rows in the Vector.
    virtual global_size_t getGlobalLength() const {
      return this->getBlockedMap()->getFullMap()->getGlobalNumElements();
    }

    //! Local number of rows on the calling process.
    virtual bool isSameSize(const Xpetra::MultiVector<Scalar,LocalOrdinal,GlobalOrdinal,Node> & /* vec */) const {
      throw Xpetra::Exceptions::RuntimeError("BlockedVector::isSameSize: routine not implemented. It has no value as one must iterate on the partial vectors.");
      TEUCHOS_UNREACHABLE_RETURN(0);
    }

    //@}

    //! @name Overridden from Teuchos::Describable
    //@{

    //! A simple one-line description of this object.
    virtual std::string description() const {
      return std::string("BlockedVector");
    }

    //! Print the object with the given verbosity level to a FancyOStream.
    virtual void describe(Teuchos::FancyOStream &out, const Teuchos::EVerbosityLevel verbLevel=Teuchos::Describable::verbLevel_default) const {
      out << description() << std::endl;
      for(size_t r = 0; r < this->getBlockedMap()->getNumMaps(); r++)
        getMultiVector(r)->describe(out, verbLevel);
    }

    virtual void replaceMap(const RCP<const Map>& map) {
      BlockedMultiVector::replaceMap(map);
    }

    //! Import.
    virtual void doImport(const DistObject<Scalar, LocalOrdinal, GlobalOrdinal, Node> &/* source */, const Import& /* importer */, CombineMode /* CM */) {
      throw Xpetra::Exceptions::RuntimeError("BlockedVector::doImport: Not supported by BlockedVector.");
    }

    //! Export.
    virtual void doExport(const DistObject<Scalar, LocalOrdinal, GlobalOrdinal, Node> &/* dest */, const Import& /* importer */, CombineMode /* CM */) {
      throw Xpetra::Exceptions::RuntimeError("BlockedVector::doExport: Not supported by BlockedVector.");
    }

    //! Import (using an Exporter).
    virtual void doImport(const DistObject<Scalar, LocalOrdinal, GlobalOrdinal, Node> &/* source */, const Export& /* exporter */, CombineMode /* CM */) {
      throw Xpetra::Exceptions::RuntimeError("BlockedVector::doImport: Not supported by BlockedVector.");
    }

    //! Export (using an Importer).
    virtual void doExport(const DistObject<Scalar, LocalOrdinal, GlobalOrdinal, Node> &/* dest */, const Export& /* exporter */, CombineMode /* CM */) {
      throw Xpetra::Exceptions::RuntimeError("BlockedVector::doExport: Not supported by BlockedVector.");
    }

    //@}

    //! @name Xpetra specific
    //@{

    //! Set seed for Random function.
    virtual void setSeed(unsigned int seed) {
      for(size_t r = 0; r < this->getBlockedMap()->getNumMaps(); ++r) {
        getMultiVector(r)->setSeed(seed);
      }
    }


    virtual void randomize(bool bUseXpetraImplementation = false) {
      for(size_t r = 0; r < this->getBlockedMap()->getNumMaps(); ++r) {
        getMultiVector(r)->randomize(bUseXpetraImplementation);
      }
    }

    //! Set vector values to random numbers. XPetra implementation
    virtual void Xpetra_randomize()
    {
      Xpetra::Vector<Scalar,LocalOrdinal,GlobalOrdinal,Node>::Xpetra_randomize();
    }

#ifdef HAVE_XPETRA_KOKKOS_REFACTOR
    typedef typename Kokkos::Details::ArithTraits<Scalar>::val_type impl_scalar_type;
    typedef Kokkos::DualView<impl_scalar_type**, Kokkos::LayoutStride,
        typename node_type::execution_space,
        Kokkos::MemoryUnmanaged> dual_view_type;
    typedef typename dual_view_type::host_mirror_space host_execution_space;
    typedef typename dual_view_type::t_dev::execution_space dev_execution_space;

    /// \brief Return an unmanaged non-const view of the local data on a specific device.
    /// \tparam TargetDeviceType The Kokkos Device type whose data to return.
    ///
    /// \warning Be aware that the view on the Vector data is non-persisting, i.e.
    ///          only valid as long as the Vector does not run of scope!
    template<class TargetDeviceType>
    typename Kokkos::Impl::if_c<
      Kokkos::Impl::is_same<
        typename dev_execution_space::memory_space,
        typename TargetDeviceType::memory_space>::value,
        typename dual_view_type::t_dev_um,
        typename dual_view_type::t_host_um>::type
    getLocalView () const {
      if(Kokkos::Impl::is_same<
                   typename host_execution_space::memory_space,
                   typename TargetDeviceType::memory_space
         >::value) {
        return getHostLocalView();
      } else {
        return getDeviceLocalView();
      }
    }

    virtual typename dual_view_type::t_host_um getHostLocalView ()  const {
      typename dual_view_type::t_host_um test;
      return test;
    }
    virtual typename dual_view_type::t_dev_um  getDeviceLocalView() const {
      typename dual_view_type::t_dev_um test;
      return test;
    }

#endif

    //@}

    //! Access function for the underlying Map this DistObject was constructed with.
    Teuchos::RCP< const Map> getMap() const { XPETRA_MONITOR("BlockedVector::getMap"); return this->getBlockedMap(); }

    /// return partial Vector associated with block row r
    Teuchos::RCP<MultiVector> getMultiVector(size_t r) const {
      return BlockedMultiVector::getMultiVector(r);
    }

    /// return partial Vector associated with block row r
    Teuchos::RCP<MultiVector> getMultiVector(size_t r, bool bThyraMode) const {
      return BlockedMultiVector::getMultiVector(r,bThyraMode);
    }

    /// set partial Vector associated with block row r
    void setMultiVector(size_t r, Teuchos::RCP<const Vector> v, bool bThyraMode) {
      BlockedMultiVector::setMultiVector(r,v,bThyraMode);
      return;
    }

    /// merge BlockedVector blocks to a single Vector
    Teuchos::RCP<MultiVector> Merge() const {
      return BlockedMultiVector::Merge();
    }


  protected:
    /// \brief Implementation of the assignment operator (operator=);
    ///   does a deep copy.
    ///
    /// Each subclass must implement this.  This includes
    /// Xpetra::EpetraVector and Xpetra::TpetraVector as well as
    /// Xpetra::BockedVector
    virtual void assign (const MultiVector& rhs) {
      BlockedMultiVector::assign(rhs);
    }

    //virtual void assign (const MultiVector& rhs) {
    //  throw Xpetra::Exceptions::RuntimeError("BlockedVector::assign: Not supported by BlockedVector.");
    //}

  private:
    //Teuchos::RCP<const BlockedMap>          map_;         ///< blocked map containing the sub block maps (either thyra or xpetra mode)
    //std::vector<Teuchos::RCP<Vector> > vv_;          ///< array containing RCPs of the partial vectors
  }; // BlockedVector class

} // Xpetra namespace

#define XPETRA_BLOCKEDVECTOR_SHORT
#endif // XPETRA_BLOCKEDVECTOR_HPP
