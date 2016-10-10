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
									taskCountLimit_(10)
{

	// if (AppSettings.isDefined())
	// {

	// 	tasks_																	=		
		
	// }

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

	this->addTask(Task(1, Time::Now() + Duration::Seconds(10))) ;
	this->addTask(Task(2, Time::Now() + Duration::Seconds(20))) ;
	this->addTask(Task(3, Time::Now() + Duration::Seconds(30))) ;
	this->addTask(Task(4, Time::Now() + Duration::Seconds(40))) ;

	timer_.initializeMs(1000, Delegate<void()>(&TaskManager::onManage, this)).start() ; // TBM param

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

const Vector<Task>&				TaskManager::accessTasks					( ) const
{
	return tasks_ ;
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

bool							TaskManager::addTask						(	const	Task&						aTask								)
{

	for (uint idx = 0; idx < tasks_.size(); ++idx)
	{

		if (tasks_[idx].getId() == aTask.getId())
		{
			return false ;
		}

	}

	while (tasks_.size() >= taskCountLimit_)
	{

		if (tasks_.firstElement().getStatus() != Task::Status::Pending)
		{
			tasks_.removeElementAt(0) ;
		}

	}

	if (tasks_.size() < taskCountLimit_)
	{

		tasks_.addElement(aTask) ;

		return true ;

	}

	return false ;

}

bool							TaskManager::addImmediateTask				( )
{

	return this->addTask(Task(this->getNextTaskId(), Time::Now())) ;

}

bool							TaskManager::removeTaskWithId				(	const	uint&						aTaskId								)
{

	for (uint idx = 0; idx < tasks_.size(); ++idx)
	{

		const Task&				task 											=		tasks_[idx] ;

		if (task.getId() == aTaskId)
		{

			tasks_.removeElementAt(idx) ;

			return true ;

		}

	}

	return false ;

}

void							TaskManager::onManage						( )
{

	// Serial.println("Managing tasks...") ;

	Time 						currentTime										=		Time::Now() ;

	// Executing tasks

	for (uint idx = 0; idx < tasks_.size(); ++idx)
	{

		Task&					task 											=		tasks_[idx] ;

		if (task.getStatus() == Task::Status::Pending)
		{

			if (task.getExecutionTime() <= currentTime)
			{

				// Executing task...

				task.execute() ;

			}

		}

	}

	// Adding new tasks

	// TBI...

	// Serial.println("Managing tasks [OK]") ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////