
#include <cassert>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;


#include <Rcpp.h>


template <typename T>
struct osms
{
  typedef
  tree<
    pair<T,int>,
    null_type,
    less<pair<T,int> >,
    rb_tree_tag,
    tree_order_statistics_node_update>
  osms_impl;
  
  osms_impl impl;
  unsigned long int count;

  osms();
  void insert(const T&);
  T at(const int&) const;
};

template <typename T>
osms<T>::osms() : count(0) {}

template <typename T>
void osms<T>::insert(const T& val)
{
  impl.insert({val,count++});
}

template <typename T>
T osms<T>::at(const int& rank) const
{
  auto it = impl.find_by_order(rank);
  return std::get<0>(*it);
}


RCPP_MODULE(oss){
    using namespace Rcpp ;
    
    class_<osms<double> >("osms")
    // expose the default constructor
    .constructor()
    .method("insert",&osms<double>::insert)
    .method("at",&osms<double>::at)  
    ;
}











