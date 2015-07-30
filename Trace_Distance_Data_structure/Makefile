# Makefile for TraceSet class and testing framework for the TraceSet class

CXXFLAGS    =	-g -stdlib=libc++ -std=c++11 -Wall -Wextra -pedantic 
CXX	    =	clang++

GTEST_DIR   = gtest
GTEST_OBJS  = gtest-all.o

# Flags passed to the preprocessor.
# We d not know if pthreads is available in the system, so
# disable its use.
CPPFLAGS += -I. -DGTEST_HAS_PTHREAD=0

TARGETS 	    =	trace-set-test trace-set traceset-commandline
TRACETEST_OBJS     =	TraceSet.o trace-set-test.o $(GTEST_OBJS)
TRACE_OBJS	=	traceloader.o TraceSet.o
TRACE_COMMAND_LINE_OBJS	=	traceset-commandline.o TraceSet.o

# ----- Make Rules -----

all:	$(TARGETS)

clean:
	rm -f $(TARGETS) $(TRACETEST_OBJS) $(TRACE_OBJS) $(TRACE_COMMAND_LINE_OBJS)

# Calling make test will run the gtest frame work in trace-set-test.cpp 
test: trace-set-test
	./trace-set-test

# Calling make trace will run the main in traceloader.cpp
trace: trace-set
	./trace-set

# Calling make trace-commandline will run the main in traceset-commandline.cpp
trace-set-commandline: traceset-commandline
	./traceset-commandline

# Executables
trace-set: $(TRACE_OBJS)
	$(CXX) $(LDFLAGS) $(LIBS) $(CXXFLAGS) -o $@ $(TRACE_OBJS)

trace-set-test:	$(TRACETEST_OBJS) 
	$(CXX) $(LDFLAGS) $(LIBS) $(CXXFLAGS) -o $@ $(TRACETEST_OBJS)

traceset-commandline: $(TRACE_COMMAND_LINE_OBJS)
	$(CXX) $(LDFLAGS) $(LIBS) $(CXXFLAGS) -o $@ $(TRACE_COMMAND_LINE_OBJS)

# Objects
TraceSet.o: TraceSet.hpp TraceSet.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c TraceSet.cpp

trace-set-test.o: trace-set-test.cpp 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c trace-set-test.cpp

traceloader.o: traceloader.cpp TraceSet.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c traceloader.cpp

traceset-commandline.o: traceset-commandline.cpp TraceSet.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c traceset-commandline.cpp


#
# Google Test Code
#
gtest-all.o : gtest/gtest.h gtest/gtest-all.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c gtest/gtest-all.cc
