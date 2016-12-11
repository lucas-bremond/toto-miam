////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the TotoMiam library.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file 						TotoMiam/Duration.cpp
///	@author 					Lucas Bremond <lucas@axelspace.com>
///	@date 						9 Oct 2016

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoMiam/Time.hpp>
#include <TotoMiam/Duration.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TotoMiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

								Duration::Duration 							( )
								:	defined_(false),
									duration_(0)
{

}

								Duration::Duration 							( 	const 	Time&						anEarlierTime,
																				const 	Time&						aLaterTime							)
								:	defined_(true),
									duration_(aLaterTime.getUnixTime() - anEarlierTime.getUnixTime())
{

}

bool							Duration::operator ==						(	const 	Duration&					aDuration 							) const
{
	return (duration_ == aDuration.duration_) ;
}

bool							Duration::operator !=						(	const 	Duration&					aDuration 							) const
{
	return (duration_ != aDuration.duration_) ;
}

bool							Duration::operator <=						(	const 	Duration&					aDuration 							) const
{
	return (duration_ <= aDuration.duration_) ;
}

bool							Duration::operator <						(	const 	Duration&					aDuration 							) const
{
	return (duration_ < aDuration.duration_) ;
}

bool							Duration::operator >=						(	const 	Duration&					aDuration 							) const
{
	return (duration_ >= aDuration.duration_) ;
}

bool							Duration::operator >						(	const 	Duration&					aDuration 							) const
{
	return (duration_ > aDuration.duration_) ;
}

bool							Duration::isDefined							( ) const
{
	return defined_ ;
}

int								Duration::getSeconds						( ) const
{
	return duration_ ;
}

String							Duration::getString							( ) const
{

	char buffer[64] ;
	
	sprintf(buffer, "%d [sec]", duration_) ;	

	return String(buffer) ;

}

Duration 						Duration::Undefined							( )
{
	
	Duration 					duration ;

	duration.defined_															=		false ;
	duration.duration_															=		0 ;

	return duration ;

}

Duration 						Duration::Zero								( )
{
	
	Duration 					duration ;

	duration.defined_															=		true ;
	duration.duration_															=		0 ;

	return duration ;

}

Duration 						Duration::Seconds							( 	const 	int&						aSecondCount						)
{

	Duration 					duration ;

	duration.defined_															=		true ;
	duration.duration_															=		aSecondCount ;

	return duration ;

}

Duration 						Duration::Minutes							( 	const 	int&						aMinuteCount						)
{

	Duration 					duration ;

	duration.defined_															=		true ;
	duration.duration_															=		aMinuteCount * 60 ;

	return duration ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////