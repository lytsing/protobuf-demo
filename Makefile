all:
	protoc --cpp_out=. demo.people.proto
	protoc --java_out=. demo.people.proto
	g++ -g -Wall server.cc demo.people.pb.cc -o s -lprotobuf
	g++ -g -Wall client.cc demo.people.pb.cc -o c -lprotobuf
	javac TestPeople.java com/example/tutorial/PersonProtos.java

clean:
	rm s c *~ *.class com demo.people.pb.cc demo.people.pb.h -rf
