package main

import "node/communicator"

func main() {
	comm := communicator.NewCommunicator(1)
	comm.Listen()
	defer comm.Delete()
}
