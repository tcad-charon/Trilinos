#ifndef ML_MATRIX_FREE_PRECONDITIONER
#define ML_MATRIX_FREE_PRECONDITIONER

#include "ml_include.h"
#if defined(HAVE_ML_EPETRA) && defined(HAVE_ML_EPETRAEXT)
#include <string>
#include "ml_epetra.h"
#include "Epetra_Operator.h"
#include "Teuchos_ParameterList.hpp"

class Epetra_Comm;
class Epetra_Map;
class Epetra_BlockMap;
class Epetra_CrsGraph;
class Epetra_MultiVector;
class Epetra_CrsMatrix;

namespace ML_Epetra {

class MatrixFreePreconditioner : public Epetra_Operator 
{
  public:
    //! Constructor
    MatrixFreePreconditioner(const Epetra_Operator& Operator,
                             const Epetra_CrsGraph& Graph,
                             Teuchos::ParameterList& List,
                             const Epetra_MultiVector& NullSpace);

    //! destructor
    ~MatrixFreePreconditioner();

    int SetUseTranspose(bool UseTranspose);

    int Apply(const Epetra_MultiVector& X, Epetra_MultiVector& Y) const;

    int ApplyInverse(const Epetra_MultiVector& X, Epetra_MultiVector& Y) const;

    double NormInf() const
    {
      return(-1.0);
    }

    const char * Label() const
    {
      return(Label_.c_str());
    }

    bool UseTranspose() const
    {
      return(false);
    }

    bool HasNormInf() const
    {
      return(false);
    }

    //! Returns a reference to the communicator object.
    const Epetra_Comm & Comm() const
    {
      return(Comm_);
    }

    //! Returns the domain map of the operator.
    const Epetra_Map & OperatorDomainMap() const
    {
      return(Operator_.OperatorDomainMap());
    }

    //! Returns the range map of the operator.
    const Epetra_Map & OperatorRangeMap() const
    {
      return(Operator_.OperatorRangeMap());
    }

    const Epetra_CrsMatrix& C() const
    {
      return(*C_);
    }

    const Epetra_CrsMatrix& P() const
    {
      return(*P_);
    }

    int Coarsen(ML_Operator* A, ML_Aggregate** aggr, ML_Operator** P, 
                ML_Operator** R, ML_Operator** C);

    ML_Comm* Comm_ML()
    {
      return(Comm_ML_);
    }

  private:
    ML_Comm* Comm_ML_;

    //! Computes the preconditioner.
    int Compute(const Epetra_MultiVector& NullSpace);

    //! Label of this object
    std::string Label_; 
    //! Communicator object
    const Epetra_Comm& Comm_;
    //! Fine-level operator
    const Epetra_Operator& Operator_;
    //! Fine-level graph
    const Epetra_CrsGraph& Graph_;
    //! List containing all the parameters
    Teuchos::ParameterList List_;
    //! Prolongator from coarse to fine
    Epetra_CrsMatrix* P_;
    Epetra_CrsMatrix* R_;
    Epetra_CrsMatrix* C_;

}; // class MatrixFreePreconditioner

} // namespace ML_Epetra

#endif // HAVE_ML_EPETRA
#endif // ML_MATRIX_FREE_PRECONDITIONER
