////////////////////////////////////////////////////////////////////////////////
//
//  Author: Cosmin Cremarenco 
//  Email: cosmin.cremarenco(non spammers remove this] @gmail.com
////////////////////////////////////////////////////////////////////////////////
#include <cstdarg>
#include <iostream>
#include <fstream>
#include <string>

#include <algorithm>
#include <vector>

#if _WIN32
#include <sstream>
#include <windows.h>
#endif

#include "tracer.h"

static std::ofstream gs_fileStream;

#ifdef _WIN32
static std::ostringstream gs_winDebugStream;
#endif

static std::ostream* gs_outStream = &std::cout; 

static bool gs_activateInclude;
static std::vector<std::string> gs_include;

static bool gs_activateExclude;
static std::vector<std::string> gs_exclude;

static void MakeString(std::string& str,
                       const char* moduleName,
                       const char* fmt,
                       const va_list& ap)
{
  std::string format(moduleName);
  format.append(":");
  format.append(fmt);
  format.append("\n");

#define MAX_MESSAGE_LENGTH 1024 
  char message[MAX_MESSAGE_LENGTH];
  
  vsnprintf(message, MAX_MESSAGE_LENGTH, format.c_str(), const_cast<va_list&>(ap));
  
#undef MAX_MESSAGE_LENGTH

  str = message;
}

static void ResetFilter()
{
  gs_activateInclude = false;
  gs_include.clear();

  gs_activateExclude = false;
  gs_exclude.clear();
}

void TraceOutF(const char* moduleName, 
               const char* fmt, ...)
{
  if ( gs_outStream )
  {
    bool process = true;
    
    if ( gs_activateInclude )
    {
      process = std::find(gs_include.begin(), 
                          gs_include.end(),
                          std::string(moduleName)) 
                != gs_include.end();
    }

    if ( gs_activateExclude )
    {
      process = std::find(gs_exclude.begin(), 
                          gs_exclude.end(),
                          std::string(moduleName)) 
                == gs_exclude.end();
    }

    if ( process )
    {
      va_list ap;
      va_start(ap, fmt);

      std::string message;

      MakeString(message, moduleName, fmt, ap);

      *gs_outStream << message;

      gs_outStream->flush();

#if _WIN32
      if ( gs_outStream == &gs_winDebugStream )
      {
        OutputDebugString(gs_winDebugStream.str().c_str());
        gs_winDebugStream.str("");
      }
#endif

      va_end(ap);
    }
  }
}

void TraceToFile(const char* fileName)
{
  ResetFilter();

  gs_fileStream.open(fileName);

  if ( !gs_fileStream )
  {
    fprintf(stderr, "Unable to open trace file \"%s\" for writing.\n", fileName);

    gs_outStream = NULL;
  }
  else
    gs_outStream = &gs_fileStream;
}

void TraceToConsole()
{
  ResetFilter();

  gs_outStream = &std::cout;
}

void TraceNull()
{
  ResetFilter();

  gs_outStream = NULL;
}

#ifdef _WIN32
void TraceWin32()
{
  ResetFilter();

  gs_outStream = &gs_winDebugStream;
}
#endif

std::ostream* GetOutStream()
{
  return gs_outStream;
}

void TraceInclude(const char* moduleName)
{
  gs_activateInclude = true;

  gs_include.push_back(moduleName);
}

void TraceExclude(const char* moduleName)
{
  gs_activateExclude = true;

  gs_exclude.push_back(moduleName);
}

