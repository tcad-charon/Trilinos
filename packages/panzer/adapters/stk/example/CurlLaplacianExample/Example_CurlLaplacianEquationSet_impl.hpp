#ifndef USER_APP_EQUATIONSET_ENERGY_T_HPP
#define USER_APP_EQUATIONSET_ENERGY_T_HPP

#include "Teuchos_ParameterList.hpp"
#include "Teuchos_StandardParameterEntryValidators.hpp"
#include "Teuchos_RCP.hpp"
#include "Teuchos_Assert.hpp"
#include "Phalanx_DataLayout_MDALayout.hpp"
#include "Phalanx_FieldManager.hpp"

#include "Panzer_IntegrationRule.hpp"
#include "Panzer_BasisIRLayout.hpp"

// include evaluators here
#include "Panzer_Integrator_BasisTimesScalar.hpp"
#include "Panzer_Integrator_GradBasisDotVector.hpp"
#include "Panzer_ScalarToVector.hpp"
#include "Panzer_Sum.hpp"
#include "Panzer_Constant.hpp"

// ***********************************************************************
template <typename EvalT>
Example::CurlLaplacianEquationSet<EvalT>::
CurlLaplacianEquationSet(const panzer::InputEquationSet& ies,
		   const panzer::CellData& cell_data,
		   const Teuchos::RCP<panzer::GlobalData>& global_data,
		   const bool build_transient_support) :
  panzer::EquationSet_DefaultImpl<EvalT>(ies, cell_data, global_data, build_transient_support )
{
   TEUCHOS_ASSERT(ies.prefix==""); // have an assertion to gurantee no prefix
   this->m_eqset_prefix = "";      // for simplicity assume no prefix

   // ********************
   // Panzer uses strings to match fields. In this section we define the
   // name of the fields provided by this equation set. This is a bit strange
   // in that this is not the fields necessarily required by this equation set.
   // For instance for the momentum equations in Navier-Stokes only the velocity
   // fields are added, the pressure field is added by continuity.
   //
   // In this case "EFIELD" is the lone field.  We also name the curl
   // for this field. These names automatically generate evaluators for "EFIELD"
   // and "CURL_EFIELD" gathering the basis coefficients of "EFIELD" and
   // the values of the EFIELD and CURL_EFIELD fields at quadrature points.
   //
   // After all the equation set evaluators are added to a given field manager, the
   // panzer code adds in appropriate scatter evaluators to distribute the
   // entries into the residual and the Jacobian operator. These operators will be
   // "required" by the field manager and will serve as roots of evaluation tree.
   // The leaves of this tree will include the gather evaluators whose job it is to
   // gather the solution from a vector.
   // ********************

   // ********************
   // Assemble DOF names and Residual names
   // ********************
   this->m_dof_names->push_back("EFIELD");
 
   this->m_dof_curl_names->push_back("CURL_EFIELD");
 
   if(this->m_build_transient_support)
      this->m_dof_time_derivative_names->push_back("DOT_EFIELD");
 
   this->m_residual_names->push_back("RESIDUAL_EFIELD");
 
   this->m_scatter_name = "Scatter_RESIDUAL_EFIELD";
 
   // ********************
   // Build Basis Functions and Integration Rules
   // ********************
   
   this->setupDOFs(cell_data.baseCellDimension());
 
   // ********************
   // Parse valid options
   // ********************
   // The "Options" parameter list is included in ies.params
}

// ***********************************************************************
template <typename EvalT>
void Example::CurlLaplacianEquationSet<EvalT>::
buildAndRegisterEquationSetEvaluators(PHX::FieldManager<panzer::Traits>& fm,
				      const std::vector<std::pair<std::string,Teuchos::RCP<panzer::BasisIRLayout> > > & dofs,
				      const Teuchos::ParameterList& user_data) const
{
  using Teuchos::ParameterList;
  using Teuchos::RCP;
  using Teuchos::rcp;
  
  // ********************
  // Energy Equation
  // ********************

  // Transient Operator: Assembles \int \dot{T} v
  if (this->m_build_transient_support) {
    ParameterList p("Transient Residual");
    p.set("Residual Name", "RESIDUAL_EFIELD_TRANSIENT_OP"); // we are defining the name of this operator
    p.set("Value Name", "DOT_EFIELD"); // this field is constructed by the panzer library
    p.set("Basis", this->m_basis);
    p.set("IR", this->m_int_rule);
    p.set("Multiplier", 1.0);

    RCP< PHX::Evaluator<panzer::Traits> > op = 
      rcp(new panzer::Integrator_BasisTimesVector<EvalT,panzer::Traits>(p));
    
    fm.template registerEvaluator<EvalT>(op);
  }

  // Diffusion Operator: Assembles \int \nabla T \cdot \nabla v
  {
    double thermal_conductivity = 1.0;

    ParameterList p("Diffusion Residual");
    p.set("Residual Name", "RESIDUAL_EFIELD_DIFFUSION_OP");
    p.set("Value Name", "CURL_EFIELD"); // this field is constructed by the panzer library
    p.set("Test Field Name", "EFIELD"); 
    p.set("Basis", this->m_basis);
    p.set("IR", this->m_int_rule);
    p.set("Multiplier", -thermal_conductivity);
    
    RCP< PHX::Evaluator<panzer::Traits> > op = 
      rcp(new panzer::Integrator_CurlBasisDotVector<EvalT,panzer::Traits>(p));

    fm.template registerEvaluator<EvalT>(op);
  }

  // Mass operator
  {   
    ParameterList p("Source Residual");
    p.set("Residual Name", "RESIDUAL_EFIELD_MASS_OP");
    p.set("Value Name", "EFIELD"); 
    p.set("Test Field Name", "EFIELD"); 
    p.set("Basis", this->m_basis);
    p.set("IR", this->m_int_rule);
    p.set("Multiplier", -1.0);
    
    RCP< PHX::Evaluator<panzer::Traits> > op = 
      rcp(new panzer::Integrator_BasisTimesVector<EvalT,panzer::Traits>(p));
    
    fm.template registerEvaluator<EvalT>(op);
  }
  
  // Source Operator
  {   
    ParameterList p("Source Residual");
    p.set("Residual Name", "RESIDUAL_EFIELD_SOURCE_OP");
    p.set("Value Name", "SOURCE_EFIELD"); // this field must be provided by the closure model factory
                                               // and specified by the user
    p.set("Test Field Name", "EFIELD"); 
    p.set("Basis", this->m_basis);
    p.set("IR", this->m_int_rule);
    p.set("Multiplier", -1.0);
    
    RCP< PHX::Evaluator<panzer::Traits> > op = 
      rcp(new panzer::Integrator_BasisTimesVector<EvalT,panzer::Traits>(p));
    
    fm.template registerEvaluator<EvalT>(op);
  }

  // Use a sum operator to form the overall residual for the equation
  {
    RCP<std::vector<std::string> > sum_names = 
      rcp(new std::vector<std::string>);

    // these are the names of the residual values to sum together
    sum_names->push_back("RESIDUAL_EFIELD_DIFFUSION_OP");
    sum_names->push_back("RESIDUAL_EFIELD_MASS_OP");
    sum_names->push_back("RESIDUAL_EFIELD_SOURCE_OP");
    if (this->m_build_transient_support)
      sum_names->push_back("RESIDUAL_EFIELD_TRANSIENT_OP");

    ParameterList p;
    p.set("Sum Name", "RESIDUAL_EFIELD"); 
       // this name is special, the scatter evalutor depends on the field
       // named "RESIDUAL_EFIELD" for evaluation
    p.set("Values Names", sum_names);
    p.set("Data Layout", this->m_basis->functional);

    RCP< PHX::Evaluator<panzer::Traits> > op = 
      rcp(new panzer::Sum<EvalT,panzer::Traits>(p));

    fm.template registerEvaluator<EvalT>(op);
  }

}

// ***********************************************************************

#endif
