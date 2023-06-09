package communicator

import (
	"bytes"
	"encoding/binary"
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"net"
	"node/deserializer"
	"node/serializer"
	"os"
	"strconv"
	"time"
)

const SERVER string = "127.0.0.1:60005"

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
type Settings struct {
	Ip          string `json:"server_ip"`
	Server_port int    `json:"server_port"`
	Port        int    `json:"proxy_port"`
}
type ServerInfo struct {
	Port int
}

func (communicator *Communicator) initServerConnection() bool {
	jsonFile, err := os.Open("settings.json")
	if err != nil {
		fmt.Println(err)
	}
	byteValue, _ := ioutil.ReadAll(jsonFile)
	var settings Settings
	err = json.Unmarshal(byteValue, &settings)
	if err != nil {
		fmt.Println(err)
	}
	InfoObj := ServerInfo{Port: settings.Port}
	info, err := json.Marshal(InfoObj)

	data := info
	serializedMessage := serializer.SerializedMessageToServer{
		Code:   serializer.CONNECTION_REQUEST,
		Length: len(data),
		Data:   data,
	}
	serializedMessageBytes := serializer.SerializeToServer(serializedMessage)
	_, err = communicator.serSock.Write(serializedMessageBytes)
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
		msg := 220
		buff := new(bytes.Buffer)
		err := binary.Write(buff, binary.LittleEndian, uint16(msg))
		checkError(err)
		_, err = communicator.serSock.Write(buff.Bytes())
		checkError(err)
		reply := make([]byte, 1024)
		_, err = communicator.serSock.Read(reply)
		checkError(err)
		fmt.Println("keepalive succesful")
		time.Sleep(120 * time.Second)
	}
}

func NewCommunicator() *Communicator {
	communicator := Communicator{}

	serSock, err := net.Dial("tcp", SERVER)
	if err != nil {
		panic(err)
	}
	communicator.serSock = serSock

	communicator.initServerConnection()

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
	socket, err := net.Listen("tcp", "127.0.0.1:8686")
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

	socket2, err := net.Dial("tcp", IP+":"+strconv.Itoa(Port))
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

func checkError(err error) {

	if err != nil {
		log.Fatal(err)
	}
}
