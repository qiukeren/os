package main

import (
	"testing"
)

func TestFileMeta_ToBytes(t *testing.T) {
	var f = FileMeta{}
	if len(f.ToBytes()) != 92 {
		t.Errorf("file meta not 92")
	}
}

func TestPartHeader_ToBytes(t *testing.T) {
	v := &PartHeader{}
	if got := v.ToBytes(); len(got) != 12 {
		t.Errorf("PartHeader.ContentToBytes() = %v, want %v", len(got), 12)
	}
}
