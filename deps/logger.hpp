/*********************************
 * author     : mostafa khaled
 * date       : Sun Apr 14 02:22:36 PM EET 2024
 * desc       : 
 * note       : include (iostream fstream string) before using this header file.
 ********************************/
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <string_view>

#ifdef WIN32
 #include <windows.h>
#endif

class Log
{
  public:
#ifdef WIN32
    enum class Mode { console, file, dialog };
#else
    enum class Mode { console, file };
#endif

    enum class Level { normal, debug, warning, all };
  public:
    Log();
   ~Log() = default;

  public:
    static void mode_console();
    static void mode_file(std::string_view ofs);
#ifdef WIN32
    static void mode_dialog(HWND hwnd = NULL);
#endif

    static void level(Level level);

    static void info(std::string_view msg);
    static void debug(std::string_view msg);
    static void warn(std::string_view msg);
    static void error(std::string_view msg);
    static void fatal(std::string_view msg);
    
  private:
    static Level&            m_level() { static Level level = Level::normal; return level;}
    static Mode&           m_mode() { static Mode _mode = Mode::console; return _mode;}
    static std::ofstream&  m_file_stream()
    {
      static std::ofstream ofs;
      return ofs;
    }
#ifdef WIN32
    static HWND& handle() { static HWND hwnd = NULL; return hwnd;}
#endif
};

#endif /* !LOGGER_HPP */
