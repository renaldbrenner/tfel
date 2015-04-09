/*!
 * \file   include/TFEL/Math/st2tot2.hxx  
 * \brief    
 * \author Helfer Thomas
 * \date   19 November 2013
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef _LIB_TFEL_MATH_ST2TOT2_H_
#define _LIB_TFEL_MATH_ST2TOT2_H_ 

#include<string>
#include<cstddef>
#include<cassert>

#include"TFEL/Config/TFELConfig.hxx"

#include"TFEL/Metaprogramming/StaticAssert.hxx"

#include"TFEL/TypeTraits/IsScalar.hxx"
#include"TFEL/TypeTraits/BaseType.hxx"
#include"TFEL/TypeTraits/IsInvalid.hxx"
#include"TFEL/TypeTraits/IsAssignableTo.hxx"
#include"TFEL/TypeTraits/IsSafelyReinterpretCastableTo.hxx"

#include"TFEL/Math/fsarray.hxx"
#include"TFEL/Math/General/BasicOperations.hxx"
#include"TFEL/Math/General/EmptyRunTimeProperties.hxx"

#include"TFEL/Math/Forward/st2tot2.hxx"
#include"TFEL/Math/Stensor/StensorSizeToDime.hxx"
#include"TFEL/Math/Tensor/TensorSizeToDime.hxx"
#include"TFEL/Math/ST2toT2/ST2toT2Concept.hxx"
#include"TFEL/Math/ST2toT2/ST2toT2ConceptOperations.hxx"
#include"TFEL/Math/ST2toT2/ST2toT2Expr.hxx"
#include"TFEL/Math/ST2toT2/StensorProductLeftDerivativeExpr.hxx"
#include"TFEL/Math/ST2toT2/StensorProductRightDerivativeExpr.hxx"

namespace tfel{
  
  namespace math {

    /*
     * Partial specialisation for st2tot2
     */
    template<unsigned short N,typename T>
    struct ST2toT2Traits<st2tot2<N,T> >{
      typedef T              NumType;
      typedef unsigned short IndexType;
      static const unsigned short dime = N;
    };

    /*!
     * \brief a base for stensor or classes acting like stensor.
     * \param Child : child class
     * \param N     : spatial dimension
     * \param T     : numerical type
     */
    template<typename Child>
    struct st2tot2_base
    {
      /*!
       * Assignement operator
       */
      template<typename St2tot2Type>
      TFEL_MATH_INLINE 
      typename tfel::meta::EnableIf<
	tfel::meta::Implements<St2tot2Type,ST2toT2Concept>::cond &&
	ST2toT2Traits<Child>::dime==ST2toT2Traits<St2tot2Type>::dime &&
	tfel::typetraits::IsAssignableTo<typename ST2toT2Traits<St2tot2Type>::NumType,
					 typename ST2toT2Traits<Child>::NumType>::cond,
	Child&>::type
      operator=(const St2tot2Type&);
      //! Assignement operator
      template<typename St2tot2Type>
      TFEL_MATH_INLINE 
      typename tfel::meta::EnableIf<
	tfel::meta::Implements<St2tot2Type,ST2toT2Concept>::cond &&
	ST2toT2Traits<Child>::dime==ST2toT2Traits<St2tot2Type>::dime &&
	tfel::typetraits::IsAssignableTo<typename ST2toT2Traits<St2tot2Type>::NumType,
					 typename ST2toT2Traits<Child>::NumType>::cond,
	Child&>::type
      operator+=(const St2tot2Type&);
      //! Assignement operator
      template<typename St2tot2Type>
      TFEL_MATH_INLINE 
      typename tfel::meta::EnableIf<
	tfel::meta::Implements<St2tot2Type,ST2toT2Concept>::cond &&
	ST2toT2Traits<Child>::dime==ST2toT2Traits<St2tot2Type>::dime &&
	tfel::typetraits::IsAssignableTo<typename ST2toT2Traits<St2tot2Type>::NumType,
					 typename ST2toT2Traits<Child>::NumType>::cond,
	Child&>::type
      operator-=(const St2tot2Type&);
      /*!
       * operator*=
       */
      template<typename T2>
      TFEL_MATH_INLINE 
      typename tfel::meta::EnableIf<
	tfel::typetraits::IsScalar<T2>::cond&&
	tfel::meta::IsSameType<typename ResultType<typename ST2toT2Traits<Child>::NumType,
						   T2,OpMult>::type,
			       typename ST2toT2Traits<Child>::NumType>::cond,
	Child&>::type
      operator*=(const T2);
      /*!
       * operator/=
       */
      template<typename T2>
      TFEL_MATH_INLINE 
      typename tfel::meta::EnableIf<
	tfel::typetraits::IsScalar<T2>::cond&&
        tfel::meta::IsSameType<typename ResultType<typename ST2toT2Traits<Child>::NumType,
						   T2,OpDiv>::type,
			       typename ST2toT2Traits<Child>::NumType>::cond,
	Child&>::type
      operator/=(const T2);
    }; // end of struct st2tot2_base

    template<unsigned short N,typename T>
    struct st2tot2
      : public ST2toT2Concept<st2tot2<N,T> >,
	public fsarray<StensorDimeToSize<N>::value*TensorDimeToSize<N>::value,T>,
	public st2tot2_base<st2tot2<N,T> >
    {
      /*!
       * \param[in] B : second tensor of the product
       * \return the left part of the derivative of a tensor product
       */
      template<typename StensorType>
      static TFEL_MATH_INLINE 
      typename tfel::meta::EnableIf<
	tfel::meta::Implements<StensorType,StensorConcept>::cond &&
	StensorTraits<StensorType>::dime==N&&
	tfel::typetraits::IsAssignableTo<typename StensorTraits<StensorType>::NumType,T>::cond,
	ST2toT2Expr<st2tot2<N,T>,StensorProductLeftDerivativeExpr<N> > >::type
      tpld(const StensorType&);
      /*!
       * \param[in] B : second tensor of the product
       * \param[in] C : derivative of the first tensor
       * \return the left part of the derivative of a tensor product
       */
      template<typename StensorType,
	       typename ST2toST2Type>
      static TFEL_MATH_INLINE 
      typename tfel::meta::EnableIf<
	tfel::meta::Implements<StensorType,StensorConcept>::cond &&
	tfel::meta::Implements<ST2toST2Type,ST2toST2Concept>::cond &&
	StensorTraits<StensorType>::dime==N&&
	ST2toST2Traits<ST2toST2Type>::dime==N&&
	tfel::typetraits::IsAssignableTo<typename ComputeBinaryResult<typename StensorTraits<StensorType>::NumType,
								      typename ST2toST2Traits<ST2toST2Type>::NumType,
								      OpMult>::Result,T>::cond,
	ST2toT2Expr<st2tot2<N,T>,StensorProductLeftDerivativeExpr<N> > >::type
      tpld(const StensorType&,
	   const ST2toST2Type&);
      /*!
       * \param[in] A : first tensor of the product
       * \return the right part of the derivative of a tensor product
       */
      template<typename StensorType>
      static TFEL_MATH_INLINE 
      typename tfel::meta::EnableIf<
	tfel::meta::Implements<StensorType,StensorConcept>::cond &&
	StensorTraits<StensorType>::dime==N&&
	tfel::typetraits::IsAssignableTo<typename StensorTraits<StensorType>::NumType,T>::cond,
	ST2toT2Expr<st2tot2<N,T>,StensorProductRightDerivativeExpr<N> > >::type
      tprd(const StensorType&);
      /*!
       * \param[in] A : first tensor of the product
       * \param[in] C : derivative of the first tensor
       * \return the right part of the derivative of a tensor product
       */
      template<typename StensorType,
	       typename ST2toST2Type>
      static TFEL_MATH_INLINE 
      typename tfel::meta::EnableIf<
	tfel::meta::Implements<StensorType,StensorConcept>::cond &&
	tfel::meta::Implements<ST2toST2Type,ST2toST2Concept>::cond &&
	StensorTraits<StensorType>::dime==N&&
	ST2toST2Traits<ST2toST2Type>::dime==N&&
	tfel::typetraits::IsAssignableTo<typename ComputeBinaryResult<typename StensorTraits<StensorType>::NumType,
								      typename ST2toST2Traits<ST2toST2Type>::NumType,
								      OpMult>::Result,T>::cond,
	ST2toT2Expr<st2tot2<N,T>,StensorProductRightDerivativeExpr<N> > >::type
      tprd(const StensorType&,
	   const ST2toST2Type&);
      /*!
       * This is a StensorConcept requirement.
       */
      typedef EmptyRunTimeProperties RunTimeProperties;
      /*!
       * \brief Default Constructor 
       */
      TFEL_MATH_INLINE 
      explicit st2tot2()
      {};
      /*!
       * \brief Default Constructor 
       * \param T, value used to initialise the components of the st2tot2 
       */
      TFEL_MATH_INLINE 
      explicit st2tot2(const T);
      /*!
       * \brief Copy Constructor
       */
      TFEL_MATH_INLINE 
      st2tot2(const st2tot2<N,T>& src);
      // Copy Constructor
      template<typename T2,typename Expr>
      TFEL_MATH_INLINE 
      st2tot2(const ST2toT2Expr<st2tot2<N,T2>,Expr>& src);
      /*!
       * Import values
       */
      template<typename T2>
      TFEL_MATH_INLINE2 typename tfel::meta::EnableIf<
	tfel::typetraits::IsSafelyReinterpretCastableTo<T2,typename tfel::typetraits::BaseType<T>::type>::cond,
	void>::type
      import(const T2* const);
      /*!
       * Assignement operator
       */
      using st2tot2_base<st2tot2>::operator=;

      //! access operator
      TFEL_MATH_INLINE const T& operator()(const unsigned short,const unsigned short) const;      
      //! access operator
      TFEL_MATH_INLINE       T& operator()(const unsigned short,const unsigned short);
      /*!
       * Return the RunTimeProperties of the tvector
       * \return tvector::RunTimeProperties
       */
      TFEL_MATH_INLINE RunTimeProperties
      getRunTimeProperties(void) const;

      template<typename InputIterator>
      TFEL_MATH_INLINE2 void copy(const InputIterator src);

    }; // end of struct st2tot2
        
  } // end of namespace math

  namespace typetraits{
    
    template<unsigned short N,typename T2,typename T>
    struct IsAssignableTo<tfel::math::st2tot2<N,T2>,
			  tfel::math::st2tot2<N,T> >
    {
      /*!
       *  Result
       */
      static const bool cond = IsAssignableTo<T2,T>::cond;
    };
    
  } // end of namespace typetraits

} // end of namespace tfel

#include"TFEL/Math/ST2toT2/st2tot2.ixx"
#include"TFEL/Math/ST2toT2/st2tot2ResultType.hxx"

#endif /* _LIB_TFEL_MATH_ST2TOT2_H */

