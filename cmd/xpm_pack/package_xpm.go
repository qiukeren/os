package main

import (
	"io/ioutil"
	"log"
	"os"
	"path"
	"path/filepath"

	"gopkg.in/yaml.v2"
)

const packageName = "package.yaml"

type XpmPackageMeta struct {
	File   string `json:"file"`
	Target string `json:"target"`
}

type Build struct {
	Project string           `json:"project"`
	Scripts []string         `json:"scripts"`
	Files   []XpmPackageMeta `json:"files"`
}

func main() {
	log.SetFlags(log.Lshortfile | log.LstdFlags)
	err := filepath.Walk(".", func(pathStr string, info os.FileInfo, err error) error {
		if err != nil {
			return err
		}
		if info.IsDir() {
			return nil
		}
		if path.Base(pathStr) != packageName {
			return nil
		}
		buildPack(pathStr)
		return nil
	})
	if err != nil {
		log.Println(err)
	}
}

func buildPack(pathStr string) {
	var dir = path.Dir(pathStr)
	var err error
	var buildFile []byte
	buildFile, err = ioutil.ReadFile(pathStr)
	if err != nil {
		log.Println(err)
		return
	}
	var b = Build{}
	err = yaml.Unmarshal(buildFile, &b)
	if err != nil {
		log.Println("error: %v", err)
		return
	}

	var xpmPackage = XpmPackage{}

	// var outBuffer = bytes.Buffer{}
	// table := tablewriter.NewWriter(&outBuffer)
	// table.SetHeader([]string{"Project", "FileName", "Target", "Size"})

	meta := MetaContent{
		Version: Version{MajorVersion: 0xFFFFFFFF, MinorVersion: 0xEEEEEEEE, Revision: 0xAAAAAAAA},
	}
	copy(meta.Name[:], "project_name")
	meta.Description = []byte("project description? asiofuasiodfua")

	xpmPackage.Contents = append(xpmPackage.Contents, &meta)

	for _, file := range b.Files {
		var sourceFile = path.Join(dir, file.File)
		var targetFile = path.Join("target", file.Target)

		var f = FileContent{}
		f.AddFile(sourceFile, targetFile)

		xpmPackage.Contents = append(
			xpmPackage.Contents,
			&f,
		)
	}
	//Pretty(xpmPackage.ToBytes(), os.Stdout)

	ioutil.WriteFile("test.xpm", xpmPackage.ToBytes(), 0644)
}

func Size(f string) int64 {
	s, _ := os.Stat(f)
	if s == nil {
		return 0
	}
	return s.Size()
}
