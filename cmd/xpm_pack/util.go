package main

import "encoding/binary"

func toBytes32(a uint32) []byte {
	var buf = [4]byte{}
	binary.BigEndian.PutUint32(buf[0:4], a)
	return buf[0:4]
}

func toBytes64(a uint64) []byte {
	var buf = [8]byte{}
	binary.BigEndian.PutUint64(buf[0:8], a)
	return buf[0:8]
}
