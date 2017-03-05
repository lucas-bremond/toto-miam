////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the TotoMiam library.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file 						TotoMiam/TaskManager.cpp
///	@author 					Lucas Bremond <lucas@axelspace.com>
///	@date 						9 Oct 2016

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// #include <TotoMiam/StepperMotorController.hpp>

// #include <TotoMiam/AppSettings.hpp>
#include <TotoMiam/Configuration.hpp>
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
									taskCountLimit_(10),
									currentTaskPtr_(nullptr)
{

}

bool							TaskManager::isActive						( ) const
{
	return active_ ;
}

void							TaskManager::start							( )
{

	if (this->isActive())
	{
		this->stop() ;
	}

	active_																		=		true ;

	this->load() ;

	this->addRule(Rule::AtTime(1, CalendarDate(2016, 12, 11, 20, 30, 0), Duration::Seconds(60))) ;
	this->addRule(Rule::AtTime(2, CalendarDate(2016, 12, 11, 7, 30, 0), Duration::Seconds(60))) ;

	timer_.initializeMs(1000, Delegate<void()>(&TaskManager::onManage, this)) ; // TBM param
	
	timer_.start() ;

}

void							TaskManager::stop							( )
{

	if (!this->isActive())
	{
		return ;
	}

	timer_.stop() ;

	active_																		=		false ;

}

void							TaskManager::associateApplicationStorage	(			ApplicationStorage&			anApplicationStorage				)
{
	applicationStoragePtr_														=		&anApplicationStorage ;
}

bool							TaskManager::hasRuleWithId					(	const	uint&						aRuleId								) const
{

	for (uint idx = 0; idx < rules_.size(); ++idx)
	{

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

		if (rules_[idx].getId() == aRule.getId())
		{
			return false ;
		}

	}

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

		if (tasks_[idx].getId() == aTask.getId())
		{
			return false ;
		}

	}

	if (tasks_.size() >= taskCountLimit_)
	{

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

		// TBC...
	
	}

}

void							TaskManager::save							( )
{

	if ((applicationStoragePtr_ != nullptr) && applicationStoragePtr_->isDefined())
	{

		// TBC...
	
	}

}

void							TaskManager::onManage						( )
{

	Time 						currentTime										=		Time::Now() ;

	// Executing tasks

	for (uint idx = 0; idx < tasks_.size(); ++idx)
	{

		Task&					task 											=		tasks_[idx] ;

		if (task.getStatus() == Task::Status::Pending)
		{

			if (task.getExecutionTime() <= currentTime)
			{

				task.execute() ;

				this->save() ;

				return ;

			}

		}

	}

	// Cheking rules

	for (uint idx = 0; idx < rules_.size(); ++idx)
	{

		Rule&					rule 											=		rules_[idx] ;

		bool					hasCorrespondingPendingTask						=		false ;

		for (uint idx = 0; idx < tasks_.size(); ++idx)
		{

			Task&				task 											=		tasks_[idx] ;

			if (task.isRuleDefined() && (task.getRuleId() == rule.getId()) && (task.getStatus() == Task::Status::Pending))
			{
				
				hasCorrespondingPendingTask										=		true ;

				break ;

			}

		}

		if (!hasCorrespondingPendingTask)
		{

			// Adding task...

			this->addTask(Task(this->getNextTaskId(), rule.getNextExecutionTime(), rule.getTaskDuration(), rule.getId())) ;

			rule.resetExecutionTime(rule.getNextExecutionTime()) ;

			this->save() ;

			return ;

		}

	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////