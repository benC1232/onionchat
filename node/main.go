package main

import "node/communicator"

func main() {

	//every time there is an error close the communicator and exit
	//create a new communicator
	communicator := communicator.NewCommunicator(3)
	go communicator.Listen()
	defer communicator.Delete()

}
