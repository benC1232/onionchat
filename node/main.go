package main

import "node/communicator"

func main() {
	communicator := communicator.NewCommunicator(1)
	communicator.Listen()
	defer communicator.Delete()

}
