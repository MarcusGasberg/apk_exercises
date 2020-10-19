#include <ostream>
#include <ctime>

#include "Events.hpp"

std::ostream& operator<<( std::ostream& os, const Event& ev ) 
{
   const std::time_t creationTime = std::chrono::system_clock::to_time_t(ev.creationTime());
   char buffer[26];
   ctime_s(buffer, 26, &creationTime);
   os << buffer;
   
   return os;
}
