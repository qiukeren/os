package main

import "syscall"

func stat(outFile string) (stat, uid, gid, as, an, ms, mn, cs, cn uint64) {
	var err error
	var s = syscall.Stat_t{}
	err = syscall.Stat(outFile, &s)
	if err != nil {
		panic(err)
	}
	return uint64(s.Mode), uint64(s.Uid), uint64(s.Gid), uint64(s.Atimespec.Sec), uint64(s.Atimespec.Nsec), uint64(s.Mtimespec.Sec), uint64(s.Mtimespec.Nsec), uint64(s.Ctimespec.Sec), uint64(s.Ctimespec.Nsec)
}
