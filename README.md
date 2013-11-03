tinytracer
==========

TinyTracer is a simple library for code tracing. It offers facilities
to trace the program execution much like you would do using printf statements.

It is meant to be much easier to use than rlog, log4cpp, log4cxx.

Starting trace is quite simple by calling "TraceToConsole" (this is done 
by default), "TraceToFile" and then calling TFx macros for outputting trace
statements.

If using Windows, alternatively, you can call TraceWin32 
and "OutputDebugString" will be used in order to send the trace messages to output.

Tracing is meant to be kept in the release version, the overhead is minimal.

Tracing is done on the basis of modules (.cpp files) and can be disabled/enabled
explicitly by calling TraceInclude/TraceExclude.

A Makefile is provided for building the tracer.o that you can link directly
to your program. You can also compile and run the test in test.cpp

