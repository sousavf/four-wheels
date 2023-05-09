#ifndef Chromossome_h
#define Chromossome_h

#include <vector>
#include <iostream>

class Chromossome
{
	friend class GeneticAlgorithm;

	public:
		Chromossome();
		Chromossome(int genes);
		Chromossome(const Chromossome &another_chromo);
		Chromossome(const std::vector< double > &genes);
		Chromossome(const std::vector< double > &genes, double fitness);
		~Chromossome();

		bool operator == (const Chromossome &another_chromo);
		bool operator < (const Chromossome &another_chromo);
		bool operator > (const Chromossome &another_chromo);
		double& operator [] (const int &index);
		double GetFitness();
		void SetFitness(double fitness);
		void IncFitness(double fitness);
		void DecFitness(double fitness);
		int Length() const;
		void GetGenes(std::vector< double > &genes);
		std::vector< double > GetGenes() const;
		void SetGenes(std::vector< double > &genes);

		friend std::ostream& operator << (std::ostream& os, const Chromossome& chromossome);
		friend std::istream& operator >> (std::istream& is, Chromossome& chromossome);

	protected:
		std::vector< double > genes;
		double fitness;

};

#endif
