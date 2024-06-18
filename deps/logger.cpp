#include <iostream>
#include <string>
#include <fstream>
#include "logger.hpp"

#ifdef WIN32
  #include <windows.h>
#endif /* WIN32 */

std::string reset("\033[0m");

Log::Log()
{
  m_mode() = Mode::console;
  m_file_stream();
}

void Log::mode_console()
{
  if(m_mode() == Mode::file)
    m_file_stream().close();

  m_mode() = Mode::console;
}

void Log::mode_file(std::string_view path)
{
  m_file_stream().open(std::string(path));
  if(!m_file_stream().is_open())
  {
    m_mode() = Mode::console;
  }
  m_mode() = Mode::file;
}

#ifdef WIN32
void Log::mode_dialog(HWND hwnd)
{
  if(m_mode() == Mode::file)
    m_file_stream().close();

  handle() = hwnd;
  m_mode() = Mode::dialog;
}
#endif

void Log::level(Level l)
{
  m_level() = l;
}

void Log::info(std::string_view msg)
{
  switch(m_mode())
  {
    case Mode::console:
      {
        std::cout << "info : " << msg << reset << '\n';
        break;
      }
    case Mode::file:
      {
        (m_file_stream()) << "info : " << msg << '\n';
        break;
      }
#ifdef WIN32
    case Mode::dialog:
    {
      MessageBox(handle(), std::string(msg).c_str(), "info :-", MB_OK | MB_ICONINFORMATION);
      break;
    }
#endif
  }
}

void Log::debug(std::string_view msg)
{
  if(m_level() != Level::debug && m_level() != Level::all)
    return;

  switch(m_mode())
  {
    case Mode::console:
      {
        std::cout << "\033[32mdebug: " << msg << reset << '\n';
        break;
      }
    case Mode::file:
      {
        (m_file_stream()) << "debug: " << msg << '\n';
        break;
      }
#ifdef WIN32
    case Mode::dialog:
    {
      MessageBox(handle(), std::string(msg).c_str(), "debug:-", MB_OK | MB_ICONEXCLAMATION); // add exclimation mark later!!
      break;
    }
#endif
  }
}

void Log::warn(std::string_view msg)
{
  if(m_level() != Level::warning && m_level() != Level::all)
    return;
  switch(m_mode())
  {
    case Mode::console:
      {
        std::cout << "\033[1;35mwarn : " << msg << reset << '\n';
        break;
      }
    case Mode::file:
      {
        (m_file_stream()) << "warn: " << msg << '\n';
        break;
      }
#ifdef WIN32
    case Mode::dialog:
    {
      MessageBox(handle(), std::string(msg).c_str(), "warn:-", MB_OK | MB_ICONWARNING);
      break;
    }
#endif
  }
}

void Log::error(std::string_view msg)
{
  switch(m_mode())
  {
    case Mode::console:
      {
        std::cerr << "\033[31merror: " << msg << reset <<  '\n';
        break;
      }
    case Mode::file:
      {
        (m_file_stream()) << "error: " << msg << '\n';
        break;
      }
#ifdef WIN32
    case Mode::dialog:
    {
      MessageBox(handle(), std::string(msg).c_str(), "error:-", MB_OK | MB_ICONERROR);
      break;
    }
#endif
  }
}

//call std::exit(-1) if called. use this function wisely
void Log::fatal(std::string_view msg)
{
  switch(m_mode())
  {
    case Mode::console:
      {
        std::cerr << "\033[1;31mfatal: " << msg << reset << '\n';
        std::exit(-1);
        break;
      }
    case Mode::file:
      {
        (m_file_stream()) << "fatal: " << msg << '\n';
        std::exit(-1);
        break;
      }
#ifdef WIN32
    case Mode::dialog:
    {
      MessageBox(handle(), std::string(msg).c_str(), "fatal:-", MB_OK | MB_ICONERROR);
      std::exit(-1);
      break;
    }
#endif
  }
}
