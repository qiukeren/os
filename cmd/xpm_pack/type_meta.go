package main

type MetaContent struct {
	Header PartHeader

	Version Version

	Name        [32]byte
	Description []byte
}

func (f *MetaContent) GetHeader() PartHeader {
	return f.Header
}

func (f *MetaContent) HeaderToBytes() []byte {
	f.Header.Type = TypeMeta
	f.Header.Size = uint64(len(f.ContentToBytes()))
	return f.Header.ToBytes()
}

func (f *MetaContent) ContentToBytes() []byte {

	var c []byte
	//log.Printf("%#v", f.Name[0:32])
	//log.Printf("% 0x", f.Name)
	c = append(c, f.Version.ToBytes()...)
	c = append(c, f.Name[0:32]...)
	c = append(c, toBytes32(uint32(len(f.Description)))...)
	c = append(c, f.Description...)
	//log.Printf("% 0x", c)
	return c
}
