# Sierpinski Triangle SML

This is a very simple implementation of a Sierpinski Triangle done in SFML. I made this as a fun little side project as the Sierpinski has to be one of the funnest and easiest fractals to produce. My implementation is very simple and just uses an std::vector to hold all the points. The calculated coordinates are stored in a sf::Vector2f , drawing these points is then done by iterating through the std::vector and drawing a unit circle at the current position. Calculating the points is done recursively, a depth and the current existing vector is also passed by reference. I must admit this isn't the most optimized code and many optimizations can be made (for instance no need for return in calculateNewPosition , but I wrote it to better understand SFML and the C++ language. 
### References:
[Sierpinski Triangle - Wikipedia](https://en.wikipedia.org/wiki/Sierpi%C5%84ski_triangle)
