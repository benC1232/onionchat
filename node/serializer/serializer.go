package serializer

// from the server codes
const (
	CONNECTION_REQUEST    int = 210
	DISCONNECTION_REQUEST int = 215
	KEEP_ALIVE_REQUEST    int = 220
)

//the protocol from other client/node

/*
the protocol is as follows:
length field (the length of the data field): 4 bytes
IP field: 4 bytes
port field: 2 bytes
data field: (undefined length)
*/

// the serializer will get a struct with the above fields and return a byte array
type SerializedMessageToNode struct {
	length int
	IP     string
	Port   int
	data   []byte
}

// the serializer
func SerializeToNode(serializedMessageToNode SerializedMessageToNode) []byte {
	//get the length field
	length := make([]byte, 4)
	length[0] = byte(serializedMessageToNode.length >> 24)
	length[1] = byte(serializedMessageToNode.length >> 16)
	length[2] = byte(serializedMessageToNode.length >> 8)
	length[3] = byte(serializedMessageToNode.length)

	//get the ip field
	ip := make([]byte, 4)
	ip[0] = byte(serializedMessageToNode.IP[0])
	ip[1] = byte(serializedMessageToNode.IP[1])
	ip[2] = byte(serializedMessageToNode.IP[2])
	ip[3] = byte(serializedMessageToNode.IP[3])

	//get the port field
	port := make([]byte, 2)
	port[0] = byte(serializedMessageToNode.Port >> 8)
	port[1] = byte(serializedMessageToNode.Port)

	//get the data field
	dataField := serializedMessageToNode.data

	//concatenate the fields
	serializedMessage := append(length, ip...)
	serializedMessage = append(serializedMessage, port...)
	serializedMessage = append(serializedMessage, dataField...)

	return serializedMessage
}

//the protocol from the server

/*
the protocol is as follows:
the code field: 1 byte (256 possible values)
length field (the length of the data field): 4 bytes
data field: (undefined length)

the data field is a json string
*/

// the serializer will get a struct with the above fields and return a byte array
type SerializedMessageToServer struct {
	code   int
	length int
	data   []byte
}

// the serializer
func SerializeToServer(serializedMessageToServer SerializedMessageToServer) []byte {
	//get the code field
	code := make([]byte, 1)
	code[0] = byte(serializedMessageToServer.code)

	//get the length field
	length := make([]byte, 4)
	length[0] = byte(serializedMessageToServer.length >> 24)
	length[1] = byte(serializedMessageToServer.length >> 16)
	length[2] = byte(serializedMessageToServer.length >> 8)
	length[3] = byte(serializedMessageToServer.length)

	//get the data field
	dataField := serializedMessageToServer.data

	//concatenate the fields
	serializedMessage := append(code, length...)
	serializedMessage = append(serializedMessage, dataField...)

	return serializedMessage
}