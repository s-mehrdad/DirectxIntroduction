﻿// ********************************************************************************
/// <summary>
/// 
/// </summary>
/// <created>ʆϒʅ,22.07.2019</created>
/// <changed>ʆϒʅ,24.07.2019</changed>
// ********************************************************************************

#ifndef LOGGING_H
#define LOGGING_H


// the severity of the log entity
enum logType { info = 0, debug, warning, error };


// the log entity
struct Log
{
  unsigned short id;
  logType type;
  std::string cMoment;
  std::thread::id threadId;
  std::string threadName;
  std::string message;

  Log ();
  void set ( const logType&,
             const std::thread::id&,
             const std::string&,
             const std::string& );

  static unsigned short count;
};


// file stream policy
class toFile
{
private:
  std::ofstream fileStream;
  bool ready;
public:
  toFile ();
  ~toFile ();
  const bool& state ();
  int write ( const Log& );
};


// screen stream policy
//class toScreen {};


// log engine
template<class tType>
class Logger
{
private:
  std::list<Log> buffer; // buffer list container 
  tType policy; // output stream policy
  std::timed_mutex writeGuard; // write guard
  std::thread commit; // write engine thread
  std::atomic_flag operating { ATOMIC_FLAG_INIT }; // lock-free atomic flag (checking the running state)
public:
  Logger ();
  ~Logger ();
  void push ( const Log& );

  template<class tType>
  friend void loggerEngine ( Logger<tType>* ); // write engine
};


// don't call this function: solution for linker error, when using templates.
void problemSolver ();


#endif // !LOGGING_H
