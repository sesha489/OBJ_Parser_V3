#include"OBJ_parse.h"

void main()
{
	bool FileResult;
	FileResult=false;
	OBJ_parse Obj;
	string FileName, MaterialName;

	cout<<"OBJ Parser"<<endl;
	cout<<endl;
	cout<<"Enter file name: ";
	cin>>FileName;
	MaterialName = FileName+".mtl";
	FileName += ".obj";
	//cout<<endl;
	FileResult = Obj.OpenFile(FileName, MaterialName);
	cout<<endl;

	while(FileResult==false)
	{
		system("cls");
		cout<<"OBJ Parser"<<endl;
		cout<<endl;
		cout<<"Error on opening the file"<<fixed<<endl<<endl;
		cout<<"Enter file name: ";
		cin>>FileName;
		MaterialName = FileName + ".mtl";
		FileName += ".obj";
		cout<<endl;
		FileResult = Obj.OpenFile(FileName, MaterialName);
		cout<<endl;
	}
	
	Obj.Menu();
	Obj.Selection();
	//Obj.ReadFile();
	//cout<<endl;
	//Obj.ConvertFile();
	//cout<<endl;
	system("cls");
	Obj.CloseFile();
	std::cin.sync();
	std::cin.get();
}