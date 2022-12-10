package serializer

const (
	CONNECTION_REQUEST    int = 210
	DISCONNECTION_REQUEST int = 215
	KEEP_ALIVE_REQUEST    int = 220
)

type SerializedMessageToNode struct {
	length int
	IP     string
	Port   int
	data   []byte
}

func SerializeToNode(serializedMessageToNode SerializedMessageToNode) []byte {
	length := make([]byte, 4)
	length[0] = byte(serializedMessageToNode.length >> 24)
	length[1] = byte(serializedMessageToNode.length >> 16)
	length[2] = byte(serializedMessageToNode.length >> 8)
	length[3] = byte(serializedMessageToNode.length)

	ip := make([]byte, 4)
	ip[0] = byte(serializedMessageToNode.IP[0])
	ip[1] = byte(serializedMessageToNode.IP[1])
	ip[2] = byte(serializedMessageToNode.IP[2])
	ip[3] = byte(serializedMessageToNode.IP[3])

	port := make([]byte, 2)
	port[0] = byte(serializedMessageToNode.Port >> 8)
	port[1] = byte(serializedMessageToNode.Port)

	dataField := serializedMessageToNode.data

	serializedMessage := append(length, ip...)
	serializedMessage = append(serializedMessage, port...)
	serializedMessage = append(serializedMessage, dataField...)

	return serializedMessage
}

type SerializedMessageToServer struct {
	Code   int
	Length int
	Data   []byte
}

func SerializeToServer(serializedMessageToServer SerializedMessageToServer) []byte {
	code := make([]byte, 1)
	code[0] = byte(serializedMessageToServer.Code)

	length := make([]byte, 4)
	length[0] = byte(serializedMessageToServer.Length >> 24)
	length[1] = byte(serializedMessageToServer.Length >> 16)
	length[2] = byte(serializedMessageToServer.Length >> 8)
	length[3] = byte(serializedMessageToServer.Length)

	dataField := serializedMessageToServer.Data

	serializedMessage := append(code, length...)
	serializedMessage = append(serializedMessage, dataField...)

	return serializedMessage
}
