/*!
 * \file   mfront/include/MFront/MFrontLawInterfaceFactory.hxx
 * \brief  
 * \author Helfer Thomas
 * \date   09 nov 2006
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef _LIB_MFRONTLAWINTERFACEFACTORY_HXX_
#define _LIB_MFRONTLAWINTERFACEFACTORY_HXX_ 

#include<vector>
#include<string>
#include<map>

#include"TFEL/Config/TFELConfig.hxx"
#include"MFront/MFrontLawVirtualInterface.hxx"

namespace mfront{

  struct TFEL_VISIBILITY_EXPORT MFrontLawInterfaceFactory
  {

    typedef MFrontLawVirtualInterface* (*InterfaceCreator)(void);
    
    static MFrontLawInterfaceFactory&
    getMFrontLawInterfaceFactory();

    std::vector<std::string>
    getRegistredInterfaces(void);

    void
    registerInterfaceCreator(const std::string&,
			     InterfaceCreator);

    void
    registerInterfaceAlias(const std::string&,
			   const std::string&);

    void
    registerInterfaceDependency(const std::string&,
				const std::string&);
    
    std::vector<std::string>
    getInterfaceDependencies(const std::string&);

    MFrontLawVirtualInterface* 
    getInterfacePtr(const std::string&);
    
    void
    reset(void);

    void
    clear(void);

    ~MFrontLawInterfaceFactory();

  private:

    typedef std::map<std::string,std::string> AliasContainer;
    typedef std::map<std::string,InterfaceCreator> InterfaceCreatorsContainer;
    typedef std::map<std::string,MFrontLawVirtualInterface *> InterfaceContainer;
    typedef std::map<std::string,std::vector<std::string> > InterfaceDependencyContainer;

    TFEL_VISIBILITY_LOCAL
    MFrontLawInterfaceFactory();

    TFEL_VISIBILITY_LOCAL
    InterfaceDependencyContainer&
    getDependenciesMap(void);

    TFEL_VISIBILITY_LOCAL
    InterfaceCreatorsContainer&
    getInterfaceCreatorsMap(void);

    TFEL_VISIBILITY_LOCAL
    InterfaceContainer&
    getInterfacesMap(void);

    TFEL_VISIBILITY_LOCAL
    AliasContainer&
    getAliasesMap(void);

  };

} // end of namespace mfront  

#endif /* _LIB_MFRONTLAWINTERFACEFACTORY_HXX */
