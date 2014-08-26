/*!
 * \file   st2tost2.ixx
 * \brief  This file implements the methods of the class st2tost2.
 * \author Helfer Thomas
 * \date   02 jun 2006
 */

#ifndef _LIB_TFEL_ST2TOST2_IXX_
#define _LIB_TFEL_ST2TOST2_IXX_ 

#include <cmath>
#include <iterator>
#include <algorithm>

#include"TFEL/FSAlgorithm/FSAlgorithm.hxx"

#include"TFEL/Metaprogramming/EnableIf.hxx"

#include"TFEL/TypeTraits/IsSafelyReinterpretCastableTo.hxx"
#include"TFEL/Math/General/StorageTraits.hxx"
#include"TFEL/Math/Vector/VectorUtilities.hxx"
#include"TFEL/Math/Matrix/MatrixUtilities.hxx"

namespace tfel{

  namespace math {


    // Assignement operator
    template<typename Child>
    template<typename ST2toST2Type>
    typename tfel::meta::EnableIf<
      tfel::meta::Implements<ST2toST2Type,ST2toST2Concept>::cond &&
      ST2toST2Traits<Child>::dime==ST2toST2Traits<ST2toST2Type>::dime &&
      tfel::typetraits::IsAssignableTo<typename ST2toST2Traits<ST2toST2Type>::NumType,
				       typename ST2toST2Traits<Child>::NumType>::cond,
      Child&>::type
    st2tost2_base<Child>::operator=(const ST2toST2Type& src)
    {
      Child& child = static_cast<Child&>(*this);
      matrix_utilities<StensorDimeToSize<ST2toST2Traits<Child>::dime>::value,
		       StensorDimeToSize<ST2toST2Traits<Child>::dime>::value,
		       StensorDimeToSize<ST2toST2Traits<Child>::dime>::value>::copy(src,child);
      return child;
    }

    template<typename Child>
    template<typename ST2toST2Type>
    typename tfel::meta::EnableIf<
      tfel::meta::Implements<ST2toST2Type,ST2toST2Concept>::cond &&
      ST2toST2Traits<Child>::dime==ST2toST2Traits<ST2toST2Type>::dime &&
      tfel::typetraits::IsAssignableTo<typename ST2toST2Traits<ST2toST2Type>::NumType,
				       typename ST2toST2Traits<Child>::NumType>::cond,
      Child&>::type
    st2tost2_base<Child>::operator+=(const ST2toST2Type& src)
    {
      Child& child = static_cast<Child&>(*this);
      matrix_utilities<StensorDimeToSize<ST2toST2Traits<Child>::dime>::value,
		       StensorDimeToSize<ST2toST2Traits<Child>::dime>::value,
		       StensorDimeToSize<ST2toST2Traits<Child>::dime>::value>::plusEqual(child,src);
      return child;
    }

    // Assignement operator
    template<typename Child>
    template<typename ST2toST2Type>
    typename tfel::meta::EnableIf<
      tfel::meta::Implements<ST2toST2Type,ST2toST2Concept>::cond &&
      ST2toST2Traits<Child>::dime==ST2toST2Traits<ST2toST2Type>::dime &&
      tfel::typetraits::IsAssignableTo<typename ST2toST2Traits<ST2toST2Type>::NumType,
				       typename ST2toST2Traits<Child>::NumType>::cond,
      Child&>::type
    st2tost2_base<Child>::operator-=(const ST2toST2Type& src)
    {
      Child& child = static_cast<Child&>(*this);
      matrix_utilities<StensorDimeToSize<ST2toST2Traits<Child>::dime>::value,
		       StensorDimeToSize<ST2toST2Traits<Child>::dime>::value,
		       StensorDimeToSize<ST2toST2Traits<Child>::dime>::value>::minusEqual(child,src);
      return child;
    }

    // *= operator
    template<typename Child>
    template<typename T2>
    typename tfel::meta::EnableIf<
      tfel::typetraits::IsScalar<T2>::cond&&
      tfel::meta::IsSameType<typename ResultType<typename ST2toST2Traits<Child>::NumType,
						 T2,OpMult>::type,
			     typename ST2toST2Traits<Child>::NumType>::cond,
      Child&>::type
    st2tost2_base<Child>::operator*=(const T2 s)
    {
      Child& child = static_cast<Child&>(*this);
      matrix_utilities<StensorDimeToSize<ST2toST2Traits<Child>::dime>::value,
		       StensorDimeToSize<ST2toST2Traits<Child>::dime>::value,
		       StensorDimeToSize<ST2toST2Traits<Child>::dime>::value>::multByScalar(child,s);
      return child;
    }

    // /= operator
    template<typename Child>
    template<typename T2>
    typename tfel::meta::EnableIf<
      tfel::typetraits::IsScalar<T2>::cond&&
      tfel::meta::IsSameType<typename ResultType<typename ST2toST2Traits<Child>::NumType,
						 T2,OpDiv>::type,
			     typename ST2toST2Traits<Child>::NumType>::cond,
      Child&>::type
    st2tost2_base<Child>::operator/=(const T2 s)
    {
      Child& child = static_cast<Child&>(*this);
      matrix_utilities<StensorDimeToSize<ST2toST2Traits<Child>::dime>::value,
		       StensorDimeToSize<ST2toST2Traits<Child>::dime>::value,
		       StensorDimeToSize<ST2toST2Traits<Child>::dime>::value>::divByScalar(child,s);
      return child;
    }

    template<unsigned short N, typename T>
    st2tost2<N,T>::st2tost2(const T init)
    {
      tfel::fsalgo::fill<StensorDimeToSize<N>::value*
			 StensorDimeToSize<N>::value>::exe(this->v,init);
    }

    template<unsigned short N, typename T>
    st2tost2<N,T>::st2tost2(const st2tost2<N,T>& src)
    {
      matrix_utilities<StensorDimeToSize<N>::value,
		       StensorDimeToSize<N>::value,
		       StensorDimeToSize<N>::value>::copy(src,*this);
    }

    template<unsigned short N, typename T>
    const st2tost2<N,T>&
    st2tost2<N,T>::Id(void){
      static const st2tost2<N,T> sId(st2tost2<N,T>::ST2TOST2_IDENTITY);
      return sId;
    } // end of st2tost2<N,T>::Id

    template<unsigned short N, typename T>
    const st2tost2<N,T>&
    st2tost2<N,T>::J(void){
      static const st2tost2<N,T> sJ(st2tost2<N,T>::ST2TOST2_J);
      return sJ;
    } // end of st2tost2<N,T>::J

    template<unsigned short N, typename T>
    const st2tost2<N,T>&
    st2tost2<N,T>::IxI(void){
      static const st2tost2<N,T> sIxI(st2tost2<N,T>::ST2TOST2_IxI);
      return sIxI;
    } // end of st2tost2<N,T>::IxI

    template<unsigned short N, typename T>
    const st2tost2<N,T>&
    st2tost2<N,T>::K(void){
      static const st2tost2<N,T> sK(st2tost2<N,T>::ST2TOST2_K);
      return sK;
    } // end of st2tost2<N,T>::K

    template<unsigned short N, typename T>
    const st2tost2<N,T>&
    st2tost2<N,T>::M(void){
      static const st2tost2<N,T> sM(T(1.5)*st2tost2<N,T>::K());
      return sM;
    } // end of st2tost2<N,T>::M

    template<unsigned short N,typename T>
    template<typename T2,typename Expr>
    st2tost2<N,T>::st2tost2(const ST2toST2Expr<st2tost2<N,T2>,Expr>& src){
      matrix_utilities<StensorDimeToSize<N>::value,
		       StensorDimeToSize<N>::value,
		       StensorDimeToSize<N>::value>::copy(src,*this);
    }

    template<unsigned short N,typename T>
    st2tost2<N,T>::st2tost2(const st2tost2<N,T>::ParticularSt2toSt2 id){
      using namespace std;
      unsigned short i,j;
      std::fill(this->v,this->v+StensorDimeToSize<N>::value*StensorDimeToSize<N>::value,T(0));
      if(id==ST2TOST2_IDENTITY){
	for(i=0;i!=StensorDimeToSize<N>::value;++i){
	  this->operator()(i,i)=T(1);
	}
      } else if (id==ST2TOST2_J){
	for(i=0;i!=3;++i){
	  for(j=0;j!=3;++j){
	    this->operator()(i,j)=1/T(3);
	  }
	}
      } else if (id==ST2TOST2_IxI){
	for(i=0;i!=3;++i){
	  for(j=0;j!=3;++j){
	    this->operator()(i,j)=T(1);
	  }
	}
      } else if (id==ST2TOST2_K){
	for(i=0;i!=3;++i){
	  for(j=0;j!=3;++j){
	    if(i==j){
	      this->operator()(i,j)=2/T(3);
	    } else {
	      this->operator()(i,j)=-1/T(3);
	    }
	  }
	}
	for(i=3;i!=StensorDimeToSize<N>::value;++i){
	  this->operator()(i,i)=T(1);
	}
      }
    } // end of st2tost2(const st2tost2<N,T>::ParticularSt2toSt2)

    template<unsigned short N, typename T>
    T& 
    st2tost2<N,T>::operator()(const unsigned short i,const unsigned short j){
      assert(i<StensorDimeToSize<N>::value);
      assert(j<StensorDimeToSize<N>::value);
      return this->v[StensorDimeToSize<N>::value*i+j];
    }

    template<unsigned short N, typename T>
    const T& 
    st2tost2<N,T>::operator()(const unsigned short i,const unsigned short j) const{
      assert(i<StensorDimeToSize<N>::value);
      assert(j<StensorDimeToSize<N>::value);
      return this->v[StensorDimeToSize<N>::value*i+j];
    }

    template<unsigned short N, typename T>
    template<typename InputIterator>
    TFEL_MATH_INLINE2 void st2tost2<N,T>::copy(const InputIterator src)
    {
      tfel::fsalgo::copy<StensorDimeToSize<N>::value*StensorDimeToSize<N>::value>::exe(src,*this);
    }

    template<unsigned short N, typename T>
    typename st2tost2<N,T>::RunTimeProperties
    st2tost2<N,T>::getRunTimeProperties(void) const
    {
      return RunTimeProperties();
    } // end of st2tost2<N,T>::getRunTimeProperties

  } //end of namespace math

} // end of namespace tfel

#endif /* _LIB_TFEL_ST2TOST2_IXX */

