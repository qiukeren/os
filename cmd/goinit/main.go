package main

import (
	"fmt"
	"github.com/u-root/u-root/pkg/libinit"
	"log"
	"os"
	"os/exec"
	"strconv"
	"syscall"
)

func main() {
	log.SetFlags(log.LstdFlags | log.Lshortfile)
	{
		var err error
		err = syscall.Mount("proc", "proc", "proc", 0, "")
		if err != nil {
			log.Println(err)
		}
		err = syscall.Mount("sys", "sys", "sysfs", 0, "")
		if err != nil {
			log.Println(err)
		}
		err = syscall.Mount("dev", "dev", "devtmpfs", 0, "")
		if err != nil {
			log.Println(err)
		}
	}

	for i := 1; i <= 7; i++ {
		go func(idx int) {
			tty(fmt.Sprintf("tty%d", idx), 38400)
		}(i)
	}

	libinit.WaitOrphans()
}

func tty(port string, baud int) {
	envs := os.Environ()

	cmd := exec.Command("/mgetty", port, strconv.Itoa(baud))
	cmd.Env = envs

	//debug("running %v", cmd)
	if err := cmd.Start(); err != nil {
		log.Printf("Error starting %v: %v", port, err)
		return
	}
	if err := cmd.Process.Release(); err != nil {
		log.Printf("Error releasing process %v:%v", port, err)
	}
	// stop after first valid command
	return

}
