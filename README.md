# A simple bank application
This project aims to explore some object-oriented programming (OOP) techniques through a **Banking System** Project in C++.


## Meta
 * **Bachelor of Science in Electrical Engineering - Federal University of Espírito Santo**
 * **Course:** INF09324 Applied Computer Programming
 * **Author:** Alaf do Nascimento Santos
 * **License**: [MIT](LICENSE)
 * **Year:** 2017

## Documentation
Since this repository is a result of a Brazilian undergraduate course project focused on object-oriented programming (OOP) techniques developed in 2017, all the produced documentation is in Portuguese. This document can be found in the docs folder.

## Compilation and Usage
Firstly, create a build folder inside the project directory. The following command may help you:

***$ mkdir build***

Then, go inside the created folder and type the following in order to compile to programme:
***$ cd build***

***$ cmake ..***

***$ make***

You just compiled the sensorHandler binary. In order to run it, go back to the root TP directory and execute it. Type:

***$ cd ..***

***./bank***

#### Simplified Makefile
Inside the root TP folder, you can find a Makefile which has the following make commands:

- **make** or **make all**: builds the project so you only need to create the build folder instead of doing the entire previous procedure.
- **make run**: executes the programme.
- **make clean**: clean the build folder and delete the sensorHandler binary file.
