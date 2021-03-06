/*! 
 * \file   mfront/include/MFront/ModelDescription.hxx
 * \brief
 * \author Thomas Helfer
 * \brief  12 jun 2010
 * \copyright Copyright (C) 2006-2018 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef LIB_MFRONT_MODELDESCRIPTION_HXX
#define LIB_MFRONT_MODELDESCRIPTION_HXX 

#include<set>
#include<map>
#include<string>

#include"MFront/MFrontConfig.hxx"
#include"MFront/VariableDescription.hxx"
#include"MFront/StaticVariableDescription.hxx"
#include"MFront/VariableBoundsDescription.hxx"

namespace mfront
{

  //! Class describing a model
  struct MFRONT_VISIBILITY_EXPORT ModelDescription
  {
    //! a model may contain several function
    struct MFRONT_VISIBILITY_EXPORT Function
    {
      //! default constructor
      Function();
      //! copy constructor
      Function(const Function&);
      //! move constructor
      Function(Function&&);
      //! assignement
      Function& operator=(const Function&);
      //! move assignement
      Function& operator=(Function&&);
      //! destructor
      ~Function();
      //! list of variables used by the function
      std::set<std::string> usedVariables;
      //! list of variables modified by the function
      std::set<std::string> modifiedVariables;
      //! list of constant material properties used by the function
      std::set<std::string> constantMaterialProperties;
      //! list of parameters used by the function
      std::set<std::string> parameters;
      //! depths of each variables
      std::map<std::string,unsigned short> depths;
      //! name of the function
      std::string name;
      //! body of the function
      std::string body;
      //! line starting the definition of the function in the initial
      //! MFront file
      unsigned int line = 0u;
      //! if true, the body of the function uses the time increment dt
      bool useTimeIncrement = false;
    }; // end of struct MFrontData::Function
    /*!
     * \brief decompose a variable name to get the basis and the depth
     * of the variable
     */
    std::pair<std::string,unsigned short>
    decomposeVariableName(const std::string&) const;
    //! defaut constructor
    ModelDescription();
    //! copy constructor
    ModelDescription(const ModelDescription&);
    //! move constructor
    ModelDescription(ModelDescription&&);
    //! assignement operator
    ModelDescription& operator=(const ModelDescription&);
    //! move assignement operator
    ModelDescription& operator=(ModelDescription&&);
    /*!
     * \return the variable description with the given name
     * \param[in] n: variable name
     */
    const VariableDescription&
    getVariableDescription(const std::string&) const;
    /*!
     * \brief associate a glossary name to a variable 
     * \param[in] v: variable name
     * \param[in] g: glossary name
     */
    void setGlossaryName(const std::string&,
			 const std::string&);
    /*!
     * \brief associate a glossary name to a variable 
     * \param[in] v: variable name
     * \param[in] g: glossary name
     */
    void setEntryName(const std::string&,
		      const std::string&);
    /*!
     * \brief add a material law
     * \param[in] m : added material law name
     */
    void addMaterialLaw(const std::string&);
    /*!
     * \brief append the given code to the includes
     */
    void appendToIncludes(const std::string&);
    /*!
     * \brief append the given code to the members
     */
    void appendToMembers(const std::string&);
    /*!
     * \brief append the given code to the private code
     */
    void appendToPrivateCode(const std::string&);
    /*!
     * \brief append the given code to the sources
     */
    void appendToSources(const std::string&);
    //! desctructor
    virtual ~ModelDescription();
    //! list of functions declared
    std::vector<Function> functions;
    //! list of all outputs
    VariableDescriptionContainer outputs;
    //! list of all inputs
    VariableDescriptionContainer inputs;
    //! list of all parameters
    VariableDescriptionContainer parameters;
    //! list of all constant material properties
    VariableDescriptionContainer constantMaterialProperties;
    //! static variables
    StaticVariableDescriptionContainer staticVars;
    //! material name
    std::string material;
    //! library name
    std::string library;
    //! class name
    std::string className;
    //! additionnal header files
    std::string includes;
    //!specific sources
    std::string sources;
    //! private code
    std::string privateCode;
    //! class member
    std::string members;
    std::set<std::string> domains;
    //! list of material laws used
    std::vector<std::string> materialLaws;
    //! list of variables names
    std::set<std::string> memberNames;
    //! list of variables names
    std::set<std::string> staticMemberNames;
    /*!
     * \brief register a name.
     * \param[in] n : name
     * \param[in] b : if false, don't check if variable has already
     * been reserved yet. If true, check if the variable has alredy
     * been registred and throws an exception if it does, register it
     * otherwise
     * \note this method is called internally by the registerVariable
     * and registerStaticVariable methods.
     */
    void reserveName(const std::string&);
    /*!
     * \brief register a static member name
     * \param[in] n : name
     */
    void registerMemberName(const std::string&);
    /*!
     * \brief register a static member name
     * \param[in] n : name
     */
    void registerStaticMemberName(const std::string&);
    /*!
     * \brief look if a name is reserved
     * \param[in] n : name
     */
    bool isNameReserved(const std::string&) const;
    //! \return the list of reserved names
    std::set<std::string>& getReservedNames();
  protected:
    /*!
     * check that a variable exists
     * \param[in] v: variable name
     */
    void checkVariableExistence(const std::string&) const;
    //! \return the list of reserved names
    const std::set<std::string>& getReservedNames() const;
  private:
    /*!
     * \return the variable description with the given name
     * \param[in] n: variable name
     */
    VariableDescription& getVariableDescription(const std::string&);
    //! set glossary names
    std::map<std::string,std::string> glossaryNames;
    //! entry names
    std::map<std::string,std::string> entryNames;
    //! list of reserved names
    std::set<std::string> reservedNames;
  }; // end of struct ModelDescription

} // end of namespace mfront

#endif /* LIB_MFRONT_MODELDESCRIPTION_HXX */
