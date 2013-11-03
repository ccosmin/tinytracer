////////////////////////////////////////////////////////////////////////////////
//
//  Author: Cosmin Cremarenco 
//  Email: cosmin.cremarenco(non spammers remove this] @gmail.com
////////////////////////////////////////////////////////////////////////////////
#ifndef __TRACER_H__
#define __TRACER_H__

#include <ostream>
#include <vector>
#include <iterator>

void TraceOutF(const char* moduleName, 
               const char* fmt, ...);

/**
    Send all trace output to @a fileName.
 */
void TraceToFile(const char* fileName);

/**
    Send all trace output to the console.
 */
void TraceToConsole();

/**
    Stop trace messages.
 */
void TraceNull();

#ifdef _WIN32
/**
    Use OutputDebugString to perform tracing. 
 */
void TraceWin32();
#endif

std::ostream* GetOutStream();

template <class T>
void TraceObjectHelper(std::ostream& outStream, const T& obj)
{
  outStream << obj << std::endl;
}

template <class T>
void TraceObjectHelper(std::ostream& outStream, const std::vector<T>& v)
{
  outStream << "vector" << std::endl << "[" << std::endl;
  for ( typename std::vector<T>::const_iterator pos = v.begin();
        pos != v.end();
        ++pos )
  {
    outStream << "\t";

    TraceObjectHelper(outStream, *pos);
  }
  outStream << "[" << std::endl;
}

template <class T>
void TraceObject(const char* moduleName, const T& obj)
{
  std::ostream* outStream = GetOutStream();

  if ( outStream )
  {
    *outStream << moduleName << ":";

    TraceObjectHelper(*outStream, obj);
  }
}

void TraceInclude(const char* moduleName);

void TraceExclude(const char* moduleName);

#define TF0(fmt) TraceOutF(__FILE__, fmt); 
#define TF1(fmt, p1) TraceOutF(__FILE__, fmt, p1); 
#define TF2(fmt, p1, p2) TraceOutF(__FILE__, fmt, p1, p2); 
#define TF3(fmt, p1, p2, p3) TraceOutF(__FILE__, fmt, p1, p2, p3); 

#define TO(obj) TraceObject(__FILE__, (obj));

#endif
