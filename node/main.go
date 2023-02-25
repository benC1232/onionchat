package main

import "node/communicator"

func main() {
	comm := communicator.NewCommunicator()
	comm.Listen()
	defer comm.Delete()
}
