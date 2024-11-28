#pragma once

#include "Solution.hpp"

class GeneticAlgorithm {
public:
	GeneticAlgorithm(SolutionSettings settings);
	~GeneticAlgorithm();

	void select();
	void mutate();
	void crossover();
	void evaluate();


private:
	Solution* solutions;



};
