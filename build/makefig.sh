#!/bin/bash
# Seto Balian 29/08/2014

gprof ./test_cce | ./gprof2dot.py | dot -Teps -o output.eps

