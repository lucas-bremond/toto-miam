////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the TotoMiam library.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file 						TotoMiam/StepperMotorController.cpp
///	@author 					Lucas Bremond <lucas@axelspace.com>
///	@date 						9 Oct 2016

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoMiam/Configuration.hpp>

#include <TotoMiam/StepperMotorController.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TotoMiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

byte							phases[]										=		{1, 3, 2, 6, 4, 12, 8, 9} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

								StepperMotorController::StepperMotorController ( )
								:	pin_A_(0),
									pin_B_(0),
									pin_C_(0),
									pin_D_(0),
									stepsPerRotation_(4096),
									busy_(false),
									phase_(0),
									steps_(0),
									dir_(0),
									i_(0)
{

}

bool							StepperMotorController::isDefined			( ) const
{
	return (pin_A_ != pin_B_) && (pin_A_ != pin_C_) && (pin_A_ != pin_D_) && (pin_B_ != pin_C_) && (pin_B_ != pin_D_) && (pin_C_ != pin_D_) ;
}

bool							StepperMotorController::isBusy				( ) const
{
	return busy_ ;
}

void							StepperMotorController::rotate				(	const	Angle&						anAngle								)
{

	Serial.println("StepperMotorController :: rotate...") ;

	if (!this->isDefined())
	{
		return ;
	}

	if (this->isBusy())
	{
		return ;
	}

	this->reset() ;

	busy_																		=		true ;

	steps_ 																		=		anAngle.getRevolutions() * stepsPerRotation_ ;

	dir_																		=		(steps_ > 0) - (steps_ < 0) ;

	// Serial.println("StepperMotorController :: rotate >> dir_ = ") ;
	// Serial.println(dir_) ;
	
	steps_																	   *=		dir_ ;

	// Serial.println("StepperMotorController :: rotate >> steps_ = ") ;
	// Serial.println(steps_) ;

	timer_.initializeMs(1, Delegate<void()>(&StepperMotorController::loop, this)) ; // TBM param
	
	timer_.start() ;

}

StepperMotorController			StepperMotorController::Pins				(	const	uint8_t&					aFirstPin,
																				const	uint8_t&					aSecondPin,
																				const	uint8_t&					aThirdPin,
																				const	uint8_t&					aFourthPin							)
{

	StepperMotorController		stepperMotorController ;

	stepperMotorController.pin_A_												=		aFirstPin ;
	stepperMotorController.pin_B_												=		aSecondPin ;
	stepperMotorController.pin_C_												=		aThirdPin ;
	stepperMotorController.pin_D_												=		aFourthPin ;

	return stepperMotorController ;

}

void							StepperMotorController::loop				( )
{

	// Serial.println("StepperMotorController :: loop...") ;

	// Serial.print("StepperMotorController :: loop >> i_ = ") ;
	// Serial.println(i_) ;

	if (i_ < steps_)
	{

		this->writePins(phases[phase_]) ;

		phase_																	=		(8 + phase_ + dir_) % 8 ;
		
		i_++ ;

	} else {

		timer_.stop() ;

		this->reset() ;

	}

}

void							StepperMotorController::writePins			(	const	int&						aBitmap								)
{

	// Serial.println("StepperMotorController :: writePins...") ;
	
	// Serial.print("StepperMotorController :: writePins >> aBitmap = ") ;
	// Serial.println(aBitmap) ;

	digitalWrite(pin_A_, aBitmap & 8 ? HIGH : LOW) ;
	digitalWrite(pin_B_, aBitmap & 4 ? HIGH : LOW) ;
	digitalWrite(pin_C_, aBitmap & 2 ? HIGH : LOW) ;
	digitalWrite(pin_D_, aBitmap & 1 ? HIGH : LOW) ;

}

void							StepperMotorController::reset				( )
{

	// Serial.println("StepperMotorController :: reset...") ;

	pinMode(pin_A_, OUTPUT) ;
	pinMode(pin_B_, OUTPUT) ;
	pinMode(pin_C_, OUTPUT) ;
	pinMode(pin_D_, OUTPUT) ;

	this->writePins(0) ;

	phase_																		=		0 ;
	steps_																		=		0 ;
	dir_																		=		0 ;
	i_																			=		0 ;

	busy_																		=		false ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////