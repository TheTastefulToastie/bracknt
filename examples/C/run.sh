#!/bin/sh
bracknt example.c | gcc -xc -o example - && ./example
