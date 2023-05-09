#ifndef WEATHER_H
#define WEATHER_H


enum weather
{
	Dia,
	Dia_Nevoeiro,
	Noite,
	Noite_Nevoeiro
};


class Weather
{	
	public:
		static weather activeWeather;
};

#endif;