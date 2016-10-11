////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the TotoMiam library.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file 						TotoMiam/Rule.cpp
///	@author 					Lucas Bremond <lucas@axelspace.com>
///	@date 						9 Oct 2016

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoMiam/CalendarDate.hpp>

#include <TotoMiam/Rule.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TotoMiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

								Rule::Rule 									( )
								:	id_(0),
									type_(Rule::Type::Undefined),
									previousExecutionTime_(Time::Undefined()),
									nextExecutionTime_(Time::Undefined())
{

}

bool							Rule::isDefined								( ) const
{
	return type_ != Rule::Type::Undefined ;
}

uint							Rule::getId									( ) const
{
	return id_ ;
}

Rule::Type 						Rule::getType								( ) const
{
	return type_ ;
}

Time							Rule::getPreviousExecutionTime				( ) const
{
	return previousExecutionTime_ ;
}

Time							Rule::getNextExecutionTime					( ) const
{

	if (nextExecutionTime_.isDefined())
	{
		return nextExecutionTime_ ;
	}
	
	switch (type_)
	{

		case Rule::Type::Time:
		{

			if (previousExecutionTime_.isDefined())
			{

				nextExecutionTime_												=		previousExecutionTime_ + Duration::Seconds(86400) ;

			} else {

				CalendarDate	nextExecutionCalendarDate						=		CalendarDate::Time(Time::Now()) ;

				nextExecutionCalendarDate.setHours(time_.getHours()) ;
				nextExecutionCalendarDate.setMinutes(time_.getMinutes()) ;
				nextExecutionCalendarDate.setSeconds(time_.getSeconds()) ;

				nextExecutionTime_												=		Time::CalendarDate(nextExecutionCalendarDate) ;

			}

			break ;

		}

		case Rule::Type::Interval:
		{

			if (previousExecutionTime_.isDefined())
			{

				nextExecutionTime_												=		previousExecutionTime_ + interval_ ;

			} else {

				nextExecutionTime_												=		Time::Now() + interval_ ;

			}

			break ;

		}

	}

	return nextExecutionTime_ ;

}

void 							Rule::resetExecutionTime					(	const 	Time&						aTime 								)
{

	previousExecutionTime_														=		aTime ;
	nextExecutionTime_															=		Time::Undefined() ;

}

Rule							Rule::AtTime								(	const 	uint&						anId,
																				const 	CalendarDate&				aCalendarDate						)
{

	Rule						rule ;

	rule.id_																	=		anId ;
	rule.type_																	=		Rule::Type::Time ;
	rule.time_																	=		aCalendarDate ;

	return rule ;

}

Rule							Rule::AtInterval							(	const 	uint&						anId,
																				const 	Duration&					aDuration							)
{

	Rule						rule ;

	rule.id_																	=		anId ;
	rule.type_																	=		Rule::Type::Interval ;
	rule.interval_																=		aDuration ;

	return rule ;

}

String							Rule::getStringOfType						(	const 	Rule::Type&					aType								)
{

	switch (aType)
	{

		case Rule::Type::Undefined:
			return "Undefined" ;

		case Rule::Type::Time:
			return "Time" ;

		case Rule::Type::Interval:
			return "Interval" ;

	}

	return "Error" ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////