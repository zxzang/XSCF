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


#include <sstream>

#include "controller.h"


using namespace xcsf;


Controller::~Controller()
{}



const string SEPARATOR = ":";


enum Command {
  Reward,
  Predict
};


Command
parse(const string& text)
{
  if (text == "R") return Reward;
  if (text == "P") return Predict;
  throw invalid_argument("Unknown command!");
}
  

void
validate(const string& line, size_t position)
{
    if (position == string::npos) {
      stringstream error;
      error << "Invalid line '" << line << "'."
	    << "Check it does use '" << SEPARATOR << "' as a separator.";
      throw invalid_argument(error.str());
    }
}


Decoder::Decoder(istream& source, Controller& target)
  :_source(source),
   _target(target)
{}


void
Decoder::decode(void)
{
  string line;
  while (getline(_source, line)) {
    size_t position = line.find(SEPARATOR, 0);
    validate(line, position);
    Command command = parse(line.substr(0, position));
    string value = line.substr(position+1);
    switch(command) {
    case Reward:
      _target.reward(stod(value));
      break;
    case Predict:
      _target.predict(Vector::parse(value));
      break;
    }
  }
  
}


Encoder::Encoder(ostream& out)
  :_out(out)
{}


Encoder::~Encoder()
{}


void
Encoder::show_prediction(const Vector& prediction)
{
  _out << prediction << endl;
}


AgentController::AgentController(Encoder& encoder, const RuleFactory& factory)
  :Controller()
  ,_encoder(encoder)
  ,_factory(factory)
  ,_agents()
{
  _agents.push_back(new Agent(_factory));
}


AgentController::~AgentController()
{
  for(auto each_agent: _agents) {
    delete each_agent;
  }
}


void
AgentController::select_action(const Vector& inputs) const
{
  Vector prediction = { 1, 2, 3 };
  _encoder.show_prediction(prediction);
};


void
AgentController::reward(double prize)
{
  _agents[0]->reward(prize);
}


void
AgentController::predict(const Vector& context)
{
  const Vector prediction = _agents[0]->select_action(context);
  _encoder.show_prediction(prediction);
}



BasicRuleFactory::BasicRuleFactory()
  :RuleFactory()
  ,_rules()
{};


BasicRuleFactory::~BasicRuleFactory()
{
  for (auto each_rule: _rules) {
    delete each_rule;
  }
}


void
BasicRuleFactory::initialise(RuleSet& rules) const
{
  for (unsigned int index=1 ; index<5 ; index++) {
    unsigned int lower = 25 * (index - 1);
    unsigned int upper = 25 * index;
    int mode = (lower + upper) / 2;
      
    Rule* rule = new Rule({ Interval(lower, upper) }, { mode }, 1., 1., 0.);
    rules.add(*rule);
    _rules.push_back(rule);
  }  
}
