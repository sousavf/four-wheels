#ifndef TrackCollection_h
#define TrackCollection_h

#include <vector>
#include "Track.h"

class TrackCollection
{
	public:
		TrackCollection();
		~TrackCollection();

		void AddTrack(Track &track);
		void AddRandomTrack(double length);
		void AddRandomTrack(int segments);
		bool RemoveTrack(int index);
		void RemoveTracks();
		Track* GetTrack(int index) const;
		int Length() const;
		void Load(const char* filename);
		void Save(const char* filename) const;

		friend std::ostream& operator << (std::ostream &os, const TrackCollection &trackCollection);
		friend std::istream& operator >> (std::istream &is, TrackCollection &trackCollection);

	protected:
		std::vector< Track* > tracks;
};

#endif