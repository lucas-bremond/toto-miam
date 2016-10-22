////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the TotoMiam library.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file 						TotoMiam/TaskManager.hpp
///	@author 					Lucas Bremond <lucas@axelspace.com>
///	@date 						9 Oct 2016

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __TotoMiam_TaskManager_HPP_INCLUDED__
#define __TotoMiam_TaskManager_HPP_INCLUDED__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SmingCore/SmingCore.h>

#include <TotoMiam/ApplicationStorage.hpp>

#include <TotoMiam/Rule.hpp>
#include <TotoMiam/Task.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TotoMiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class TaskManager
{

	public:

								TaskManager 								( ) ;

		bool					isActive									( ) const ;

		void					start										( ) ;
		void					stop										( ) ;

		void					associateApplicationStorage					(			ApplicationStorage&			anApplicationStorage				) ;

		bool					hasRuleWithId								(	const	uint&						aRuleId								) const ;
		bool					hasTaskWithId								(	const	uint&						aTaskId								) const ;

		const Rule&				accessRuleWithId							(	const	uint&						aRuleId								) const ;
		const Task&				accessTaskWithId							(	const	uint&						aTaskId								) const ;

		const Vector<Rule>&		accessRules									( ) const ;
		const Vector<Task>&		accessTasks									( ) const ;

		uint					getNextRuleId								( ) const ;
		uint					getNextTaskId								( ) const ;

		bool					addRule										(	const	Rule&						aRule								) ;
		bool					addTask										(	const	Task&						aTask								) ;

		bool					removeRuleWithId							(	const	uint&						aRuleId								) ;
		bool					removeTaskWithId							(	const	uint&						aTaskId								) ;

		bool					addImmediateTask							( ) ;

	private:

		bool					active_ ;

		ApplicationStorage*		applicationStoragePtr_ ;

		Vector<Rule>			rules_ ;
		Vector<Task>			tasks_ ;

		uint					ruleCountLimit_ ;
		uint					taskCountLimit_ ;

		Timer					timer_ ;

		DriverPWM				motorDriver_ ;
		Timer 					motorTimer_ ;
		uint					motorTimerLoopMs_ ;

		Task*					currentTaskPtr_ ;
		uint					motorCount_ ;
		uint					motorMaxCount_ ;

		void					load										( ) ;
		void					save										( ) ;

		void					onManage									( ) ;

		void					doManageMotor								( ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////