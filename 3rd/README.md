# 用于存放第三方库压缩文件
## 解析XML
* **rapidxml-1.13.zip:  xml**

  ```c++
  typedef typename xml_node<Ch> value_type;
  typedef typename xml_node<Ch> &reference;
  typedef typename xml_node<Ch> *pointer;
  typedef std::ptrdiff_t difference_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  ```

  **改为**

  ```c++
  typedef xml_node<Ch> value_type;
  typedef xml_node<Ch> &reference;
  typedef xml_node<Ch> *pointer;
  typedef typename std::ptrdiff_t difference_type;
  typedef typename std::bidirectional_iterator_tag iterator_category;
  ```
## 网络库LIBEVENT
* **libevent-2.1.8-stable.tar**
  ```c++
  编辑 *.a 步骤
  1)  ./configure CPPFLAGS=-fPIC --disable-shared --disable-openss
  2)  make
  3)  cd ./.libs
  ```

## proto
* **protobuf-cpp-3.7.0-rc-2.zip**
  compile and install protocal
  ```c++
  ./configure --prefix=/usr/local/protobuf
  make
  make check
  make install
  ```

  protobuf install path
  ```c++
  usr/local/bin
  usr/local/lib
  usr/local/include 
  ```

  protobuf environment value  
  ```c++
  1) export LD_LIBRARY_PATH=/usr/local/lib

  2) vim /etc/ld.so.conf 
     add "/usr/local/lib"
  ```
