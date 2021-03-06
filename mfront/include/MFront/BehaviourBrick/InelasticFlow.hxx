/*!
 * \file   include/MFront/BehaviourBrick/InelasticFlow.hxx
 * \brief
 * \author Thomas Helfer
 * \date   15/03/2018
 * \copyright Copyright (C) 2006-2018 CEA/DEN, EDF R&D. All rights
 * reserved.
 * This project is publicly released under either the GNU GPL Licence
 * or the CECILL-A licence. A copy of thoses licences are delivered
 * with the sources of TFEL. CEA or EDF may also distribute this
 * project under specific licensing conditions.
 */

#ifndef LIB_MFRONT_BEHAVIOURBRICK_INELASTICFLOW_HXX
#define LIB_MFRONT_BEHAVIOURBRICK_INELASTICFLOW_HXX

#include <memory>
#include "TFEL/Material/ModellingHypothesis.hxx"
#include "MFront/MFrontConfig.hxx"
#include "MFront/BehaviourDescription.hxx"

namespace tfel {
  namespace utilities {
    // forward declaration
    struct Data;
  }  // end of namespace utilities
}  // end of namespace tfel

namespace mfront {

  // forward declaration
  struct AbstractBehaviourDSL;

  namespace bbrick {

    // forward declaration
    struct StressPotential;
    // forward declaration
    struct StressCriterion;
    // forward declaration
    struct IsotropicHardeningRule;
    // forward declaration
    struct KinematicHardeningRule;
    // forward declaration
    struct StressCriterion;
    // forward declaration
    struct OptionDescription;

    //! \brief class describing an inelastic flow.
    struct MFRONT_VISIBILITY_EXPORT InelasticFlow {
      //! a simple alias
      using Data = tfel::utilities::Data;
      //! a simple alias
      using DataMap = std::map<std::string, Data>;
      //! a simple alias
      using ModellingHypothesis = tfel::material::ModellingHypothesis;
      //! a simple alias
      using Hypothesis = ModellingHypothesis::Hypothesis;
      //! a simple alias
      using MaterialPropertyInput = BehaviourDescription::MaterialPropertyInput;
      /*!
       * \param[in,out] bd: behaviour description
       * \param[in,out] dsl: abstract behaviour dsl
       * \param[in] id: flow id
       * \param[in] d: options
       */
      virtual void initialize(BehaviourDescription&,
                              AbstractBehaviourDSL&,
                              const std::string&,
                              const DataMap&) = 0;
      /*!
       * \return the flow options
       */
      virtual std::vector<OptionDescription> getOptions() const = 0;
      /*!
       * \brief complete the variable description
       * \param[in/out] bd: behaviour description
       * \param[in] dsl: abstract behaviour dsl
       * \param[in] id: flow id
       */
      virtual void completeVariableDeclaration(BehaviourDescription&,
                                               const AbstractBehaviourDSL&,
                                               const std::string&) const = 0;
      /*!
       * \brief method called at the end of the input file processing
       * \param[in] dsl: abstract behaviour dsl
       * \param[in] bd: behaviour description
       * \param[in] sp: stress potential
       * \param[in] id: flow id
       */
      virtual void endTreatment(BehaviourDescription&,
                                const AbstractBehaviourDSL&,
                                const StressPotential&,
                                const std::string&) const = 0;
      /*!
       * \brief returns if the flow requires an activation state for the
       * resolution.
       * \note this basically means that an isotropic hardening rule is defined
       * and this method could also have been named
       * `isIsotropicHardeningRuleDefined`, but this name does not reflect the
       * true intention of the author.
       */
      virtual bool requiresActivationState() const = 0;
      /*!
       * \brief add the intialization of the activation state of the
       * `BehaviourData::BeforeInitializeLocalVariables` code block`.
       * \note at this stage, the stress potential has already been called and
       * the elastic prediction of the stress `sigel` is available.
       * \param[in/out] bd: behaviour description
       * \param[in] sp: stress potential
       * \param[in] id: flow id
       */
      virtual void computeInitialActivationState(BehaviourDescription&,
                                                 const StressPotential&,
                                                 const std::string&) const = 0;
      //! destructor
      virtual ~InelasticFlow();

    };  // end of struct InelasticFlow

  }  // end of namespace bbrick

}  // end of namespace mfront

#endif /* LIB_MFRONT_BEHAVIOURBRICK_INELASTICFLOW_HXX */
