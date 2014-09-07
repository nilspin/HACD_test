// HACD_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;
using namespace HACD;

struct point
{
	float x;
	float y;
	float z;
	point() {}
	point(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
	bool operator==(const point &other) const
	{
		return (x==other.x && y==other.y && z==other.z);
	}
};

template<>
struct hash<point>
{
	size_t operator()(const point &p) const
	{
		return (((size_t)(p.x * 322433) ^ (size_t)(p.y * 781307) ^ (size_t)(p.z * 411833) ) % 193);
	}
};

int main()
{
	cout << "Hello";
	
	//initialize data structures
	ICHull* CHull = new ICHull();
	vector<Vec3<Real> > vertList;
	unordered_map<point,size_t> hashTable = {};
//	unordered_set<point> hashTable = {};
	//Add points into the hull
	point Points[9];
	Points[0].x = 1; Points[0].y = 1; Points[0].z = 1;
	Points[1].x = 1; Points[1].y = 1; Points[1].z = -1;
	Points[2].x = -1; Points[2].y = 1; Points[2].z = 1;
	Points[3].x = -1; Points[3].y = 1; Points[3].z = -1;
	Points[4].x = 1; Points[4].y = -1; Points[4].z = 1;
	Points[5].x = 1; Points[5].y = -1; Points[5].z = -1;
	Points[6].x = -1; Points[6].y = -1; Points[6].z = 1;
	Points[7].x = -1; Points[7].y = -1; Points[7].z = -1;
	Points[8].x = 0; Points[8].y = 0; Points[8].z = 0;

	

	for (int i = 0; i < 9; i++)
	{
		Vec3<Real> tempVertex(Points[i].x, Points[i].y, Points[i].z);

		CHull->AddPoint(tempVertex);
	}

	//Process
	CHull->Process();

	//Get mesh
	TMMesh *computedMesh = &CHull->GetMesh();

	CircularList<TMMVertex>* vertexList = &computedMesh->GetVertices();
	CircularListElement<TMMVertex>* vert = vertexList->GetHead();

	CircularList<TMMTriangle>* triList = &computedMesh->GetTriangles();
	
	int VertexSize = vertexList->GetSize();
	
	for (int i = 0; i < VertexSize; i++)
	{
		 TMMVertex *v = (&vert->GetData());
		 Vec3<Real> Vertex(v->GetVertex());
		 vertList.push_back(Vertex);
		 vert = vert->GetNext();	 
	}

	vector<Vec3<Real> >::iterator itr;
	int i = 0;
	for (itr = vertList.begin(); itr != vertList.end(); ++itr)
	{
		point P(itr->X(),itr->Y(),itr->Z());
		hashTable.insert(make_pair(P,i));
		i++;
		cout << "X = " <<itr->X() << " Y = " <<itr->Y() << " Z = " <<itr->Z() << endl;
	}

	cout << "hash table entries : " << endl;
	unordered_map<point, size_t>::iterator hashItr = hashTable.begin();
	while (hashItr!=hashTable.end())
	{
		point P(hashItr->first);
		cout << "point "<<hashItr->second<< " corresponds to : ("<<P.x << " ," << P.y << " ," << P.z << ")" << endl;
		++hashItr;
	}

	point k(1,1,1);
	hashItr = hashTable.find(k);
	cout << "k found at " << hashItr->second << " position";
	int n;
	cin >> n;
	return 0;
}

