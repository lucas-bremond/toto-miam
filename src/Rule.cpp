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
									time_(CalendarDate::Undefined()),
									interval_(Duration::Zero()),
									taskDuration_(Duration::Zero()),
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

CalendarDate					Rule::getTime 								( ) const
{
	return time_ ;
}

Duration 						Rule::getInterval 							( ) const
{
	return interval_ ;
}

Duration 						Rule::getTaskDuration						( ) const
{
	return taskDuration_ ;
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
				nextExecutionTime_												=		previousExecutionTime_ + Duration::Seconds(86400) ; // 86400 = 24 x 3600
			}
			else
			{

				CalendarDate	nextExecutionCalendarDate						=		CalendarDate::Time(Time::Now()) ;

				nextExecutionCalendarDate.setHours(time_.getHours()) ;
				nextExecutionCalendarDate.setMinutes(time_.getMinutes()) ;
				nextExecutionCalendarDate.setSeconds(time_.getSeconds()) ;

				nextExecutionTime_												=		Time::CalendarDate(nextExecutionCalendarDate) ;

				if (nextExecutionTime_ < Time::Now())
				{
					nextExecutionTime_											=		nextExecutionTime_ + Duration::Seconds(86400) ; // 86400 = 24 x 3600
				}

			}

			break ;

		}

		case Rule::Type::Interval:
		{

			if (previousExecutionTime_.isDefined())
			{
				nextExecutionTime_												=		previousExecutionTime_ + interval_ ;
			}
			else
			{
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
																				const 	CalendarDate&				aCalendarDate,
																				const 	Duration&					aTaskDuration						)
{

	Rule						rule ;

	rule.id_																	=		anId ;
	rule.type_																	=		Rule::Type::Time ;
	rule.time_																	=		aCalendarDate ;
	rule.taskDuration_															=		aTaskDuration ;

	return rule ;

}

Rule							Rule::AtInterval							(	const 	uint&						anId,
																				const 	Duration&					anInterval,
																				const 	Duration&					aTaskDuration						)
{

	Rule						rule ;

	rule.id_																	=		anId ;
	rule.type_																	=		Rule::Type::Interval ;
	rule.interval_																=		anInterval ;
	rule.taskDuration_															=		aTaskDuration ;

	return rule ;

}

Rule::Type						Rule::TypeFromString						(	const 	String&						aString								)
{

	if (aString == "Undefined")
	{
		return Rule::Type::Undefined ;
	}

	if (aString == "Time")
	{
		return Rule::Type::Time ;
	}

	if (aString == "Interval")
	{
		return Rule::Type::Interval ;
	}

	return Rule::Type::Undefined ;

}

String							Rule::StringFromType						(	const 	Rule::Type&					aType								)
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