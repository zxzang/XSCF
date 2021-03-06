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


#include "CppUTest/TestHarness.h"

#include "helpers.h"



using namespace xcsf;



TEST_GROUP(TestInterval)
{
  const unsigned int lower = 12;
  const unsigned int upper = 24;
  Interval *interval;

  void setup(void) {
    interval = new Interval(lower, upper);
  }

  void teardown(void) {
    delete interval;
  }
    
};


TEST(TestInterval, test_lower)
{
  CHECK(lower == interval->lower());
}


TEST(TestInterval, test_upper)
{
  CHECK(upper == interval->upper());
}

TEST(TestInterval, test_equality)
{
  CHECK(*interval == *interval);
  CHECK(*interval == Interval(lower, upper));
}

TEST(TestInterval, test_inequality)
{
  CHECK(*interval != Interval(lower, upper+1));
  CHECK(*interval != Interval(lower+1, upper));
}

TEST(TestInterval, test_invalid_bounds)
{
  CHECK_THROWS(std::invalid_argument, { Interval(lower, lower-1); });
}


TEST_GROUP(TestRandomizer)
{
  vector<double> sequence = {0, 0.5, 1};
  Randomizer *generate;

  void setup(void)
  {
    generate = new TestableRandomizer(sequence);
  }

  void teardown(void)
  {
    delete generate;
  }

};


TEST(TestRandomizer, test_canned_response)
{
  for (unsigned int index=0 ; index<25 ; ++index) {
    CHECK(generate->uniform() == sequence[index % 3]); 
  }

}


TEST(TestRandomizer, test_unsigned_int)
{
  unsigned int value = generate->unsigned_int(0, 100);
  CHECK_EQUAL(0, value);

  value = generate->unsigned_int(0, 100);
  CHECK_EQUAL(49, value);

  value = generate->unsigned_int(0, 100);
  CHECK_EQUAL(99, value);
}


TEST(TestRandomizer, test_real_output)
{
  double total(0);
  Randomizer generate;
  for(unsigned int i=0 ; i<10000 ; ++i) {
    total += generate.uniform();
  }

  CHECK(total > 0);
  
}
