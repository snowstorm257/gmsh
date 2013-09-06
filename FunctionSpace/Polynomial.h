#ifndef _POLYNOMIAL_H_
#define _POLYNOMIAL_H_

#include <string>
#include <stack>
#include <vector>
#include "fullMatrix.h"

/**
   @class Polynomial
   @brief Represents @c 3D polynomials

   This class represents @c 3D polynomials.@n
   A @c 3D polynomials uses monomials of '@c xyz' type.
 */

// We suppose 3D Polynomial
class Polynomial{
 private:
  static const char coefName[3];

  struct monomial_t{
    double coef;
    int power[3];
  };

  int         nMon;
  monomial_t*  mon;

 public:
   Polynomial(double coef,
              int powerX,
              int powerY,
              int powerZ);

   Polynomial(const Polynomial& other);
   Polynomial(void);
  ~Polynomial(void);

  void derivative(int dim);
  std::vector<Polynomial> gradient(void) const;
  static std::vector<Polynomial> curl(const std::vector<Polynomial>& p);
  static Polynomial divergence(const std::vector<Polynomial>& p);

  double operator()
    (double x, double y, double z) const;

  double at
    (double x, double y, double z) const;

  static fullVector<double> at(const std::vector<Polynomial>& P,
                               double x,
                               double y,
                               double z);

  Polynomial operator+(const Polynomial& other) const;
  Polynomial operator-(const Polynomial& other) const;
  Polynomial operator*(const Polynomial& other) const;
  Polynomial operator*(double alpha) const;

  void add(const Polynomial& other);
  void sub(const Polynomial& other);
  void mul(const Polynomial& other);
  void mul(double alpha);

  void power(int n);

  Polynomial compose(const Polynomial& other) const;
  Polynomial compose(const Polynomial& otherA,
                     const Polynomial& otherB) const;
  Polynomial compose(const Polynomial& otherA,
                     const Polynomial& otherB,
                     const Polynomial& otherC) const;

  void operator=(const Polynomial& other);

  std::string toString(void) const;

 private:
  static std::string toString(const monomial_t* mon, const bool isAbs);

  static bool isSmaller(const monomial_t* a, const monomial_t*b);
  static bool isEqual(const monomial_t* a, const monomial_t*b);
  static bool isSmallerPower(const monomial_t* a, const monomial_t* b);
  static bool isEqualPower(const monomial_t* a, const monomial_t* b);

  static void sort(monomial_t* mon, int size);
  static void swap(monomial_t* mon, int i, int j);

  static int mergeMon(monomial_t* sourceA, int sizeA,
                      monomial_t* sourceB, int sizeB,
                      monomial_t** dest);

  static int mult(const monomial_t* sourceA, int sizeA,
                  const monomial_t* sourceB, int sizeB,
                  monomial_t** dest);

  static void mult(monomial_t* source, int size, double alpha);

  static void distribute(monomial_t* src, int size, const monomial_t* m);

  static void compose(const monomial_t* src,
                      Polynomial comp,
                      std::stack<monomial_t>* stk);

  static void compose(const monomial_t* src,
                      Polynomial compA, Polynomial compB,
                      std::stack<monomial_t>* stk);

  static void compose(const monomial_t* src,
                      Polynomial compA, Polynomial compB, Polynomial compC,
                      std::stack<monomial_t>* stk);

  static Polynomial polynomialFromStack(std::stack<monomial_t>& stk);

  static monomial_t* copyMonomial(const monomial_t* src, int size);

  static monomial_t* zeroPolynomial(void);
  static monomial_t* unitPolynomial(void);
};

/**
   @fn Polynomial::Polynomial(double, int, int, int)
   @param coef The coeficient of the futur monomial
   @param powerX The power of the '@c x' coordinate
   of the futur monomial
   @param powerY The power of the '@c y' coordinate
   of the futur monomial
   @param powerZ The power of the '@c z' coordinate
   of the futur monomial
   @return Returns a new Monomial with the given
   parameters
   @note
   Note that Monomials are special case of Polynomial%s
   **

   @fn Polynomial::Polynomial(const Polynomial&)
   @param other A Polynomial
   @return Returns a new Polynomial, which is
   the @em copy of the given one
   **

   @fn Polynomial::Polynomial(void)
   @return Returns a new Polynomial, which is
   @em empty
   @warning
   An @em empty Polynomial means: @em A @em Polynomial
   @em with @em no @em monomials.@n
   In particular, the empty Polynomial is @em not
   the @em zero @em Polynomial.@n
   Indeed, the @em zero @em Polynomial has one monomial,
   @em @c 0.
   **

   @fn Polynomial::~Polynomial
   @return Deletes this Polynomial
   **

   @fn Polynomial::derivative
   @param dim The dimention to use for the
   derivation
   @returns Derivates this Polynomial with
   respect to the given dimention
   @note
   Dimention:
   @li @c 0 is for the @c x coordinate
   @li @c 1 is for the @c y coordinate
   @li @c 2 is for the @c z coordinate
   **

   @fn Polynomial::gradient
   @return Returns a Vector with the gradient
   of this Polynomial
   **

   @fn Polynomial::curl
   @param p A vector of Polynomial%s
   @return Returns the @em curl of the given
   vector of Polynomial%s
   **

   @fn Polynomial::divergence
   @param p A vector of Polynomial%s
   @return Returns the @em divergence of the given
   vector of Polynomial%s
   **

   @fn double Polynomial::operator()(double, double, double)
   @param x A value
   @param y A value
   @param z A value
   @return Returns the @em evaluation of this
   Polynomial at (@c x, @c y, @c z)
   **

   @fn double Polynomial::at(double, double, double) const
   @param x A value
   @param y A value
   @param z A value
   @return Returns the @em evaluation of this
   Polynomial at (@c x, @c y, @c z)
   **

   @fn fullVector<double> Polynomial::at(const std::vector<Polynomial>&, double, double, double)
   @param P A vector of Polynomial%s
   @param x A value
   @param y A value
   @param z A value
   @return Returns a fullVector with the @em evaluation of
   the given vector of Polynomial%s at (@c x, @c y, @c z)
   **

   @fn Polynomial Polynomial::operator+(const Polynomial&) const
   @param other An other Polynomial
   @return Returns a @em new Polynomial, which is the
   @em sum of this Polynomial and the given one
   **

   @fn Polynomial Polynomial::operator-(const Polynomial&) const
   @param other An other Polynomial
   @return Returns a @em new Polynomial, which is the
   @em difference of this Polynomial and the given one
   **

   @fn Polynomial Polynomial::operator*(const Polynomial&) const
   @param other An other Polynomial
   @return Returns a @em new Polynomial, which is the
   @em product of this Polynomial and the given one
   **

   @fn Polynomial Polynomial::operator*(double) const
   @param alpha A value
   @return Returns a @em new Polynomial,
   which is this Polynomial @em multiplied by @c alpha
   **

   @fn Polynomial::add
   @param other An other Polynomial
   @return The given Polynomial is
   @em added to this Polynomial
   @note
   The result of this operation is stored in
   this Polynomial
   **

   @fn Polynomial::sub
   @param other An other Polynomial
   @return The given Polynomial is
   @em substracted to this Polynomial
   @note
   The result of this operation is stored in
   this Polynomial
   **

   @fn void Polynomial::mul(const Polynomial&)
   @param other An other Polynomial
   @return The given Polynomial is
   @em multiplied with this Polynomial
   @note
   The result of this operation is stored in
   this Polynomial
   **

   @fn void Polynomial::mul(double)
   @param alpha A value
   @return This Polynomial is @em multiplied
   by the given value
   @note
   The result of this operation is stored in
   this Polynomial
   **

   @fn Polynomial::power
   @param n A @em natural number
   @return Takes this Polynomial to the power @c n
   **

   @fn Polynomial Polynomial::compose(const Polynomial&) const
   @param other An other Polynomial,
   called @c Q(x, @c y, @c z)
   @return
   Let this Polynomial be @c P(x, @c y, @c z).@n
   This method returns a @em new Polynomial,
   representing @c P(Q(x, @c y, @c z), @c y, @c z)
   **

   @fn Polynomial Polynomial::compose(const Polynomial&, const Polynomial&) const
   @param otherA An other Polynomial,
   called @c Q(x, @c y, @c z)
   @param otherB An other Polynomial,
   called @c R(x, @c y, @c z)
   @return
   Let this Polynomial be @c P(x, @c y, @c z).@n
   This method returns a @em new Polynomial, representing
   @c P(Q(x, @c y, @c z), @c R(x, @c y, @c z), @c z)
   **

   @fn void Polynomial::operator=(const Polynomial&)
   @param other A Polynomial
   @return Sets this Polynomial to a @em copy
   of the given one
   **

   @fn Polynomial::toString
   @return Returns a string representing this Polynomial
*/

//////////////////////
// Inline Functions //
//////////////////////

inline double Polynomial::operator() (double x,
                                      double y,
                                      double z) const{
  return at(x, y, z);
}

inline bool Polynomial::isEqual(const Polynomial::monomial_t* a,
                                const Polynomial::monomial_t* b){
  return a->power[0] == b->power[0] &&
         a->power[1] == b->power[1] &&
         a->power[2] == b->power[2];
}

inline bool Polynomial::isSmallerPower(const Polynomial::monomial_t* a,
                                       const Polynomial::monomial_t* b){

  return
    a->power[0] + a->power[1] + a->power[2]
    <
    b->power[0] + b->power[1] + b->power[2] ;
}

inline bool Polynomial::isEqualPower(const Polynomial::monomial_t* a,
                                     const Polynomial::monomial_t* b){

  return
    a->power[0] + a->power[1] + a->power[2]
    ==
    b->power[0] + b->power[1] + b->power[2] ;
}

#endif
