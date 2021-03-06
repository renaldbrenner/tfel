/*! 
 * \file  include/TFEL/Math/power.hxx
 * \brief
 * \author Thomas Helfer
 * \brief 13 janv. 2012
 * \copyright Copyright (C) 2006-2018 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef LIB_TFEL_MATH_POWER_HXX
#define LIB_TFEL_MATH_POWER_HXX 

#include<type_traits>
#include"TFEL/Config/TFELConfig.hxx"
#include"TFEL/TypeTraits/IsScalar.hxx"
#include"TFEL/Math/General/ComputeUnaryResult.hxx"

namespace tfel{

  namespace math{

    template<int N,unsigned int D=1>
    struct Power;

    template<int N,unsigned int D>
    struct UnaryResultType<float,Power<N,D> >
    {
      using type = float;
    };

    template<int N,unsigned int D>
    struct UnaryResultType<double,Power<N,D> >
    {
      using type = double;
    };

    template<int N,unsigned int D>
    struct UnaryResultType<long double,Power<N,D> >
    {
      using type = long double;
    };

    template<int N,typename T>
    TFEL_MATH_INLINE
    typename std::enable_if<
      tfel::typetraits::IsScalar<T>::cond,
      T>::type
    power(const T);
  
    template<int N,unsigned int D,typename T>
    TFEL_MATH_INLINE
    typename std::enable_if<
      tfel::typetraits::IsScalar<T>::cond,
      T>::type
    power(const T);

  } // end of namespace math

} // end of namespace tfel

#include"TFEL/Math/power.ixx"

#endif /* LIB_TFEL_MATH_POWER_HXX */
