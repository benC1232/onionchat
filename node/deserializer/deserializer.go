package deserializer

import (
	"encoding/json"
)

// from the server codes
const (
	CONNECTION_APPROVAL_RESPONSE int = 10
	KEEP_ALIVE_RESPONSE          int = 50
	ERROR_RESPONSE               int = 100
)

//the protocol from other client/node

/*
the protocol is as follows:
length field (the length of the data field): 4 bytes
IP field: 4 bytes
port field: 2 bytes
data field: (undefined length)
*/

// when deserializing, it will return a struct with the above fields
type DeserializedMessageFromNode struct {
	length int
	IP     string
	Port   int
	Data   []byte
}

// the deserializer
func DeserializeFromNode(data []byte) DeserializedMessageFromNode {
	//get the length field
	length := int(data[0])<<24 + int(data[1])<<16 + int(data[2])<<8 + int(data[3])

	//get the ip field
	ip := string(data[4]) + "." + string(data[5]) + "." + string(data[6]) + "." + string(data[7])

	//get the port field
	port := int(data[8])<<8 + int(data[9])

	//get the data field
	dataField := data[10:]

	return DeserializedMessageFromNode{length, ip, port, dataField}
}

//the protocol from the server

/*
the protocol is as follows:
the code field: 1 byte (256 possible values)
length field (the length of the data field): 4 bytes
data field: (undefined length)

the data field is a json string
*/

// when deserializing, it will return a struct with the above fields
type DeserializedMessageFromServer struct {
	Code   int
	length int
	data   map[string]interface{}
}

// the deserializer
func DeserializeFromServer(data []byte) DeserializedMessageFromServer {
	//get the code field
	code := int(data[0])

	//get the length field
	length := int(data[1])<<24 + int(data[2])<<16 + int(data[3])<<8 + int(data[4])

	//get the data field
	dataField := data[5:]

	//unmarshal the data field
	var dataMap map[string]interface{}
	json.Unmarshal(dataField, &dataMap)

	return DeserializedMessageFromServer{code, length, dataMap}
}
