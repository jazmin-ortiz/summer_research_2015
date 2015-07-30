# Makefile for postCluto loader. 

CXXFLAGS    =	-g -stdlib=libc++ -std=c++11 -Wall -Wextra -pedantic 
CXX	    =	clang++

# Flags passed to the preprocessor.
# We have no idea here whether pthreads is available in the system, so
# disable its use.
CPPFLAGS += -I. -DGTEST_HAS_PTHREAD=0

TARGETS 	    =	post-cluto
CLUTO_OBJS	=	postcluto.o cluster_parse/ClusterParse.o trace_set/TraceSet.o

# ----- Make Rules -----

all:	$(TARGETS)

post-cluto: $(CLUTO_OBJS)
	$(CXX) $(LDFLAGS) $(LIBS) $(CXXFLAGS) -o $@ $(CLUTO_OBJS)

clean: 
	rm -f $(TARGETS) $(CLUTO_OBJS)

TraceSet.o:  trace_set/TraceSet.hpp trace_set/TraceSet.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c trace_set/TraceSet.cpp

ClusterParse.o:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c cluster_parse/ClusterParse.cpp

postcluto.o: postcluto.cpp trace_set/TraceSet.hpp cluster_parse/ClusterParse.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c postcluto.cpp