#include "Mapper.h"
#include "FunctionSpaceScalar.h"

FunctionSpaceScalar::FunctionSpaceScalar(GroupOfElement& goe,
                                         const Basis& basis){
  scalar = true;
  build(goe, basis);
}

FunctionSpaceScalar::~FunctionSpaceScalar(void){
  // Done by FunctionSpace
}

double FunctionSpaceScalar::
interpolateInABC(const MElement& element,
                 const std::vector<double>& coef,
                 double abc[3]) const{

  // Get Basis Functions //
  const size_t nFun = (*basis)[0]->getNFunction();
  fullMatrix<double> fun(nFun, 1);

  (*basis)[0]->getFunctions(fun, element, abc[0], abc[1], abc[2]);

  // Interpolate (in Reference Place) //
  double val = 0;

  for(size_t i = 0; i < nFun; i++)
    val += fun(i, 0) * coef[i];

  // Return Interpolated Value //
  return val;
}

fullVector<double> FunctionSpaceScalar::
interpolateDerivativeInABC(const MElement& element,
                           const std::vector<double>& coef,
                           double abc[3]) const{
  // Get Jacobian //
  fullMatrix<double> invJac(3, 3);
  (*basis)[0]->getReferenceSpace().getJacobian(element,
                                               abc[0], abc[1], abc[2],
                                               invJac);
  invJac.invertInPlace();

  // Get Basis Functions //
  const size_t nFun = (*basis)[0]->getNFunction();
  fullMatrix<double> fun(nFun, 3);

  (*basis)[0]->getDerivative(fun, element, abc[0], abc[1], abc[2]);

  // Interpolate (in Reference Place) //
  fullMatrix<double> val(1, 3);
  val(0, 0) = 0;
  val(0, 1) = 0;
  val(0, 2) = 0;

  for(size_t i = 0; i < nFun; i++){
    val(0, 0) += fun(i, 0) * coef[i];
    val(0, 1) += fun(i, 1) * coef[i];
    val(0, 2) += fun(i, 2) * coef[i];
  }

  // Return Interpolated Value //
  fullVector<double> map(3);
  Mapper::hCurl(val, 0, 0, invJac, map);
  return map;
}
