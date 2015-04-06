Mindstorm-Rover
===============

This project implements path finding and map exploration for the LEGO Mindstorms NXT robot. The goal is to enable the robot to navigate in a constrained, static but unexplored environment, drawing a map as it goes, and to find the fastest path between two points. 

The first iterations of this project will remain computer simulations, avoiding many technical difficulties. Indeed, implementing the code on a real-life Mindstorms robot is much more challenging, if only because of the multiple inherent inaccuracies of the robot.

Implementation
--------------

This project makes use of C++ classes and some very useful standard library data structures. It should remain compatible with the C++98 standard. 

Currently implemented are a simple maze generator to create varied test maps as well as a basic Depth-First Search (DFS) to explore the map. This is still very much a WIP, so there is more to come...

Version
-------

0.02

Compilation
-----------

`make`

The default makefile will generate a debug version with gprof profiling enabled. 

License
-------

The MIT License (MIT)

Copyright (c) 2014 REPOmAN2v2

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.