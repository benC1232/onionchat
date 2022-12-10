package communicator

import (
	"fmt"
	"node/deserializer"
	"node/serializer"
	"time"

	"net"
)

const SERVER string = "127.0.0.1:5432"

type Pair struct {
	socket1 net.Conn
	socket2 net.Conn
}
type SocketMap struct {
	sockets []Pair
}

type Communicator struct {
	socketMap SocketMap
	serSock   net.Conn
}

func (communicator *Communicator) initServerConnection() bool {

	data := []byte{}
	serializedMessage := serializer.SerializedMessageToServer{
		Code:   serializer.CONNECTION_REQUEST,
		Length: 0,
		Data:   data,
	}
	serializedMessageBytes := serializer.SerializeToServer(serializedMessage)
	_, err := communicator.serSock.Write(serializedMessageBytes)
	if err != nil {
		panic(err)
	}

	buffer := make([]byte, 1024)
	_, err = communicator.serSock.Read(buffer)
	if err != nil {
		panic(err)
	}
	deserializedMessage := deserializer.DeserializeFromServer(buffer)
	return deserializedMessage.Code == deserializer.CONNECTION_APPROVAL_RESPONSE

}

func (communicator *Communicator) keepAlive() {
	for {
		time.Sleep(3 * time.Second)
		fmt.Println("keep alive")
	}
}

func NewCommunicator(numOfConnectionRequestToServer int) *Communicator {
	communicator := Communicator{}

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

func (communicator *Communicator) Delete() {
	for _, pair := range communicator.socketMap.sockets {
		pair.socket1.Close()
		pair.socket2.Close()
	}

	communicator.socketMap.sockets = []Pair{}

	data := []byte{}
	serializedMessageBytes := serializer.SerializeToServer(serializer.SerializedMessageToServer{
		Code:   serializer.DISCONNECTION_REQUEST,
		Length: 0,
		Data:   data,
	})
	_, err := communicator.serSock.Write(serializedMessageBytes)
	if err != nil {
		panic(err)
	}
	communicator.serSock.Close()

}

func (communicator *Communicator) Listen() {
	socket, err := net.Listen("tcp", "127.0.0.1:5432")
	if err != nil {
		panic(err)
	}
	for {
		conn, err := socket.Accept()
		if err != nil {
			panic(err)
		}
		go communicator.handleNewConnection(conn)
	}
}

func (communicator *Communicator) handleCommunication(pair Pair) {
	for {
		buffer := make([]byte, 1024)
		_, err := pair.socket2.Read(buffer)
		if err != nil {
			panic(err)
		}
		deserializedMessage := deserializer.DeserializeFromNode(buffer)
		data := deserializedMessage.Data
		_, err = pair.socket1.Write(data)
		if err != nil {
			panic(err)
		}

		pair.socket1, pair.socket2 = pair.socket2, pair.socket1
	}
}

func (communicator *Communicator) handleNewConnection(socket net.Conn) {
	buffer := make([]byte, 1024)
	_, err := socket.Read(buffer)
	if err != nil {
		panic(err)
	}

	deserializedMessage := deserializer.DeserializeFromNode(buffer)
	IP := deserializedMessage.IP
	Port := deserializedMessage.Port
	data := deserializedMessage.Data

	socket2, err := net.Dial("tcp", IP+":"+string(Port))
	if err != nil {
		panic(err)
	}

	pair := Pair{
		socket1: socket,
		socket2: socket2,
	}

	communicator.socketMap.sockets = append(communicator.socketMap.sockets, pair)

	_, err = socket2.Write(data)
	if err != nil {
		panic(err)
	}

	go communicator.handleCommunication(pair)

}
