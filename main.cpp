/*
  main.cpp
  Convert .ltb to .x files
  
  written by Perez on 07-01-2013
  Copyright (c) 2013 Perezhk's Blog. All Rights reserved.
*/

#include "stdafx.h"
#include "ltb_file.h"

using namespace std;

uint ModelVersion, PieceNum;
uint16 StringLength;
uint Length;
float Radius;
uint VertexNum, FaceNum;
uint Type;
char* PieceName;

uint flag = 0;

vector<Vector3D> PieceVertex;
vector<Vector3D> PieceNormal;
vector<Face> PieceFace;
vector<Vector2D> TextureCoord;
Vector3D vector3;
Vector2D vector2;
Face face;

LtbHeader ltbheader;
LtbInfo ltbinfo;

fstream reader;
ofstream writer;

int LTSkip(int i) {
	reader.seekg((int)reader.tellg() + i);
}

int LTRead(LtbHeader &mem) {
	reader.read((char*)&mem, sizeof(mem));
}

int LTRead(LtbInfo &mem) {
	reader.read((char*)&mem, sizeof(mem));
}

int LTRead(uint &mem) {
	reader.read((char*)&mem, sizeof(mem));
}

int LTRead(uint16 &mem) {
	reader.read((char*)&mem, sizeof(mem));
}

int LTRead(float &mem) {
	reader.read((char*)&mem, sizeof(mem));
}

int LTRead(Vector3D &mem) {
	reader.read((char*)&mem, sizeof(mem));
}

int LTRead(Vector2D &mem) {
	reader.read((char*)&mem, sizeof(mem));
}

int LTRead(Face &mem) {
	reader.read((char*)&mem, sizeof(mem));
}

int LTRead(char* mem, uint len) {
	reader.read(mem, len);
}

int ExportX(char* path, uint i) {
	if (i == 0) {
		writer << "xof 0303txt 0032" << endl;
		writer << fixed << setprecision(8) << endl;
	}
	writer << "Mesh ";
	writer.write(PieceName, StringLength);
	writer << " {" << endl;
	writer << VertexNum << ";" << endl;
	for (int i=0;i < VertexNum;i++) {
		if (i == VertexNum-1)
			writer << PieceVertex[i].x << ";" << PieceVertex[i].y << ";" << PieceVertex[i].z << ";;" << endl;
		else
			writer << PieceVertex[i].x << ";" << PieceVertex[i].y << ";" << PieceVertex[i].z << ";," << endl;
	}
	writer << FaceNum << ";" << endl;
	for (int n=0;n < FaceNum;n++) {
		if (n == FaceNum-1)
			writer << "3;" << PieceFace[n].x << ";" << PieceFace[n].y << ";" << PieceFace[n].z << ";;" << endl;
		else
			writer << "3;" << PieceFace[n].x << ";" << PieceFace[n].y << ";" << PieceFace[n].z << ";," << endl;
	}
	writer << "MeshNormals {" << endl;
	writer << VertexNum << ";" << endl;
	for (int i=0;i < VertexNum;i++) {
		if (i == VertexNum-1)
			writer << PieceNormal[i].x << ";" << PieceNormal[i].y << ";" << PieceNormal[i].z << ";;" << endl;
		else
			writer << PieceNormal[i].x << ";" << PieceNormal[i].y << ";" << PieceNormal[i].z << ";," << endl;
	}
	writer << FaceNum << ";" << endl;
	for (int n=0;n < FaceNum;n++) {
		if (n == FaceNum-1)
			writer << "3;" << PieceFace[n].x << ";" << PieceFace[n].y << ";" << PieceFace[n].z << ";;" << endl;
		else
			writer << "3;" << PieceFace[n].x << ";" << PieceFace[n].y << ";" << PieceFace[n].z << ";," << endl;
	}
	writer << "}" << endl;
	writer << "MeshTextureCoords {" << endl;
	writer << VertexNum << ";" << endl;
	for (int i=0;i < VertexNum;i++) {
		if (i == VertexNum-1)
			writer << TextureCoord[i].x << ";" << TextureCoord[i].y << ";;" << endl;
		else
			writer << TextureCoord[i].x << ";" << TextureCoord[i].y << ";" << endl;
	}
	writer << "}" << endl;
	writer << "}" << endl;
}

int ImportLTB(char* path, char* wpath) {
	reader.open(path, ios::binary | ios::in);
	writer.open(wpath, ios::trunc);
	
	if (!reader)
		return 1;
	if (!writer)
		return 1;
		
	LTRead(ltbheader);
	LTRead(ModelVersion);
	LTRead(ltbinfo);
	LTRead(StringLength);
	LTRead(Radius);
	LTSkip(4);
	LTRead(PieceNum);
	for (int i=0;i < PieceNum;i++) {
		flag = 0;
		PieceVertex.clear();
		PieceNormal.clear();
		PieceFace.clear();
		TextureCoord.clear();
		
		LTRead(StringLength);
		PieceName = new char[StringLength+1];
		LTRead(PieceName, StringLength);
		LTSkip(45);
		LTRead(Length);
		LTRead(VertexNum);
		LTRead(FaceNum);
		LTRead(Type);
		
		LTSkip(22);
		if (Type == 1 && ltbinfo.m_nKeyFrames > 0) {
			LTSkip(2);
			flag += 34;
		}
		else if (Type == 1)
			flag += 26;
		else if (Type == 4)
			flag += 22;
		else
			return 1;
		for (int i=0;i < VertexNum;i++) {
			LTRead(vector3);
			PieceVertex.push_back(vector3);
			if (Type == 4)
				LTSkip(12);
			LTRead(vector3);
			PieceNormal.push_back(vector3);
			LTRead(vector2);
			TextureCoord.push_back(vector2);
			if (Type == 1)
				flag += 32;
			else if (Type == 4)
				flag += 44;
		}
		for (int i=0;i < FaceNum;i++) {
			LTRead(face);
			PieceFace.push_back(face);
			flag += 6;
		}
		ExportX(wpath, i);
		LTSkip(Length - flag);
	}
	
	reader.close();
	
	return 0;
}

int main(int argc, char *argv[]) {
	if (argc == 1)
		return 1;
	if (argc != 3)
		return 1;
	ImportLTB(argv[1], argv[2]);
	return 0;
}
