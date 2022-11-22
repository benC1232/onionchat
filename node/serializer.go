package node

//serializer.go

import (
	"encoding/binary"
	"errors"
)

func SerializeMessage(msg Message) ([]byte, error) {
	//check if the message is valid
	if !msg.IsValid {
		return []byte{}, errors.New("the message is not valid")
	}

	//create the byte array
	message := make([]byte, 5+msg.Length)

	//set the code
	message[0] = msg.Code

	//set the length
	binary.BigEndian.PutUint32(message[1:5], msg.Length)

	//set the data
	copy(message[5:], msg.Data)

	//return the message
	return message, nil
}
