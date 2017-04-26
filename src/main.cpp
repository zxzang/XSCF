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


#include "application.h"


using namespace std;
using namespace xcsf;


int
main(int argc, char** argv)
{
  cout << APPLICATION << " v" << VERSION << endl; 

  RuleFactory* factory = new BasicRuleFactory();
  Application application(cin, cout, *factory);
  application.run();

  return 0;
}
