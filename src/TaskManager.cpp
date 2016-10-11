////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the TotoMiam library.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file 						TotoMiam/TaskManager.cpp
///	@author 					Lucas Bremond <lucas@axelspace.com>
///	@date 						9 Oct 2016

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// #include <TotoMiam/AppSettings.hpp>
#include <TotoMiam/Duration.hpp>

#include <TotoMiam/TaskManager.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TotoMiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

								TaskManager::TaskManager 					( )
								:	active_(false),
									applicationStoragePtr_(nullptr),
									ruleCountLimit_(10),
									taskCountLimit_(10)
{

}

bool							TaskManager::isActive						( ) const
{
	return active_ ;
}

void							TaskManager::start							( )
{

	Serial.println("Starting Task Manager...") ;

	if (this->isActive())
	{
		this->stop() ;
	}

	active_																		=		true ;

	this->load() ;

	this->addRule(Rule::AtInterval(1, Duration::Seconds(10))) ;
	this->addRule(Rule::AtInterval(2, Duration::Seconds(30))) ;

	this->addTask(Task(1, Time::Now() + Duration::Seconds(10))) ;
	this->addTask(Task(2, Time::Now() + Duration::Seconds(20))) ;
	this->addTask(Task(3, Time::Now() + Duration::Seconds(30))) ;
	this->addTask(Task(4, Time::Now() + Duration::Seconds(40))) ;

	timer_.initializeMs(5000, Delegate<void()>(&TaskManager::onManage, this)).start() ; // TBM param

	Serial.println("Starting Task Manager [OK]") ;

}

void							TaskManager::stop							( )
{

	Serial.println("Stopping Task Manager...") ;

	if (!this->isActive())
	{
		return ;
	}

	active_																		=		false ;

	Serial.println("Stopping Task Manager [OK]") ;

}

void							TaskManager::associateApplicationStorage	(			ApplicationStorage&			anApplicationStorage				)
{
	applicationStoragePtr_														=		&anApplicationStorage ;
}

bool							TaskManager::hasRuleWithId					(	const	uint&						aRuleId								) const
{

	for (uint idx = 0; idx < rules_.size(); ++idx)
	{

		wdt_feed() ;

		const Rule&				rule 											=		rules_[idx] ;

		if (rule.getId() == aRuleId)
		{
			return true ;
		}

	}

	return false ;

}

bool							TaskManager::hasTaskWithId					(	const	uint&						aTaskId								) const
{

	for (uint idx = 0; idx < tasks_.size(); ++idx)
	{

		wdt_feed() ;

		const Task&				task 											=		tasks_[idx] ;

		if (task.getId() == aTaskId)
		{
			return true ;
		}

	}

	return false ;

}

const Rule&						TaskManager::accessRuleWithId				(	const	uint&						aRuleId								) const
{

	for (uint idx = 0; idx < rules_.size(); ++idx)
	{

		wdt_feed() ;

		const Rule&				rule 											=		rules_[idx] ;

		if (rule.getId() == aRuleId)
		{
			return rule ;
		}

	}

}

const Task&						TaskManager::accessTaskWithId				(	const	uint&						aTaskId								) const
{

	for (uint idx = 0; idx < tasks_.size(); ++idx)
	{

		wdt_feed() ;

		const Task&				task 											=		tasks_[idx] ;

		if (task.getId() == aTaskId)
		{
			return task ;
		}

	}

}

const Vector<Rule>&				TaskManager::accessRules					( ) const
{
	return rules_ ;
}

const Vector<Task>&				TaskManager::accessTasks					( ) const
{
	return tasks_ ;
}

uint							TaskManager::getNextRuleId					( ) const
{

	uint						nextRuleId 										=		1 ;

	for (uint idx = 0; idx < rules_.size(); ++idx)
	{

		wdt_feed() ;

		uint					ruleId 											=		rules_[idx].getId() ;

		if (nextRuleId <= ruleId)
		{
			nextRuleId 															=		ruleId + 1 ;
		}

	}

	return nextRuleId ;

}

uint							TaskManager::getNextTaskId					( ) const
{

	uint						nextTaskId 										=		1 ;

	for (uint idx = 0; idx < tasks_.size(); ++idx)
	{

		wdt_feed() ;

		uint					taskId 											=		tasks_[idx].getId() ;

		if (nextTaskId <= taskId)
		{
			nextTaskId 															=		taskId + 1 ;
		}

	}

	return nextTaskId ;

}

bool							TaskManager::addRule						(	const	Rule&						aRule								)
{

	for (uint idx = 0; idx < rules_.size(); ++idx)
	{

		wdt_feed() ;

		if (rules_[idx].getId() == aRule.getId())
		{
			return false ;
		}

	}

	// while (rules_.size() >= ruleCountLimit_)
	// {

	// 	rules_.removeElementAt(0) ;

	// }

	if (rules_.size() < ruleCountLimit_)
	{

		rules_.addElement(aRule) ;

		this->save() ;

		return true ;

	}

	return false ;

}

bool							TaskManager::addTask						(	const	Task&						aTask								)
{

	for (uint idx = 0; idx < tasks_.size(); ++idx)
	{

		wdt_feed() ;

		if (tasks_[idx].getId() == aTask.getId())
		{
			return false ;
		}

	}

	while (tasks_.size() >= taskCountLimit_)
	{

		wdt_feed() ;

		if (tasks_.firstElement().getStatus() != Task::Status::Pending)
		{
			tasks_.removeElementAt(0) ;
		}

	}

	if (tasks_.size() < taskCountLimit_)
	{

		tasks_.addElement(aTask) ;

		this->save() ;

		return true ;

	}

	return false ;

}

bool							TaskManager::removeRuleWithId				(	const	uint&						aRuleId								)
{

	for (uint idx = 0; idx < rules_.size(); ++idx)
	{

		const Rule&				rule 											=		rules_[idx] ;

		if (rule.getId() == aRuleId)
		{

			rules_.removeElementAt(idx) ;

			this->save() ;

			return true ;

		}

	}

	return false ;

}

bool							TaskManager::removeTaskWithId				(	const	uint&						aTaskId								)
{

	for (uint idx = 0; idx < tasks_.size(); ++idx)
	{

		const Task&				task 											=		tasks_[idx] ;

		if (task.getId() == aTaskId)
		{

			tasks_.removeElementAt(idx) ;

			this->save() ;

			return true ;

		}

	}

	return false ;

}

bool							TaskManager::addImmediateTask				( )
{
	return this->addTask(Task(this->getNextTaskId(), Time::Now())) ;
}

void							TaskManager::load							( )
{

	if ((applicationStoragePtr_ != nullptr) && applicationStoragePtr_->isDefined())
	{

		
	
	}

}

void							TaskManager::save							( )
{

	if ((applicationStoragePtr_ != nullptr) && applicationStoragePtr_->isDefined())
	{

		
	
	}

}

void							TaskManager::onManage						( )
{

	// Serial.println("Managing tasks...") ;

	Time 						currentTime										=		Time::Now() ;

	// Executing tasks

	for (uint idx = 0; idx < tasks_.size(); ++idx)
	{

		wdt_feed() ;

		Task&					task 											=		tasks_[idx] ;

		if (task.getStatus() == Task::Status::Pending)
		{

			if (task.getExecutionTime() <= currentTime)
			{

				// Executing task...

				task.execute() ;

				this->save() ;

				return ;

			}

		}

	}

	// Cheking rules

	for (uint idx = 0; idx < rules_.size(); ++idx)
	{

		wdt_feed() ;

		Rule&					rule 											=		rules_[idx] ;

		if (currentTime <= rule.getNextExecutionTime())
		{

			// Adding task...

			this->addTask(Task(this->getNextTaskId(), rule.getNextExecutionTime())) ;

			rule.resetExecutionTime(rule.getNextExecutionTime()) ;

			this->save() ;

			return ;

		}

	}

	// Serial.println("Managing tasks [OK]") ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////