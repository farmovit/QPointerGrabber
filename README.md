<h3 align="center">QPointerGrabber</h3>

<div align="center">

  [![Status](https://img.shields.io/badge/status-active-success.svg)]()
  [![GitHub Issues](https://img.shields.io/github/issues/farmovit/QPointerGrabber.svg?style=flat-square)](https://github.com/farmovit/QPointerGrabber/issues)
  [![GitHub Pull Requests](https://img.shields.io/github/issues-pr/farmovit/QPointerGrabber.svg?style=flat-square)](https://github.com/farmovit/QPointerGrabber/pulls)
  [![License](https://img.shields.io/badge/license-MIT-blue.svg)](/LICENSE)
	[![Build status](https://ci.appveyor.com/api/projects/status/54mwjk9bgnlmifxy?svg=true)](https://ci.appveyor.com/project/farmovit/qpointergrabber)

</div>

---

<p align="center"> A simple library that allows to grab(clip) a mouse pointer by a QWidget.
    <br> 
</p>

## About <a name = "about"></a>
In my projects I often need to grab a mouse pointer by some Window in a cross platform manner. 
I spend some time to get it on Linux and realized that it might be helpful for other peoples.
Please, take a look on a demo:
<img src="https://github.com/farmovit/QPointerGrabber/blob/master/pic/demo.gif" width="315" height="128" />

## 🏁 Getting Started <a name = "getting_started"></a>
You can simply clone this project and build it for your needs.

### Prerequisites
What things you need to install the software and how to install them. All you need is
```
Windows/Linux OS
CMake >= 3.5
Compiler with C++17 support
Qt5.X
```

### Build
```
mkdir build
cd build
cmake ..
make -j 8
```

## 🎈 Usage <a name="usage"></a>
Please see the [test](https://github.com/farmovit/QPointerGrabber/blob/master/test/GrabberTest.cpp) to get how it can be used.

### TODO

---
- [x] Add CI for Windows.
- [ ] Add CI for Linux.
- [ ] Add MAC OS Support.
- [ ] Create a packages for various systems.
- [ ] Extend library for QWindow.
- [ ] Extend library for window id only, i.e. without Qt Widget/Window.
