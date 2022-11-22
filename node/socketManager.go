package node

import (
	"errors"
	"net"
)

/*the message is built by the following protocol:
the protocol is built from 3 fields; the code field (1 byte), the length field (4 bytes) and the data field (length bytes; the max size of the data field is 2^32-1 bytes)


the code field:
the code field is a byte that represents the type of the message
the code field can be one of the following values:

0-100: responses from the server

	10 - the server is ready to receive a message
	20 - route response to the client (the server has found a route to the destination)
	50 - keep alive message from the server to the node
	100 - error message from the server

101-200: requests from the client
	150 - route request from the client to the server

201-255: requests from the node to the server
	210 - register to the server
	220 - keep alive response from the node to the server


the length field:
the length field is a 4 bytes integer that represents the length of the data field
meaning the length of the data field will be not more than 2^32-1 bytes (4,294,967,295 bytes)


the data field:
an array of bits that represents the data of the message
the dat field will be used in cases of route response, route request and connection request

*/

// a const for the ip address
const IP = "127.0.0.1"

// a function that gets a message struct and the socket and sends it to the server using the serializer function
func SendMessage(msg Message, socket *net.TCPConn) error {
	//serialize the message
	message, err := SerializeMessage(msg)
	if err != nil {
		return err
	}

	//send the message to the server
	_, err = socket.Write(message)
	if err != nil {
		return err
	}

	//return the error
	return nil
}

// a function that gets the socket and gets the response from the server using the deserializer function
func GetResponse(socket *net.TCPConn) (Message, error) {
	//create the buffer
	buffer := make([]byte, 1024)

	//get the response from the server
	_, err := socket.Read(buffer)
	if err != nil {
		return Message{}, err
	}

	//deserialize the message
	message, err := DeserializeMessage(buffer)
	if err != nil {
		return Message{}, err
	}

	//return the message
	return message, nil
}

// a function that handles the connection request
func HandleConnectionRequest(socket *net.TCPConn) error {
	//create the message struct
	msg := Message{
		Code:    210,
		Length:  0,
		Data:    []byte{},
		IsValid: true,
	}

	//send the message to the server
	err := SendMessage(msg, socket)
	if err != nil {
		return err
	}

	//get the response from the server
	response, err := GetResponse(socket)
	if err != nil {
		return err
	}

	//check if the response is valid
	if response.Code != 10 {
		return errors.New("the response is not valid")
	}

	//return the error
	return nil
}

// a function that Connects to the server
func ConnectToServer() (*net.TCPConn, error) {
	//create the address
	address, err := net.ResolveTCPAddr("tcp", IP+":8080")
	if err != nil {
		return nil, err
	}

	//create the socket
	socket, err := net.DialTCP("tcp", nil, address)
	if err != nil {
		return nil, err
	}

	//handle the connection request
	err = HandleConnectionRequest(socket)
	if err != nil {
		return nil, err
	}

	//return the socket
	return socket, nil
}
