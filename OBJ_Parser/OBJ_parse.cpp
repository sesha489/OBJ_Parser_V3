#include"OBJ_parse.h"

void OBJ_parse::Selection()
{
	cin>>selecOp;
	switch(selecOp){
		case 1:
			//numVert = getVertexCount();
			Menu();
			InitFile();
			//cout<<"Number of Vertices are: "<<numVert<<endl<<endl;
			Selection();
			break;
		case 2:
			Menu();
			//ConvertFile();
			ConvertFile_Ex();
			Selection();
			break;
		case 3:
			//CloseFile();
			break;
		default:
			Menu();
			cout<<"Not a valid option. Enter a valid option."<<endl<<endl;
			Selection();
	}
}

void OBJ_parse::Menu()
{
	selecOp=0;
	system("cls");
	cout<<"File opened successfully"<<fixed<<endl<<endl;
	cout<<"Read Me Important:"<<endl;
	cout<<"1. Must Initiate file before convertion."<<endl;
	cout<<"2. After initiate completes, console will provide a"<<endl;
	cout<<"   complete detail of the models present and their "<<endl;
	cout<<"   names, number of vertices, normals and faces."<<endl<<endl;
	cout<<"Type the option to execute it:"<<endl<<endl;

	cout<<"1)Initiate File."<<endl;
	cout<<"2)Convert file to .js."<<endl;
	cout<<"3)Exit."<<endl<<endl;
}

bool OBJ_parse::OpenFile(string fileName, string materialName)
{
	InFile.open(fileName.c_str());
	MatFile.open(materialName.c_str());
	if(InFile.is_open()&&MatFile.is_open()){
		//cout<<"File opened"<<fixed<<endl;
		return true;
	}else{
		//cout<<"Error opening"<<fixed<<endl;
		return false;
	}
}

int OBJ_parse::getVertexCount()
{
	string s;
	int count=0;
	InFile.clear();
	InFile.seekg(0, ios::beg);
	while(!InFile.eof()){
		getline(InFile, s);
		if(s[0]=='v'&&s[1]==' ')
			count++;
	}
	return count;
}

int OBJ_parse::getNormalCount()
{
	string s;
	int count=0;
	InFile.clear();
	InFile.seekg(0, ios::beg);
	while(!InFile.eof()){
		getline(InFile, s);
		if(s[0]=='v'&&s[1]=='n')
			count++;
	}
	return count;
}

int OBJ_parse::getFacesCount()
{
	string s;
	int count=0;
	InFile.clear();
	InFile.seekg(0, ios::beg);
	while(!InFile.eof()){
		getline(InFile, s);
		if(s[0]=='f')
			count++;
	}
	return count;
}

int OBJ_parse::getObjectCount()
{
	string s;
	int count=0;
	InFile.clear();
	InFile.seekg(0, ios::beg);
	while(!InFile.eof()){
		getline(InFile, s);
		if(s[0]=='o')
			count++;
	}
	return count;
}

void OBJ_parse::getVertices()
{
	numVert = getVertexCount();
	cout<<endl;
	cout<<"Number of Vertices              :"<<numVert<<endl;
	Vert = new Vec3[numVert];
	string s;
	int i=0;
	InFile.clear();
	InFile.seekg(0, ios::beg);

	while(!InFile.eof()){
		getline(InFile, s);
		if(s[0]=='v'&&s[1]==' '){
			std::istringstream str(s.substr(2));
			str>>Vert[i].x;str>>Vert[i].y;str>>Vert[i].z;
			i++;
		}
	}
	//for(int j=0; j<numVert; j++)
	//	cout<<Vert[j].x<<' '<<Vert[j].y<<' '<<Vert[j].z<<endl;
}

void OBJ_parse::getNormals()
{
	numNorm = getNormalCount();
	cout<<endl;
	cout<<"Number of Normals               :"<<numNorm<<endl;
	Norm = new Vec3[numNorm];
	string s;
	int i=0;
	InFile.clear();
	InFile.seekg(0, ios::beg);

	while(!InFile.eof()){
		getline(InFile, s);
		if(s[0]=='v'&&s[1]=='n'){
			std::istringstream str(s.substr(3));
			str>>Norm[i].x;str>>Norm[i].y;str>>Norm[i].z;
			i++;
		}
	}
	//for(int j=0; j<numNorm; j++)
	//	cout<<Norm[j].x<<' '<<Norm[j].y<<' '<<Norm[j].z<<endl;
}

void OBJ_parse::getFaces()
{
	numFace = getFacesCount();
	cout<<endl;
	cout<<"Number of Faces                 :"<<numFace<<endl;
	string s, temp;
	string *a, *b, *c;
	a = new string[numFace];
	b = new string[numFace];
	c = new string[numFace];
	VertIndices = new int[numFace*3];
	NormIndices = new int[numFace*3];
	int i,pos1,pos2;
	i = pos1 = pos2 = 0;
	InFile.clear();
	InFile.seekg(0, ios::beg);
	//cout.precision(6);

	while(!InFile.eof()){
		getline(InFile, s);
		if(s[0]=='f')
		{
			std::istringstream str(s.substr(2));
			str>>a[i];str>>b[i];str>>c[i];
			i++;
			//cout<<"Face   : "<<s<<endl;
		}
	}

	//for(int j=0; j<numFace; j++)
	//	cout<<a[j]<<','<<b[j]<<','<<c[j]<<endl;

	cout<<endl;
	for(int j=0; j<numFace; j++)
	{
		pos1 = a[j].find('/');
		temp = a[j].substr(pos1+1);
		pos2 = temp.find('/');
		std::istringstream str(a[j].substr(0,pos1));
		str>>VertIndices[j*3];
		std::istringstream str1(temp.substr(pos2+1));
		str1>>NormIndices[j*3];

		pos1 = b[j].find('/');
		temp = b[j].substr(pos1+1);
		pos2 = temp.find('/');
		std::istringstream str2(b[j].substr(0,pos1));
		str2>>VertIndices[(j*3)+1];
		std::istringstream str3(temp.substr(pos2+1));
		str3>>NormIndices[(j*3)+1];

		pos1 = c[j].find('/');
		temp = c[j].substr(pos1+1);
		pos2 = temp.find('/');
		std::istringstream str4(c[j].substr(0,pos1));
		str4>>VertIndices[(j*3)+2];
		std::istringstream str5(temp.substr(pos2+1));
		str5>>NormIndices[(j*3)+2];

		//cout<<VertIndices[j*3]<<','<<NormIndices[j*3]<<' ';
		//cout<<VertIndices[(j*3)+1]<<','<<NormIndices[(j*3)+1]<<' ';
		//cout<<VertIndices[(j*3)+2]<<','<<NormIndices[(j*3)+2]<<endl;
	}
}

void OBJ_parse::getObjects()
{
	numObjs = getObjectCount();
	cout<<endl;
	cout<<"Number of Objects :"<<numObjs<<endl<<endl;
	ObjName = new string[numObjs];
	string s;
	int i=0;
	InFile.clear();
	InFile.seekg(0, ios::beg);

	while(!InFile.eof()){
		getline(InFile, s);
		if(s[0]=='o'){
			std::istringstream str(s.substr(2));
			str>>ObjName[i];
			i++;
		}
	}
	for(int j=0; j<numObjs; j++)
		cout<<"Object"<<j+1<<": "<<ObjName[j]<<endl;
}

void OBJ_parse::InitFile()
{
	string s;
	Mat *ClrColl;

	int numColor, g;
	numColor = g = 0;
	MatFile.clear();
	MatFile.seekg(0, ios::beg);
	while (getline(MatFile, s)) {
		if (s[0] == 'n' && s[1] == 'e' && s[2] == 'w') {
			numColor++;
		}
	}
	ClrColl = new Mat[numColor];
	MatFile.clear();
	MatFile.seekg(0, ios::beg);
	while (getline(MatFile, s)) {
		if (s[0] == 'n' && s[1] == 'e' && s[2] == 'w') {
			std::istringstream str(s.substr(6));
			str >> ClrColl[g].MatName;
		}
		if (s[0] == 'K' && s[1] == 'd') {
			std::istringstream str(s.substr(2));
			str >> ClrColl[g].Clr.r; str >> ClrColl[g].Clr.g; str >> ClrColl[g].Clr.b;
			g++;
		}
	}

	numObjs = numVert = numNorm = numFace = 0;
	InFile.clear();
	InFile.seekg(0, ios::beg);
	while(getline(InFile, s)){
		if(s[0]=='o' && s[1]==' ')
			numObjs++;
	}

	int i, j, k, l;
	Object = new ObjectStruct[numObjs];
	for(int a=0; a<numObjs; a++)
	{
		Object[a].numObjVert = 0;
		Object[a].numObjNorm = 0;
		Object[a].numObjFace = 0;
	}
	i = 0;
	InFile.clear();
	InFile.seekg(0, ios::beg);
	while(getline(InFile, s)){
		if(s[0]=='o' && s[1]==' '){
			std::istringstream str(s.substr(2));
			str>>Object[i].ObjectName;
			i++;
		}
		if(s[0]=='v' && s[1]==' '){
			Object[i-1].numObjVert++;
		}
		if(s[0]=='v' && s[1]=='n'){
			Object[i-1].numObjNorm++;
		}
		if(s[0]=='f' && s[1]==' '){
			Object[i-1].numObjFace++;
		}
		if (s[0] == 'u' && s[1] == 's' && s[2] == 'e') {
			std::istringstream str(s.substr(6));
			str>>Object[i-1].ObjMatName;
		}
	}
	for (int a = 0; a < numObjs; a++)
	{
		for (int b = 0; b < numColor; b++) {
			if (Object[a].ObjMatName == ClrColl[b].MatName) {
				Object[a].MatClr = ClrColl[b].Clr;
			}
		}
	}

	//i = 0;
	i = j = k = l = 0;
	for(int a=0; a<numObjs; a++)
	{
		Object[a].Vertices = new Vec3[Object[a].numObjVert];
		Object[a].Normals  = new Vec3[Object[a].numObjNorm];
		Object[a].VertexIndices = new int[(Object[a].numObjFace)*3];
		Object[a].NormalIndices = new int[(Object[a].numObjFace)*3];
		Object[a].FaceP1 = new string[Object[a].numObjFace];
		Object[a].FaceP2 = new string[Object[a].numObjFace];
		Object[a].FaceP3 = new string[Object[a].numObjFace];
	}
	InFile.clear();
	InFile.seekg(0, ios::beg);
	while(getline(InFile, s)){
		if(s[0]=='o' && s[1]==' '){
			i++;
			j = k = l = 0;
		}
		if(s[0]=='v' && s[1]==' '){
			std::istringstream str(s.substr(2));
			str>>Object[i-1].Vertices[j].x;str>>Object[i-1].Vertices[j].y;str>>Object[i-1].Vertices[j].z;
			j++;
		}
		if(s[0]=='v' && s[1]=='n'){
			std::istringstream str(s.substr(2));
			str>>Object[i-1].Normals[k].x;str>>Object[i-1].Normals[k].y;str>>Object[i-1].Normals[k].z;
			k++;
		}
		if(s[0]=='f' && s[1]==' '){
			std::istringstream str(s.substr(2));
			str>>Object[i-1].FaceP1[l];str>>Object[i-1].FaceP2[l];str>>Object[i-1].FaceP3[l];
			l++;
		}
	}
	string temp;
	k = l = 0;
	for(i=0; i<numObjs; i++)
	{
		int PrevVertCount, PrevNormCount, TempI;
		PrevVertCount = PrevNormCount = 0;
		TempI = i;
		if(TempI>0)
		{
			for(TempI=i; TempI!=0; TempI--)
			{
				PrevVertCount = PrevVertCount + Object[TempI-1].numObjVert;
				PrevNormCount = PrevNormCount + Object[TempI-1].numObjNorm;
			}
		}

		for(j=0; j<Object[i].numObjFace; j++)
		{
			k = Object[i].FaceP1[j].find('/');
			temp = Object[i].FaceP1[j].substr(k+1);
			l = temp.find('/');
			std::istringstream str(Object[i].FaceP1[j].substr(0,k));
			str>>Object[i].VertexIndices[j*3];
			std::istringstream str1(temp.substr(l+1));
			str1>>Object[i].NormalIndices[j*3];
			Object[i].VertexIndices[j*3] = Object[i].VertexIndices[j*3] - PrevVertCount;
			Object[i].NormalIndices[j*3] = Object[i].NormalIndices[j*3] - PrevNormCount;

			k = Object[i].FaceP2[j].find('/');
			temp = Object[i].FaceP2[j].substr(k+1);
			l = temp.find('/');
			std::istringstream str2(Object[i].FaceP2[j].substr(0,k));
			str2>>Object[i].VertexIndices[(j*3)+1];
			std::istringstream str3(temp.substr(l+1));
			str3>>Object[i].NormalIndices[(j*3)+1];
			Object[i].VertexIndices[(j*3)+1] = Object[i].VertexIndices[(j*3)+1] - PrevVertCount;
			Object[i].NormalIndices[(j*3)+1] = Object[i].NormalIndices[(j*3)+1] - PrevNormCount;

			k = Object[i].FaceP3[j].find('/');
			temp = Object[i].FaceP3[j].substr(k+1);
			l = temp.find('/');
			std::istringstream str4(Object[i].FaceP3[j].substr(0,k));
			str4>>Object[i].VertexIndices[(j*3)+2];
			std::istringstream str5(temp.substr(l+1));
			str5>>Object[i].NormalIndices[(j*3)+2];
			Object[i].VertexIndices[(j*3)+2] = Object[i].VertexIndices[(j*3)+2] - PrevVertCount;
			Object[i].NormalIndices[(j*3)+2] = Object[i].NormalIndices[(j*3)+2] - PrevNormCount;
		}
	}

	for(int a=0; a<numObjs; a++)
		cout<<Object[a].ObjectName<<" "<<Object[a].numObjVert<<" "<<Object[a].numObjNorm<<" "<<Object[a].numObjFace<<" "<<Object[a].ObjMatName<<endl<<endl;
}

void OBJ_parse::ReadFile()
{
	long length;
	InFile.seekg(0, ios::end);
	length = InFile.tellg();
	InFile.seekg(0, ios::beg);
	cout<<"File size in bytes              : "<<dec<<length<<endl<<endl;
	cout<<"File contant as follows         : "<<endl;
	getObjects();
	getVertices();
	getNormals();
	getFaces();
}

void OBJ_parse::ConvertFile()
{
	ReadFile();
	ofstream outFile;
	outFile.open("Buffer.js");    //Use binary only to avoid 0x0D 0x0A problem

	cout<<"---------------Conversion started---------------"<<endl;
	
	outFile<<"var positions = ["<<fixed<<endl;
	/*for(int i=0;i<numVert;i++)
		outFile<<Vert[i].x<<", "<<Vert[i].y<<", "<<Vert[i].z<<","<<endl;
	outFile<<"];"<<endl<<endl;*/
	for(int i=0;i<(numFace*3);i++)
		outFile<<Vert[(VertIndices[i]-1)].x<<", "<<Vert[(VertIndices[i]-1)].y<<", "<<Vert[(VertIndices[i]-1)].z<<","<<endl;
	outFile<<"];"<<endl<<endl;

	outFile<<"const vertexNormals = ["<<endl;
	for(int i=0;i<(numFace*3);i++)
		outFile<<Norm[(NormIndices[i]-1)].x<<", "<<Norm[(NormIndices[i]-1)].y<<", "<<Norm[(NormIndices[i]-1)].z<<","<<endl;
	outFile<<"];"<<endl<<endl;

	outFile << "var faceColors = [1.0, 1.0, 1.0, 1.0]; "<<endl<<endl;
	outFile<<"const vertexCount = "<<(numFace*3)<<";"<<endl<<endl;

	outFile<<"const indices = ["<<endl;
	for(int i=0;i<numFace;i++)
	{
		//outFile<<(VertIndices[(i*3)]-1)<<", "<<(VertIndices[(i*3)+1]-1)<<", "<<(VertIndices[(i*3)+2]-1)<<","<<endl;
		outFile<<(i*3)<<", "<<((i*3)+1)<<", "<<((i*3)+2)<<","<<endl;
	}
	outFile<<"];"<<endl;

	outFile.close();
	cout<<endl;
	cout<<"---------------Conversion finished--------------"<<endl;
}

void OBJ_parse::ConvertFile_Ex()
{
	ofstream outFile;
	outFile.open("Buffer.js");    //Use binary only to avoid 0x0D 0x0A problem

	cout<<"---------------Conversion started---------------"<<endl;
	
	outFile<<"const objCount = "<<numObjs<<";"<<fixed<<endl<<endl;
	for(int x=0; x<numObjs; x++)
	{
		outFile<<"const positions"<<x+1<<" = ["<<endl;
		for(int i=0;i<(Object[x].numObjFace*3);i++)
		{
			outFile<<Object[x].Vertices[(Object[x].VertexIndices[i]-1)].x;
			outFile<<", "<<Object[x].Vertices[(Object[x].VertexIndices[i]-1)].y;
			outFile<<", "<<Object[x].Vertices[(Object[x].VertexIndices[i]-1)].z<<","<<endl;
		}
		outFile<<"];"<<endl<<endl;

		outFile<<"const vertexNormals"<<x+1<<" = ["<<endl;
		for(int i=0;i<(Object[x].numObjFace*3);i++)
		{
			outFile<<Object[x].Normals[(Object[x].NormalIndices[i]-1)].x;
			outFile<<", "<<Object[x].Normals[(Object[x].NormalIndices[i]-1)].y;
			outFile<<", "<<Object[x].Normals[(Object[x].NormalIndices[i]-1)].z<<","<<endl;
		}
		outFile<<"];"<<endl<<endl;

		outFile << "const faceColors" << x + 1 << " = [";
		outFile << Object[x].MatClr.r << ", ";
		outFile << Object[x].MatClr.g << ", ";
		outFile << Object[x].MatClr.b << ", 1.0];" << endl << endl;
		outFile<<"const vertexCount"<<x+1<<" = "<<(Object[x].numObjFace*3)<<";"<<endl<<endl;

		outFile<<"const indices"<<x+1<<" = ["<<endl;
		for(int i=0;i<Object[x].numObjFace;i++)
		{
			outFile<<(i*3)<<", "<<((i*3)+1)<<", "<<((i*3)+2)<<","<<endl;
		}
		outFile<<"];"<<endl<<endl;
	}
	outFile<<"const objDetails = ["<<endl;
	for(int x=0; x<numObjs;x++)
		outFile<<"positions"<<x+1<<", vertexNormals"<<x+1<<", faceColors"<<x+1<<", vertexCount"<<x+1<<", indices"<<x+1<<","<<endl;
	outFile<<"];"<<endl;

	outFile.close();
	cout<<endl;
	cout<<"---------------Conversion finished--------------"<<endl;
}

void OBJ_parse::CloseFile()
{
	InFile.close();
	MatFile.close();
	Object=NULL;
	cout<<"File Closed\n";
}