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

#include "MapStorage.hpp"
#include <openssl/evp.h>
#include <iostream>

static std::string encrypt(const std::string text, const std::string key);
static std::string decrypt(const std::string text, const std::string key);

MapStorage::MapStorage() :  _serializer(),
			    _map(_serializer.read()) {}

void MapStorage::put(const std::string & key, const std::string & value) {
  (*_map)[encrypt(key, "holacaracola")] = encrypt(value, "holacaracola");
  _serializer.write(*_map);
}

std::string MapStorage::get(const std::string & key) {
  return decrypt((*_map)[encrypt(key, "holacaracola")], "holacaracola");
}

std::list<std::string> MapStorage::searchKeys(const std::string &  pattern) {
  std::list<std::string> results;
  return results;
}

MapStorage::~MapStorage() {
  delete _map;
}

// Encrypt/Decrypt functions here

static std::string encrypt(const std::string text, const std::string key) {
  EVP_CIPHER_CTX ctx;
  EVP_CIPHER_CTX_init(&ctx);

  int outlen, tmplen;
  unsigned char * outbuf = new unsigned char[text.length() * 100];
  const unsigned char iv[] = {'i','e','n','c','t','y','e','k'};
  const unsigned char * k = reinterpret_cast<const unsigned char*>(key.data());
  const unsigned char * in = reinterpret_cast<const unsigned char*>(text.data());
  EVP_EncryptInit_ex(&ctx, EVP_bf_cbc(), NULL, k, iv);

  EVP_EncryptUpdate(&ctx, outbuf, &outlen, in, text.length());
  EVP_EncryptFinal_ex(&ctx, outbuf + outlen, &tmplen);
  outlen += tmplen;
  EVP_CIPHER_CTX_cleanup(&ctx);
  std::string s(reinterpret_cast<const char*>(outbuf), outlen);
  std::cout << s << std::endl;
  return s;
}

static std::string decrypt(const std::string text, const std::string key) {
  EVP_CIPHER_CTX ctx;
  EVP_CIPHER_CTX_init(&ctx);

  int outlen, tmplen;
  unsigned char * outbuf = new unsigned char[text.length() * 100];
  const unsigned char iv[] = {'i','e','n','c','t','y','e','k'};
  const unsigned char * k = reinterpret_cast<const unsigned char*>(key.data());
  const unsigned char * in = reinterpret_cast<const unsigned char*>(text.data());
  EVP_DecryptInit_ex(&ctx, EVP_bf_cbc(), NULL, k, iv);

  EVP_DecryptUpdate(&ctx, outbuf, &outlen, in, text.length());
  EVP_DecryptFinal_ex(&ctx, outbuf + outlen, &tmplen);
  outlen += tmplen;
  EVP_CIPHER_CTX_cleanup(&ctx);
  std::string s(reinterpret_cast<const char*>(outbuf), outlen);
  std::cout << s << std::endl;
  return s;
}
