`SpinDec` - C++ Library for Spin Decoherence
==========================================

Solves for the many-body dynamics of a central spin system coupled to
an interacting spin bath.

- Implements the cluster correlation expansion.
- Includes special methods for donor qubits in silicon.
- Includes executable for CPMG dephasing (T2) of donors in silicon
interacting with 29Si nuclear impurities (nuclear spin diffusion).

Installation
------------

Requirements:

- [Eigen]: For linear algebra.
- [CMake]: For building and installing.
- [boost]: For program options, shared pointers and random
number generators.
- Optional: [Intel MKL] optimization for Eigen.

The following instructions are for a Unix-like environment
without root privileges.

Clone this repo.

```sh
git clone http://github.com/sbalian/spindec.git
```

To build,

```sh
cd spindec
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/home/myusrname
make -j4 all
make install
```

The argument to cmake defines the installation location
(here set to `/home/myusrname`).
If you invoke cmake without specifying the location, it will
install to your default system prefix (requires root).

The -j option to *make* parallelizes the build process using
the specified number of cores.

If all went well, you should now have the static library and
executables. The library, headers and executables should be
located in `/home/myusrname/lib`, `/home/myusrname/include` and
`/home/myusrname/bin` respectively.

Optionally, to enable MKL optimization in Eigen,
pass -DSPINDEC_USE_MKL=ON to cmake. You will need the
MKL libraries for this step. For further customization,
see CMakeLists.txt.

`SpinDec` has been tested on Linux and Mac OS X.

Usage
-----

Include the `SpinDec/base.h` header in your source and link with
`libspindec`.

The executable `spindec-dsnsd` has a `--help` option.
See also "Getting Help" below.

Example
-------

Follow the instructions under "Installation".

Open `spindec/tests/spindec-test-cce1.cpp` to see the source with
comments on the example problem. Using the cluster correlation
expansion up to 3rd order, it calculates the Hahn spin echo decay of
a central donor spin in silicon for a nuclear spin bath
(spin-1/2 29Si with a natural abundance of 4.7%).

To see the decay, run `spindec-test-cce1`.
The test executable is not installed, so run it in the build
directory.

The source for `spindec-dsnsd` (`src/spindec-dsnsd.cpp`) should also serve
as a good example.

Getting help
------------

- A reference manual generated using doxygen is available.
It has instructions on how to use the library and includes the code
structure (with inheritance diagrams).
- Alternatively, help can be directly viewed in in header files
(in `include/SpinDec`).
- Source files (in `src/`) may contain more information,
usually geared more towards implementation (these are not included
in the reference manual).
- See `src/spindec-dsnsd.cpp` and `tests/spindec-test-cce1.cpp` for
examples.

License and how to cite
-----------------------

`SpinDec` is free to use under the GNU General Public License.
See the `LICENSE` file for more details.

If you use any part of the code in a publication,
please cite it as follows:

`S. J. Balian, SpinDec: C++ Library for Spin Decoherence,
http://github.com/sbalian/spindec (2011-2016).`

Here is the BibTeX entry:

```text
@misc{SpinDec,
  title = {SpinDec: C++ library for spin decoherence},
  author = {Balian, Setrak J.},
  howpublished = {http://github.com/sbalian/spindec},
  year = {2011--2016}
}
```

History
-------

SpinDec is based on bits and pieces of old code for certain spin baths
and central spin systems. These were written by Seto Balian starting
in 2011. Methods used to efficiently fill Hamiltonian matrix elements
were originally written in Fortran by Tania Monteiro.
Development for SpinDec as an open-source project started in May 2013.

Acknowledgements
----------------

- Tania Monteiro
- Martin Uhrin
- Wayne Witzel
- Gavin Morley
- Roland Guichard
- Leonardo Banchi

See also
--------

For pseudospins and more:
http://github.com/UCLGuichard/CCPQ

Contact
-------

[Seto Balian](mailto:seto.balian@gmail.com)


[Eigen]:http://eigen.tuxfamily.org
[CMake]: http://www.cmake.org/
[boost]: http://www.boost.org/
[Intel MKL]: https://software.intel.com/en-us/intel-mkl

