package main

import "syscall"

func stat(outFile string) (stat, uid, gid, as, an, ms, mn, cs, cn uint64) {
	var err error
	var s = syscall.Stat_t{}
	err = syscall.Stat(outFile, &s)
	if err != nil {
		panic(err)
	}
	return uint64(s.Mode), uint64(s.Uid), uint64(s.Gid), uint64(s.Atim.Sec), uint64(s.Atim.Nsec), uint64(s.Mtim.Sec), uint64(s.Mtim.Nsec), uint64(s.Ctim.Sec), uint64(s.Ctim.Nsec)
}
