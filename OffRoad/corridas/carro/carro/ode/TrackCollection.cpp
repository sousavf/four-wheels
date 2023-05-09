#include "TrackCollection.h"
#include <fstream>

/// Cria uma nova colec��o para reposit�rio de pistas.
TrackCollection::TrackCollection()
{
}



/// Destr�i a collec��o de pistas.
TrackCollection::~TrackCollection()
{
	for (int i = 0; i < (int) this->tracks.size(); i++)
	{
		delete this->tracks[i];
	}
}



/// Adiciona uma nova pista � collec��o.
void TrackCollection::AddTrack(Track &track)
{
	this->tracks.push_back(new Track(track));
}



/// Adiciona uma nova pista constru�da � sorte e com length � colec��o.
void TrackCollection::AddRandomTrack(double length)
{
	Track* newTrack = new Track();
	
	newTrack->Random(length);
	this->tracks.push_back(newTrack);
}



/// Adiciona uma nova pista constru�da � sorte e com segments � colec��o.
void TrackCollection::AddRandomTrack(int segments)
{
	Track* newTrack = new Track();
	
	newTrack->Random(segments);
	this->tracks.push_back(newTrack);
}



/// Apaga a pista na posi��o index.
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



/// Devolve o n�mero de pistas.
int TrackCollection::Length() const
{
	return (int)this->tracks.size();
}



/// Carrega a colec��o de pistas em filename.
void TrackCollection::Load(const char* filename)
{
	this->tracks.clear();
	std::ifstream ifile(filename);
	ifile >> *this;
	ifile.close();
}



/// Grava a colec��o de pistas para filename.
void TrackCollection::Save(const char* filename) const
{
	std::ofstream ofile(filename);
	ofile << *this;
	ofile.close();
}



/// Grava no stream a colec��o de pistas.
std::ostream& operator << (std::ostream &os, const TrackCollection &trackCollection)
{
	os << trackCollection.Length() << std::endl;

	for (int i = 0; i < trackCollection.Length(); i++)
	{
		os << *(trackCollection.GetTrack(i)) << std::endl;
	}

	return os;
}



/// Carrega uma colec��o de pistas do stream.
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



/// Apaga todas as pistas da colec��o.
void TrackCollection::RemoveTracks()
{
	while(this->Length())
	{
		RemoveTrack(0);
	}
}