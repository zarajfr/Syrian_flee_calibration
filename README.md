
# Syrian_flee_calibration
This repository implement the calibration of flee decisions in refugee displacement, using Syrian flee data. 
This repository is complemented by other repositories Syrian_destination_calibration, Syrian_displacement_simulation and Visualising_Syrian_flow, for a thorough data-driven simulation of Syrian refugee flows.
***
## Authors

 * Zahra Jafari, <zahra.jafari.17@ucl.ac.uk>
   * UCL Jill Dando Institute of Security and Crime Science, University College London
 * Toby Davies,
   * UCL Jill Dando Institute of Security and Crime Science, University College London
 * Shane Johnson,
   * UCL Jill Dando Institute of Security and Crime Science, University College London

# Introduction

This is a code repository for the paper " Data-driven simulation tool for predicting refugee flows and migration policy".
It provides all the information, data and code that are required in order to replicate the analyses presented in the paper.
This document provides the instruction and the description of the content of the repository. This analysis can be applied to any other coonflict-induced migration scenarios once the input data is incorporated appropriately; including conflict, population, and spatial network used in the source code. The details of the analyses are documented within the source file as comments.

# Documentation

Simulation guidline is available to download at : 

# Requirements

The project uses standard C++ 14 compiler and the source code should run on any standard operating system (i.e. Linux/Unix, MacOS, Windows).

# Content of the repository

## Scripts

  - `simulator.cpp`
  - `agent.cpp`
  - `graph.cpp`
  - `node.cpp`
  - `flee_calib.cpp`
  - `openga.hpp` <-- This is the OpenGA library in C++ developed by Mohammadi et. al. <-- github link: https://github.com/Arash-codedev/openGA#readme
  - `main.cpp`
  - `Makefile`

## Directories

  - `macro_data`
    - Includes the spatio-temporal data on migration factors, as well as the Syrian flow data.
### Input format

The data is geocoded at the spatial granularity of the spatial network implemented in the source code. The temporal intervals are monthly. The directory includes csv files corresponding to migration factors and displacement flow. The temporal units are across the columns and the space is across the rows.

## Results

Simulation ourputs are saved in a CSV file. The result can be visualised using the Python codes shared in the Visualising_Syrian_flow repository of this account.
