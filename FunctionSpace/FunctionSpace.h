#ifndef _FUNCTIONSPACE_H_
#define _FUNCTIONSPACE_H_

#include <map>
#include <vector>

#include "Basis.h"

#include "Comparators.h"
#include "Dof.h"
#include "GroupOfDof.h"

#include "Mesh.h"
#include "GroupOfElement.h"

#include "MElement.h"
#include "MVertex.h"
#include "MEdge.h"
#include "MFace.h"

/**
    @interface FunctionSpace
    @brief Common Interface of all Function Spaces

    This is the @em common @em interface of
    all Function Spaces.@n

    A FunctionSpace is defined on a @em support,
    which is a collection of MElement%s (GroupOfElement).@n

    Those MElement%s @em must belong to the @em same Mesh.

    A FunctionSpace is also responsible for the generation of all
    the Dof%s and GroupOfDof%s related to its geometrical @em Support.

    @todo
    Allow Hybrid Mesh@n
    Remove call to GroupOfElement:::orientAllElements()
*/

class Mesh;
class GroupOfElement;

class FunctionSpace{
 protected:
  // Geometry //
  const Mesh*     mesh;
  GroupOfElement* goe;

  // Basis //
  std::vector<const Basis*>* basis;
  size_t nBasis;
  size_t fPerVertex;
  size_t fPerEdge;
  size_t fPerFace;
  size_t fPerCell;

  // Scalar Field ? //
  bool scalar;

  // Dofs //
  std::set<const Dof*, DofComparator>*     dof;
  std::vector<GroupOfDof*>*                group;
  std::map<
    const MElement*,
    const GroupOfDof*, ElementComparator>* eToGod;

 public:
  virtual ~FunctionSpace(void);

  const std::vector<const Basis*>& getBasis(const MElement& element) const;
  const Basis&                     getBasis(size_t i) const;
  size_t                           getNBasis(void) const;

  GroupOfElement& getSupport(void) const;
  bool            isScalar(void) const;

  std::vector<Dof> getKeys(const MElement& element) const;
  std::vector<Dof> getKeys(const MVertex& vertex) const;
  std::vector<Dof> getKeys(const MEdge& edge) const;
  std::vector<Dof> getKeys(const MFace& face) const;

  const std::vector<const Dof*>   getAllDofs(void) const;
  const std::vector<GroupOfDof*>& getAllGroups(void) const;

  const GroupOfDof& getGoDFromElement(const MElement& element) const;

  size_t dofNumber(void) const;
  size_t groupNumber(void) const;

 protected:
  // Init
  FunctionSpace(void);

  void build(GroupOfElement& goe,
             const Basis& basis);

  // Dof
  void buildDof(void);
  void insertDof(Dof& d,
                 std::vector<const Dof*>& trueDof,
                 size_t index);
};


/**
   @internal
   @fn FunctionSpace::FunctionSpace
   Instatiate a new FunctionSpace
   @endinternal
   **

   @fn FunctionSpace::~FunctionSpace
   Deletes this FunctionSpace
   **

   @fn FunctionSpace::getSupport
   @return Returns the support of this
   FunctionSpace
   **

   @fn FunctionSpace::isScalar
   @return Returns:
   @li @c true, if this FunstionSpace is scalar
   @li @c flase, otherwise
   **

   @fn vector<Dof> FunctionSpace::getKeys(const MElement& element) const
   @param element A MElement
   @return Returns all the Dof%s associated to the given MElement
   **

   @fn vector<Dof> FunctionSpace::getKeys(const MVertex& vertex) const
   @param vertex A MVertex
   @return Returns all the Dof%s associated to the given MVertex
   **

   @fn vector<Dof> FunctionSpace::getKeys(const MEdge& edge) const
   @param edge A MEdge
   @return Returns all the Dof%s associated to the given MEdge
   **

   @fn vector<Dof> FunctionSpace::getKeys(const MFace& face) const
   @param face A MFace
   @return Returns all the Dof%s associated to the given MFace
   **

   @fn FunctionSpace::getAllDofs
   @return Returns all the @em Dof%s associated to every Element%s
   of this FunctionSpace @em support
   **

   @fn FunctionSpace::getAllGroups
   @return Returns all the @em GroupOfDof%s associated to every Element%s
   of this FunctionSpace @em support
   **

   @fn FunctionSpace::getGoDFromElement
   @param element An Element of the FunctionSpace Support
   @return Returns the @em GroupOfDof%s associated to
   the given @em Element
   @note
   If the given Element is not in the FunctionSpace Support,
   an Exception is thrown
   **

   @fn FunctionSpace::dofNumber
   @return Returns the number of Dof%s
   given by FunctionSpace::getAllDofs()
   **

   @fn FunctionSpace::groupNumber
   @return Returns the number of GroupOfDof%s
   given by FunctionSpace::getAllGroups()
   **
*/


//////////////////////
// Inline Functions //
//////////////////////

inline const std::vector<const Basis*>&
FunctionSpace::getBasis(const MElement& element) const{
  return *basis;
}

inline const Basis& FunctionSpace::getBasis(size_t i) const{
  return *(*basis)[i];
}

inline size_t FunctionSpace::getNBasis(void) const{
  return nBasis;
}

inline GroupOfElement& FunctionSpace::getSupport(void) const{
  return *goe;
}

inline bool FunctionSpace::isScalar(void) const{
  return scalar;
}

inline size_t FunctionSpace::dofNumber(void) const{
  return dof->size();
}

inline size_t FunctionSpace::groupNumber(void) const{
  return group->size();
}

inline const std::vector<const Dof*> FunctionSpace::getAllDofs(void) const{
  return std::vector<const Dof*>(dof->begin(), dof->end());
}

inline const std::vector<GroupOfDof*>& FunctionSpace::getAllGroups(void) const{
  return *group;
}

#endif
