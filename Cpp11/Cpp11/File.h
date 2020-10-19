#pragma once
#include <stdio.h>
#include <string>

class File
{
    FILE* file_;
    std::string file_name_;
public:
    template<typename STR, typename = std::enable_if_t<std::is_convertible_v<STR, std::string>>>
    File(STR&& file_name) : file_name_(std::forward<STR>(file_name))
    {
        fopen_s(&file_, file_name_.c_str(), "w+b");
    }

    File(const File& other) = delete;
    File& operator= (const File& other) = delete;

    File(File&& other) noexcept
        :file_(std::move(other.file_)), file_name_(std::move(other.file_name_))
    {
        other.file_ = nullptr;
    }

    File& operator= (File&& other) noexcept
    {
        if(this != &other)
        {
            fclose(file_);
            delete file_;
            file_ = nullptr;
            std::swap(other.file_, file_);
        }

        return *this;
    }

    ~File()
    {
        if(file_ != nullptr){
            fclose(file_);
            delete file_;
        }
    }

    const std::string& file_name() const
    {
        return file_name_;
    }

    std::string read() const
    {
        fseek(file_, 0L, SEEK_END);
    
        const int size = ftell(file_);

        rewind(file_);

        char* str = new char[size + 1];

        fread(str, sizeof(char), size, file_);

        str[size] = '\0';

        auto result = std::string(str);

        delete[] str;

        return result;
    }

    void write(const std::string& data)
    {
        fprintf_s(file_,"%s", data.c_str());
    }
};

