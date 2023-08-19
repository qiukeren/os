package main

import (
	"crypto/md5"
	"encoding/hex"
	"io/ioutil"
)

type FileContent struct {
	Header PartHeader

	FileMeta FileMeta

	Md5     [32]byte
	NameLen uint32
	Name    []byte
	Size    uint64
	Content []byte
}

// FileMeta 60 bytes
type FileMeta struct {
	//total 4 * 3 = 12 Byte
	Stat uint32
	Uid  uint32
	Gid  uint32

	//total 8 * 6 = 48 Byte
	AtimSec  uint64
	AtimNsec uint64
	MtimSec  uint64
	MtimNsec uint64
	CtimSec  uint64
	CtimNsec uint64
}

func (f *FileMeta) ToBytes() []byte {
	var b []byte
	b = append(b, toBytes32(f.Stat)...)
	b = append(b, toBytes32(f.Uid)...)
	b = append(b, toBytes32(f.Gid)...)

	b = append(b, toBytes64(f.AtimSec)...)
	b = append(b, toBytes64(f.AtimNsec)...)
	b = append(b, toBytes64(f.MtimSec)...)
	b = append(b, toBytes64(f.MtimNsec)...)
	b = append(b, toBytes64(f.CtimSec)...)
	b = append(b, toBytes64(f.CtimNsec)...)

	return b
}

func (f *FileContent) AddFile(outFile string, name string) {

	c, err := ioutil.ReadFile(outFile)
	if err != nil {
		panic(err)
	}

	h := md5.New()
	h.Write(c)
	hash := []byte(hex.EncodeToString(h.Sum(nil)))
	copy(f.Md5[:], hash)

	f.Content = c
	f.Size = uint64(len(f.Content))

	f.Name = []byte(name)
	f.NameLen = uint32(len(f.Name))

	var stat, uid, gid, as, an, ms, mn, cs, cn = stat(outFile)
	f.meta(stat, uid, gid, as, an, ms, mn, cs, cn)
}

func (f *FileContent) meta(stat, uid, gid, as, an, ms, mn, cs, cn uint64) {

	f.FileMeta = FileMeta{
		Stat:     uint32(stat),
		Uid:      uint32(uid),
		Gid:      uint32(gid),
		AtimSec:  as,
		AtimNsec: an,
		MtimSec:  ms,
		MtimNsec: mn,
		CtimSec:  cs,
		CtimNsec: cn,
	}
}

func (f *FileContent) HeaderToBytes() []byte {
	f.Header.Type = TypeFile
	f.Header.Size = uint64(len(f.ContentToBytes()))
	return f.Header.ToBytes()
}

func (f *FileContent) ContentToBytes() []byte {
	var contentB = []byte{}

	contentB = append(contentB, f.FileMeta.ToBytes()...)

	contentB = append(contentB, f.Md5[:]...)
	contentB = append(contentB, toBytes32(f.NameLen)...)
	contentB = append(contentB, f.Name...)
	contentB = append(contentB, toBytes64(f.Size)...)
	contentB = append(contentB, f.Content...)

	var c []byte
	c = append(c, contentB...)

	return c
}

func (f *FileContent) GetHeader() PartHeader {
	return f.Header
}
