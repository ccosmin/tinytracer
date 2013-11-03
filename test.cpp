////////////////////////////////////////////////////////////////////////////////
//
//  Author: Cosmin Cremarenco 
//  Email: cosmin.cremarenco(non spammers remove this] @gmail.com
////////////////////////////////////////////////////////////////////////////////
#include "tracer.h"

int main()
{
  TraceToConsole();

  TF0("This to output.");

  char fileName[] = "log.txt";
  TraceToFile(fileName);

  TF1("Tracing was switched to file %s", fileName); 

  TraceToConsole();

  TraceExclude("test.cpp");

  TF0("This won't be seen, test.cpp was excluded");
}

