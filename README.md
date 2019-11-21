# QtLager

## Framework for Redux-like UI programming with C++

### Introduction

In a nutshell, QtLager is a framework for React/Redux-like programming for C++. It is based on
[Qt](https://www.qt.io/), a widespread, platform-independend library for UI development, and
[Lager](https://github.com/arximboldi/lager), an excellent library for functional/Redux-like
programming for C++ by Juanpe. With this framework you can create fast and responsive desktop and
mobile applications.

### Using QtLager

This framework is still in __very__ early development. It is going to change a lot in the next few
weeks, so be careful if you already want to use it and maybe contact me for further pointers.

- clone this repo into your project folder or add it as a submodule
- Do a `git submodule update --init --recursive`
- Create a new cmake subdirectory-project in the parent folder and add Core
- Create at least one reducer and one view plugin
  - you can create as many reducer and view plugins as you want
- In the main view plugin create a qrc-file with a main.qml in it
  - this is the qml-file that will be executed at startup (qrc:/main.qml)
  - other views can be included by setting context properties on the root context
- Define the actions and the model in the respective files in Core/Sources

### Goals

My goals with this framework are:
- Quick and easy start even for people new to C++ and functional concepts
- Minimal development overhead through hot-reloading
- Clear instructions and tutorials
- Easy deployment and auto-update
- Well tested and easy to test
