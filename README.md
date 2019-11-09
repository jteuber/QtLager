# QtLager

## Framework for Redux-like UI programming with C++

### Introduction

In a nutshell, QtLager is React/Redux for C++. It is a framework based on Qt
and Lager, an excellent library for functional/Redux-like programming for C++
by Juanpe. With this framework you can create fast and responsive desktop and
mobile applications.

### Using QtLager

- clone this repo into your project folder or add it as a submodule
- git submodule update --init --recursive
- Create a new cmake subdirectory-project in the parent folder and add Core
- Create at least one reducer and one view plugin
  - you can create as many reducer and view plugins as you want
- In the main view plugin create a qrc-file with a main.qml in it
  - this is the qml-file that will be executed at startup (qrc:/main.qml)
  - other views can be included by setting context properties on the root context
- Define the actions and the model in the respective files in Core/Sources
