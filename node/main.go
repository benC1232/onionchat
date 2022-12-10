package main

import "node/communicator"

func main() {
	communicator := communicator.NewCommunicator(1)
	go communicator.Listen()
	defer communicator.Delete()

}
