////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the TotoMiam library.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file 						TotoMiam/Task.cpp
///	@author 					Lucas Bremond <lucas@axelspace.com>
///	@date 						9 Oct 2016

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoMiam/Configuration.hpp>

#include <TotoMiam/Task.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TotoMiam
{
bool state = true ;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

								Task::Task 									( )
								:	id_(0),
									status_(Task::Status::Undefined),
									executionTime_(Time::Undefined())
{

}

								Task::Task 									( 	const 	uint&						anId,
																				const 	Time&						anExecutionTime						)
								:	id_(anId),
									status_(Task::Status::Pending),
									executionTime_(anExecutionTime)
{

}

bool							Task::isDefined								( ) const
{
	return status_ != Task::Status::Undefined ;
}

uint							Task::getId									( ) const
{
	return id_ ;
}

Task::Status 					Task::getStatus								( ) const
{
	return status_ ;
}

Time 							Task::getExecutionTime						( ) const
{
	return executionTime_ ;
}

void							Task::setStatus								(	const 	Task::Status&				aStatus								)
{
	status_																		=		aStatus ;
}

void							Task::execute								( )
{

	Serial.println("Executing task...") ;

	status_																		=		Task::Status::Executing ;

	// digitalWrite(LED_PIN, HIGH) ;

	// delay(3000) ;

	// digitalWrite(LED_PIN, LOW) ;

	digitalWrite(LED_PIN, state);
	state = !state;
	
	status_																		=		Task::Status::Completed ;

	Serial.println("Executing task [OK]") ;

}

String							Task::getStringOfStatus						(	const 	Task::Status&				aStatus								)
{

	switch (aStatus)
	{

		case Task::Status::Undefined:
			return "Undefined" ;

		case Task::Status::Pending:
			return "Pending" ;

		case Task::Status::Executing:
			return "Executing" ;

		case Task::Status::Completed:
			return "Completed" ;

		case Task::Status::Failed:
			return "Failed" ;

	}

	return "Error" ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////