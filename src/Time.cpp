////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the TotoMiam library.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file 						TotoMiam/Time.cpp
///	@author 					Lucas Bremond <lucas@axelspace.com>
///	@date 						9 Oct 2016

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoMiam/Time.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TotoMiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

								Time::Time 									( )
								:	timestamp_(0)
{

}

bool							Time::operator ==							(	const 	Time&						aTime 								) const
{
	return (timestamp_ == aTime.timestamp_) ;
}

bool							Time::operator !=							(	const 	Time&						aTime 								) const
{
	return (timestamp_ != aTime.timestamp_) ;
}

bool							Time::operator <=							(	const 	Time&						aTime 								) const
{
	return (timestamp_ <= aTime.timestamp_) ;
}

bool							Time::operator <							(	const 	Time&						aTime 								) const
{
	return (timestamp_ < aTime.timestamp_) ;
}

bool							Time::operator >=							(	const 	Time&						aTime 								) const
{
	return (timestamp_ >= aTime.timestamp_) ;
}

bool							Time::operator >							(	const 	Time&						aTime 								) const
{
	return (timestamp_ > aTime.timestamp_) ;
}

Time 							Time::operator +							(	const 	Duration&					aDuration							) const
{

	if (this->isDefined())
	{

		Time 					time(*this) ;

		time.timestamp_														   +=		aDuration.getSeconds() ;

		return time ;

	}

	return Time::Undefined() ;

}

bool							Time::isDefined								( ) const
{
	return (timestamp_ > 0) ;
}

String							Time::getString								( ) const
{
	return DateTime(timestamp_).toFullDateTimeString() + " [UTC]" ;
}

Time 							Time::Undefined								( )
{
	
	Time 						time ;

	time.timestamp_																=		0 ;

	return time ;

}

Time 							Time::Now									( )
{

	// time_t						systemTime										=		RTC.getRtcSeconds() ;
	// time_t 						UTCTime											=		systemTime - (timezoneDiff * SECS_PER_HOUR) ;

	// return Time(UTCTime) ;

	return Time::Unix(SystemClock.now(TimeZone::eTZ_UTC).toUnixTime()) ;

}

Time 							Time::Unix									( 	const 	time_t&						aTimestamp							)
{

	Time 						time ;

	time.timestamp_																=		aTimestamp ;

	return time ;

}

Time 							Time::Parse									( 	const 	String&						aTimeString							)
{

	// XXXX-XX-XX XX:XX:XX [UTC]

	if (aTimeString.length() != 25)
	{
		return Time::Undefined() ;
	}

	Serial.println(aTimeString) ;

	int16_t 					year											=		aTimeString.substring(0, 4).toInt() ;
	int8_t 						month											=		aTimeString.substring(5, 7).toInt() ;
	int8_t 						day												=		aTimeString.substring(8, 10).toInt() ;

	int8_t 						hours											=		aTimeString.substring(11, 13).toInt() ;
	int8_t 						minutes											=		aTimeString.substring(14, 16).toInt() ;
	int8_t 						seconds											=		aTimeString.substring(17, 19).toInt() ;

	String 						timeScale										=		aTimeString.substring(20, 25) ;

	Serial.println(year) ;
	Serial.println(month) ;
	Serial.println(day) ;
	Serial.println(hours) ;
	Serial.println(minutes) ;
	Serial.println(seconds) ;
	Serial.println(timeScale) ;

	if ((year < 1970) || (year > 2050))
	{
		return Time::Undefined() ;
	}

	if ((month < 1) || (month > 12))
	{
		return Time::Undefined() ;
	}

	if ((day < 1) || (day > 31))
	{
		return Time::Undefined() ;
	}

	if ((hours < 0) || (hours > 24))
	{
		return Time::Undefined() ;
	}

	if ((minutes < 0) || (minutes > 60))
	{
		return Time::Undefined() ;
	}

	if ((seconds < 0) || (seconds > 60))
	{
		return Time::Undefined() ;
	}

	if (timeScale != "[UTC]")
	{
		return Time::Undefined() ;
	}

	DateTime 					dateTime ;

	dateTime.setTime(seconds, minutes, hours, day, month, year) ;

	return Time::Unix(dateTime.toUnixTime()) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////