#ifndef Selection_h
#define Selection_h

class Chromossome;
class GeneticAlgorithm;

class Selection
{
	public:
		virtual Chromossome& Select(GeneticAlgorithm* ga) const = 0;
};

#endif