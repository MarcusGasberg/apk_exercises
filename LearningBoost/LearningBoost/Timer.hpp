#ifndef TIMER_HPP_
#define TIMER_HPP_
#include <string>
#include <map>
#include <thread>
#include <functional>
#include <chrono>
#include <set>
#include "Events.hpp"

class Timer
{
public:
  explicit Timer( int timer = 10);
  int attach(std::function<void (const std::shared_ptr<Event>&)> cb);
  void detach(int cbId);
  
  ~Timer();  
  
private:
  int  timerThreadFunction();
  void notify_all(const std::shared_ptr<Event>& e);

  std::map<int, std::function<void(const std::shared_ptr<Event>&)>> callbacks_;
  int           eventTimer_;
  std::thread*	thread_;
  bool          terminator_;	
};






#endif
