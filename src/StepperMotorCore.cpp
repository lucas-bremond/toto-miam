////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the TotoMiam library.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file 						TotoMiam/StepperMotorCore.cpp
///	@author 					Lucas Bremond <lucas@axelspace.com>
///	@date 						9 Oct 2016

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <HardwareTimer.h>

#include <TotoMiam/Configuration.hpp>
#include <TotoMiam/StepperMotorController.hpp>

#include <TotoMiam/StepperMotorCore.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TotoMiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// To do: add multi-channel support

byte							phases[]										=		{1, 3, 2, 6, 4, 12, 8, 9} ;

Hardware_Timer					hardwareTimer ;

uint8_t							maxChannelCount									=		1 ;

double							outputRadius ;
double							inputRadius ;
uint							stepsPerRotation ;

uint8_t							pin_A ;
uint8_t							pin_B ;
uint8_t							pin_C ;
uint8_t							pin_D ;

bool							started											=		false ;
bool							reverse											=		false ;

int								phase ;
int								steps ;
int								dir ;
int								i ;

void IRAM_ATTR					writePins									(	const	int&						aBitmap								)
{

	bool 						state_A											=		aBitmap & 8 ? HIGH : LOW ;
	bool 						state_B											=		aBitmap & 4 ? HIGH : LOW ;
	bool 						state_C											=		aBitmap & 2 ? HIGH : LOW ;
	bool 						state_D											=		aBitmap & 1 ? HIGH : LOW ;

	// Serial.print(state_A) ;
	// Serial.print(", ") ;
	// Serial.print(state_B) ;
	// Serial.print(", ") ;
	// Serial.print(state_C) ;
	// Serial.print(", ") ;
	// Serial.print(state_D) ;
	// Serial.print("\n") ;

	digitalWrite(pin_A, state_A) ;
	digitalWrite(pin_B, state_B) ;
	digitalWrite(pin_C, state_C) ;
	digitalWrite(pin_D, state_D) ;

}

void IRAM_ATTR					hardwareLoop								( )
{

	if (!started)
	{
		return ;
	}

	hardwareTimer.setIntervalUs(2000) ;
	// hardwareTimer.setIntervalMs(2000) ;
	
	hardwareTimer.startOnce() ;

	// Serial.println("StepperMotorCore :: hardwareLoop...") ;

	if (i <= steps)
	{

		writePins(phases[phase]) ;

		phase																	=		(8 + phase + dir) % 8 ;
		
		i++ ;

	} else {

		if (!reverse)
		{
			
			phase																=		0 ;
			dir																	=		-dir ;
			i																	=		0 ;

			reverse																=		true ;

		} else {

			hardwareTimer.stop() ;

			writePins(0) ;

			phase																=		0 ;
			steps																=		0 ;
			dir																	=		0 ;
			i																	=		0 ;

			started																=		false ;
			reverse																=		false ;

		}

		

		// Deactivating pins

		// pinMode(pin_A, INPUT) ;
		// pinMode(pin_B, INPUT) ;
		// pinMode(pin_C, INPUT) ;
		// pinMode(pin_D, INPUT) ;

	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

								StepperMotorCore::StepperMotorCore			( )
{

}

								StepperMotorCore::~StepperMotorCore			( )
{
	channels_.removeAllElements() ;
}

bool							StepperMotorCore::hasChannel				(			StepperMotorController&		aStepperMotorController				) const
{
	return channels_.contains(&aStepperMotorController) ;
}

bool							StepperMotorCore::isChannelBusy				(	const	StepperMotorController&		aStepperMotorController				) const
{
	return started ; // TBM
}

void							StepperMotorCore::start						( )
{

	// Serial.println("StepperMotorCore :: start...") ;

	// if (!started)
	// {
		
	// 	started																	=		true ;

	// 	hardwareTimer.initializeUs(2000, hardwareLoop) ;

	// 	hardwareTimer.startOnce() ;

	// }

	// Serial.println("StepperMotorCore :: start [OK]") ;

}
		
void							StepperMotorCore::stop						( )
{

	// if (started)
	// {

	// 	hardwareTimer.stop() ;

	// 	started																	=		false ;

	// }	

}

void							StepperMotorCore::addChannel				( 			StepperMotorController&		aStepperMotorController				)
{

	// Serial.println("StepperMotorCore :: addChannel...") ;

	if ((channels_.size() < maxChannelCount) && (!this->hasChannel(aStepperMotorController)))
	{

		channels_.add(&aStepperMotorController) ;

		inputRadius																=		aStepperMotorController.getInputRadius() ;
		outputRadius															=		aStepperMotorController.getOutputRadius() ;
		stepsPerRotation														=		aStepperMotorController.getStepsPerRotation() ;

		pin_A																	=		aStepperMotorController.getPinA() ;
		pin_B																	=		aStepperMotorController.getPinB() ;
		pin_C																	=		aStepperMotorController.getPinC() ;
		pin_D																	=		aStepperMotorController.getPinD() ;

	}

	// Serial.println("StepperMotorCore :: addChannel [OK]") ;

}

void							StepperMotorCore::removeChannel				( 			StepperMotorController&		aStepperMotorController				)
{

	// Serial.println("StepperMotorCore :: removingChannel...") ;

	if (channels_.removeElement(&aStepperMotorController))
	{

		ETS_INTR_LOCK() ;

		// getPins();
		// calcTiming();
		
		ETS_INTR_UNLOCK() ;
		
		if (channels_.size() == 0)
		{

			if (started)
			{

				started															=		false ;
			
				hardwareTimer.stop() ;

			}
			
		}
		
	}

	// Serial.println("StepperMotorCore :: removingChannel [OK]") ;

}

void							StepperMotorCore::rotate					(	const	Angle&						anAngle,
																						StepperMotorController&		aStepperMotorController				)
{

	if (started)
	{
		return ;
	}

	ETS_INTR_LOCK() ;

	// getPins();
	// calcTiming();
	
	ETS_INTR_UNLOCK() ;

	steps 																		=		anAngle.getRevolutions() * outputRadius / inputRadius * stepsPerRotation ;

	dir																			=		(steps > 0) - (steps < 0) ;

	steps																	   *=		dir ;

	pinMode(pin_A, OUTPUT) ;
	pinMode(pin_B, OUTPUT) ;
	pinMode(pin_C, OUTPUT) ;
	pinMode(pin_D, OUTPUT) ;

	// Serial.println("StepperMotorCore :: START") ;
		
	started																		=		true ;
	
	hardwareTimer.initializeUs(100000, hardwareLoop) ;

	hardwareTimer.startOnce() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

StepperMotorCore 				stepperMotorCore ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////