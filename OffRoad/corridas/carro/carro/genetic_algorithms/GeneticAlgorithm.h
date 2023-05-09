#ifndef GeneticAlgorithm_h
#define GeneticAlgorithm_h

#include <vector>
#include "Chromossome.h"
#include "Selection.h"
#include "RoulletteWheelSelection.h"
#include "RankSelection.h"
#include "TournamentSelection.h"
#include "Elitism.h"
#include "StandardElitism.h"
#include "Crossover.h"
#include "SinglePointCrossover.h"
#include "TwoPointCrossover.h"
#include "NPointCrossover.h"
#include "UniformCrossover.h"
#include "DiagonalCrossover.h"
#include "UniformScanningCrossover.h"

class GeneticAlgorithm
{
	public:
		GeneticAlgorithm(std::vector< Chromossome > &chromossomes);
		GeneticAlgorithm(double mutationRate, double crossoverRate, std::vector< Chromossome > &chromossomes);
		GeneticAlgorithm(int population_size, int genes);
		GeneticAlgorithm(double mutationRate, double crossoverRate, int population_size, int genes);
		~GeneticAlgorithm();
		
		void AddChromossome(Chromossome &chromossome);
		void RemoveChromossome(int i);
		void Replace(std::vector< Chromossome > &chromossomes);
		void Replace(Chromossome* chromossomes, int size);
		void Epoch();
		double UpdateTotalFitness();
		Chromossome& Select();
		void Mutate(Chromossome &chromossome);
		void ScaleAndInvertFitness();

		void SetGenerationCount(int value);
		void SetMaxPerturbation(double maxPerturbation);
		void SetMutationRate(double mutationRate);
		void SetSelection(Selection* selection);
		void SetDoElitism(bool value);
		void SetElitism(Elitism* function);
		void SetCrossover(Crossover* crossover);
		void SetScaleAndInvertFitness(bool value);

		int GetGenerationCount() const;
		double GetMaxPerturbation() const;
		double GetMutationRate() const;
		Selection* GetSelection() const;
		bool GetDoElitism() const;
		Elitism* GetElitism() const;
		Crossover* GetCrossover() const;
		std::vector< Chromossome > GetChromossomes() const;
		std::vector< double > GetGenes();
		bool GetScaleAndInvertFitness() const;

		double TotalFitness() const;
		int PopulationSize() const;

		Chromossome& operator [] (const int &index);


		static bool ScaleAndInvertCheck();

	protected:
		static const double MUTATION_RATE;
		static const double CROSSOVER_RATE;
		static const double MAX_PERTURBATION;

		std::vector< Chromossome > chromossomes;
		double mutationRate;
		double maxPerturbation;
		double totalFitness;
		int generationCount;
		Selection* selection;
		bool doElitism;
		Elitism* elitism;
		Crossover* crossover;
		bool scaleAndInvert;

		void Init(double mutationRate, double crossoverRate, std::vector< Chromossome > &chromossomes);
};

#endif
