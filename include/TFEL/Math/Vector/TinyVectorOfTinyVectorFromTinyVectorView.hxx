/*!
 * \file   TinyVectorOfTinyVectorFromTinyVectorView.hxx
 * \brief  TinyVectorOfTinyVectorFromTVectorView
 * This class creates an object that acts like a tiny vector of
 * tvectors.
 * \author Helfer Thomas
 * \date   16 oct 2008
 */

#ifndef _LIB_TFEL_MATH_TINYVECTOROFTVECTORFROMTINYVECTORVIEW_HXX_
#define _LIB_TFEL_MATH_TINYVECTOROFTVECTORFROMTINYVECTORVIEW_HXX_ 

#include"TFEL/Metaprogramming/StaticAssert.hxx"

#include"TFEL/Math/Vector/VectorUtilities.hxx"
#include"TFEL/Math/Vector/VectorConcept.hxx"
#include"TFEL/Math/Vector/VectorExpr.hxx"
#include"TFEL/Math/tvector.hxx"
#include"TFEL/Math/tvector.hxx"

namespace tfel
{
  
  namespace math
  {

    /*!
     *  TVector of tvectors  from Tiny Vector view expression
     * \param[in] N  : dimension used to define the tvector
     * \param[in] Mn : dimension of the underlying vector
     * \param[in] In : Index of the first tvector in the underlying vector
     * \param[in] Nn : number of tvector holed
     * \param[in] T  : underlying type
     */
    template<unsigned short N,
	     unsigned short Mn,
	     unsigned short In,
	     unsigned short Nn,
	     typename T>
    struct TinyVectorOfTinyVectorFromTinyVectorViewExpr
    {
      /*!
       * numerical type holded by the expression
       */
      typedef tvector<N,T> NumType;
    }; // end of struct TinyVectorOfTinyVectorFromTinyVectorViewExpr

    /*!
     * \param[in] N  : dimension used to define the tvector (1,2 or 3)
     * \param[in] Mn : dimension of the underlying vector
     * \param[in] In : Index of the first tvector in the underlying vector
     * \param[in] Nn : number of tvector holed
     * \param[in] T  : underlying type
     */
    template<unsigned short N,
	     unsigned short Mn,
	     unsigned short In,
	     unsigned short Nn,
	     typename T>
    struct VectorExpr<tvector<Nn,tvector<N,T> >,TinyVectorOfTinyVectorFromTinyVectorViewExpr<N,Mn,In,Nn,T> >
      : public VectorConcept<VectorExpr<tvector<Nn,tvector<N,T> >,TinyVectorOfTinyVectorFromTinyVectorViewExpr<N,Mn,In,Nn,T> > >
    {

      typedef EmptyRunTimeProperties RunTimeProperties;

      VectorExpr(tvector<Mn,T>& v_)
	: v(v_)
      {} // end of VectorExpr

      /*
       * Return the RunTimeProperties of the tvector
       * \return tvector::RunTimeProperties
       */
      const RunTimeProperties
      getRunTimeProperties(void) const
      {
	return RunTimeProperties();
      }

      const tvector<N,T>&
      operator[](const unsigned short i) const
      {
	union{
	  const T * t_ptr;
	  const tvector<N,T> * s_ptr;
	} ptr;
	ptr.t_ptr = this->v.begin()+In+i*N;
	return *(ptr.s_ptr);
      } // end of operator[] const

      tvector<N,T>&
      operator[](const unsigned short i)
      {
	union{
	  T * t_ptr;
	  tvector<N,T> * s_ptr;
	} ptr;
	ptr.t_ptr = this->v.begin()+In+i*N;
	return *(ptr.s_ptr);
      } // end of operator[]

      const tvector<N,T>&
      operator()(const unsigned short i) const
      {
	union{
	  const T * t_ptr;
	  const tvector<N,T> * s_ptr;
	} ptr;
	ptr.t_ptr = this->v.begin()+In+i*N;
	return *(ptr.s_ptr);
      } // end of operator() const

      tvector<N,T>&
      operator()(const unsigned short i)
      {
	union{
	  T * t_ptr;
	  tvector<N,T> * s_ptr;
	} ptr;
	ptr.t_ptr = this->v.begin()+In+i*N;
	return *(ptr.s_ptr);
      } // end of operator()

      /*!
       * Assignement operator
       */
      template<typename T2>
      typename tfel::meta::EnableIf<
	tfel::typetraits::IsAssignableTo<T2,T>::cond,
	VectorExpr&>::type
      operator=(const tvector<Nn,tvector<N,T2> >& s){
	VectorUtilities<N>::copy(s,*this);
	return *this;
      }
      
      /*!
       * Assignement operator
       */
      template<typename T2,typename Expr>
      typename tfel::meta::EnableIf<
	tfel::typetraits::IsAssignableTo<T2,T>::cond,
	VectorExpr&
      >::type
      operator=(const VectorExpr<tvector<Nn,tvector<N,T2> >,Expr>& s)
      {
	VectorUtilities<N>::copy(s,*this);
	return *this;
      }

      // Assignement operator
      template<typename T2>
      typename tfel::meta::EnableIf<
	tfel::typetraits::IsAssignableTo<T2,T>::cond,
	VectorExpr&
      >::type
      operator+=(const tvector<Nn,tvector<N,T2> >& s){
	VectorUtilities<N>::PlusEqual(*this,s);
	return *this;
      }
    
      // Assignement operator
      template<typename T2,typename Expr>
      typename tfel::meta::EnableIf<
	tfel::typetraits::IsAssignableTo<T2,T>::cond,
	VectorExpr&
      >::type
      operator+=(const VectorExpr<tvector<Nn,tvector<N,T2> >,Expr>& s){
	VectorUtilities<N>::PlusEqual(*this,s);
	return *this;
      }

      // Assignement operator
      template<typename T2>
      typename tfel::meta::EnableIf<
	tfel::typetraits::IsAssignableTo<T2,T>::cond,
	VectorExpr&
      >::type
      operator-=(const tvector<Nn,tvector<N,T2> >& s){
	VectorUtilities<N>::MinusEqual(*this,s);
	return *this;
      }
    
      // Assignement operator
      template<typename T2,typename Expr>
      typename tfel::meta::EnableIf<
	tfel::typetraits::IsAssignableTo<T2,T>::cond,
	VectorExpr&
      >::type
      operator-=(const VectorExpr<tvector<Nn,tvector<N,T2> >,Expr>& s){
	VectorUtilities<N>::MinusEqual(*this,s);
	return *this;
      }

      /*!
       * operator*=
       */
      template<typename T2>
      typename tfel::meta::EnableIf<
	tfel::typetraits::IsScalar<T2>::cond&&
      tfel::meta::IsSameType<typename ResultType<T,T2,OpMult>::type,T>::cond,
	VectorExpr&
      >::type
      operator*=(const T2 a){
	VectorUtilities<N>::scale(*this,a);
	return *this;
      }

      /*!
       * operator/=
       */
      template<typename T2>
      typename tfel::meta::EnableIf<
      tfel::typetraits::IsScalar<T2>::cond&&
      tfel::meta::IsSameType<typename ResultType<T,T2,OpMult>::type,T>::cond,
	VectorExpr&
	>::type
	operator/=(const T2 a){
	VectorUtilities<N>::scale(*this,1/a);
	return *this;
      }
      
    protected:
	
      tvector<Mn,T>& v;

      private:
	
	/*!
       * Simple checks
       */
	TFEL_STATIC_ASSERT((N==1u)||(N==2u)||(N==3u));
	TFEL_STATIC_ASSERT((In<Mn));
	TFEL_STATIC_ASSERT((Nn*N<=Mn-In));

    }; // end of struct VectorExpr


    template<unsigned short N,
	     unsigned short Mn,
	     unsigned short In,
	     unsigned short Nn,
	     typename T = double>
    struct TinyVectorOfTinyVectorFromTinyVectorView
    {
      typedef VectorExpr<tvector<Nn,tvector<N,T> >,TinyVectorOfTinyVectorFromTinyVectorViewExpr<N,Mn,In,Nn,T> > type;
    }; // end of struct TinyVectorOfTinyVectorFromTinyVectorView

    // Serialisation operator
    template<unsigned short N,
	     unsigned short Mn,
	     unsigned short In,
	     unsigned short Nn,
	     typename T>
    std::ostream&
    operator << (std::ostream & os,
		 const VectorExpr<tvector<Nn,tvector<N,T> >,TinyVectorOfTinyVectorFromTinyVectorViewExpr<N,Mn,In,Nn,T> >& s)
    {
      os << "[ ";
      for(unsigned short i=0;i<Nn;++i){
	os << s(i) << " ";
      }
      os << "]";
      return os;
    } // end of operator << 
    
  } // end of namespace math

  namespace typetraits{

    template<unsigned short N,
  	     unsigned short Mn,
  	     unsigned short In,
  	     unsigned short Nn,
  	     typename T>
    struct IsTemporary<tfel::math::VectorExpr<tfel::math::tvector<Nn,tfel::math::tvector<N,T> >,
					      tfel::math::TinyVectorOfTinyVectorFromTinyVectorViewExpr<N,Mn,In,Nn,T> > >
    {
      static const bool cond = false;
    };

  } // end of namespace typetraits

} // end of namespace tfel

#endif /* _LIB_TFEL_MATH_TINYVECTOROFTVECTORFROMTINYVECTORVIEW_HXX */

