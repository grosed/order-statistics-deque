// -*- C++ -*-

// Copyright (C) 2005, 2006 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the terms
// of the GNU General Public License as published by the Free Software
// Foundation; either version 2, or (at your option) any later
// version.

// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this library; see the file COPYING.  If not, write to
// the Free Software Foundation, 59 Temple Place - Suite 330, Boston,
// MA 02111-1307, USA.

// As a special exception, you may use this file as part of a free
// software library without restriction.  Specifically, if other files
// instantiate templates or use macros or inline functions from this
// file, or you compile this file and link it with other files to
// produce an executable, this file does not by itself cause the
// resulting executable to be covered by the GNU General Public
// License.  This exception does not however invalidate any other
// reasons why the executable file might be covered by the GNU General
// Public License.

// Copyright (C) 2004 Ami Tavory and Vladimir Dreizin, IBM-HRL.

// Permission to use, copy, modify, sell, and distribute this software
// is hereby granted without fee, provided that the above copyright
// notice appears in all copies, and that both that copyright notice
// and this permission notice appear in supporting documentation. None
// of the above authors, nor IBM Haifa Research Laboratories, make any
// representation about the suitability of this software for any
// purpose. It is provided "as is" without express or implied
// warranty.

/**
 * @file tree_order_statistics_example.cpp
 * An example showing how to use functors for order-statistics
 *    in tree-based containers.
 */

/**
 * In some cases tree structure can be used for various purposes asides
 *    from storing entries by key order.
 *    This example shows how a tree-based container can be used for
 *    order-statistics, i.e., for determining the order of each key
 *     in the (ordered) sequence of keys stored within the container object.
 */

#include <cassert>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>


#include <iostream>

using namespace std;
//using namespace pb_ds;
//using namespace pb_ds;

using namespace __gnu_pbds;

// A red-black tree table storing ints and their order
// statistics. Note that since the tree uses
// tree_order_statistics_node_update as its update policy, then it
// includes its methods by_order and order_of_key.
typedef
tree<
  pair<double,int>,
  // int,
  // null_mapped_type,
  null_type,
  less<pair<double,int> >,
  // less<int>,
  rb_tree_tag,
  // This policy updates nodes' metadata for order statistics.
  tree_order_statistics_node_update>
set_t;

int main()
{
  // Insert some entries into s.
  int t {0};
  set_t s;
  s.insert({12,t++});
  s.insert({505,t++});
  s.insert({30,t++});
  s.insert({1000,t++});
  s.insert({10000,t++});
  s.insert({100,t++});
  


  std::cout << s.size() << std::endl;

  for(auto& v : s)
    {
      std::cout << get<0>(v) << " : " << get<1>(v) << std::endl;
    }


  std::cout << "*****************************************" << std::endl;
  
  s.insert({30,t++});

  for(auto& v : s)
    {
      std::cout << get<0>(v) << " : " << get<1>(v) << std::endl;
    }


  auto fred = s.find_by_order(2);
  std::cout << std::get<0>(*fred) << std::endl;

  
  
  return 0;


  /*
  
  
  // The order of the keys should be: 12, 30, 100, 505, 1000, 10000.
  assert(*s.find_by_order(0) == 12);
  assert(*s.find_by_order(1) == 30);
  assert(*s.find_by_order(2) == 100);
  assert(*s.find_by_order(3) == 505);
  assert(*s.find_by_order(4) == 1000);
  assert(*s.find_by_order(5) == 10000);
  assert(s.find_by_order(6) == s.end());



  
  // The order of the keys should be: 12, 30, 100, 505, 1000, 10000.
  assert(s.order_of_key(10) == 0);
  assert(s.order_of_key(12) == 0);
  assert(s.order_of_key(15) == 1);
  assert(s.order_of_key(30) == 1);
  assert(s.order_of_key(99) == 2);
  assert(s.order_of_key(100) == 2);
  assert(s.order_of_key(505) == 3);
  assert(s.order_of_key(1000) == 4);
  assert(s.order_of_key(10000) == 5);
  assert(s.order_of_key(9999999) == 6);

  // Erase an entry.
  s.erase(30);

  // The order of the keys should be: 12, 100, 505, 1000, 10000.
  assert(*s.find_by_order(0) == 12);
  assert(*s.find_by_order(1) == 100);
  assert(*s.find_by_order(2) == 505);
  assert(*s.find_by_order(3) == 1000);
  assert(*s.find_by_order(4) == 10000);
  assert(s.find_by_order(5) == s.end());

  // The order of the keys should be: 12, 100, 505, 1000, 10000.
  assert(s.order_of_key(10) == 0);
  assert(s.order_of_key(12) == 0);
  assert(s.order_of_key(100) == 1);
  assert(s.order_of_key(505) == 2);
  assert(s.order_of_key(707) == 3);
  assert(s.order_of_key(1000) == 3);
  assert(s.order_of_key(1001) == 4);
  assert(s.order_of_key(10000) == 4);
  assert(s.order_of_key(100000) == 5);
  assert(s.order_of_key(9999999) == 5);



  for(auto& v : s)
    {
      std::cout << v << std::endl;
    }

  std::cout << "***********************" << std::endl;
  

  std::cout << s.size() << std::endl;

  std::cout << "***********************" << std::endl;
  
  std::cout << s.order_of_key(9999) << std::endl;
  std::cout << s.order_of_key(10000) << std::endl;
  std::cout << s.order_of_key(10001) << std::endl;


  std::cout << "***********************" << std::endl;
  
  for(auto& v : s)
    {
      std::cout << v << std::endl;
    }

  std::cout << *s.lower_bound(11) << std::endl;
  


  */

  
  return 0;
}

