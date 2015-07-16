# Makefile for TraceSet Tester

CXXFLAGS    =	-g -stdlib=libc++ -std=c++11 -Wall -Wextra -pedantic 
CXX	    =	clang++

GTEST_DIR   = gtest
GTEST_OBJS  = gtest-all.o

# Flags passed to the preprocessor.
# We have no idea here whether pthreads is available in the system, so
# disable its use.
CPPFLAGS += -I. -DGTEST_HAS_PTHREAD=0

TARGETS 	    =	cluster-parse-test cluster-parse
CLUSTERTEST_OBJS     =	ClusterParse.o cluster-parse-test.o $(GTEST_OBJS)
CLUSTER_OBJS	=	clusterloader.o ClusterParse.o

# ----- Make Rules -----

all:	$(TARGETS)

cluster-parse-test:	$(CLUSTERTEST_OBJS) 
	$(CXX) $(LDFLAGS) $(LIBS) $(CXXFLAGS) -o $@ $(CLUSTERTEST_OBJS)

# Calling make test will run the gtest frame work in trace-set-test.cpp 
test: cluster-parse-test
	./cluster—parse-test

cluster-parse: $(CLUSTER_OBJS)
	$(CXX) $(LDFLAGS) $(LIBS) $(CXXFLAGS) -o $@ $(CLUSTER_OBJS)

# Calling make trace will run the main in traceloader.cpp
parse: cluster-parse
	./cluster-parse

clean:
	rm -f $(TARGETS) $(CLUSTERTEST_OBJS) $(CLUSTER_OBJS)

cluster-parse-test.o: cluster-parse-test.cpp 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c cluster-parse-test.cpp

ClusterParse.o: ClusterParse.hpp ClusterParse.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ClusterParse.cpp

clusterloader.o: clusterloader.cpp ClusterParse.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c clusterloader.cpp


#
# Google Test Code
#
gtest-all.o : gtest/gtest.h gtest/gtest-all.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c gtest/gtest-all.cc 
