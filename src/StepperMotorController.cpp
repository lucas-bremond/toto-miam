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

#include <TotoMiam/StepperMotorCore.hpp>

#include <TotoMiam/StepperMotorController.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TotoMiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

								StepperMotorController::StepperMotorController ( const	uint8_t&					aFirstPin,
																				const	uint8_t&					aSecondPin,
																				const	uint8_t&					aThirdPin,
																				const	uint8_t&					aFourthPin							)
								:	pin_A_(aFirstPin),
									pin_B_(aSecondPin),
									pin_C_(aThirdPin),
									pin_D_(aFourthPin),
									inputRadius_(1.5), // TBM param
									outputRadius_(4.0), // TBM param
									stepsPerRotation_(4096), // TBM param
									mode_(StepperMotorController::Mode::Forward)
{

	stepperMotorCore.addChannel(*this) ;

}

								StepperMotorController::~StepperMotorController ( )
{

	// stepperMotorCore.removeChannel(*this) ;

}

bool							StepperMotorController::isDefined			( ) const
{
	return (pin_A_ != pin_B_) && (pin_A_ != pin_C_) && (pin_A_ != pin_D_) && (pin_B_ != pin_C_) && (pin_B_ != pin_D_) && (pin_C_ != pin_D_) ;
}

bool							StepperMotorController::isBusy				( ) const
{
	return stepperMotorCore.isChannelBusy(*this) ;
}

double							StepperMotorController::getInputRadius		( ) const
{
	return inputRadius_ ;
}

double							StepperMotorController::getOutputRadius		( ) const
{
	return outputRadius_ ;
}

uint							StepperMotorController::getStepsPerRotation	( ) const
{
	return stepsPerRotation_ ;
}

uint8_t 						StepperMotorController::getPinA				( ) const
{
	return pin_A_ ;
}

uint8_t 						StepperMotorController::getPinB				( ) const
{
	return pin_B_ ;
}

uint8_t 						StepperMotorController::getPinC				( ) const
{
	return pin_C_ ;
}

uint8_t 						StepperMotorController::getPinD				( ) const
{
	return pin_D_ ;
}

void							StepperMotorController::rotate				(	const	Angle&						anAngle								)
{

	// Serial.println("StepperMotorController :: rotate...") ;

	if (!this->isDefined())
	{
		return ;
	}

	if (this->isBusy())
	{
		return ;
	}

	stepperMotorCore.rotate(anAngle, *this) ;

	// this->reset() ;

	// busy																		=		true ;

	// steps 																		=		anAngle.getRevolutions() * stepsPerRotation_ ;

	// dir																			=		(steps > 0) - (steps < 0) ;

	// Serial.println("StepperMotorController :: rotate >> dir = ") ;
	// Serial.println(dir) ;
	
	// steps																	   *=		dir ;

	// Serial.println("StepperMotorController :: rotate >> steps_ = ") ;
	// Serial.println(steps_) ;

	// timer_.initializeMs(1, Delegate<void()>(&StepperMotorController::loop, this)) ; // TBM param
	
	// timer_.start() ;

	// pin_A																		=		pin_A_ ;
	// pin_B																		=		pin_B_ ;
	// pin_C																		=		pin_C_ ;
	// pin_D																		=		pin_D_ ;

	// busy 																		=		true ;
	// phase																		=		phase_ ;
	// steps																		=		steps_ ;
	// dir																			=		dir_ ;
	// i																			=		i_ ;

	// hardwareTimer.initializeUs(2000, StepperTimerInt) ; // TBM param
	
	// hardwareTimer.startOnce() ;

}

// StepperMotorController			StepperMotorController::Pins				(	const	uint8_t&					aFirstPin,
// 																				const	uint8_t&					aSecondPin,
// 																				const	uint8_t&					aThirdPin,
// 																				const	uint8_t&					aFourthPin							)
// {

// 	StepperMotorController		stepperMotorController ;

// 	stepperMotorController.pin_A_												=		aFirstPin ;
// 	stepperMotorController.pin_B_												=		aSecondPin ;
// 	stepperMotorController.pin_C_												=		aThirdPin ;
// 	stepperMotorController.pin_D_												=		aFourthPin ;

// 	return stepperMotorController ;

// }

// void							StepperMotorController::loop				( )
// {

// 	// Serial.println("StepperMotorController :: loop...") ;

// 	// Serial.print("StepperMotorController :: loop >> i_ = ") ;
// 	// Serial.println(i_) ;

// 	// if (i_ <= steps_)
// 	// {

// 	// 	this->writePins(phases[phase_]) ;

// 	// 	phase_																	=		(8 + phase_ + dir_) % 8 ;
		
// 	// 	i_++ ;

// 	// } else {

// 	// 	timer_.stop() ;

// 	// 	this->reset() ;

// 	// }

// }

// void							StepperMotorController::writePins			(	const	int&						aBitmap								)
// {

// 	// Serial.println("StepperMotorController :: writePins...") ;
	
// 	// Serial.print("StepperMotorController :: writePins >> aBitmap = ") ;
// 	// Serial.println(aBitmap) ;

// 	digitalWrite(pin_A_, aBitmap & 8 ? HIGH : LOW) ;
// 	digitalWrite(pin_B_, aBitmap & 4 ? HIGH : LOW) ;
// 	digitalWrite(pin_C_, aBitmap & 2 ? HIGH : LOW) ;
// 	digitalWrite(pin_D_, aBitmap & 1 ? HIGH : LOW) ;

// }

// void							StepperMotorController::reset				( )
// {

// 	// Serial.println("StepperMotorController :: reset...") ;

// 	pinMode(pin_A_, OUTPUT) ;
// 	pinMode(pin_B_, OUTPUT) ;
// 	pinMode(pin_C_, OUTPUT) ;
// 	pinMode(pin_D_, OUTPUT) ;

// 	this->writePins(0) ;

// 	phase_																		=		0 ;
// 	steps_																		=		0 ;
// 	dir_																		=		0 ;
// 	i_																			=		0 ;

// 	busy_																		=		false ;

// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////