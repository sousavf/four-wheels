#include "TrackCollection.h"
#include <fstream>

/// Cria uma nova colecção para repositório de pistas.
TrackCollection::TrackCollection()
{
}



/// Destrói a collecção de pistas.
TrackCollection::~TrackCollection()
{
	for (int i = 0; i < (int) this->tracks.size(); i++)
	{
		delete this->tracks[i];
	}
}



/// Adiciona uma nova pista à collecção.
void TrackCollection::AddTrack(Track &track)
{
	this->tracks.push_back(new Track(track));
}



/// Adiciona uma nova pista construída à sorte e com length à colecção.
void TrackCollection::AddRandomTrack(double length)
{
	Track* newTrack = new Track();
	
	newTrack->Random(length);
	this->tracks.push_back(newTrack);
}



/// Adiciona uma nova pista construída à sorte e com segments à colecção.
void TrackCollection::AddRandomTrack(int segments)
{
	Track* newTrack = new Track();
	
	newTrack->Random(segments);
	this->tracks.push_back(newTrack);
}



/// Apaga a pista na posição index.
bool TrackCollection::RemoveTrack(int index)
{
	if ( (index >= 0) && (index < (int)this->tracks.size()) )
	{
        this->tracks[index]->~Track();
		delete this->tracks[index];
		this->tracks.erase(this->tracks.begin() + index);
	
		return true;
	}

	return false;
}



/// Devolve a pista correspondente a index.
Track* TrackCollection::GetTrack(int index) const
{
	if ( (index >= 0) && (index < (int)this->tracks.size()) )
	{
		return this->tracks[index];
	}

	return NULL;
}



/// Devolve o número de pistas.
int TrackCollection::Length() const
{
	return (int)this->tracks.size();
}



/// Carrega a colecção de pistas em filename.
void TrackCollection::Load(const char* filename)
{
	this->tracks.clear();
	std::ifstream ifile(filename);
	ifile >> *this;
	ifile.close();
}



/// Grava a colecção de pistas para filename.
void TrackCollection::Save(const char* filename) const
{
	std::ofstream ofile(filename);
	ofile << *this;
	ofile.close();
}



/// Grava no stream a colecção de pistas.
std::ostream& operator << (std::ostream &os, const TrackCollection &trackCollection)
{
	os << trackCollection.Length() << std::endl;

	for (int i = 0; i < trackCollection.Length(); i++)
	{
		os << *(trackCollection.GetTrack(i)) << std::endl;
	}

	return os;
}



/// Carrega uma colecção de pistas do stream.
std::istream& operator >> (std::istream &is, TrackCollection &trackCollection)
{
	Track track;
	int tracks;

	is >> tracks;

	for (int i = 0; i < tracks; i++)
	{
		if (is >> track)
		{
			trackCollection.AddTrack(track);
		}
	}

	return is;
}



/// Apaga todas as pistas da colecção.
void TrackCollection::RemoveTracks()
{
	while(this->Length())
	{
		RemoveTrack(0);
	}
}