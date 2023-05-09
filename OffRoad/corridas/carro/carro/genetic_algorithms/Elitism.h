#ifndef Elitism_h
#define Elitism_h

#include <vector>
#include <iostream>
#include <string>

class Chromossome;
class GeneticAlgorithm;

class Elitism
{
	public:
		enum ElitismType
		{
			Standard
		};

		virtual std::vector< Chromossome > Choose(const GeneticAlgorithm* ga) const = 0;
		virtual ElitismType Type() const = 0;
		virtual std::string ToString() const;

		friend std::ostream& operator << (std::ostream& os, const Elitism& elitism);
		friend std::istream& operator >> (std::istream& is, Elitism& elitism);

		static Elitism* Read(std::istream& is);

	protected:
		virtual std::ostream& Save(std::ostream& os) const = 0;
		virtual std::istream& Load(std::istream& is) = 0;
};

#endif