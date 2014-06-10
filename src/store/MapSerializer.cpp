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

namespace storage {

  static const std::string & FILE_PATH = "/tmp/map";

  void MapSerializer::write(const std::map<std::string, std::string> &  map) const {
    std::ofstream file;
    file.open(FILE_PATH, std::fstream::out | std::fstream::app);
    for(auto entry = map.begin() ; entry != map.end() ; ++entry) {
      file << entry->first << std::endl;
      file << entry->second << std::endl;
    }
    file.close();
  }

  std::map<std::string, std::string> * MapSerializer::read() const {
    auto map = new std::map<std::string, std::string>();

    std::ifstream file;
    file.open(FILE_PATH, std::fstream::in);
    std::string key, value;
    while(getline(file, key)) {
      getline(file, value);
      (*map)[key] = value;
    }
    return map;
  }

}
