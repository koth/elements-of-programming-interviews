# `GitHub` #

Programs have been moved to [GitHub](http://elementsofprogramminginterviews.com/solutions/)

# **Project Description** #

This project contains over **250** programs corresponding to solutions to problems in our book "[Elements of Programming Interviews](http://www.amazon.com/dp/1479274836/)". These programs include classics like Dutch National Flag partitioning of an array, and reconstructing a binary tree from traversal data, as well as newer programs that exploit concurrency and heuristics.

**[Here](http://code.google.com/p/elements-of-programming-interviews/wiki/Programs) is the map from book problems to programs.**

These are primarily written in C++, and make use of C++11 features. Programs concerned with concurrency are in Java. We wrote and tested these programs on Mac OSX 10.8.5. We use `clang++` version 4.2  for C++ and Java 1.6.

From the command line, the command to compile C++ source is `clang++ -Weverything -Wno-c++98-compat -Wno-missing-prototypes TargetFile.cpp -stdlib=libc++ -std=c++11 -O4`. The Java compile command is `javac TargetFile.java`.

The Quora forum for the book is linked at `http://ElementsOfProgrammingInterviews.com`. If you have any questions or suggestions about these problems, please post there. (if you'd prefer to write to us, our contact information is at the same site.)

Adnan, Tsung-Hsien, and Amit