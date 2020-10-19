#include <iostream>
#include <boost/variant/variant.hpp>
#include <utility>

class UserDefined
{
public:
  const std::string& msg_;


  explicit UserDefined(std::string msg)
    : msg_(std::move(msg))
  {
  }

  UserDefined() = default;

  UserDefined(const UserDefined& other) { msg_ = std::move(other.msg_); };

  UserDefined& operator=(UserDefined const& other) { msg_ = other.msg_; };

  ~UserDefined() = default;

  void Hello() { std::cout << "Hello " << msg_ << std::endl; }
private:
  friend std::ostream& operator<<(std::ostream& os, const UserDefined& user_defined);
};

std::ostream& operator<<(std::ostream& os, const UserDefined& user_defined)
{
  os << user_defined.msg_;

  return os;
}

int main(int argc, char* argv[])
{
  boost::variant<const UserDefined&, const std::string&, int> variant = UserDefined("START" );

  std::cout << variant << std::endl;

}