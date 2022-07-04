# wxGraphEditor
## Graph editor using C++ built with wxWidgets.


## Features

- Сreate an directed and undirected graph
- Sign vertices of graphs
- Import and save graph files
- Highlight the components of a graph's strong connectivity
- Build a table with the names of the vertices of the components of the strong connectivity of the graph


## Installation

There is a cmake file here, but first you will have to install the wxWidgets library.
There is instructions for Ubuntu.

Installing wxWidgets library:
```sh
apt install build-essential
apt-get install libwxbase3.0-dev libwxgtk3.0-gtk3-dev
```

For compiling components:

```sh
cmake .
make
```

For launching the app:

```sh
./wxPaintingTest
```
