# Makefile for clusterParse class

CXXFLAGS    =	-g -stdlib=libc++ -std=c++11 -Wall -Wextra -pedantic 
CXX	    =	clang++

# Flags passed to the preprocessor.
# We have no idea here whether pthreads is available in the system, so
# disable its use.
CPPFLAGS += -I. -DGTEST_HAS_PTHREAD=0

TARGETS 	    =	cluster-parse
CLUSTER_OBJS	=	ClusterParse.o

# ----- Make Rules -----

all:	$(TARGETS)

cluster-parse: $(CLUSTER_OBJS)
	$(CXX) $(LDFLAGS) $(LIBS) $(CXXFLAGS) -o $@ $(CLUSTER_OBJS)

clean:
	rm -f $(TARGETS) $(CLUSTER_OBJS)

ClusterParse.o: ClusterParse.hpp ClusterParse.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ClusterParse.cpp
