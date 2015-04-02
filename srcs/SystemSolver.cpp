#include <main.hpp>

void						System::solve(void) {
	Facts					facts = getFacts();

	Facts::const_iterator	fit  = facts.begin();
	Facts::const_iterator	fite = facts.end();

	for (; fit != fite; fit++) {
		solveFact(fit->first, fit->second);
		// solveFact('F', unsolved);
		clearUsedRules();
	}

	return ;
}

void						System::solveFact(char fact, eFact oldState) {
	Rules::const_iterator	rit  = getRules().begin();
	Rules::const_iterator	rite = getRules().end();

	eFact 					newState;

	for (; rit != rite; rit++) {
		std::string			rhs = rit->getRight();
		if (rhs.find(fact) != std::string::npos) {
			if (not ruleUsed(*rit)) {
				addUsedRules(*rit);
				newState = solveRule(*rit, fact);
				if (oldState != newState)
					updateState(fact, newState);
			}
		}
	}

	return ;
}


eFact						System::solveRule(Rule rule, char fact) {
	std::string 	       	lhs = rule.getLeft();
	std::string 	       	rhs = rule.getRight();

	for(char c : lhs) {
		if (isFact(c))
			solveFact(c, getState(c));
	}
	
	for(char c : rhs) {
		if (isFact(c) and fact != c)
			solveFact(c, getState(c));
	}

	eFact 					leftState  = evaluateLeft(lhs);

	if (leftState == vrai) {
		eFact				testFalse = tryRight(rhs, fact, faux);
		eFact				testTrue  = tryRight(rhs, fact, vrai);

		if (leftState == testFalse)
			return faux;
		else if (leftState == testTrue)
			return vrai;
		else
			return undefined;
	}
	else
		return unsolved;

	return undefined;
}


eFact						System::evaluateLeft(std::string lhs) {
	lhs.insert(0, "+");

	eFact					currentState = vrai;

	for(std::string::iterator it = lhs.begin(); it != lhs.end(); ++it) {
		switch (*it) {
			case '+' :
				it = subLeft(it, currentState, '+');
				break ;
			case '|' :
				it = subLeft(it, currentState, '|');
				break ;
			case '^' :
				it = subLeft(it, currentState, '^');
				break ;
		}
	}

	return currentState;
}

std::string::iterator 		System::subLeft(std::string::iterator it, eFact & currentState, char ope) {
	char 					nextFact;
	eFact 					nextState;
	bool					bang = false;

	it++;
	nextFact = *it;

	while (nextFact == '!') {
		it++;
		nextFact = *it;
		bang = not bang;
	}

	nextState = getState(*it);

	if (bang)
		nextState = (nextState == vrai) ? faux : vrai;

	switch (ope) {
		case '+' :
			currentState = (currentState == vrai and nextState == vrai) ? vrai : faux;
			break ;
		case '|' :
			currentState = (currentState == vrai or nextState == vrai) ? vrai : faux;
			break ;
		case '^' :
			currentState = (currentState == vrai xor nextState == vrai) ? vrai : faux;
			break ;
	}

	return it;
}

eFact						System::tryRight(std::string rhs, char fact, eFact wanted) {
	rhs.insert(0, "+");

	eFact					currentState = vrai;

	for(std::string::iterator it = rhs.begin(); it != rhs.end(); ++it) {
		switch (*it) {
			case '+' :
				it = subRight(it, currentState, fact, wanted, '+');
				break ;
			case '|' :
				it = subRight(it, currentState, fact, wanted, '|');
				break ;
			case '^' :
				it = subRight(it, currentState, fact, wanted, '^');
				break ;
		}
	}

	return currentState;
}

std::string::iterator 		System::subRight(std::string::iterator it, eFact & currentState, char fact, eFact wanted, char ope) {
	char 					nextFact;
	eFact 					nextState;
	bool					bang = false;

	it++;
	nextFact = *it;

	while (nextFact == '!') {
		it++;
		nextFact = *it;
		bang = not bang;
	}

	nextState = getState(*it);

	if (nextFact == fact)
		nextState = wanted;

	if (bang)
		nextState = (nextState == vrai) ? faux : vrai;

	switch (ope) {
		case '+' :
			currentState = (currentState == vrai and nextState == vrai) ? vrai : faux;
			break ;
		case '|' :
			currentState = (currentState == vrai or nextState == vrai) ? vrai : faux;
			break ;
		case '^' :
			currentState = (currentState == vrai xor nextState == vrai) ? vrai : faux;
			break ;
	}

	return it;
}
