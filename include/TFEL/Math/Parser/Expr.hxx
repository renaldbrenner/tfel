/*!
 * \file   include/TFEL/Math/Parser/Expr.hxx
 * \brief  
 * 
 * \author Thomas Helfer
 * \date   02 oct 2007
 * \copyright Copyright (C) 2006-2018 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef LIB_TFEL_EXPR_HXX
#define LIB_TFEL_EXPR_HXX 

#include<map>
#include<set>
#include<vector>
#include<string>
#include<memory>

namespace tfel
{
  namespace math
  {

    namespace parser
    {

      struct Expr
      {
	virtual double getValue() const = 0;
	virtual void
	checkCyclicDependency(std::vector<std::string>&) const = 0;
	virtual std::shared_ptr<Expr>
	resolveDependencies(const std::vector<double>&) const = 0;
	virtual std::shared_ptr<Expr>
	clone(const std::vector<double>&) const = 0;
	virtual std::shared_ptr<Expr>
	differentiate(const std::vector<double>::size_type,
		      const std::vector<double>&) const = 0;
	virtual void
	getParametersNames(std::set<std::string>&) const = 0;
	/*!
	 * \return a string representation of the evaluator suitable to
	 * be integrated in a C++ code.
	 * \param[in] m: a map used to change the names of the variables
	 */
	virtual std::string
	getCxxFormula(const std::vector<std::string>&) const = 0;
	
	virtual std::shared_ptr<Expr>
	createFunctionByChangingParametersIntoVariables(const std::vector<double>&,
							const std::vector<std::string>&,
							const std::map<std::string,
							std::vector<double>::size_type>&) const = 0;
	virtual ~Expr();
      }; // end of struct Expr

      //! a simple alias
      using ExprPtr =  std::shared_ptr<Expr>;

      //!a simple helper function for checkCyclicDependency
      void mergeVariablesNames(std::vector<std::string>&,
			       const std::vector<std::string>&);

    } // end of namespace parser

  } // end of namespace math

} // end of namespace tfel

#endif /* LIB_TFEL_EXPR_HXX */
