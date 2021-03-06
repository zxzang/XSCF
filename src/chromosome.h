/*
 * This file is part of XCSF.
 *
 * XCSF is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * XCSF is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with XCSF.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


#ifndef XCSF_CHROMOSOME_H
#define XCSF_CHROMOSOME_H


#include <vector>
#include <iostream>

#include "rule.h"


namespace xcsf {

  
  typedef unsigned int Allele;

  typedef std::vector<Allele> Chromosome;

  std::ostream&
    operator << (std::ostream& out, const Chromosome& chromosome);


  /**
   * Convert a MetaRule back and forth to a chromosome
   */
  class Codec
  {
    
  public:
    Codec(MetaRulePool& rules);

    Chromosome
      encode(const MetaRule& rule) const;

    MetaRule*
      decode(const Dimensions& dimensions,
	     const Chromosome& chromosome,
	     const Performance& performance) const;
    
  private:
    MetaRulePool& _rules;

  };
  
}


#endif
