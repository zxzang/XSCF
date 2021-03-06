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



#include "agent.h"


using namespace xcsf;


Agent::Agent(const Evolution&		evolution,
	     const Covering&		convering,
	     const RewardFunction&	reward)
  : _evolution(evolution)
  , _cover_for(convering)
  , _reward(reward)
  , _rules()
  , _rules_to_reward()
{
  _evolution.initialise(_rules);
}


Agent::~Agent()
{}


const Vector&
Agent::predict(const Vector& input)
{
  ActivationGroup active_rules(_rules, input);
  if (active_rules.is_empty()) {
    _cover_for(_rules, input);
    active_rules = ActivationGroup(_rules, input);
  }

  PredictionGroup predictions(active_rules);
  _rules_to_reward = predictions.rules_to_reward();
  _evolution.evolve(_rules);
  return predictions.most_rewarding();
}


void
Agent::reward(double prize)
{
  _reward(prize, _rules_to_reward);
}


void
Agent::display_on(std::ostream& out) const
{
  Formatter formatter(out);
  _rules.accept(formatter);
}
