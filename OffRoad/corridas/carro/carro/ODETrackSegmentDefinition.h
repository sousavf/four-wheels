#ifndef ODETRACKSEGMENTDEFINITION_H
#define ODETRACKSEGMENTDEFINITION_H

#include "ODERequirements.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

namespace ODE
{
	/// Representa a definição de um segmento de pista.
	class ODETrackSegmentDefinition
	{
	public:
		enum Side
		{
			Front,
			Right,
			Back,
			Left
		};

		enum Block
		{
			Empty,
			StartStraightFront, 		//	| |	start line para "cima"
			StartStraightBack,  		//	| |	start line para "baixo"
			StartStraightLeft,			//	 =	start line para a esquerda
			StartStraightRight,			//	 =	start line para a direita
			Straight,					//	| |	"vertical"
			StraightSide,				//	 =	"horizontal"
			Curve90BottomToRight,		//	,-	curva 90 graus baixo-direita
			Curve90LeftToBottom,		//	-,	curva 90 graus esquerda-baixo
			Curve90TopToRight,			//	|_	curva 90 graus topo-direita
			Curve90LeftToTop,			//	 _|	curva 90 graus esquerda-topo
			RampStraightElevated,		//  |\| rampa "vertical" para cima
			RampStraightSunken,			//	|/|	rampa "vertical para baixo
			RampStraightSideElevated,	//   /\ rampa "horizontal" para cima
			RampStraightSideSunken		//   \/ rampa "horizontal" para baixo
		};

		enum Surface
		{
			Gravel,
			Grass,
			Snow,
			Ice
		};
		static ODETrackSegmentDefinition get(Block b);


		ODETrackSegmentDefinition(const vector< Side >& sides, Block type
			, bool isStartLine, Side startDirection
			, const ODEVector3 &size, ODEReal borderSize
			, ODEReal sidelinesWidth, ODEReal rampHeight);
		ODETrackSegmentDefinition(Side side1, Side side2, Block type
			, bool isStartLine, Side startDirection
			, const ODEVector3 &size, ODEReal borderSize
			, ODEReal sidelinesWidth, ODEReal rampHeight);
		ODETrackSegmentDefinition(const ODETrackSegmentDefinition &def);
		~ODETrackSegmentDefinition();

		void setSize(const ODEVector3 &size);
		void setBorderSize(ODEReal border);
		void setSizes(vector< Side > sides);
		void setType(Block block);
		void setStartLine(bool start);
		void setSidelinesWidth(ODEReal width);
		void setGroundSurface(Surface s);
		void setSidelinesSurface(Surface s);
		void setRampHeight(ODEReal h);

		const ODEVector3& getSize() const;
		ODEReal getBorderSize() const;
		const vector< Side >& getSides() const;
		Block getType() const;
		bool isStartLine() const;
		Side getStartDirection() const;
		ODEReal getSidelinesWidth() const;
		const ODEContactDefinition& getGroundContact() const;
		const ODEContactDefinition& getSidelinesContact() const;
		Surface getGroundSurface() const;
		Surface getSidelinesSurface() const;
		ODEReal getRampHeight() const;

		ODETrackSegmentDefinition& operator = (const ODETrackSegmentDefinition &t);
		friend ostream& operator << (ostream& os, const ODETrackSegmentDefinition &t);
		friend istream& operator >> (istream& is, ODETrackSegmentDefinition &t);

	protected:
		vector< Side > sides;
		ODEVector3 size;
		ODEReal borderSize;
		Block type;
		bool startLine;
		Side startDirection;
		ODEReal sidelinesWidth;
		ODEContactDefinition groundContact;
		ODEContactDefinition sidelinesContact;
		Surface groundSurface;
		Surface sidelinesSurface;
		ODEReal rampHeight;

		void Init(const vector< Side >& sides, Block type
			, bool isStartLine, Side startDirection
			, const ODEVector3 &size, ODEReal borderSize
			, ODEReal sidelinesWidth, ODEReal rampHeight);
		static const ODEContactDefinition getContactDefinition(Surface s);
	};
}

#endif