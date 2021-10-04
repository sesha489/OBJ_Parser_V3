#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
//#include<conio.h> //only for clear screen
using namespace std;

struct Vec3{
	float x, y, z;
};

struct CuColor
{
	float r, g, b;
};

struct Mat
{
	string MatName;
	CuColor Clr;
};

struct ObjectStruct{
	string ObjectName;
	string ObjMatName;
	int numObjVert;
	int numObjNorm;
	int numObjFace;

	int *VertexIndices;
	int *NormalIndices;

	Vec3 *Vertices;
	Vec3 *Normals;
	string *FaceP1;
	string *FaceP2;
	string *FaceP3;
	CuColor MatClr;
};

class OBJ_parse
{
	ifstream InFile;
	ifstream MatFile;
	ObjectStruct *Object;
private:
	int getVertexCount();
	int getNormalCount();
	int getFacesCount();
	int getObjectCount();

	void getVertices();
	void getNormals();
	void getFaces();
	void getObjects();
public:
	Vec3 *Vert;
	Vec3 *Norm;
	int *VertIndices;
	int *NormIndices;
	int numVert, numNorm, numFace, numObjs;
	string *ObjName;
	int selecOp;

	void Menu();
	void Selection();
	bool OpenFile(string fileName, string materialName);
	void ReadFile();
	void InitFile();
	void ConvertFile();
	void ConvertFile_Ex();
	void CloseFile();
};