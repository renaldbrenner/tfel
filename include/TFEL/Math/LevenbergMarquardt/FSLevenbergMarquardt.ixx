/*!
 * \file   FSLevenbergMarquardt.ixx
 * \brief  
 * 
 * \author Helfer Thomas
 * \date   21 nov 2008
 */

#ifndef _LIB_TFEL_MATH_FSLEVENBERGMARQUARDT_IXX_
#define _LIB_TFEL_MATH_FSLEVENBERGMARQUARDT_IXX_ 

#include<algorithm>

#include"TFEL/FSAlgorithm/FSAlgorithm.hxx"
#include"TFEL/Math/MathException.hxx"
#include"TFEL/Math/Function/Power.hxx"

namespace tfel
{

  namespace math
  {

    template<unsigned short N,
	     unsigned short M,
	     typename T>
    FSLevenbergMarquardt<N,M,T>::FSLevenbergMarquardt(const FSLevenbergMarquardt::PtrFun f_)
      : lambda0(T(1.e-3)),
	factor(T(2)),
	eps1(1.e-10),
	eps2(1.e-10),
	iterMax(100),
	f(f_)
    {} // end of FSLevenbergMarquardt::FSLevenbergMarquardt

    template<unsigned short N,
	     unsigned short M,
	     typename T>
    void
    FSLevenbergMarquardt<N,M,T>::setInitialDampingParameter(const T value)
    {
      this->lambda0 = value;
    } // end of FSLevenbergMarquardt<N,M,T>::setInitialDampingParameter

    template<unsigned short N,
	     unsigned short M,
	     typename T>
    void
    FSLevenbergMarquardt<N,M,T>::setFirstCriterium(const T value)
    {
      this->eps1 = value;
    } // end of FSLevenbergMarquardt<N,M,T>::setFirstCriterium

    template<unsigned short N,
	     unsigned short M,
	     typename T>
    void
    FSLevenbergMarquardt<N,M,T>::setSecondCriterium(const T value)
    {
      this->eps2 = value;
    } // end of FSLevenbergMarquardt<N,M,T>::setSecondCriterium

    template<unsigned short N,
	     unsigned short M,
	     typename T>
    void
    FSLevenbergMarquardt<N,M,T>::setMultiplicationFactor(const T value)
    {
      this->factor = value;
    } // end of FSLevenbergMarquardt<N,M,T>::setMultiplicationFactor

    template<unsigned short N,
	     unsigned short M,
	     typename T>
    void
    FSLevenbergMarquardt<N,M,T>::addData(const tvector<N,T>& x,
				       const T y)
    {
      using namespace std;
      this->data.push_back(pair<tvector<N,T>,T>(x,y));
    } // end of FSLevenbergMarquardt::addData

    template<unsigned short N,
	     unsigned short M,
	     typename T>
    void
    FSLevenbergMarquardt<N,M,T>::setInitialGuess(const tvector<M,T>& p_)
    {
      this->p = p_;
    } // end of FSLevenbergMarquardt::setInitialGuess

    template<unsigned short N,
	     unsigned short M,
	     typename T>
    void
    FSLevenbergMarquardt<N,M,T>::setMaximumIteration(const T nb)
    {
      this->iterMax = nb;
    } // end of FSLevenbergMarquardt::setInitialGuess

    template<unsigned short N,
	     unsigned short M,
	     typename T>
    const tvector<M,T>&
    FSLevenbergMarquardt<N,M,T>::execute(void)
    {
      using namespace std;
      using tfel::fsalgo::fill;
      using tfel::math::stdfunctions::power;
      typename vector<pair<tvector<N,T>,T> >::const_iterator it;
      // grad is the opposite of the gradient
      tmatrix<M,M,T> J(T(0));
      tvector<M,T> g(T(0));
      T s(T(0));
      T lambda = this->lambda0;
      unsigned short i;
      unsigned short iter;
      bool success;
      s = T(0);
      for(it=this->data.begin();it!=this->data.end();++it){
	const pair<T,tvector<M,T> >& o = (*f)(it->first,this->p);
	g += (o.first-it->second)*o.second;
	J += (o.second)^(o.second);
	s += (o.first-it->second)*(o.first-it->second);
      }
      lambda *= *(max_element(J.begin(),J.end()));
      for(i=0;i!=M;++i){
	J(i,i)+= lambda;
      }
      this->factor=2;
      success = false;
      for(iter=0;(iter!=this->iterMax)&&(!success);++iter){
	tmatrix<M,M,T> Jn(J);
	tvector<M,T>   gn(T(0));
	tvector<M,T>   h(-g);
	T sn(T(0));
	TinyMatrixSolve<M,T>::exe(Jn,h);
	fill<M*M>::exe(Jn.begin(),T(0));
	for(it=this->data.begin();it!=this->data.end();++it){
	  const pair<T,tvector<M,T> >& o = (*f)(it->first,this->p+h);
	  gn += (o.first-it->second)*o.second;
	  Jn += (o.second)^(o.second);
	  sn += (o.first-it->second)*(o.first-it->second);
	}
	T rho = (s-sn)/(0.5*(h|(lambda*h-g)));
	if(rho>0){
	  for(i=0;i!=M;++i){
	    Jn(i,i) += lambda;
	  }
	  this->p+=h;
	  T ng = norm(gn);
	  T nh = norm(h);
	  T np = norm(p);
	  if(nh<this->eps2*(np+this->eps2)){
	    success = true;
	  } else if (ng<this->eps1){
	    success = true;
	  } else {
	    // preparing next iteration
	    J = Jn;
	    g = gn;
	    s = sn;
	    lambda  = lambda*max(T(0.3333),T(1)-power<3>(2*rho-1));
	    this->factor = 2;
	  }
	} else {
	  lambda *= this->factor;
	  this->factor *= 2;
	}
      }
      if(!success){
	throw(MathDivergenceException("Maximum number of iterations reached"));
      }

      return this->p;
    } // end of execute

  } // end of namespace math

} // end of namespace tfel

#endif /* _LIB_TFEL_MATH_FSLEVENBERGMARQUARDT_IXX */

