# Makefile for FrequentPairs and corresponding test framework

CXXFLAGS    =	-g -stdlib=libc++ -std=c++11 -Wall -Wextra -pedantic 
CXX	    =	clang++

GTEST_DIR   = gtest
GTEST_OBJS  = gtest-all.o

# Flags passed to the preprocessor.
# We d not know if pthreads is available in the system, so
# disable its use.
CPPFLAGS += -I. -DGTEST_HAS_PTHREAD=0

TARGETS 	    =	frequent-pairs-test trace-set
FREQUENTPAIRSTEST_OBJS     =	FrequentPairs.o frequent-pairs-test.o $(GTEST_OBJS)
FREQUENTPAIRS_OBJS	=	frequentpairsloader.o FrequentPairs.o

# ----- Make Rules -----

all:	$(TARGETS)

frequent-pairs-test:	$(FREQUENTPAIRSTEST_OBJS) 
	$(CXX) $(LDFLAGS) $(LIBS) $(CXXFLAGS) -o $@ $(FREQUENTPAIRSTEST_OBJS)

# Calling make test will run the gtest frame work in frequent-pairs-test.cpp 
test: frequent-pairs-test
	./frequent-pairs-test

frequentpairs-set: $(FERQUENTPAIRS_OBJS)
	$(CXX) $(LDFLAGS) $(LIBS) $(CXXFLAGS) -o $@ $(FREQUENTPAIRS_OBJS)

# Calling make frequentpairs will run the main in frequentpairsloader.cpp
frequentpairs: frequentpairs-set
	./frequentpairs-set

clean:
	rm -f $(TARGETS) $(TRACETEST_OBJS) $(TRACE_OBJS)

frequent-pairs-test.o: frequent-pairs-test.cpp 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c frequent-pairs-test.cpp

FrequentPairs.o: FrequentPairs.hpp FrequentPairs.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c FrequentPairs.cpp

frequentpairsloader.o: frequentpairsloader.cpp FrequentPairs.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c frequentpairsloader.cpp


#
# Google Test Code
#
gtest-all.o : gtest/gtest.h gtest/gtest-all.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c gtest/gtest-all.cc
