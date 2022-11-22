package node

/*
the followin code is a library code that only deserialize the msg from the server:
the message is built by the following protocol:
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

//importing only the needed packages
import (
	"encoding/binary"
	"errors"
)

// the struct that represents the message
type Message struct {
	Code    byte
	Length  uint32
	Data    []byte
	IsValid bool
}

// the function that deserialize the message
func DeserializeMessage(msg []byte) (Message, error) {
	//check if the message is valid
	if len(msg) < 5 {
		return Message{}, errors.New("the message is not valid")
	}

	//create the message struct
	message := Message{}

	//get the code
	message.Code = msg[0]

	//get the length
	message.Length = binary.BigEndian.Uint32(msg[1:5])

	//get the data
	message.Data = msg[5:]

	//check if the message is valid
	if message.Length != uint32(len(message.Data)) {
		return Message{}, errors.New("the message is not valid")
	}

	//set the message as valid
	message.IsValid = true

	//return the message
	return message, nil
}
