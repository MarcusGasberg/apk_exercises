#include <iostream>
#include "Events.hpp"
#include "Timer.hpp"

#include <algorithm>


Timer::Timer( int timer) :
	eventTimer_( timer ), terminator_(false)
{
	thread_     = new std::thread([this] { timerThreadFunction(); });
}

int Timer::attach(std::function<void(const std::shared_ptr<Event>&)> cb)
{
  int id = callbacks_.size();
  callbacks_.emplace(std::make_pair(id, cb));

  return id;
}

void Timer::detach(int cbId)
{
  callbacks_.erase(cbId);
}

Timer::~Timer()
{
	terminator_ = true;
	thread_->join();
	delete thread_;
}

int Timer::timerThreadFunction()
{
  int counter = 0;
  while( !terminator_ )
  {
    std::chrono::milliseconds sleepFor( 1000 );
    std::this_thread::sleep_for( sleepFor );

    notify_all( std::make_shared<Event>() );
    if( ++counter >= eventTimer_ )
    {	
      counter = 0;
      std::cout << "EventOther created..." << std::endl;
      
      notify_all( std::make_shared<EventOther>() );
    }
  }
  return 0;
}
void Timer::notify_all(const std::shared_ptr<Event>& e)
{
  std::for_each(callbacks_.begin(), callbacks_.end(),
    [&e](const std::pair<int, std::function<void(const std::shared_ptr<Event>&)>>& cb) { cb.second(e); });
}
