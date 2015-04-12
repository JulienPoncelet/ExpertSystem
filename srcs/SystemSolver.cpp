#include <main.hpp>

void						System::solve(void) {
	Facts					facts = getFacts();

	Facts::const_iterator	fit  = facts.begin();
	Facts::const_iterator	fite = facts.end();

	for (; fit != fite; fit++) {
		solveFact(fit->first);
		clearUsedRules();
	}

	return ;
}

void						System::solveFact(char fact) {
	Rules::const_iterator	rit  = getRules().begin();
	Rules::const_iterator	rite = getRules().end();

	for (; rit != rite; rit++) {
		std::string			rhs = rit->getRight();
		if (rhs.find(fact) != std::string::npos) {
			if (not ruleUsed(*rit)) {
				addUsedRules(*rit);
				solveRule(*rit, fact);
			}
		}
	}

	return ;
}


void						System::solveRule(Rule rule, char fact) {
	std::string 	       	lhs = rule.getLeft();
	std::string 	       	rhs = rule.getRight();

	for(char c : lhs) {
		if (isFact(c))
			solveFact(c);
	}
	
	for(char c : rhs) {
		if (isFact(c) and fact != c)
			solveFact(c);
	}

	eFact 					leftState  = evaluateLeft(lhs);

	if (leftState == vrai) {
		RightMap			tmpSolutions = generateSolution(rhs);
		RightMap::iterator	sit  = tmpSolutions.begin();
		RightMap::iterator	site = tmpSolutions.end();

		for (; sit != site; sit++)
			sit->second = evaluateRight(sit->first);
		

		sit  = tmpSolutions.begin();
		RightMap			finalSolutions;

		for (; sit != site; sit++) {
			if (sit->second == vrai)
				finalSolutions[sit->first] = sit->second;
		}

		Facts 				newFacts = solutionsToFacts(rhs, finalSolutions);

		Facts::iterator		fit  = newFacts.begin();
		Facts::iterator		fite = newFacts.end();

		for (; fit != fite; fit++)
			updateState(fit->first, fit->second);
	}

	return ;
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

RightMap 						System::generateSolution(std::string rhs) {
	RightMap					solutions;
	int 						n = 0;

	for (char c : rhs) {
		if (isFact(c))
			n++;
	}

	int 						m, p, q;
	std::ostringstream 			oss;
	std::string 				tmpString;

	for (m = 0; m < pow(2, n); m++) {
		q = m;
		tmpString = rhs;
		for (p = n - 1; p >= 0; p--) {
			oss << int(q / pow(2, p));
			q = fmod(q, pow(2, p));

			for (size_t i = 0; i < tmpString.size(); i++) {
				if (isFact(tmpString[i])) {
					tmpString[i] = oss.str()[0];
					break ;
				}
			}

			oss.str("");
		}
		solutions[tmpString] = unsolved;
	}

	return solutions;
}

eFact						System::evaluateRight(std::string rhs) {
	rhs.insert(0, "+");

	eFact					currentState = vrai;

	for(std::string::iterator it = rhs.begin(); it != rhs.end(); ++it) {
		switch (*it) {
			case '+' :
				it = subRight(it, currentState, '+');
				break ;
			case '|' :
				it = subRight(it, currentState, '|');
				break ;
			case '^' :
				it = subRight(it, currentState, '^');
				break ;
		}
	}

	return currentState;
}

std::string::iterator 		System::subRight(std::string::iterator it, eFact & currentState, char ope) {
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

	nextState = (*it == '0') ? faux : vrai;

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

Facts 						System::solutionsToFacts(std::string rhs, RightMap solutions) {
	Facts 					facts;
	RightMap::iterator		site = solutions.end();	

	for (size_t i = 0; i < rhs.size(); i++) {
		if (isFact(rhs[i])) {
			CharList		tmpCharList;

			for (RightMap::iterator	sit  = solutions.begin(); sit != site; sit++) {
				tmpCharList.push_back((sit->first)[i]);
			}

			tmpCharList.unique();

			if (tmpCharList.size() >= 2)
				facts[rhs[i]] = undefined;
			else if (tmpCharList.front() == '0')
				facts[rhs[i]] = faux;
			else
				facts[rhs[i]] = vrai;
		}
	}

	return facts;
}
