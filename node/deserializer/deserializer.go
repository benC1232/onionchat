package deserializer

import (
	"encoding/json"
	"strconv"
)

const (
	CONNECTION_APPROVAL_RESPONSE int = 10
	KEEP_ALIVE_RESPONSE          int = 50
	ERROR_RESPONSE               int = 100
)

type DeserializedMessageFromNode struct {
	length int
	IP     string
	Port   int
	Data   []byte
}

func DeserializeFromNode(data []byte) DeserializedMessageFromNode {
	length := int(data[0])<<24 + int(data[1])<<16 + int(data[2])<<8 + int(data[3])

	ip := strconv.Itoa(int(data[4])) + "." +
		strconv.Itoa(int(data[5])) + "." +
		strconv.Itoa(int(data[6])) + "." +
		strconv.Itoa(int(data[7]))

	port := int(data[8])<<8 + int(data[9])

	dataField := data[10:]

	return DeserializedMessageFromNode{length, ip, port, dataField}
}

type DeserializedMessageFromServer struct {
	Code   int
	length int
	data   map[string]interface{}
}

func DeserializeFromServer(data []byte) DeserializedMessageFromServer {
	code := int(data[0])

	length := int(data[1])<<24 + int(data[2])<<16 + int(data[3])<<8 + int(data[4])

	dataField := data[5:]

	var dataMap map[string]interface{}
	json.Unmarshal(dataField, &dataMap)

	return DeserializedMessageFromServer{code, length, dataMap}
}
