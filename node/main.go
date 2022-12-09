package node

import "node/communicator"

func main() {
	communicator := communicator.NewCommunicator()
	communicator.Listen()
}
