#include <iostream>
#include <chrono>
#include <thread>
#include <cassert>
#include "print.h"

class Timer
{
private:
    std::thread timer_thread;

public:
    Timer( const bool& cond )
	: cond_( cond )
	, stop_( false )
	{ }
    
    bool stop_;
    
    bool cond_;
    
    void Start( int delay, std::function<void()> task )
	{
	    timer_thread = std::thread (
		[this, &delay, &task]
		{
		    try
		    {
		      println( stop_ );
		      assert( stop_ == false );
			while( !stop_ )
			{
			    println( "waiting ..." );
			    std::this_thread::sleep_for( std::chrono::milliseconds( delay ));
			    if( !cond_ )
			    {
				println( "message not received" );
				task();
			    }
			    else
			    {
				println( "message received" );
				std::cout << "ignoring" << std::endl;
			    }
			}
			println( "leaving loop" );
		    }
		    catch( const std::exception& e)
		    {
			std::cout << e.what() << std::endl;
		    }
		});
  }
    
    void Stop()
	{
	    stop_ = true;
	    timer_thread.join();
	}
    
    virtual ~Timer()
	{
	    Stop();
	}
};


/* class GSDispatcher() */
/* { */
/* public: */
/*     Timer timer; */
/*     bool msg_received_; */
/*     void MonitorGSDisconnect( int delay, std::function<void()> on_timeout_callback) */
/*     { */
/* 	if( on_timeout_callback ) */
/* 	{ */
/* 	    timer.Start( delay, msg_received_, on_timeout_callback ); */
/* 	} */
/*     }  */
/* }; */

/* class GSService */
/* { */
/* public: */
/*     GSDispatcher dispatcher; */
/*     GSService() */
/* 	{ */
/* 	    if( hb_enabled ) */
/* 	    { */
/* 		dispatcher.MonitorGSDisconnect(  */
/* 		    10 ,  */
/* 		    []{ */
/* 			std::cout << "notify client" << std::endl; */
/* 		    }); */
/* 	    } */
/* 	} */
/* }; */

int main()
{
  /* GSService gs_service;     */
  try
    {
      bool msg_received = true;
      Timer timer( msg_received );
      timer.Start( 1000, 
		   []{ std::cout << "timeout invoked" << std::endl; });
      std::this_thread::sleep_for( std::chrono::milliseconds( 2000 ));
      std::cout << "enable invoke" << std::endl;
      msg_received = false;
      println( "sleep ...");
      std::this_thread::sleep_for( std::chrono::milliseconds( 2000 ));
      println( "wake...");
}
  catch(const std::exception& e)
    {
      std::cout << e.what() << std::endl;
    }
  return 0;
}


