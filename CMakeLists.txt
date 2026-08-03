cmake_minimum_required(VERSION 3.10.0)
find package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(CO2_Monitor)
target_sources(app PRIVATE src/main.c)
