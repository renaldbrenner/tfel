/*!
 * \file   include/TFEL/Math/Matrix/MatrixConcept.ixx
 * \author Thomas Helfer
 * \copyright Copyright (C) 2006-2018 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef TFEL_MATH_MATRIX_CONCEPT_IXX
#define TFEL_MATH_MATRIX_CONCEPT_IXX 1

namespace tfel{

  namespace math{
    
    template<class T>
    TFEL_MATH_INLINE 
    typename MatrixTraits<T>::NumType
    MatrixConcept<T>::operator()(const typename MatrixTraits<T>::IndexType i,
				 const typename MatrixTraits<T>::IndexType j) const {
      return static_cast<const T&>(*this).operator()(i,j);
    }
    
  } // end of namespace math

} // end of namespace tfel

#endif /* TFEL_MATH_MATRIX_CONCEPT_IXX */
