////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project                    Toto|Miam
/// @file                       TotoMiam/ServerManager.hpp
/// @author                     Lucas Brémond <lucas.bremond@gmail.com>
/// @license                    MIT License

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __TotoMiam_ServerManager__
#define __TotoMiam_ServerManager__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SmingCore.h>

#include <TotoMiam/TaskManager.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace totomiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ServerManager
{

    public:

                                ServerManager                               (   const   uint                        aPort                                       =   80 ) ;

        bool                    isActive                                    ( ) const ;

        void                    start                                       ( ) ;
        void                    stop                                        ( ) ;

        void                    associateTaskManager                        (       TaskManager&                    aTaskManager                                ) ;

    private:

        uint                    port_ ;
        HttpServer*             serverPtr_ ;
        TaskManager*            taskManagerPtr_ ;

        void                    onIndex                                     (       HttpRequest&                    aRequest,
                                                                                    HttpResponse&                   aResponse                                   ) ;

        void                    onFile                                      (       HttpRequest&                    aRequest,
                                                                                    HttpResponse&                   aResponse                                   ) ;

        void                    onStatus                                    (       HttpRequest&                    aRequest,
                                                                                    HttpResponse&                   aResponse                                   ) ;

        void                    onTime                                      (       HttpRequest&                    aRequest,
                                                                                    HttpResponse&                   aResponse                                   ) ;

        void                    onRules                                     (       HttpRequest&                    aRequest,
                                                                                    HttpResponse&                   aResponse                                   ) ;

        void                    onTasks                                     (       HttpRequest&                    aRequest,
                                                                                    HttpResponse&                   aResponse                                   ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
