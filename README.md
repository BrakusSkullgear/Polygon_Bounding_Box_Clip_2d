# Polygon_Bounding_Box_Clip_2d

Simple and easy to read template class for clipping 2d polygons inside bounding box. Vertex positions are clipped into bounding box, and other optional attributes such as texcoord and color are interpolated based on the clipped position values. <br/>

Class accepts a single line, triangle or convex quad, and clips it into multiple polygons of the requested type. <br/>

See main.cpp for an example. Various types of vertexes are introduced in Vertex2d.h – file. <br/>

Example input: <br/>
![alt text](https://github.com/BrakusSkullgear/Polygon_Bounding_Box_Clip_2d/blob/main/Images/initial_input.png?raw=true)

Example output:  <br/>
![alt text](https://github.com/BrakusSkullgear/Polygon_Bounding_Box_Clip_2d/blob/main/Images/clipped_output.png?raw=true)
