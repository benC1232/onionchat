package communicator

import (
	"net"
	"node/deserializer"
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
}

// each time a communicator is created, it creates a new socket map
func NewCommunicator() *Communicator {
	return &Communicator{SocketMap{[]Pair{}}}
}

// a infinite loop that listens for new connections, when it gets the first message it will deserialize and get the dest ip from the deserialized message, then it will open a socket to the ip inside the message and register the two sockets in the data structre

func (communicator *Communicator) Listen() {
	//listen for new connections
	sock, err := net.Listen("tcp", "127.0.0.1:5432")
	if err != nil {
		panic(err)
	}
	defer sock.Close()

	for {
		//accept new connections
		conn, err := sock.Accept()
		if err != nil {
			panic(err)
		}

		//get the first message
		data := make([]byte, 1024)
		_, err = conn.Read(data)
		if err != nil {
			panic(err)
		}

		//deserialize the message
		deserializedMessage := deserializer.DeserializeFromNode(data)

		//get the dest ip from the deserialized message
		destIP := deserializedMessage.IP
		//get the dest port from the deserialized message
		destPort := deserializedMessage.Port

		//open a socket to the dest ip
		destConn, err := net.Dial("tcp", destIP+":"+string(destPort))
		if err != nil {
			panic(err)
		}

		//register the two sockets in the data structure
		communicator.socketMap.sockets = append(communicator.socketMap.sockets, Pair{conn, destConn})

		//start a new thread to listen for messages from the dest ip and start a conversation
	}

}
