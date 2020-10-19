#pragma once
#include <stdexcept>

class log_file_exception final : public std::runtime_error
{
public:
    enum class error_state { could_not_open_file, filename_is_empty };

    explicit log_file_exception(const error_state state, const std::string& str = ""): runtime_error(str), state_(state){}

    error_state get_state() const
    {
        return state_;
    }

private:
    error_state state_;
};
