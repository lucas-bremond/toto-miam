////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the TotoMiam library.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file 						TotoMiam/Duration.hpp
///	@author 					Lucas Bremond <lucas@axelspace.com>
///	@date 						9 Oct 2016

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __TotoMiam_Duration_HPP_INCLUDED__
#define __TotoMiam_Duration_HPP_INCLUDED__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SmingCore/SmingCore.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TotoMiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Time ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Duration
{

	public:

								Duration 									( ) ;

								Duration 									( 	const 	Time&						anEarlierTime,
																				const 	Time&						aLaterTime							) ;

		bool					operator ==									(	const 	Duration&					aDuration 							) const ;
		bool					operator !=									(	const 	Duration&					aDuration 							) const ;
		bool					operator <=									(	const 	Duration&					aDuration 							) const ;
		bool					operator <									(	const 	Duration&					aDuration 							) const ;
		bool					operator >=									(	const 	Duration&					aDuration 							) const ;
		bool					operator >									(	const 	Duration&					aDuration 							) const ;

		bool					isDefined									( ) const ;

		int						getSeconds									( ) const ;
		String					getString									( ) const ;

		static Duration 		Undefined									( ) ;

		static Duration 		Zero										( ) ;

		static Duration 		Seconds										( 	const 	int&						aSecondCount						) ;
		static Duration 		Minutes										( 	const 	int&						aMinuteCount						) ;

	private:

		bool					defined_ ;
		int						duration_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////