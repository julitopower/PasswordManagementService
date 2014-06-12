/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Julio Delgado
 *
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

#include "MapSerializer.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>

namespace storage {

  static const std::string & FILE_PATH = "/tmp/map";

  void MapSerializer::write(const std::map<std::vector<char>, std::vector<char> > &  map) const {
    std::ofstream file;
    file.open(FILE_PATH, std::fstream::out | std::fstream::binary);
    for(auto entry = map.begin() ; entry != map.end() ; ++entry) {
      char size = entry->first.size();
      std::cout << "Size of field: " << size << std::endl;
      file.write(&size, 1);
      file.write((char *)(entry->first.data()), (int)size);
      
      size = entry->second.size();
      std::cout << "Size of field: " << size << std::endl;
      file.write(&size, 1);
      file.write((char *)(entry->second.data()), (int)size);
    }
    file.close();
  }

  std::map<std::vector<char>, std::vector<char> > * MapSerializer::read() const {
    auto map = new std::map<std::vector<char>, std::vector<char> >();

    std::ifstream file;
    file.open(FILE_PATH, std::fstream::in | std::fstream::binary);

    if(!file.is_open()) return map;
    while(!file.eof()) {
      char size;
      file.read(&size,1);
      if(!file) return map;

      std::cout << "Reading Key " << (int)size << std::endl;
      char * key = new char[size];
      file.read(key, size);
      std::vector<char> keyVector(key, key + (int)size);

      file.read(&size,1);
      std::cout << "Reading Value " << (int)size << std::endl;
      char * value = new char[size];
      file.read(value, size);
      std::vector<char> valueVector(value, value + (int)size);
      (*map)[keyVector] = valueVector;
      delete[] key;
      delete[] value;
    }
    file.close();
    return map;
  }

}
