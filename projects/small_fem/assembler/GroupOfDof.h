#ifndef _GROUPOFDOF_H_
#define _GROUPOFDOF_H_

#include <vector>
#include "GroupTyped.h"
#include "Dof.h"

#include "FunctionSpace.h"
#include "Mesh.h"

#include "MElement.h"

class DofManager;

/**
   @class GroupOfDof
   @brief Handels a Group of Dof%s with @em geometrical meaning

   This class handles a Group of Dof%s with a @em geometrical meaning 
   (@e e.g: Dof%s that belongs to the same (finite) element).@n

   It also gives acces to the underlying Geometrical Element.

   @note
   Note that a user @em can't instantiate a GroupOfDof.@n
   This is the DofManager's job.
*/

class GroupOfDof: public GroupTyped<Dof>{
 private:
  static unsigned int nextId;
  unsigned int            id;

  const MElement*      element;

  unsigned int nDof;
  std::vector<const Dof*>* dof;
  
  unsigned int nextDof;
  
  friend class DofManager;

 public:
  virtual unsigned int getNumber(void) const;
  virtual unsigned int getId(void) const;
  virtual unsigned int getType(void)   const;
  
  virtual const Dof&                     get(unsigned int i) const; 
  virtual const std::vector<const Dof*>& getAll(void) const;
  
  const MElement& getGeoElement(void) const;

  virtual std::string toString(void) const;

 private:
   GroupOfDof(unsigned int numberOfDof, 
	      const MElement& geoElement);

  ~GroupOfDof(void);

  void add(const Dof* dof);
};


/**
   @fn GroupOfDof::get
   @param i An interger ranging from 0 
   to GroupOfDof::getNumber() - 1
   @return Returns the ith element of the Group
   **

   @fn GroupOfDof::getAll
   @return Returns all the elements of the Group
   **

   @fn GroupOfDof::getGeoElement
   @return Returns the underlying Geometrical Element
   **
*/

//////////////////////
// Inline Functions //
//////////////////////

inline unsigned int GroupOfDof::getNumber(void) const{
  return nDof;
}

inline unsigned int GroupOfDof::getId(void) const{
  return id;
}

inline unsigned int GroupOfDof::getType(void) const{
  return 0;
}

inline const Dof& GroupOfDof::get(unsigned int i) const{
  return *((*dof)[i]);
}
 
inline const std::vector<const Dof*>& GroupOfDof::getAll(void) const{
  return *dof;
}

inline const MElement& GroupOfDof::getGeoElement(void) const{
  return *element;
}

#endif
