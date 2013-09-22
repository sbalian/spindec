// For generating lattice vectors in Cartesian coordinates (x,y,z).
//
// Created  19/09/2012 diamondcubic -> lattice
// Modified 20/09/2012, 12/11/2012, 14/11/2012, 15/11/2012, 19/11/2012
// Modified 11/12/2012 - commented out some generate + get random lattice vecs method + minor improvement to generate method
// Modified 17/01/2013
// Modified 25/02/2013
// Modified 08/05/2013
// Modified 13/05/2013
// Seto Balian
// V1

#include "stdincludes.hpp"
#include "named.hpp"
#include "threevector.hpp"
#include "lattice.hpp"

using namespace std;

lattice::lattice() : named("")
{
  set_lattice_constant(1.0);
  clear_lattice_vectors();
}

lattice::lattice(const string & name_in, const double lattice_constant_in) : named(name_in)
{
  set_lattice_constant(lattice_constant_in);
  clear_lattice_vectors();
}
  
double lattice::get_lattice_constant() const {
  return lattice_constant; 
}

void lattice::set_lattice_constant(const double lattice_constant_in) {
  lattice_constant = lattice_constant_in;
  scale_lattice_vectors(get_lattice_constant());
}

vector<threevector> lattice::get_lattice_vectors () const {
  return lattice_vectors;
}

threevector lattice::get_lattice_vector (const int i) const {
  return lattice_vectors[i];
}

//// NOTE: Needs more commenting
//int lattice::generate_random_diamond_cubic(const double cubic_size, const double frac) {

//  clear_lattice_vectors();
//  int number_of_lattice_vectors = int(pow((cubic_size/get_lattice_constant()),3.0)*8.0*frac);

//  // Declarations

//  // Random numbers
//  int ra1, ra2, ra3, rb;

//  // Primitive lattice vectors
//  threevector a1(0.0,0.0,0.0);
//  threevector a2(0.0,0.0,0.0);
//  threevector a3(0.0,0.0,0.0);

//  // Basis vectors
//  threevector b1 = threevector(0.0,0.0,0.0);
//  threevector b2 = threevector(0.0,0.5,0.5);
//  threevector b3 = threevector(0.5,0.0,0.5);
//  threevector b4 = threevector(0.5,0.5,0.0);
//  threevector b5 = threevector(0.75,0.75,0.75);
//  threevector b6 = threevector(0.75,0.25,0.25);
//  threevector b7 = threevector(0.25,0.75,0.25);
//  threevector b8 = threevector(0.25,0.25,0.75);

//  b1 = b1*get_lattice_constant();
//  b2 = b2*get_lattice_constant();
//  b3 = b3*get_lattice_constant();
//  b4 = b4*get_lattice_constant();
//  b5 = b5*get_lattice_constant();
//  b6 = b6*get_lattice_constant();
//  b7 = b7*get_lattice_constant();
//  b8 = b8*get_lattice_constant();

//  threevector vector_out;
//  int i,j;
//  bool success;

//  int max_rand = int(cubic_size/get_lattice_constant());

//  for (i=0;i<number_of_lattice_vectors;i++) {

//    while (1) {

//      vector_out = threevector(0.0,0.0,0.0);
//      success = 1;

//      // Generate random numbers
//      ra1 = rand()%(max_rand+1);
//      ra2 = rand()%(max_rand+1);
//      ra3 = rand()%(max_rand+1);

//      rb = rand()%(8);

//      // Primitive lattice vectors
//      a1.set_x(get_lattice_constant()*double(ra1));
//      a2.set_y(get_lattice_constant()*double(ra2));
//      a3.set_z(get_lattice_constant()*double(ra3));


//      switch (rb) {
//        case 0:
//          vector_out = a1 + a2 + a3 + b1;
//          break;
//        case 1:
//          vector_out = a1 + a2 + a3 + b2;
//          break;
//        case 2:
//          vector_out = a1 + a2 + a3 + b3;
//          break;
//        case 3:
//          vector_out = a1 + a2 + a3 + b4;
//          break;
//        case 4:
//          vector_out = a1 + a2 + a3 + b5;
//          break;
//        case 5:
//          vector_out = a1 + a2 + a3 + b6;
//          break;
//        case 6:
//          vector_out = a1 + a2 + a3 + b7;
//          break;
//        case 7:
//          vector_out = a1 + a2 + a3 + b8;
//          break;
//        default:
//          cout << error_by_name() << "Random integer not between 0 and 7." << endl;
//          return 0;
//      }

//      // Shift cube such that (0,0,0) is at the centre of the cube
//      vector_out.set_x(vector_out.get_x() - cubic_size/2.0);
//      vector_out.set_y(vector_out.get_y() - cubic_size/2.0);
//      vector_out.set_z(vector_out.get_z() - cubic_size/2.0);

//      // Exclude origin
//      if ( (vector_out.get_x() == 0.0) && (vector_out.get_y() == 0.0) && (vector_out.get_z() == 0.0) ) {
//        continue;
//      }

//      // Avoid duplicates
//      for (j=0;j<get_lattice_vectors_size();j++) {
//        if ( (get_lattice_vector(j).get_x() == vector_out.get_x()) &&
//             (get_lattice_vector(j).get_y() == vector_out.get_y()) &&
//             (get_lattice_vector(j).get_z() == vector_out.get_z()) ) {
//          success = 0;
//          break;
//        }
//      }
//      if (success == 0) {continue;} else {break;}
//      break;
//    }

//    add_lattice_vector(vector_out);

//  }

//  return number_of_lattice_vectors;

//}

// NOTE: Needs more commenting
void lattice::old_generate_diamond_cubic(const int size) {

  const double squareSize = (size) * get_lattice_constant();

  // METHOD FROM WIKIPEDIA: http://en.wikipedia.org/wiki/Diamond_cubic
  // DATE: 03/11/2011
  // (0,0,0), (0,2,2), (2,0,2), (2,2,0),
  // (3,3,3), (3,1,1), (1,3,1), (1,1,3)
  // ADD MULTIPLES OF 4 TO THESE
  // SCALE BY 1/4 a0

  if (size <= 0) {
    cout << error_by_name() << "Argument size to method void generate_lattice_vectors(int size) must be non-zero positive." << endl;
    return; 
  }
  
  clear_lattice_vectors ();

  threevector l1(0.0,0.0,0.0);
  threevector l2(0.0,2.0,2.0);
  threevector l3(2.0,0.0,2.0);
  threevector l4(2.0,2.0,0.0);
  threevector l5(3.0,3.0,3.0);
  threevector l6(3.0,1.0,1.0);
  threevector l7(1.0,3.0,1.0);
  threevector l8(1.0,1.0,3.0);

  threevector r;

  // Martin : changed code so that 0 0 0 at centre ...
  threevector toadd;
  int i,j,k;
  for (i=-size;i<=size;i++) {
    for (j=-size;j<=size;j++) {
      for (k=-size;k<=size;k++) {
        toadd.set_x(4.0*double(i));
        toadd.set_y(4.0*double(j));
        toadd.set_z(4.0*double(k));
        // exclude the origin
        if ((abs(i) + abs(j) + abs(k)) != 0) {
          r = (l1 + toadd)*(get_lattice_constant()/4.0);
          if( r.get_max_abs_comp() < squareSize) {
            add_lattice_vector( r );
          }
        }

        r = (l2 + toadd)*(get_lattice_constant()/4.0);
          if( r.get_max_abs_comp() < squareSize) {
          add_lattice_vector( r );
        }

        r = (l3 + toadd)*(get_lattice_constant()/4.0);
          if( r.get_max_abs_comp() < squareSize) {
          add_lattice_vector( r );
        }

        r = (l4 + toadd)*(get_lattice_constant()/4.0);
          if( r.get_max_abs_comp() < squareSize) {
          add_lattice_vector( r );
        }

        r = (l5 + toadd)*(get_lattice_constant()/4.0);
          if( r.get_max_abs_comp() < squareSize) {
          add_lattice_vector( r );
        }

        r = (l6 + toadd)*(get_lattice_constant()/4.0);
          if( r.get_max_abs_comp() < squareSize) {
          add_lattice_vector( r );
        }

        r = (l7 + toadd)*(get_lattice_constant()/4.0);
          if( r.get_max_abs_comp() < squareSize) {
          add_lattice_vector( r );
        }

        r = (l8 + toadd)*(get_lattice_constant()/4.0);
          if( r.get_max_abs_comp() < squareSize) {
          add_lattice_vector( r );
        }
      }
    }
  }
  
  return;

}

// NOTE: Needs more commenting
int lattice::generate_random_diamond_cubic(const int size, const int bath_abundance_ppm) {

   const double squareSize = (size) * get_lattice_constant();
   //squareSize = 43.44;

  // METHOD FROM WIKIPEDIA: http://en.wikipedia.org/wiki/Diamond_cubic
  // DATE: 03/11/2011
  // (0,0,0), (0,2,2), (2,0,2), (2,2,0),
  // (3,3,3), (3,1,1), (1,3,1), (1,1,3)
  // ADD MULTIPLES OF 4 TO THESE
  // SCALE BY 1/4 a0

  if (size <= 0) {
    cout << error_by_name() << "Argument size must be non-zero positive." << endl;
    return 0;
  }
  
  clear_lattice_vectors();

  threevector l1(0.0,0.0,0.0);
  threevector l2(0.0,2.0,2.0);
  threevector l3(2.0,0.0,2.0);
  threevector l4(2.0,2.0,0.0);
  threevector l5(3.0,3.0,3.0);
  threevector l6(3.0,1.0,1.0);
  threevector l7(1.0,3.0,1.0);
  threevector l8(1.0,1.0,3.0);

  threevector r;


  // Martin : changed code so that 0 0 0 at centre ...
  threevector toadd;
  int i,j,k;
  for (i=-size;i<=size;i++) {
    for (j=-size;j<=size;j++) {
      for (k=-size;k<=size;k++) {
        toadd.set_x(4.0*double(i));
        toadd.set_y(4.0*double(j));
        toadd.set_z(4.0*double(k));
        // exclude the origin
        if ((abs(i) + abs(j) + abs(k)) != 0) {
          r = (l1 + toadd)*(get_lattice_constant()/4.0);
          if( r.get_max_abs_comp() <= squareSize) {
            if ((rand()%1000000) < bath_abundance_ppm) {
              add_lattice_vector( r );
            }
          }
        }

        r = (l2 + toadd)*(get_lattice_constant()/4.0);
          if( r.get_max_abs_comp() <= squareSize) {
            if ((rand()%1000000) < bath_abundance_ppm) {
              add_lattice_vector( r );
            }
        }

        r = (l3 + toadd)*(get_lattice_constant()/4.0);
          if( r.get_max_abs_comp() <= squareSize) {
            if ((rand()%1000000) < bath_abundance_ppm) {
              add_lattice_vector( r );
            }
        }

        r = (l4 + toadd)*(get_lattice_constant()/4.0);
          if( r.get_max_abs_comp() <= squareSize) {
            if ((rand()%1000000) < bath_abundance_ppm) {
              add_lattice_vector( r );
            }
        }

        r = (l5 + toadd)*(get_lattice_constant()/4.0);
          if( r.get_max_abs_comp() <= squareSize) {
            if ((rand()%1000000) < bath_abundance_ppm) {
              add_lattice_vector( r );
            }
        }

        r = (l6 + toadd)*(get_lattice_constant()/4.0);
          if( r.get_max_abs_comp() <= squareSize) {
            if ((rand()%1000000) < bath_abundance_ppm) {
              add_lattice_vector( r );
            }
        }

        r = (l7 + toadd)*(get_lattice_constant()/4.0);
          if( r.get_max_abs_comp() <= squareSize) {
            if ((rand()%1000000) < bath_abundance_ppm) {
              add_lattice_vector( r );
            }
        }

        r = (l8 + toadd)*(get_lattice_constant()/4.0);
          if( r.get_max_abs_comp() <= squareSize) {
            if ((rand()%1000000) < bath_abundance_ppm) {
              add_lattice_vector( r );
            }
        }
      }
    }
  }
  
  return get_lattice_vectors_size();

}

vector<threevector> lattice::get_lattice_vectors (const double max_radius) const {
  vector<threevector> vvout;
  int i;
  for (i=0;i<get_lattice_vectors_size();i++) {
    if (get_lattice_vector(i).mod()<=max_radius) {
      vvout.push_back(get_lattice_vector(i));
    }
  }
  return vvout;
}

int lattice::get_lattice_vectors_size() const {
  return lattice_vectors.size(); 
}

vector<threevector> lattice::get_random_lattice_vectors(const double frac) const {
  int originalN = get_lattice_vectors_size();
  vector<threevector> randomvectors;
  vector<int> randomindices;
  int N = int(originalN*frac);
  int randomint;
  int i,j;
  bool duplicate;
  for (i=0;i<N;i++) {
    duplicate = 0;
    randomint = rand()%originalN;
    for (j=0;j<int(randomindices.size());j++) {
      if (randomint == randomindices[j]) {
         duplicate = 1;
         break;
      }
    }
    if (duplicate == 1) {
      i = i-1;
      continue;
    }
    randomindices.push_back(randomint);
  }
  
  
  for (i=0;i<int(randomindices.size());i++) {
    randomvectors.push_back(get_lattice_vector(randomindices[i]));
  }
  return randomvectors;
  
}

double lattice::get_max_mod(const vector<threevector> & vvin) {
  int i;
  darray sizes;
  for (i=0;i<int(vvin.size());i++) {
    sizes.push_back(vvin[i].mod());
  }
  return *max_element(sizes.begin(),sizes.end());
}

double lattice::get_max_lattice_vector_mod() const {
  return get_max_mod(lattice_vectors);
}

double lattice::get_max_abs_comp(const vector<threevector> & vvin) {
  int i;
  darray sizes;
  for (i=0;i<int(vvin.size());i++) {
    sizes.push_back(vvin[i].get_max_abs_comp());
  }
  return *max_element(sizes.begin(),sizes.end());
}

double lattice::get_max_lattice_vector_abs_comp() const {
  return get_max_abs_comp(lattice_vectors);
}

void lattice::set_lattice_vectors (const vector<threevector> & lattice_vectors_in) {
  lattice_vectors = lattice_vectors_in;
  return;
}

void lattice::add_lattice_vector(const threevector & lattice_vector) {
  lattice_vectors.push_back(lattice_vector);
  return;
}

void lattice::clear_lattice_vectors () {
  lattice_vectors.clear();
  return;
}

void lattice::scale_lattice_vectors(const double scalefactor) {
  int i;
  threevector scaledvec;
  vector<threevector> scaledvecs;
  for (i=0;i<get_lattice_vectors_size();i++) {
    scaledvec = get_lattice_vector(i)*scalefactor;
    scaledvecs.push_back(scaledvec);
  }
  clear_lattice_vectors();
  set_lattice_vectors(scaledvecs);
  return;
}

void lattice::write_lattice_vectors(const string & filename) const {
  ofstream outfile(filename.c_str());
  int i;
  for (i=0;i<get_lattice_vectors_size();i++) {
    outfile << left;
    outfile << scientific;
    outfile << setprecision(5);
    if ( (get_lattice_vector(i).get_x() == 0) && (get_lattice_vector(i).get_y() == 0) && (get_lattice_vector(i).get_z() == 0) ) {continue;}
    outfile << setw(25) << get_lattice_vector(i).get_x();
    outfile << setw(25) << get_lattice_vector(i).get_y();
    outfile << setw(25) << get_lattice_vector(i).get_z() << endl;
  }
  outfile.close();
  return;
}

void lattice::read_lattice_vectors(const string & filename) {
  ifstream infile(filename.c_str());
  if (!infile.is_open()) {
    cout << error_by_name() << "Input file named " << filename << " does not exist in the working directory." << endl;
  }
  
  int nlines = 0;
  string temps;
  while (getline(infile, temps)) {
    if (temps == "") {
      continue;
    }
    nlines++;
  }


  infile.clear();
  infile.seekg(0);

  clear_lattice_vectors();
  threevector lattice_vector;
  double component;
  int i;
  for (i=0;i<nlines;i++) {
    infile >> component;
    lattice_vector.set_x(component);
    infile >> component;
    lattice_vector.set_y(component);
    infile >> component;
    lattice_vector.set_z(component);
    add_lattice_vector(lattice_vector);
  }
  
  return;

}

void lattice::seed_random_number_generator() const {
  srand ( time(NULL) );
  return;
}


double lattice::get_average_lattice_vector_separation() const {

  double avgsep = 0.0;
  int i, j;
  int n = get_lattice_vectors_size();
  threevector i_vec, j_vec, diff;
  int p = 0;

  for (i=0;i<n;i++) {
    i_vec = get_lattice_vector(i);

    j = 0;
    while (j<i) {
      j_vec = get_lattice_vector(j);
      diff = i_vec - j_vec;
      avgsep = avgsep + diff.mod();
      p = p + 1;
      j = j + 1;
    }
    
    
  }

  
  return avgsep/double(p);

}

////int main () {

////int size = 15;
////lattice silat("silicon",5.43);
////int temp = silat.generate_random_diamond_cubic(size,2e6);

////cout << silat.get_max_lattice_vector_mod() << endl;
////return 0;

////}





