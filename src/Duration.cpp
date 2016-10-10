////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the TotoMiam library.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file 						TotoMiam/Duration.cpp
///	@author 					Lucas Bremond <lucas@axelspace.com>
///	@date 						9 Oct 2016

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoMiam/Duration.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TotoMiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

								Duration::Duration 							( )
								:	duration_(0)
{

}

bool							Duration::operator ==						(	const 	Duration&						aDuration 								) const
{
	return (duration_ == aDuration.duration_) ;
}

bool							Duration::operator !=						(	const 	Duration&						aDuration 								) const
{
	return (duration_ != aDuration.duration_) ;
}

bool							Duration::operator <=						(	const 	Duration&						aDuration 								) const
{
	return (duration_ <= aDuration.duration_) ;
}

bool							Duration::operator <						(	const 	Duration&						aDuration 								) const
{
	return (duration_ < aDuration.duration_) ;
}

bool							Duration::operator >=						(	const 	Duration&						aDuration 								) const
{
	return (duration_ >= aDuration.duration_) ;
}

bool							Duration::operator >						(	const 	Duration&						aDuration 								) const
{
	return (duration_ > aDuration.duration_) ;
}

time_t							Duration::getSeconds						( ) const
{
	return duration_ ;
}

String							Duration::getString							( ) const
{

	char buffer[64] ;
	
	sprintf(buffer, "%d [sec]", duration_) ;	

	return String(buffer) ;

}

Duration 						Duration::Zero								( )
{
	
	Duration 					duration ;

	duration.duration_															=		0 ;

	return duration ;

}

Duration 						Duration::Seconds							( 	const 	time_t&						aSecondCount						)
{

	Duration 					duration ;

	duration.duration_															=		aSecondCount ;

	return duration ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////