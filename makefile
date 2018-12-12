cc = g++
output = loader
src =./IGMainProject/IGPluginLoader/IGPluginManager.cpp \
	 ./IGMainProject/IGPluginLoader/IGPluginLoader.cpp \
	 ./IGMainProject/Dependencies/rapidxml/rapidxml.hpp \
   	 ./IGMainProject/Dependencies/rapidxml/rapidxml_iterators.hpp \
	 ./IGMainProject/Dependencies/rapidxml/rapidxml_print.hpp \
	 ./IGMainProject/Dependencies/rapidxml/rapidxml_utils.hpp \
	 ./IGMainProject/IGPluginLoader/IGDynamicLib.cpp
lib = -ldl
flag = -g -o

$(output): $(src)
	$(cc) $^ $(flag) $@ $(lib)
	mv loader ./Bin

clean:
	rm -rf $(output) ./Bin/loader
