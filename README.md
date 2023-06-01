# FdF
To start the journey in graphic programming, FdF offers to represent “iron wire” meshing in 3D.

## .fdf files
The coordinates of the landscape are stored in a .fdf file passed as a parameter to
the program. Here is an example:
```
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0 10 10  0  0 10 10  0  0  0 10 10 10 10 10  0  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10 10 10 10 10  0  0  0  0 10 10 10 10  0  0  0
0  0  0 10 10 10 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10 10 10 10 10  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
```
Each number represents a point in space:
* The horizontal position corresponds to its axis.
* The vertical position corresponds to its ordinate.
* The value corresponds to its altitude.

## Approach
https://en.wikipedia.org/wiki/Rotation_matrix
https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

## How to use
- Run `make` in the root of the repository.
- Run ` ./fdf test_maps/<.fdf file> `.

<img width="2032" alt="42 fdf" src="https://github.com/pweinstock/FdF/assets/37242263/81229ee0-6d06-4214-baa0-b613a45f4cb2">

## Controls

|Action                       |Controls                                            |
|---------------------------- |:--------------------------------------------------:|
|Move map: up down left right | :arrow_up: :arrow_down: :arrow_left: :arrow_right: |
|Spin                         |Q F                                                 |
|Rotate                       |W A S D                                             |
|ZOOM                         |+ -                                                 |
|Exit                         |ESC                                                 |

<img width="2032" alt="mars fdf" src="https://github.com/pweinstock/FdF/assets/37242263/efc0abcd-32ab-4f2b-af71-d883f40654c6">
<img width="2032" alt="t2 fdf" src="https://github.com/pweinstock/FdF/assets/37242263/a2535066-12a2-4126-a963-b91f2cff507a">
