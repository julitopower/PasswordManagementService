/**                                                                                                                                        
 * The MIT License (MIT)                                                                                                                   
 *                                                                                                                                         
 * Copyright (c) 2014 Julio Delgado                                                                                                        
                                                                                                                                           
 * Permission is hereby granted, free of charge, to any person obtaining a copy                                                            
 * of this software and associated documentation files (the "Software"), to deal                                                           
 * in the Software without restriction, including without limitation the rights                                                            
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell                                                               
 * copies of the Software, and to permit persons to whom the Software is                                                                   
 * furnished to do so, subject to the following conditions:                                                                                
 *                                                                                                                                         
 * The above copyright notice and this permission notice shall be included in all                                                          
 * copies or substantial portions of the Software.                                                                                         
 *                                                                                                                                         
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR                                                              
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,                                                                
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE                                                             
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                                                                  
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,                                                           
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE                                                           
 * SOFTWARE.                                                                                                                               
 **/

#include "Adder.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <sstream>
#include <iostream>

Adder::Adder(){}

int Adder::add(const std::string & json) const {
  using boost::property_tree::ptree;
  ptree tree;
  std::stringstream ss;
  ss << json;

  // Here goes the processing
  int acum = 0;
  try {
    read_json(ss, tree);
    BOOST_FOREACH(ptree::value_type & v , tree.get_child("numbers")) {
      acum += v.second.get_value<int>();
    }
  } catch(...) {
    return 0;
  }
  return acum;
}
