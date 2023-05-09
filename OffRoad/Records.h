#ifndef RECORDS_H
#define RECORDS_H

#include "Race.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

typedef struct Time
{
	int minutes;
	int seconds;
} Time;

typedef struct Record
{
	string track;
	int laps;
	Time time;
} Record;

/// Classe para gravar os melhores tempos.
class Records
{
public:
	Records(const char* filename);
	~Records();

	void add(const Race &race);
	void add(const Record &record);
	void load();
	void clear();
	void save() const;
	int count() const;
	const Record & getRecord(int i) const;

	friend ostream& operator << (ostream& os, const Records& records);
	friend istream& operator >> (istream& is, Records& records);
	friend ostream& operator << (ostream& os, const Record& record);
	friend istream& operator >> (istream& is, Record& record);
	friend ostream& operator << (ostream& os, const Time& time);
	friend istream& operator >> (istream& is, Time& time);
	friend bool operator > (const Time& time1, const Time& time2);
	friend bool operator < (const Time& time1, const Time& time2);

	static Time toTime(int miliseconds);

protected:
	string filename;
	vector< Record > records;
};

#endif