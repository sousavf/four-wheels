#include "Records.h"
#include <fstream>

bool operator > (const Time& time1, const Time& time2)
{
	if (time1.minutes > time2.minutes)
	{
		return true;
	}

	if ( (time1.minutes == time2.minutes)
			&& (time1.seconds > time2.seconds) )
	{
		return true;
	}

	return false;
}



bool operator < (const Time& time1, const Time& time2)
{
	return (time2 > time1);
}



/// Recebe 
Records::Records(const char* filename)
{
	this->filename = filename;
	load();
}



/// Destrutor.
Records::~Records()
{
}



/// Adiciona o tempo de uma corrida.
void Records::add(const Race &race)
{
	Record record;
	int best = 0;

	/// descobre qual foi o carro que terminou a corrida
	for (int i = 1; i < (int)race.count(); i++)
	{
		if (race.getCounter(i).getLaps() == race.getLaps())
		{
			best = i;
			break;
		}
	}
	record.track = race.getTrackODE().getName();
	record.time = toTime(race.getCounter(best).getTotalTime());
	record.laps = race.getLaps();
	add(record);
}



/// Adiciona um record à lista de records.
void Records::add(const Record &record)
{
	for (int i = 0; i < count(); i++)
	{
		if (getRecord(i).track == record.track && getRecord(i).laps == record.laps)
		{
			if (record.time < getRecord(i).time)
			{
				this->records[i] = record;

				return;
			}
			else
			{
				return;
			}
		}
	}
	this->records.push_back(record);
}



/// Carrega as informações do ficheiro.
void Records::load()
{
	ifstream ifile(this->filename.c_str());

	if (ifile.is_open())
	{
		ifile >> *this;
		ifile.close();
	}
}



/// Limpa a lista de records.
void Records::clear()
{
	this->records.clear();
}



/// Gravas as informações para o ficheiro.
void Records::save() const
{
	ofstream ofile(this->filename.c_str());

	ofile << *this;
	ofile.close();
}



/// Indica o nr. de recordes que tem.
int Records::count() const
{
	return (int)this->records.size();
}



/// Devolve o recorde correspondente ao índice i.
const Record & Records::getRecord(int i) const
{
	return this->records[i];
}



ostream& operator << (ostream& os, const Records& records)
{
	os << records.count() << endl;

	for (int i = 0; i < records.count(); i++)
	{
		os << records.records[i] << endl;
	}

	return os;
}



istream& operator >> (istream& is, Records& records)
{
	Record record;
	int count;

	is >> count;

	for (int i = 0; i < count; i++)
	{
		is >> record;
		records.add(record);
	}
	
	return is;
}



ostream& operator << (ostream& os, const Record& record)
{
	os << record.track;
	os << '\t';
	os << record.laps;
	os << '\t';
	os << record.time;

	return os;
}



istream& operator >> (istream& is, Record& record)
{
	char track[1000];
	Time time;
	int laps;

	is.get(track, 1000, '\t');
	is >> laps;
	//is >> c;
	is >> time;
	record.track = track;
	record.track = record.track.substr(1);
	record.time = time;
	record.laps = laps;

	return is;
}



ostream& operator << (ostream& os, const Time& time)
{
	os << time.minutes << ":" << time.seconds;

	return os;
}



istream& operator >> (istream& is, Time& time)
{
	int minutes, seconds;
	char c;

	is >> minutes;
	is >> c; // ignora :
	is >> seconds;

	time.minutes = minutes;
	time.seconds = seconds;

	return is;
}



Time Records::toTime(int miliseconds)
{
	Time time;

	time.seconds = (int)(miliseconds * 0.001f);
	
	if (time.seconds >= 60)
	{
		time.minutes = floor(time.seconds / 60.0f);
		time.seconds = time.seconds - time.minutes * 60.0f;
	}
	else
	{
		time.minutes = 0;
	}

	return time;
}