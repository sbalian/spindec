// See Cluster.h for description.
// Seto Balian, Aug 22, 2014

#include "SpinDec/Cluster.h"
#include <algorithm>

namespace SpinDec
{

// Stolen from krishna222
// http://stackoverflow.com/questions/728972/finding-all-the-subsets-of-a-set
// Note: this method includes the empty set in its output!
// Sorting should be preserved TODO check
vector<UIntArray> Cluster::subsets(const UIntArray& v, const UInt size) const
{
  
  if(size==0) {
    return vector< UIntArray >(1);
  }
  
  // recursion
  vector< UIntArray > output = subsets(v,size-1);
  
  vector< UIntArray > temp(output);
  for(typeof(temp.begin()) it = temp.begin();
      it !=temp.end(); it++)
  {
   (*it).push_back(v[size-1]);
  }
  output.insert(output.end(), (temp).begin(), (temp).end());
  return output;
  
}

vector<UIntArray> Cluster::subsets(const UIntArray& v) const
{
  return subsets(v,v.size());
}

Cluster::Cluster(const UIntArray& labels)
{
  labels_ = labels;
}

Cluster::Cluster()
{
}

void Cluster::add(const UInt label)
{
  labels_.push_back(label);
  
  // sort
  std::sort (labels_.begin(), labels_.end());
  
}

bool Cluster::operator ==(const Cluster& rhs) const
{
  
  if (rhs.num_spins() != num_spins()) {
    return false;
  }
  
  // because always sorted ...
  for (UInt i=0;i<num_spins();i++) {
    if (labels_[i] != rhs.labels_[i]) {
      return false;
    }
  }
  
  // all ok
  return true;
  
}

UInt Cluster::num_spins() const
{
  return labels_.size();
}

UInt Cluster::get_label(const UInt index) const
{
  return labels_[index];
}

vector<Cluster> Cluster::subsets() const
{
  vector< UIntArray > all_subsets = subsets(labels_,labels_.size());
  vector< UIntArray > subsets_excluding_empty_set;
  
  for (UInt i = 0; i < all_subsets.size();i++) {
    UInt subset_size = all_subsets[i].size();
    if (subset_size == 0) {
      continue;
    } else {
        subsets_excluding_empty_set.push_back(all_subsets[i]);
    }
  }
  
  // output
  vector<Cluster> output;
  for (UInt i = 0;i<subsets_excluding_empty_set.size();i++) {
    output.push_back(Cluster(subsets_excluding_empty_set[i]));
  }
  return output;

}

vector<Cluster> Cluster::proper_subsets() const
{
  
  vector< UIntArray > all_subsets = subsets(labels_,labels_.size());
  vector< UIntArray > proper_subsets_excluding_empty_set;
  
  for (UInt i = 0; i < all_subsets.size();i++) {
    UInt subset_size = all_subsets[i].size();
   
    if (subset_size == 0) {
      continue;
    }
    
    if (subset_size == num_spins()) {
      continue;
    }
    
    // else
    proper_subsets_excluding_empty_set.push_back(all_subsets[i]);
    
  }
  
  // output
  vector<Cluster> output;
  for (UInt i = 0;i<proper_subsets_excluding_empty_set.size();i++) {
    output.push_back(Cluster(proper_subsets_excluding_empty_set[i]));
  }
  return output;
  
}


std::ostream& operator<<(std::ostream& os,
    Cluster const & cluster)
{

  // To restore formatting later
  std::ios::fmtflags f( std::cout.flags() );
  
  for (UInt i=0;i<cluster.num_spins();i++) {
    os << cluster.get_label(i) << "\t";
  }
  os << std::endl;
  
  // Restore formatting
  std::cout.flags( f );
  
  return os;
  
}

} // namespace SpinDec

