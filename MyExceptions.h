#pragma once
// ������ -���������� exception ��� �������� ��������� �������� ��������� � �������� ������ ������
#include <exception>  

class  UsernameExist : public std:: exception
{
public:
    virtual const char* what() const noexcept override
    {
        return " Username Exist ! \n";
    }
};
class  UsernameNotExist : public std::exception
{
public:
    virtual const char* what() const noexcept override
    {
        return " UsernameNotExist! \n";
    }
};

class  WrongPassword : public std::exception
{
public:
    virtual const char* what() const noexcept override
    {
        return " �WrongPassword!\n";
    }
};
class  NotAutorized : public std::exception
{
public:
    virtual const char* what() const noexcept override
    {
        return " NotAutorized!\n";
    }
};
class  NotAdmin : public std::exception
{
public:
    virtual const char* what() const noexcept override
    {
        return " NotAdmin!\n";
    }
};
class  ALLisreserved : public std::exception
{
public:
    virtual const char* what() const noexcept override
    {
        return " ALLisreserved!\n";
    }
};
class   MessNotSent : public std::exception
{
public:
    virtual const char* what() const noexcept override
    {
        return " �MessNotSent!\n";
    }
};
