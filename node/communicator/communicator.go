package communicator

import (
	"fmt"
	"node/deserializer"
	"node/serializer"
	"time"

	"net"
)

const SERVER string = "127.0.0.1:5432"

//create a data structure to hold up  an array of pairs of sockets (each socket can listen and send)

type Pair struct {
	//a pair of sockets
	socket1 net.Conn
	socket2 net.Conn
}
type SocketMap struct {
	//an array of pairs of sockets
	sockets []Pair
}

type Communicator struct {
	//a map of sockets
	socketMap SocketMap
	//socket to server
	serSock net.Conn
}

//when creating a new communicator, it will ask for the server for a CONNECTION_REQUEST and after it get approved it will create the data structre
func (communicator *Communicator) initServerConnection() bool {

	//empty data
	data := []byte{}
	//create a new serialized message
	serializedMessage := serializer.SerializedMessageToServer{
		Code:   serializer.CONNECTION_REQUEST,
		Length: 0,
		Data:   data,
	}
	//serialize the message
	serializedMessageBytes := serializer.SerializeToServer(serializedMessage)
	//send the message
	_, err := communicator.serSock.Write(serializedMessageBytes)
	if err != nil {
		panic(err)
	}

	//get the response
	//create a buffer
	buffer := make([]byte, 1024)
	//read the response
	_, err = communicator.serSock.Read(buffer)
	if err != nil {
		panic(err)
	}
	//deserialize the response
	deserializedMessage := deserializer.DeserializeFromServer(buffer)
	return deserializedMessage.Code == deserializer.CONNECTION_APPROVAL_RESPONSE



}

//keep alive function
func (communicator *Communicator) keepAlive() {
	//every 3 second print"keep alive"
	for {
		time.Sleep(3 * time.Second)
		fmt.Println("keep alive")
	}
}

// NewCommunicator each time a communicator is created, it creates a new socket map
func NewCommunicator(numOfConnectionRequestToServer int) *Communicator {
	communicator := Communicator{}

	//create a new socket to the server
	serSock, err := net.Dial("tcp", SERVER)
	if err != nil {
		panic(err)
	}
	communicator.serSock = serSock

	i := 0
	for i = 0; i < numOfConnectionRequestToServer; i++ {
		if communicator.initServerConnection() {
			break
		}
	}
	if i == numOfConnectionRequestToServer {
		panic("could not connect to server")
	}


	go communicator.keepAlive()
	return &communicator

}

// Delete distractor for the communicator
func (communicator *Communicator) Delete() {
	//close all sockets
	for _, pair := range communicator.socketMap.sockets {
		pair.socket1.Close()
		pair.socket2.Close()
	}

	//empty the socket map
	communicator.socketMap.sockets = []Pair{}

	//send a message to the server to the server to disconnect
	//empty data
	data := []byte{}
	//create a new serialized message
	serializedMessageBytes := serializer.SerializeToServer(serializer.SerializedMessageToServer{
		Code:   serializer.DISCONNECTION_REQUEST,
		Length: 0,
		Data:   data,
	})
	//send the message
	_, err := communicator.serSock.Write(serializedMessageBytes)
	if err != nil {
		panic(err)
	}
	//close the socket to the server
	communicator.serSock.Close()

}

//listen for new connections
func (communicator *Communicator) Listen() {
	//create a new socket
	socket, err := net.Listen("tcp", "127.0.0.1:5432")
	if err != nil {
		panic(err)
	}
	for {
		//accept a new connection
		conn, err := socket.Accept()
		if err != nil {
			panic(err)
		}
		//handle the new connection
		go communicator.handleNewConnection(conn)
	}
}

//a function that handles the communication between the two sockets in a pair (it listens to the first socket and sends the data to the second socket and vice versa)
func (communicator *Communicator) handleCommunication(pair Pair) {
	for {
		//create a buffer
		buffer := make([]byte, 1024)
		//read the response
		_, err := pair.socket2.Read(buffer)
		if err != nil {
			panic(err)
		}
		//deserialize the response
		deserializedMessage := deserializer.DeserializeFromNode(buffer)
		data := deserializedMessage.Data
		//send the data to the other node
		_, err = pair.socket1.Write(data)
		if err != nil {
			panic(err)
		}

		//swap the sockets
		pair.socket1, pair.socket2 = pair.socket2, pair.socket1
	}
}

//handle a new connection from a node/client
func (communicator *Communicator) handleNewConnection(socket net.Conn) {
	//when getting a new client deserialize the message and find the ip/port of the other node
	//create a buffer
	buffer := make([]byte, 1024)
	//read the response
	_, err := socket.Read(buffer)
	if err != nil {
		panic(err)
	}
	//deserialize the response
	deserializedMessage := deserializer.DeserializeFromNode(buffer)
	IP := deserializedMessage.IP
	Port := deserializedMessage.Port
	data := deserializedMessage.Data
	//create a new socket
	socket2, err := net.Dial("tcp", IP+":"+string(Port))
	if err != nil {
		panic(err)
	}
	//create a new pair
	pair := Pair{
		socket1: socket,
		socket2: socket2,
	}
	//add the pair to the socket map
	communicator.socketMap.sockets = append(communicator.socketMap.sockets, pair)
	//send the data to the other node
	_, err = socket2.Write(data)
	if err != nil {
		panic(err)
	}

	//handle the communication between the two sockets
	go communicator.handleCommunication(pair)

}




