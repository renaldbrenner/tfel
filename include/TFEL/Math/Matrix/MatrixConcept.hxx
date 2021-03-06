/*!
 * \file   include/TFEL/Math/Matrix/MatrixConcept.hxx
 * \brief  This file declares the MatrixTraits, MatrixConcept and MatrixType classes.
 * \author Thomas Helfer
 * \date   04 May 2006
 * \copyright Copyright (C) 2006-2018 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef LIB_TFEL_MATH_MATRIXCONCEPT_HXX
#define LIB_TFEL_MATH_MATRIXCONCEPT_HXX 1

#include<type_traits>

#include"TFEL/Config/TFELConfig.hxx"
#include"TFEL/Metaprogramming/InvalidType.hxx"
#include"TFEL/Math/General/ResultType.hxx"
#include"TFEL/Math/General/BasicOperations.hxx"
#include"TFEL/Math/General/ConceptRebind.hxx"
#include"TFEL/Math/Forward/MatrixConcept.hxx"

namespace tfel{

  namespace math{

    /*!
     * \class MatrixTraits
     * \brief A traits class for matrices.
     * \param T, a matrix type.
     * This traits gives acces to the two main characteristics, 
     * its underlying numerical type and its index type.
     * \warning this class shall be overloaded for each matrix type. 
     * This is du to the fact that we utilise CRTP to define the 
     * MatrixConcept class, so the characteristic of the matrix type
     * must be known \b before this type is defined.
     * \author Thomas Helfer
     * \date   04 May 2006
     */
    template<typename T>
    struct MatrixTraits{
      /*!
       * Gives acces to the numerical types upon which the matrix is build.
       * \see InvalidType
       */
      typedef tfel::meta::InvalidType NumType;
      /*!
       * Gives access to the index type used by the matrix.
       * \see InvalidType
       */
      typedef tfel::meta::InvalidType IndexType;
    };
    //! a simple alias
    template<typename T>
    using MatrixNumType = typename MatrixTraits<T>::NumType;
    /*!
     * \class MatrixTag
     * \brief Helper class to characterise matrices.
     */ 
    struct MatrixTag
    {}; // end of MatrixTag

    /*!
     * \class MatrixConcept
     * \brief A class used to model the concept of matrices.
     * Here we use the curiously recurring template pattern.  
     * \param T, a matrix type.
     * \author Thomas Helfer
     * \date   04 May 2006
     */
    template<typename T>
    struct MatrixConcept 
    {
      using ConceptTag = MatrixTag;
      /*!
       * \param  i: the row index
       * \param  j: the column index
       * \return m(i,j)
       */
      typename MatrixTraits<T>::NumType
      operator()(const typename MatrixTraits<T>::IndexType,
		 const typename MatrixTraits<T>::IndexType) const ;

    protected:
      MatrixConcept() = default;
      MatrixConcept(MatrixConcept&&) = default;
      MatrixConcept(const MatrixConcept&) = default;
      MatrixConcept&
      operator=(const MatrixConcept&) = default;
      ~MatrixConcept() = default;
    };

    //! paratial specialisation for matrices
    template<typename Type>
    struct ConceptRebind<MatrixTag,Type>
    {
      using type = MatrixConcept<Type>;
    };
  
  } // end of namespace math

} // end of namespace tfel

#include"TFEL/Math/Matrix/MatrixConcept.ixx"

#endif /* LIB_TFEL_MATH_MATRIXCONCEPT_HXX */
