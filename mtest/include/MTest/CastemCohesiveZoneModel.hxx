/*! 
 * \file  mtest/include/MTest/CastemCohesiveZoneModel.hxx
 * \brief
 * \author Thomas Helfer
 * \brief 07 avril 2013
 * \copyright Copyright (C) 2006-2018 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef LIB_MTEST_CASTEMCOHESIVEZONEMODEL_HXX
#define LIB_MTEST_CASTEMCOHESIVEZONEMODEL_HXX 

#include"TFEL/System/ExternalFunctionsPrototypes.hxx"
#include"MTest/StandardBehaviourBase.hxx"

namespace mtest
{

  /*!
   * A class to handle mechanical beheaviours written using the umat
   * interface
   */
  struct TFEL_VISIBILITY_LOCAL CastemCohesiveZoneModel
    : public StandardBehaviourBase
  {
    /*!
     * \param[in] h : modelling hypothesis
     * \param[in] l : library name
     * \param[in] b : behaviour name
     */
    CastemCohesiveZoneModel(const Hypothesis,
			    const std::string&,
			    const std::string&);
    /*!
     * \brief compute the *real* rotation matrix
     * \param[in] mp : material properties
     * \param[in] r  : rotation matrix defined by the user
     * \note this method is only meaningfull for the umat (Cast3M)
     * interface
     */
    tfel::math::tmatrix<3u,3u,real>
    getRotationMatrix(const tfel::math::vector<real>&,
		      const tfel::math::tmatrix<3u,3u,real>&) const override;
    /*!
     * \param[out] v : initial values of the driving variables
     */
    virtual void
    getGradientsDefaultInitialValues(tfel::math::vector<real>&) const override;
    /*!
     * \brief allocate internal workspace
     * \param[in] wk : workspace
     */
    void allocate(BehaviourWorkSpace&) const override;
    /*!
     * \return the default type of stiffness matrix used by the behaviour
     */
     StiffnessMatrixType getDefaultStiffnessMatrixType() const override;
    /*!
     * \brief integrate the mechanical behaviour over the time step
     * \return a pair. The first member is true if the integration was
     * successfull, false otherwise. The second member contains a time
     * step scaling factor.
     * \param[out] wk    : behaviour workspace
     * \param[in]  s     : current state
     * \param[in]  ktype : type of the stiffness matrix
     */
    std::pair<bool,real>
    computePredictionOperator(BehaviourWorkSpace&,
			      const CurrentState&,
			      const StiffnessMatrixType) const override;
    /*!
     * \brief integrate the mechanical behaviour over the time step
     * \return a pair. The first member is true if the integration was
     * successfull, false otherwise. The second member contains a time
     * step scaling factor.
     * \param[out/in] s     : current state
     * \param[out]    wk    : behaviour workspace
     * \param[in]     dt    : time increment
     * \param[in]     ktype : type of the stiffness matrix
     */
    std::pair<bool,real>
    integrate(CurrentState&,
	      BehaviourWorkSpace&,
	      const real,
	      const StiffnessMatrixType) const override;
    std::vector<std::string> getOptionalMaterialProperties() const override;
    void setOptionalMaterialPropertiesDefaultValues(EvolutionManager&,
						    const EvolutionManager&) const override;
    //! destructor
    ~CastemCohesiveZoneModel() override;
  protected:
    /*!
     * \brief compute the elastic stiffness
     * \param[out] Kt   : tangent operator
     * \param[in]  mp   : material properties
     * \param[in]  drot : rotation matrix (Fortran convention)
     */
    virtual void
    computeElasticStiffness(tfel::math::matrix<real>&,
			    const tfel::math::vector<real>&,
			    const tfel::math::tmatrix<3u,3u,real>&) const;
    //! the umat fonction
    tfel::system::CastemFctPtr fct;
  }; // end of struct MTest
  
} // end of namespace mtest

#endif /* LIB_MTEST_CASTEMCOHESIVEZONEMODEL_HXX */

