# summer_research_2015

At present, this repository contains the code which we personally have written 
this summer.  For other software (which this code depends on), see the code in 
/research/geoff/2015 on knuth.  

That includes BORG (see the paper BORG: Block-reORGanization for 
Self-Optimizing Storage Systems for a description) which we modified 
slightly, to only spit out the block reorganization without actually 
implementing the changes in the kernel, and Cluto, a clustering algorithm 
presented in the paper "CHAMELEON: A Hierarchical Clustering Algorithm Using 
Dynamic Modeling".

The code presently contained in this repository are a TraceSet data structure, which 
we use to roughly test the block reorganizations we generate based on traces, and 
a program which reconstructs a hierarchical tree based on Cluto's output file. 

README modified by Elizabeth Krenkel, July 17, 2015 (ekrenkel@g.hmc.edu)
