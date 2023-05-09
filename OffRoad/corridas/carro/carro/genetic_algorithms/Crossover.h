#ifndef Crossover_h
#define Crossover_h

#include "Chromossome.h"
#include "../ode/Math.h"
#include <iostream>
#include <string>

class Crossover
{
	public:
		enum CrossoverType
		{
			SinglePoint,
			TwoPoint,
			Uniform,
			UniformScanning,
			NPoint,
			Diagonal
		};

		Crossover();
		Crossover(double probability);
		~Crossover();

		bool Reproduce(const std::vector< Chromossome > &parents, std::vector< Chromossome > &sons) const;
		int GetParentsCount() const;
		int GetSonsCount() const;
		double GetProbability() const;
		void SetProbability(double value);
		virtual std::string ToString() const;

		friend std::ostream& operator << (std::ostream& os, const Crossover& crossover);
		friend std::istream& operator >> (std::istream& is, Crossover& crossover);
		virtual CrossoverType Type() const = 0;

		static Crossover* Read(std::istream& is);

	protected:
		int parents;
		int sons;
		double probability;

		void Init(int parents, int sons, double probability);
		virtual std::ostream& Save(std::ostream& os) const;
		virtual std::istream& Load(std::istream& is);
		virtual void Cross(const std::vector< Chromossome > &parents
									, std::vector< Chromossome > &sons) const = 0;
		static void GenesToChromossomes(const std::vector< double > *genes, const int size
										, std::vector< Chromossome > &chromossomes);
};

#endif