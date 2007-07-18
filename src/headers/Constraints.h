/*
 * $Id$
 */

#ifndef __CONSTRAINTS_H
#define __CONSTRAINTS_H

namespace mpplas {

  namespace Constraints {
    /** Ensures at compile time that class @a D derives from base class
     * @B. 
     *
     * From Imperfect C++, by Matthew Wilson, page 5, section 1.2.1   
     * @note This check has no runtime cost whatsoever.
     *
     */
    template<typename D, typename B>
      struct must_have_base{
        ~must_have_base(){
          void(*p)(D*, B*) = constraints;
        }
        private:
        static void constraints(D* pd, B* pb){
          pb = pd;
        }
      };
  }
}
#endif
