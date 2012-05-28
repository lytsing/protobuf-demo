
Protobuf demo
======================

C++ server and Java client commumication with socket

Download and install protobuf
-------------

Go to http://code.google.com/p/protobuf/ download the latest updates version

    wget http://protobuf.googlecode.com/files/protobuf-2.4.1.tar.bz2
    tar xvf protobuf-2.4.1.tar.bz2
    cd protobuf-2.4.1/
    ./configure && make && make install

Normal, it installed in /usr/local

You need to export the environment variable, edit ~/.bashrc , add:

    export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
    export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig$PKG_CONFIG_PATH


If you use Ubuntu, it is very easy to install:

    sudo apt-get install libprotobuf-dev libprotobuf-java
    export CLASSPATH=$CLASSPACH:/usr/share/java/protobuf.jar

Compile
-------------

In unix* like system:

    export CLASSPATH=./lib/protobuf-java-2.4.1.jar:$CLASSPATH
    make

How to use
-------------

Open one terminal, start the server:

$ ./s

Open another terminal, run the client:

$ ./c

or

$ java TestPeople


Enjoy coding!

