# 用于存放第三方库压缩文件

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


