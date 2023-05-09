#ifndef StandardElitism_h
#define StandardElitism_h

#include "Elitism.h"

class StandardElitism : public Elitism
{
	public:
		StandardElitism();
		StandardElitism(int elitistSize);
		~StandardElitism();

		std::vector< Chromossome > Choose(const GeneticAlgorithm* ga) const;
		void SetElitistSize(int value);
		int GetElitistSize() const;
		virtual ElitismType Type() const;

	protected:
		int elitistSize;

		void Init(int elitistSize);
		static bool Bigger(Chromossome &c1, Chromossome &c2);
		virtual std::ostream& Save(std::ostream& os) const;
		virtual std::istream& Load(std::istream& is);
};

#endif