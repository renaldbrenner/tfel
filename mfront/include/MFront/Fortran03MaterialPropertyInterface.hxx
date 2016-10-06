/*!
 * \file   mfront/include/MFront/Fortran03MaterialPropertyInterface.hxx
 * \brief  This file declares the Fortran03MaterialPropertyInterface class.
 * \author Helfer Thomas
 * \date   1 décembre 2008
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef LIB_MFRONTFORTRAN03LAWINTERFACE_H_
#define LIB_MFRONTFORTRAN03LAWINTERFACE_H_ 

#include"MFront/CMaterialPropertyInterfaceBase.hxx"

namespace mfront{

  struct Fortran03MaterialPropertyInterface
    : public CMaterialPropertyInterfaceBase
  {
    static std::string 
    getName(void);
    
    Fortran03MaterialPropertyInterface();
    /*!
     * \param[in] k  : keyword treated
     * \param[in] i:   list of interfaces to which the keyword is restricted
     * \param[in] p  : iterator to the current token
     * \param[in] pe : iterator past the end of the file
     * \return a pair. The first entry is true if the keyword was
     * treated by the interface. The second entry is an iterator after
     * the last token treated.
     */
    virtual std::pair<bool,tfel::utilities::CxxTokenizer::TokensContainer::const_iterator>
    treatKeyword(const std::string&,
		 const std::vector<std::string>&,
		 tfel::utilities::CxxTokenizer::TokensContainer::const_iterator,
		 const tfel::utilities::CxxTokenizer::TokensContainer::const_iterator) override;
    /*!
     * \brief : fill the target descripton
     * \param[out] d   : target description
     * \param[in]  mpd : material property description
     */
    virtual void getTargetsDescription(TargetsDescription&,
				       const MaterialPropertyDescription&) override;
    /*!
     * \brief generate the output files
     * \param[in] mpd : material property description
     * \param[in] fd  : mfront file description
     */
    virtual void writeOutputFiles(const MaterialPropertyDescription&,
				  const FileDescription&) override;
    //! destructor
    virtual ~Fortran03MaterialPropertyInterface();
        
  private:
    
    virtual void
    writeParameterList(std::ostream&,
		       const VariableDescriptionContainer&) override;

    virtual void
    writeInterfaceSpecificVariables(const VariableDescriptionContainer&) override;

    virtual void
    writeSrcPreprocessorDirectives(const MaterialPropertyDescription&) override;

    virtual void
    writeBeginHeaderNamespace(void) override;

    virtual void
    writeEndHeaderNamespace(void) override;

    virtual void
    writeBeginSrcNamespace(void) override;

    virtual void
    writeEndSrcNamespace(void) override;

    /*!
     * \param const std::string&, name of the material
     * \param const std::string&, name of the class
     */
    virtual std::string
    getHeaderFileName(const std::string&,
		      const std::string&) const override;

    /*!
     * \param const std::string&, name of the material
     * \param const std::string&, name of the class
     */
    virtual std::string
    getSrcFileName(const std::string&,
		   const std::string&) const override;

    /*!
     * \param const std::string&, name of the material
     * \param const std::string&, name of the class
     */
    virtual std::string
    getFunctionName(const std::string&,
		    const std::string&) const override;

    /*!
     * \param const std::string&, name of the material
     * \param const std::string&, name of the class
     */
    virtual std::string
    getCheckBoundsFunctionName(const std::string&,
			       const std::string&) const override;

    virtual bool
    requiresCheckBoundsFunction(void) const override;

  private:

    std::string module;
    
  }; // end of Fortran03MaterialPropertyInterface

} // end of namespace mfront

#endif /* LIB_MFRONTFORTRAN03LAWINTERFACE_H_ */
