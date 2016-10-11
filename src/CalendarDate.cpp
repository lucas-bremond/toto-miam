////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the TotoMiam library.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file 						TotoMiam/CalendarDate.cpp
///	@author 					Lucas Bremond <lucas@axelspace.com>
///	@date 						9 Oct 2016

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoMiam/Time.hpp>

#include <TotoMiam/CalendarDate.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TotoMiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

								CalendarDate::CalendarDate 					( )
								:	year_(0),
									month_(0),
									day_(0),
									hours_(0),
									minutes_(0),
									seconds_(0)
{

}

bool							CalendarDate::operator ==					(	const 	CalendarDate&				aCalendarDate 						) const
{
	return (year_ == aCalendarDate.year_) && (month_ == aCalendarDate.month_) && (day_ == aCalendarDate.day_) && (hours_ == aCalendarDate.hours_) && (minutes_ == aCalendarDate.minutes_) && (seconds_ == aCalendarDate.seconds_) ;
}

bool							CalendarDate::operator !=					(	const 	CalendarDate&				aCalendarDate 						) const
{
	return (year_ != aCalendarDate.year_) || (month_ != aCalendarDate.month_) || (day_ != aCalendarDate.day_) || (hours_ != aCalendarDate.hours_) || (minutes_ != aCalendarDate.minutes_) || (seconds_ != aCalendarDate.seconds_) ;
}

bool							CalendarDate::isDefined						( ) const
{
	return (year_ != 0) || (month_ != 0) || (day_ != 0) || (hours_ != 0) || (minutes_ != 0) || (seconds_ != 0) ;
}

int16_t							CalendarDate::getYear						( ) const
{
	return year_ ;
}

int8_t							CalendarDate::getMonth						( ) const
{
	return month_ ;
}

int8_t							CalendarDate::getDay						( ) const
{
	return day_ ;
}

int8_t							CalendarDate::getHours						( ) const
{
	return hours_ ;
}

int8_t							CalendarDate::getMinutes					( ) const
{
	return minutes_ ;
}

int8_t							CalendarDate::getSeconds					( ) const
{
	return seconds_ ;
}

String							CalendarDate::getString						( ) const
{
	
	// 2000-01-01 00:00:00 [UTC]

	char buffer[25] ;
	
	sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d [UTC]", year_, month_, day_, hours_, minutes_, seconds_) ;	

	return String(buffer) ;

}

void							CalendarDate::setYear						( 	const 	int16_t&					aYearCount							)
{
	year_																		=			aYearCount ;
}

void							CalendarDate::setMonth						( 	const 	int8_t&						aMonthCount							)
{
	month_																		=			aMonthCount ;
}

void							CalendarDate::setDay						( 	const 	int8_t&						aDayCount							)
{
	day_																		=			aDayCount ;
}

void							CalendarDate::setHours						( 	const 	int8_t&						aHourCount							)
{
	hours_																		=			aHourCount ;
}

void							CalendarDate::setMinutes					( 	const 	int8_t&						aMinuteCount						)
{
	minutes_																	=			aMinuteCount ;
}

void							CalendarDate::setSeconds					( 	const 	int8_t&						aSecondCount						)
{
	seconds_																	=			aSecondCount ;
}

CalendarDate 					CalendarDate::Undefined						( )
{
	
	CalendarDate 				calendarDate ;

	calendarDate.year_															=		0 ;
	calendarDate.month_															=		0 ;
	calendarDate.day_															=		0 ;
	
	calendarDate.hours_															=		0 ;
	calendarDate.minutes_														=		0 ;
	calendarDate.seconds_														=		0 ;

	return calendarDate ;

}

CalendarDate					CalendarDate::Time							(	const 	TotoMiam::Time&				aTime 								)
{

	CalendarDate 				calendarDate ;

	// TBM !!!

	int16_t 					year											=		0 ;
	int8_t 						month											=		0 ;
	int8_t 						day												=		0 ;

	int8_t 						hours											=		0 ;
	int8_t 						minutes											=		0 ;
	int8_t 						seconds											=		0 ;

	if ((year < 1970) || (year > 2050))
	{
		return CalendarDate::Undefined() ;
	}

	if ((month < 1) || (month > 12))
	{
		return CalendarDate::Undefined() ;
	}

	if ((day < 1) || (day > 31))
	{
		return CalendarDate::Undefined() ;
	}

	if ((hours < 0) || (hours > 24))
	{
		return CalendarDate::Undefined() ;
	}

	if ((minutes < 0) || (minutes > 60))
	{
		return CalendarDate::Undefined() ;
	}

	if ((seconds < 0) || (seconds > 60))
	{
		return CalendarDate::Undefined() ;
	}

	// if (timeScale != "[UTC]")
	// {
	// 	return Time::Undefined() ;
	// }

	calendarDate.year_															=		year ;
	calendarDate.month_															=		month ;
	calendarDate.day_															=		day ;
	
	calendarDate.hours_															=		hours ;
	calendarDate.minutes_														=		minutes ;
	calendarDate.seconds_														=		seconds ;

	return calendarDate ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////